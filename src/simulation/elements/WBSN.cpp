#include "simulation/ElementCommon.h"
#include "simulation/CyensTools.h"

//#TPT-Directive ElementClass Element_WBSN PT_WBSN 227
Element_WBSN::Element_WBSN()
{
	Identifier = "DEFAULT_PT_WBSN";
	Name = "WBSN";
	FullName = "W";
	Colour = PIXPACK(0x333300);
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

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 20;
	Description = "W bosons. Positive and negative carriers of the weak force.";

	Properties = TYPE_ENERGY | PROP_LIFE_DEC | PROP_LIFE_KILL_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_WBSN::update;
	Graphics = &Element_WBSN::graphics;
}

//#TPT-Directive ElementHeader Element_WBSN static int update(UPDATE_FUNC_ARGS)
int Element_WBSN::update(UPDATE_FUNC_ARGS)
{
	
	return 0;
}

//#TPT-Directive ElementHeader Element_WBSN static int graphics(GRAPHICS_FUNC_ARGS)
int Element_WBSN::graphics(GRAPHICS_FUNC_ARGS) {

	*cola = *colr = *colg = *colb = 0;
	*firea = 0x12;
	*firer = 0x33;
	*fireg = 0x33;
	*fireb = 0x33;

	*pixel_mode |= FIRE_BLEND;
	return 0;
}

Element_WBSN::~Element_WBSN() {}
