#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_CO PT_CO 197
Element_CO::Element_CO()
{
	Identifier = "DEFAULT_PT_CO";
	Name = "CO";
	FullName = "Carbon Monoxide";
	Colour = PIXPACK(0x999999);
	MenuVisible = 1;
	MenuSection = SC_GAS;
	Enabled = 1;

	Advection = 0.8f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.4f;
	Loss = 0.70f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 0.99f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 1;

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 88;
	Description = "Carbon Monoxide. Produced from burning coal.";

	Properties = TYPE_GAS | PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_CO::update;
}

//#TPT-Directive ElementHeader Element_CO static int update(UPDATE_FUNC_ARGS)
int Element_CO::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r)continue;

			}

	if (parts[i].temp > 1000.0f) {
		sim->part_change_type(i, x, y, rand() % 2 ? PT_CBNL : PT_ELEC);
	}
	return 0;
}


Element_CO::~Element_CO() {}
