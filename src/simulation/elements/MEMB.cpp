#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_MEMB PT_MEMB 234
Element_MEMB::Element_MEMB()
{
	Identifier = "DEFAULT_PT_MEMB";
	Name = "MEMB";
	FullName = "Semipermeable membrane";
	Colour = PIXPACK(0x707070);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 50;

	Weight = 150;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Semipermeable membrane. Used for the enrichment of uranium";

	Properties = TYPE_SOLID | PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1983.15f;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_MEMB::update;
}

//#TPT-Directive ElementHeader Element_MEMB static int update(UPDATE_FUNC_ARGS)
int Element_MEMB::update(UPDATE_FUNC_ARGS)
{
	// update code here
	for (int rx = -2; rx <= 2; rx++)
		for (int ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_UF6)
				{
					if (parts[ID(r)].tmp == 235)
					{
						parts[i].tmp2 = 1;
					//	Simulation::init_can_move(i, parts)
					}
					else
					{
						parts[i].tmp2 = 0;
					}
					
				}
				else
				{
					parts[i].tmp2 = 0;
				}

			}


	return 0;
}

Element_MEMB::~Element_MEMB() {}
