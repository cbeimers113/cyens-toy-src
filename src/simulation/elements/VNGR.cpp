#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_VNGR()
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
	HotAir = 0.000f * CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 40;

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

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp > 100.0f + 273.15f) {
		sim->part_change_type(i, x, y, PT_ACTA);
		for (int yy = -1; yy <= 1; yy++) // A way to make sure the wtrv gets spawned, not the most efficient
			for (int xx = -1; xx <= 1; xx++)
				if (x + xx >= 0 && x + xx < XRES && y + yy >= 0 && y + yy < YRES && !sim->pmap[y + yy][x + xx]) {
					sim->create_part(-1, x + xx, y + yy, PT_WTRV);
					return 0;
				}
	}
	return 0;
}

