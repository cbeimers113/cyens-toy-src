#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_WBSN()
{
	Identifier = "DEFAULT_PT_WBSN";
	Name = "WBSN";
	FullName = "W";
	Colour = PIXPACK(0x333300);
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
	Description = "W bosons. Positive and negative carriers of the weak force.";

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
	// update code here

	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	*cola = *colr = *colg = *colb = 0;
	*firea = 0x12;
	*firer = 0x33;
	*fireg = 0x33;
	*fireb = 0x33;

	*pixel_mode |= FIRE_BLEND;
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	float a = RNG::Ref().between(0, 35) * 0.17453f;
	sim->parts[i].life = RNG::Ref().between(1, 5);
	sim->parts[i].tmp = RNG::Ref().between(0, 1);
	sim->parts[i].vx = 10.0f * cosf(a);
	sim->parts[i].vy = 10.0f * sinf(a);
}