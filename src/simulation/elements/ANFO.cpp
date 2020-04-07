#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_ANFO()
{
	Identifier = "DEFAULT_PT_ANFO";
	Name = "ANFO";
	FullName = "Ammonium Nitrate Fuel Oil";
	Colour = PIXPACK(0xafafaf);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
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

	Flammable = 500;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 50;

	HeatConduct = 251;
	Description = "Ammonium Nitrate Fuel Oil (ANFO) explosive.";

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
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 300.0f) {
		sim->pv[y / CELL][x / CELL] += 35.0f;
		sim->create_part(-1, x + rand() % 3 - 1, y + rand() % 3 - 1, rand() % 10 < 3 ? PT_FIRE : PT_SMKE);
	}
	return 0;
}

