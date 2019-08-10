#include "simulation/Elements.h"
#include "../CyensTools.h"

//#TPT-Directive ElementClass Element_CRBN PT_CRBN 189
Element_CRBN::Element_CRBN()
{
	Identifier = "DEFAULT_PT_CRBN";
	Name = "CRBN";
	FullName = "Carbon";
	Colour = PIXPACK(0x6e6e6e);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 85;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 70;
	Description = "Carbon, essential to organic compounds and life.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_CRBN::update;
}

Element_CRBN::~Element_CRBN() {}

//#TPT-Directive ElementHeader Element_CRBN static int update(UPDATE_FUNC_ARGS)
int Element_CRBN::update(UPDATE_FUNC_ARGS)
{
	bool harden = sim->pv[y / CELL][x / CELL] >= 200.0f;

	int GRPH180[]{
		-1, -1, -1,
		PT_CRBN, PT_CRBN, PT_CRBN,
		-1, -1, -1
	};

	int GRPH45[] = {
		-1, -1, PT_CRBN,
		-1, PT_CRBN, -1,
		PT_CRBN, -1, -1
	};

	int GRPH90[] = {
		-1, PT_CRBN, -1,
		-1, PT_CRBN, -1,
		-1, PT_CRBN, -1
	};

	int GRPH135[] = {
		PT_CRBN, -1, -1,
		-1, PT_CRBN, -1,
		-1, -1, PT_CRBN
	};

	int recipe[9];

	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;

				if (TYP(r) == PT_H2) {
					sim->part_change_type(i, x, y, PT_GAS);
					sim->kill_part(ID(r));
				}

				if (TYP(r) == PT_O2) {
					sim->part_change_type(i, x, y, PT_CO2);
					sim->kill_part(ID(r));
				}

				if (TYP(r) == PT_GAS && !isAlkyne(parts[i].life, parts[i].tmp) && parts[i].temp > 273.15f + 10.0f * parts[i].life) {
					parts[ID(r)].life++;
					parts[ID(r)].tmp++;
					sim->kill_part(i);
				}

				recipe[(rx + 1) + (ry + 1) * 3] = TYP(r);
			}

	if (harden) {
		if (Element_CRBN::compareRecipes(recipe, GRPH180, PT_CRBN, PT_INST)) {
			sim->part_change_type(ID(pmap[y][x - 1]), x - 1, y, PT_INST);
			sim->part_change_type(ID(pmap[y][x + 1]), x + 1, y, PT_INST);
			sim->part_change_type(i, x, y, PT_INST);
		}
		else if (Element_CRBN::compareRecipes(recipe, GRPH45, PT_CRBN, PT_INST)) {
			sim->part_change_type(ID(pmap[y - 1][x - 1]), x - 1, y - 1, PT_INST);
			sim->part_change_type(ID(pmap[y + 1][x + 1]), x + 1, y + 1, PT_INST);
			sim->part_change_type(i, x, y, PT_INST);
		}
		else if (Element_CRBN::compareRecipes(recipe, GRPH90, PT_CRBN, PT_INST)) {
			sim->part_change_type(ID(pmap[y - 1][x]), x, y - 1, PT_INST);
			sim->part_change_type(ID(pmap[y + 1][x]), x, y + 1, PT_INST);
			sim->part_change_type(i, x, y, PT_INST);
		}
		else if (Element_CRBN::compareRecipes(recipe, GRPH135, PT_CRBN, PT_INST)) {
			sim->part_change_type(ID(pmap[y + 1][x - 1]), x - 1, y + 1, PT_INST);
			sim->part_change_type(ID(pmap[y - 1][x + 1]), x + 1, y - 1, PT_INST);
			sim->part_change_type(i, x, y, PT_INST);
		}
		else {
			if (sim->pv[y / CELL][x / CELL] < 235.0f || rand() % 100>5)return 0;
			sim->part_change_type(i, x, y, PT_COAL);
			parts[i].life = 110;
			parts[i].tmp = -1;

		}
	}

	return 0;
}

//tMatch is the centre element
//#TPT-Directive ElementHeader Element_CRBN static bool compareRecipes(int rFound[9], int rSource[9], int tMatch, int tProd)
bool Element_CRBN::compareRecipes(int rFound[9], int rSource[9], int tMatch, int tProd) {
	if (rSource[4] != tMatch)return false;
	for (int i = 0; i < 9; i++) {
		if ((rSource[i] == -1) != ((rFound[i] == tMatch || rFound[i] == tProd)))
			continue;
		else if (rFound[i] != rSource[i]) return false;
	}
	return true;
}
