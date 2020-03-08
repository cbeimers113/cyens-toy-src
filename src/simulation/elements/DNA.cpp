#include "simulation/ElementCommon.h"

int Element_RNA_update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_DNA()
{
	Identifier = "DEFAULT_PT_DNA";
	Name = "DNA";
	FullName = "DNA";
	Colour = PIXPACK(0xD4FFFF);
	MenuVisible = 0;
	MenuSection = SC_BIOLOGY;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.0f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 0;

	HeatConduct = 70;
	Description = "Deoxyribonucleic acid, the biological code of life.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_RNA_update;
	Create = &create;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	sim->parts[i].sHeadIndex = -1;
}