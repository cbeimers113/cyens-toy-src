#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_CCL2 PT_CCL2 213
Element_CCL2::Element_CCL2()
{
	Identifier = "DEFAULT_PT_CCL2";
	Name = "CCL2";
	FullName = "Dichlorocarbene";
	Colour = PIXPACK(0x37455b);
	MenuVisible = 1;
	MenuSection = SC_GAS;
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
	Description = "Dichlorocarbene.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_CCL2::update;
}

Element_CCL2::~Element_CCL2() {}

//#TPT-Directive ElementHeader Element_CCL2 static int update(UPDATE_FUNC_ARGS)
int Element_CCL2::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_CCL2)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;

				if (TYP(r) == PT_AMIN) {
					sim->part_change_type(i, x, y, PT_ISCY);
					sim->kill_part(ID(r));
				}
			}
	return 0;
}