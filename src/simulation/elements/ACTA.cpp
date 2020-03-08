#include "simulation/ElementCommon.h"

int Element_ACID_update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_ACTA()
{
	Identifier = "DEFAULT_PT_ACTA";
	Name = "ACTA";
	FullName = "Acetic Acid";
	Colour = PIXPACK(0xE9F0D3);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 20;

	HeatConduct = 25;
	Description = "Acetic acid, mix with water to make vinegar.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_ACID_update;
	Create = &create;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	sim->parts[i].life = 75;
	sim->parts[i].tmp2 = 500;
}