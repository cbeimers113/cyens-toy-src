#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_N2 PT_N2 188
Element_N2::Element_N2()
{
	Identifier = "DEFAULT_PT_N2";
	Name = "N2";
	FullName = "Nitrogen";
	Colour = PIXPACK(0x90C3D4);
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
	Description = "Nitrogen gas, used to synthesize amines, amides, explosives and fertilizer.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 76.9f;
	LowTemperatureTransition = PT_LNTG;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_N2::update;
}

Element_N2::~Element_N2() {}

//#TPT-Directive ElementHeader Element_N2 static int update(UPDATE_FUNC_ARGS)
int Element_N2::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_N2)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;

				if (TYP(r) == PT_PLNT) {
					sim->part_change_type(ID(r), x + rx, y + ry, PT_VINE);
					sim->kill_part(i);
				}

				if (TYP(r) == PT_H2) {
					sim->part_change_type(i, x, y, PT_NH3);
					sim->kill_part(ID(r));
				}

				if (TYP(r) == PT_CRBN) {
					sim->part_change_type(i, x, y, PT_CYAN);
					sim->kill_part(ID(r));
				}

				if (TYP(r) == PT_AMID) {
					sim->part_change_type(i, x, y, PT_UREA);
					sim->kill_part(ID(r));
				}
			}
	return 0;
}