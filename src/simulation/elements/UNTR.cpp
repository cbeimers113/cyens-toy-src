#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_UNTR()
{
	Identifier = "DEFAULT_PT_UNTR";
	Name = "UNTR";
	FullName = "Urea Nitrate";
	Colour = PIXPACK(0x91EDAE);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 10;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 21;

	HeatConduct = 70;
	Description = "Urea nitrate explosive.";

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
	if (parts[i].temp < 436.15f) return 0;

	sim->part_change_type(i, x, y, parts[i].temp >= 673.15f ? PT_NITR : PT_SMKE);
	sim->pv[y / CELL][x / CELL] += 5.0f;

	return 0;
}
