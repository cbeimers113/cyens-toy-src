#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_WSTE()
{
	Identifier = "DEFAULT_PT_WSTE";
	Name = "WSTE";
	FullName = "Chemical Waste";
	Colour = PIXPACK(0xdfff5e);
	MenuVisible = 1;
	MenuSection = SC_CRACKER;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 35;

	HeatConduct = 29;
	Description = "Chemical waste.";

	Properties = TYPE_PART;

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

static int update(UPDATE_FUNC_ARGS) {
	//Solves weird bug where WSTE was getting created as a nonexisting subtype and still survived 
	if (parts[i].tmp2 < WSTE_SDM_ACETATE || parts[i].tmp2 > WSTE_TRSDM_PHOSPHATE)
		sim->kill_part(i);
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	switch (cpart->tmp2) {
	case WSTE_SDM_ACETATE:
		*colr = 0xf7;
		*colg = 0xff;
		*colb = 0xd9;
		break;
	case WSTE_TRSDM_PHOSPHATE:
		*colr = 0xff;
		*colg = 0xd9;
		*colb = 0xd9;
		break;
	default:
		*colr = 0xdf;
		*colg = 0xff;
		*colb = 0x5e;
		break;
	}

	*pixel_mode |= PMODE_BLUR;
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	sim->parts[i].tmp2 = -1;
}
