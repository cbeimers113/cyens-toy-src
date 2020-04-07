#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_CO()
{
	Identifier = "DEFAULT_PT_CO";
	Name = "CO";
	FullName = "Carbon Monoxide";
	Colour = PIXPACK(0x999999);
	MenuVisible = 1;
	MenuSection = SC_GAS;
	Enabled = 1;

	Advection = 0.8f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.4f;
	Loss = 0.70f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 0.99f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 1;

	HeatConduct = 88;
	Description = "Carbon Monoxide. Produced from burning coal.";

	Properties = TYPE_GAS | PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 1000.0f)
		sim->part_change_type(i, x, y, rand() % 2 ? PT_CBNL : PT_ELEC);

	return 0;
}

