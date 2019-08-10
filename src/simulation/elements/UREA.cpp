#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_UREA PT_UREA 210
Element_UREA::Element_UREA()
{
	Identifier = "DEFAULT_PT_UREA";
	Name = "UREA";
	FullName = "Urea";
	Colour = PIXPACK(0xE2ED66);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.0f;
	HotAir = 0.0f	* CFDS;
	Falldown = 2;

	Flammable = 25;
	Explosive = 0;
	Meltable = 0;
	Hardness = 5;

	Weight = 40;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 42;
	Description = "Urea. An ingredient of liquid waste and some explosives.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_UREA::update;
}

Element_UREA::~Element_UREA() {}

//#TPT-Directive ElementHeader Element_UREA static int update(UPDATE_FUNC_ARGS)
int Element_UREA::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r || TYP(r) == PT_UREA)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;

				if (TYP(r) == PT_HNO3) {
					sim->part_change_type(i, x, y, PT_UNTR);
					sim->kill_part(ID(r));
				}
			}
	return 0;
}