#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_CLCO PT_CLCO 212
Element_CLCO::Element_CLCO()
{
	Identifier = "DEFAULT_PT_CLCO";
	Name = "CLCO";
	FullName = "Chlorocarbon";
	Colour = PIXPACK(0x424851);
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
	Description = "Chlorocarbon compound.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_CLCO::update;
}

Element_CLCO::~Element_CLCO() {}

//#TPT-Directive ElementHeader Element_CLCO static int update(UPDATE_FUNC_ARGS)
int Element_CLCO::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_CLCO)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;

				if (TYP(r) == PT_SDHX) {
					sim->part_change_type(i, x, y, PT_CCL2);
					sim->part_change_type(ID(r), x + rx, y + ry, PT_GAS);
				}
			}
	return 0;
}