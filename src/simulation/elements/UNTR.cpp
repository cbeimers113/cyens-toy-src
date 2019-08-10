#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_UNTR PT_UNTR 211
Element_UNTR::Element_UNTR()
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
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 10;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 21;

	Temperature = R_TEMP + 273.15f;
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

	Update = &Element_UNTR::update;
}

Element_UNTR::~Element_UNTR() {}

//#TPT-Directive ElementHeader Element_UNTR static int update(UPDATE_FUNC_ARGS)
int Element_UNTR::update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp < 436.15f)return 0;
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (TYP(r) != PT_NONE)continue;
				sim->part_change_type(ID(r), x + rx, y + ry, rand() % 10 < 7 ? PT_NITR : PT_BANG);
				sim->pv[y / CELL][x / CELL] += 15.0f;
			}
	sim->part_change_type(i, x, y, PT_FIRE);
	parts[i].dcolour = 0x00ff00;
	return 0;
}