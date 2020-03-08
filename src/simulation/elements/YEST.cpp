#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_YEST()
{
	Identifier = "DEFAULT_PT_YEST";
	Name = "YEST";
	FullName = "Yeast";
	Colour = PIXPACK(0xEEE0C0);
	MenuVisible = 1;
	MenuSection = SC_BIOLOGY;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 15;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 80;

	HeatConduct = 70;
	Description = "Yeast, grows when warm (~37C).";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 373.0f;
	HighTemperatureTransition = PT_DYST;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	bool o2 = false;
	int o2i;
	// First loop for j = find O2, second loop = find sugar
	for (int j = 0; j < 2; j++)
		for (rx = (j ? -1 : -3); rx < (j ? 2 : 4); rx++)
			for (ry = (j ? -1 : -3); ry < (j ? 2 : 4); ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y + ry][x + rx];
					if (!r)
						continue;
					if (j && TYP(r) == PT_DYST && RNG::Ref().chance(1, 6) && !sim->legacy_enable)
					{
						sim->part_change_type(i, x, y, PT_DYST);
					}
					if (!j && TYP(r) == PT_O2) {
						o2 = true;
						o2i = ID(r);
					}
					//respiration of YEST to produce WTRV and CO2 in presence of O2 or else ALCL and CO2
					if (j && TYP(r) == PT_SUGR && parts[ID(r)].tmp == SUGR_GLUCOSE) {
						sim->create_part(-1, x + rand() % 3 - 1, y + rand() % 3 - 1, PT_CO2);
						sim->part_change_type(ID(r), x + rx, y + ry, o2 ? PT_WTRV : PT_ALCL);
						if (o2) {
							sim->kill_part(o2i);
							o2 = false;
						}
						else {
							parts[ID(r)].life = 2;
							parts[ID(r)].tmp = 6;
						}
					}
				}
	if (parts[i].temp > 303 && parts[i].temp < 317) {
		sim->create_part(-1, x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1), PT_YEST);
	}
	return 0;
}
