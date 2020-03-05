#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_U239 PT_U239 239
Element_U239::Element_U239()
{
	Identifier = "DEFAULT_PT_U239";
	Name = "U239";
	FullName = "Uranium 239";
	Colour = PIXPACK(0x407520);
	MenuVisible = 0;
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
	Meltable = 0;
	Hardness = 0;
	PhotonReflectWavelengths = 0x001FCE00;

	Weight = 105;

	Temperature = R_TEMP + 4.0f + 273.15f;
	HeatConduct = 251;
	Description = "";

	Properties = TYPE_PART | PROP_NEUTPASS | PROP_RADIOACTIVE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 913.15;
	HighTemperatureTransition = PT_LAVA;

	// element properties here

	Update = &Element_U239::update;
}

//#TPT-Directive ElementHeader Element_U239 static int update(UPDATE_FUNC_ARGS)
int Element_U239::update(UPDATE_FUNC_ARGS)
{
	int timer;
	if (timer >= 10000)
	{
		sim->part_change_type(i, x, y, PT_PLUT);
	}
	timer++;
	return 0;
}

Element_U239::~Element_U239() {}
