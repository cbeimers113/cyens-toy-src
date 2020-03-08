#include "simulation/ElementCommon.h"
#include "../CyensTools.h"
#include <stack>

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_PHOS()
{
	Identifier = "DEFAULT_PT_PHOS";
	Name = "PHOS";
	FullName = "Phosphorus";
	Colour = PIXPACK(0xfcddd2);
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
	HotAir = 0.000f * CFDS;
	Falldown = 1;

	Flammable = 500;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 25;

	HeatConduct = 20;
	Description = "Phosphorus. Turns from white to red over time. White phosphorus burns on contact with O2.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
	Graphics = &graphics;
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].life <= 0)parts[i].tmp = PHOS_RED;
	int s = 0;
	int r;
	std::stack<int>oxygens;
	for (int ry = -1; ry < 2; ry++)
		for (int rx = -1; rx < 2; rx++)
			if (BOUNDS_CHECK) {
				if (parts[i].tmp == PHOS_WHITE) {
					r = pmap[y + ry][x + rx];
					if (!r && sim->photons[y + ry][x + rx]) {
						r = sim->photons[y + ry][x + rx];
						if (r) parts[i].life = 0;
						else continue;
					}
					if (TYP(r) == PT_O2) {
						sim->part_change_type(i, x, y, PT_FIRE);
					}
					else if (TYP(r) == PT_NONE || sim->elements[TYP(r)].Properties & TYPE_GAS) {
						s++;
					}
				}
				else {
					r = pmap[y + ry][x + rx];
					if (!r)continue;
					if (TYP(r) == PT_O2 && s < 3) {
						s++;
						oxygens.push(ID(r));
					}
				}
				if (parts[i].tmp && s == 3) {
					sim->part_change_type(i, x, y, PT_PHPT);
					while (!oxygens.empty()) {
						sim->kill_part(oxygens.top());
						oxygens.pop();
					}
				}
				else if (!parts[i].tmp)
					parts[i].life -= s;
			}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	bool r = cpart->tmp == PHOS_RED;

	*colr = r ? 0xc2 : 0xfc;
	*colg = r ? 0x40 : 0xdd;
	*colb = r ? 0x30 : 0xd2;

	*pixel_mode |= PMODE_FLAT;
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	sim->parts[i].life = rand() % 1000 + 500;
}