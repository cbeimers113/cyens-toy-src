#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_WAX PT_WAX 33
Element_WAX::Element_WAX()
{
	Identifier = "DEFAULT_PT_WAX";
	Name = "WAX";
	FullName = "Hydrocarbon Wax";
	Colour = PIXPACK(0xF0F0BB);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 25;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 44;
	Description = "Hydrocarbon wax. Melts into DESL or MWAX.";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_WAX::update;
}

//#TPT-Directive ElementHeader Element_WAX static int update(UPDATE_FUNC_ARGS)
int Element_WAX::update(UPDATE_FUNC_ARGS) {
	//WAX is a low to medium carbon solid, it should not have any more than 19 carbons.
	if (parts[i].life > 19)sim->part_change_type(i, x, y, PT_PRFN);

	int t = parts[i].temp - sim->pv[y / CELL][x / CELL];	//Pressure affects state transitions
	//Melting
	if ((parts[i].life < 5 && t >= (-200 + 273.15)) || (parts[i].life >= 5 && parts[i].life < 12 && t >= (16.5f*parts[i].life - 200 + 273.15)) || (parts[i].life >= 12 && t > (14.3f*sqrt(parts[i].life - 12)) + 273.15))
	{
		if (parts[i].life < 8)//Low carbon melting
			sim->part_change_type(i, x, y, PT_MWAX);
		else //Medium carbon melting
			sim->part_change_type(i, x, y, PT_DESL);
	}

	return 0;
}

Element_WAX::~Element_WAX() {}
