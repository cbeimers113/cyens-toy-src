#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_GAMA PT_GAMA 236
Element_GAMA::Element_GAMA()
{
	Identifier = "DEFAULT_PT_GAMA";
	Name = "GAMA";
	Colour = PIXPACK(0xFFFFFF);
	MenuVisible = 1;
	MenuSection = SC_QUANTUM;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = -.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = -1;

	Temperature = R_TEMP + 2000.15f;		
	HeatConduct = 20;
	Description = "Gamma rays are very high energy and penetrating power photons usually emmited by radiation sources";

	Properties = TYPE_ENERGY | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	// element properties here

	Update = &Element_GAMA::update;
	Graphics = &Element_GAMA::graphics;
}

//#TPT-Directive ElementHeader Element_GAMA static int update(UPDATE_FUNC_ARGS)
int Element_GAMA::update(UPDATE_FUNC_ARGS)
{
	// update code here

	return 0;
}

//#TPT-Directive ElementHeader Element_GAMA static int graphics(GRAPHICS_FUNC_ARGS)
int Element_GAMA::graphics(GRAPHICS_FUNC_ARGS)
{
	// graphics code here
	// return 1 if nothing dymanic happens here

	return 0;
}

Element_GAMA::~Element_GAMA() {}
