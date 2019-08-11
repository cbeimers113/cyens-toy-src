#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_AMIN PT_AMIN 207
Element_AMIN::Element_AMIN()
{
	Identifier = "DEFAULT_PT_AMIN";
	Name = "AMIN";
	FullName = "Amine Compound";
	Colour = PIXPACK(0xCACCCA);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.10f;
	Gravity = 0.00f;
	Diffusion = 3.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 1;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Amine compound.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_AMIN::update;
}

Element_AMIN::~Element_AMIN() {}

//#TPT-Directive ElementHeader Element_AMIN static int update(UPDATE_FUNC_ARGS)
int Element_AMIN::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_AMIN)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_CBNL) {
					sim->part_change_type(i, x, y, PT_AMID);
					sim->kill_part(ID(r));
				}
			}
	return 0;
}