#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_U235 PT_U235 230
Element_U235::Element_U235()
{
	Identifier = "DEFAULT_PT_U235";
	Name = "U235";
	FullName = "Uranium 235";
	Colour = PIXPACK(0x307020);
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

	Weight = 90;

	Temperature = R_TEMP + 30.0f + 273.15f;
	HeatConduct = 251;
	Description = "Uranium 235. A rare uranium isotope.";

	Properties = TYPE_PART | PROP_RADIOACTIVE | PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1405.15f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_U235::update;
}

//#TPT-Directive ElementHeader Element_U235 static int update(UPDATE_FUNC_ARGS)
int Element_U235::update(UPDATE_FUNC_ARGS)
{
	for (int rx = -1; rx < 1; rx++)
		for (int ry = -1; ry < 1; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_NEUT && rand() % 10 == 1) // fission 10% of chance
				{
					for (int ne = 0; ne <= 4; ne++) {
						sim->create_part(ne, x, y, PT_NEUT);
					}
					parts[ID(pmap[y][x])].temp += 400.0f;
					if (rand() % 30 == 1)
					{
						sim->part_change_type(i, x, y, PT_NWST);
					}
				}
			}
	return 0;
}
Element_U235::~Element_U235() {}
