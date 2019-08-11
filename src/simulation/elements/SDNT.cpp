#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_SDNT PT_SDNT 223
Element_SDNT::Element_SDNT() {
	Identifier = "DEFAULT_PT_SDNT";
	Name = "SDNT";
	FullName = "Sodium Nitrate";
	Colour = PIXPACK(0x9b8ba3);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 25;

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 30;
	Description = "Sodium nitrate, a fertilizer.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 813.15f;
	HighTemperatureTransition = PT_SMKE;

	Update = &Element_SDNT::update;
}

//#TPT-Directive ElementHeader Element_SDNT static int update(UPDATE_FUNC_ARGS)
int Element_SDNT::update(UPDATE_FUNC_ARGS) {
	int r, rx, ry;
	for (ry = -1; ry < 2; ry++)
		for (rx = -1; rx < 2; rx++)
			if (BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_SDNT)
					continue;
				if (TYP(r) == PT_PLNT) {
					sim->part_change_type(ID(r), x + rx, y + ry, PT_VINE);
					sim->kill_part(i);
				}
			}
	return 0;
}

Element_SDNT::~Element_SDNT() {}
