#include "simulation/ElementCommon.h"
#include "simulation/CyensTools.h"

//#TPT-Directive ElementClass Element_PHAC PT_PHAC 221
Element_PHAC::Element_PHAC() {
	Identifier = "DEFAULT_PT_PHAC";
	Name = "PHAC";
	FullName = "Phosphoric Acid";
	Colour = PIXPACK(0xD39aED);
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
	Hardness = 0;

	Weight = 10;

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 34;
	Description = "Phosphoric acid. A weak acid.";

	Properties = TYPE_LIQUID | PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_ACID::update;
}

Element_PHAC::~Element_PHAC() {}
