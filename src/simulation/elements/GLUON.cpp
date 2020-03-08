#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_GLUON()
{
	Identifier = "DEFAULT_PT_GLUON";
	Name = "g-ON";
	FullName = "Gluon";
	Colour = PIXPACK(0x234669);
	MenuVisible = 1;
	MenuSection = SC_QUANTUM;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = -.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = -1;

	HeatConduct = 20;
	Description = "Gluons. The carrier of the strong force.";

	Properties = TYPE_ENERGY | PROP_LIFE_DEC | PROP_LIFE_KILL_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
	Graphics = &graphics;
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
	int xx = RNG::Ref().between(-1, 1);
	int yy = RNG::Ref().between(-1, 1);
	sim->strongForce[y][x] = v2f{ parts[i].vx * xx,parts[i].vy * yy };
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	*cola = *colr = *colg = *colb = 0;
	*firea = 0x12;
	*firer = 0x23;
	*fireg = 0x46;
	*fireb = 0x69;

	*pixel_mode |= FIRE_BLEND;
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	float a = RNG::Ref().between(0, 35) * 0.17453f;
	sim->parts[i].life = RNG::Ref().between(5, 10);
	sim->parts[i].tmp = RNG::Ref().between(0, 3);
	sim->parts[i].vx = 10.0f * cosf(a);
	sim->parts[i].vy = 10.0f * sinf(a);
}