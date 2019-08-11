#include "simulation/ElementCommon.h"
#include "simulation/CyensTools.h"

//#TPT-Directive ElementClass Element_SUGR PT_SUGR 220
Element_SUGR::Element_SUGR()
{
	Identifier = "DEFAULT_PT_SUGR";
	Name = "SUGR";
	FullName = "Sugar";
	Colour = PIXPACK(0xfcf9f0);
	MenuVisible = 1;
	MenuSection = SC_BIOLOGY;
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
	HeatConduct = 20;
	Description = "Monosaccharide sugar.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_SUGR::update;
}

//#TPT-Directive ElementHeader Element_SUGR static int update(UPDATE_FUNC_ARGS)
int Element_SUGR::update(UPDATE_FUNC_ARGS) {
	if (parts[i].tmp == SUGR_GLUCOSE)return 0;
	int r, rx, ry;
	bool phosphate = false;
	int pi = -1;
	for (ry = -1; ry < 2; ry++)
		for (rx = -1; rx < 2; rx++)
			if (BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r || phosphate)continue;
				if (TYP(r) == PT_PHPT) {
					phosphate = true;
					pi = ID(r);
				}
			}
	if (phosphate)
		for (ry = -1; ry < 2; ry++)
			for (rx = -1; rx < 2; rx++)
				if (BOUNDS_CHECK) {
					r = pmap[y + ry][x + rx];
					if (!r)continue;
					if (TYP(r) == PT_NCTD) {
						if (parts[i].tmp == SUGR_RIBOSE && (parts[ID(r)].tmp == NCTD_BONDED_AU || parts[ID(r)].tmp == NCTD_BONDED_GC)) {
							sim->part_change_type(i, x, y, PT_RNA);
							sim->kill_part(ID(r));
							sim->kill_part(pi);
						}
						else if (parts[i].tmp == SUGR_DEOXYRIBOSE && (parts[ID(r)].tmp == NCTD_BONDED_TA || parts[ID(r)].tmp == NCTD_BONDED_GC)) {
							sim->part_change_type(i, x, y, PT_DNA);
							sim->kill_part(ID(r));
							sim->kill_part(pi);
						}
					}
				}
	return 0;
}

Element_SUGR::~Element_SUGR() {}
