#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);

void Element::Element_RBAC()
{
	Identifier = "DEFAULT_PT_RBAC";
	Name = "RBAC";
	FullName = "Rubbing Alcohol";
	Colour = PIXPACK(0xD4CBFF);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.0f;
	HotAir = 0.0f * CFDS;
	Falldown = 2;

	Flammable = 25;
	Explosive = 0;
	Meltable = 0;
	Hardness = 5;

	Weight = 40;

	HeatConduct = 42;
	Description = "Rubbing alcohol. Kills viruses.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
}
