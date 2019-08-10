#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_VNGR PT_VNGR 195
Element_VNGR::Element_VNGR()
{
	Identifier = "DEFAULT_PT_VNGR";
	Name = "VNGR";
	FullName = "Vinegar";
	Colour = PIXPACK(0xF0F0F0);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 40;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Vinegar. Will be useful for electrochemistry.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_VNGR::update;
}

Element_VNGR::~Element_VNGR() {}

//#TPT-Directive ElementHeader Element_VNGR static int update(UPDATE_FUNC_ARGS)
int Element_VNGR::update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 100.0f + 273.15f) {
		sim->create_part(-1, x + rand() % 3 - 1, y + rand() % 3 - 1, PT_WTRV);
		sim->part_change_type(i, x, y, PT_ACTA);
	}
	return 0;
}