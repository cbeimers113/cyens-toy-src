#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_DESL PT_DESL 58
Element_DESL::Element_DESL()
{
	Identifier = "DEFAULT_PT_DESL";
	Name = "DESL";
	FullName = "Diesel Fuel";
	Colour = PIXPACK(0x440000);
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

	Flammable = 50;
	Explosive = 0;
	Meltable = 0;
	Hardness = 5;

	Weight = 15;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 42;
	Description = "Liquid diesel.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_DESL::update;
}

//#TPT-Directive ElementHeader Element_DESL static int update(UPDATE_FUNC_ARGS)
int Element_DESL::update(UPDATE_FUNC_ARGS) {
	//DESL is a medium carbon liquid, it should not have any more than 19 carbons or any less than 8.
	if (parts[i].life < 8)sim->part_change_type(i, x, y, PT_MWAX);
	else if (parts[i].life > 19)sim->part_change_type(i, x, y, PT_OIL);

	int t = parts[i].temp - sim->pv[y / CELL][x / CELL];	//Pressure affects state transitions
	//Freezing into WAX
	if (t <= (14.3f  * sqrt((parts[i].life - 12))) + 273.15)
		sim->part_change_type(i, x, y, PT_WAX);
	//Boiling into GAS
	if (t > (4 * sqrt(500 * (parts[i].life - 4))) + 273.15)
		sim->part_change_type(i, x, y, PT_GAS);

	return 0;
}

Element_DESL::~Element_DESL() {}
