#include "simulation/Elements.h"
#include <stack>

//#TPT-Directive ElementClass Element_PHPT PT_PHPT 219
Element_PHPT::Element_PHPT() {
	Identifier = "DEFAULT_PT_PHPT";
	Name = "PO4";
	FullName = "Phosphate Ion";
	Colour = PIXPACK(0xd9d0d0);
	MenuVisible = 1;
	MenuSection = SC_GAS;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 1.50f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 1;

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 20;
	Description = "Phosphate ion. Can form phosphoric acid and is involved in nucleotide synthesis.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_PHPT::update;
}

//#TPT-Directive ElementHeader Element_PHPT static int update(UPDATE_FUNC_ARGS)
int Element_PHPT::update(UPDATE_FUNC_ARGS) {
	int rx, ry;
	int r;
	int h = 0;
	std::stack<int>hydrogens;
	for (ry = -1; ry < 2; ry++)
		for (rx = -1; rx < 2; rx++)
			if (BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r)continue;
				if (TYP(r) == PT_H2 && h < 3) {
					h++;
					hydrogens.push(ID(r));
				}
			}
	if (h == 3) {
		sim->part_change_type(i, x, y, PT_PHAC);
		while (!hydrogens.empty()) {
			sim->kill_part(hydrogens.top());
			hydrogens.pop();
		}
	}
	return 0;
}

Element_PHPT::~Element_PHPT() {}
