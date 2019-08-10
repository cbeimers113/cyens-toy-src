#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_PRFN PT_PRFN 186
Element_PRFN::Element_PRFN()
{
	Identifier = "DEFAULT_PT_PRFN";
	Name = "PRFN";
	FullName = "Solid High Carbon Wax";
	Colour = PIXPACK(0xA0A066);
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

	Flammable = 75;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 100;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 44;
	Description = "Paraffin wax. Melts into OIL.";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_PRFN::update;
}

//#TPT-Directive ElementHeader Element_PRFN static int update(UPDATE_FUNC_ARGS)
int Element_PRFN::update(UPDATE_FUNC_ARGS) {
	//PRFN is a high carbon solid, it should not have any less than 20 carbons.
	if (parts[i].life < 20)sim->part_change_type(i, x, y, PT_WAX);

	int t = parts[i].temp - sim->pv[y / CELL][x / CELL];	//Pressure affects state transitions
	//Melting
	if (t > (14.3f*sqrt(parts[i].life - 12)) + 273.15)
	sim->part_change_type(i, x, y, PT_OIL);

	return 0;
}

Element_PRFN::~Element_PRFN() {}
