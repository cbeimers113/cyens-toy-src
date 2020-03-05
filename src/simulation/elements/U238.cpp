#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_U238 PT_U238 229
Element_U238::Element_U238()
{
	Identifier = "DEFAULT_PT_U238";
	Name = "U238";
	FullName = "Uranium 238";
	Colour = PIXPACK(0x709020);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.4f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 0;
	PhotonReflectWavelengths = 0x003FC000;

	Weight = 95;

	Temperature = R_TEMP + 30.0f + 273.15f;
	HeatConduct = 251;
	Description = "Uranium 238. The most common uranium isotope.";

	Properties = TYPE_PART | PROP_RADIOACTIVE | PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1405.15f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_U238::update;
}

//#TPT-Directive ElementHeader Element_U238 static int update(UPDATE_FUNC_ARGS)
int Element_U238::update(UPDATE_FUNC_ARGS) {

	for (int rx = -1; rx < 1; rx++)
		for (int ry = -1; ry < 1; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_NEUT && rand() % 50 == 1) // fission 2% of chance
				{
							sim->part_change_type(i, x, y, PT_U239);
				}
				else if (TYP(r) == PT_NEUT)
				{
					sim->kill_part(ID(r));
				}
			}
	return 0;
}


Element_U238::~Element_U238() {}
