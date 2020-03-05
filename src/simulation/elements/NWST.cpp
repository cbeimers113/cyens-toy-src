#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_NWST PT_NWST 235
Element_NWST::Element_NWST()
{
	Identifier = "DEFAULT_PT_NWST";
	Name = "NWST";
	Colour = PIXPACK(0x4c5d10);
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
	PhotonReflectWavelengths = 0x4c5d10;

	Weight = 80;

	Temperature = R_TEMP + 30.0f + 273.15f;
	HeatConduct = 251;
	Description = "Nuclear waste. Subproducts of nuclear fission.";


	Properties = TYPE_PART | PROP_NEUTPASS | PROP_RADIOACTIVE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1185.15;
	HighTemperatureTransition = PT_LAVA;

	Update = &Element_NWST::update;
	Graphics = &Element_NWST::graphics;
}

//#TPT-Directive ElementHeader Element_NWST static int update(UPDATE_FUNC_ARGS)
int Element_NWST::update(UPDATE_FUNC_ARGS)
{
	// update code here

	return 0;
}

//#TPT-Directive ElementHeader Element_NWST static int graphics(GRAPHICS_FUNC_ARGS)
int Element_NWST::graphics(GRAPHICS_FUNC_ARGS)
{
	// graphics code here
	// return 1 if nothing dymanic happens here

	return 0;
}

Element_NWST::~Element_NWST() {}
