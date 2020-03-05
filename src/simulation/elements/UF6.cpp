#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_UF6 PT_UF6 231
Element_UF6::Element_UF6()
{
	Identifier = "DEFAULT_PT_UF6";
	Name = "UF6";
	FullName = "Uranium hexafluoride";
	Colour = PIXPACK(0xDCDCDC);
	MenuVisible = 0;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.4f;
	AirDrag = 0.04f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = -0.1f;
	Gravity = 0.18f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 2;
	Hardness = 2;

	Weight = 70;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 211;
	Description = "Uranium hexafluoride. Molecule used in the process of enriching uranium.";

	Properties = TYPE_PART | PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 330.15;
	HighTemperatureTransition = NT;

	Update = &Element_UF6::update;

}

//#TPT-Directive ElementHeader Element_UF6 static int update(UPDATE_FUNC_ARGS)
int Element_UF6::update(UPDATE_FUNC_ARGS)
{
	// update code here

	return 0;
}


Element_UF6::~Element_UF6() {}
