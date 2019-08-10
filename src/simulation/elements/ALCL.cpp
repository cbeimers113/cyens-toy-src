#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_ALCL PT_ALCL 192
Element_ALCL::Element_ALCL()
{
	Identifier = "DEFAULT_PT_ALCL";
	Name = "ALCL";
	FullName = "Alcohol";
	Colour = PIXPACK(0xD4CBCB);
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
	Description = "Organic alcohol.";

	Properties = TYPE_LIQUID | PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_ALCL::update;
}

//#TPT-Directive ElementHeader Element_ALCL static int update(UPDATE_FUNC_ARGS)
int Element_ALCL::update(UPDATE_FUNC_ARGS) {
	//ALCL is an organic liquid, it should not have any more than 60 carbons. (Should move all these to CyensToys.cpp)
	if (parts[i].life > 60)parts[i].life = 60;

	int w = 0;
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (!r)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				if (TYP(r) == PT_WATR || TYP(r) == PT_DSTW)
					if (++w > 2) {
						parts[i].ctype = 0;
						sim->part_change_type(i, x, y, PT_RBAC);
						sim->kill_part(ID(r));
					}
			}
	return 0;
}

Element_ALCL::~Element_ALCL() {}
