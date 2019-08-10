#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_SDHX PT_SDHX 204
Element_SDHX::Element_SDHX()
{
	Identifier = "DEFAULT_PT_SDHX";
	Name = "SDHX";
	FullName = "Sodium Hydroxide";
	Colour = PIXPACK(0xefefef);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 100;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 35;

	Temperature = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Sodium hydroxide. Neutralizes acids.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = NULL;
}

Element_SDHX::~Element_SDHX() {}
