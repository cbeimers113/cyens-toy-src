#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

//#TPT-Directive ElementClass Element_QARK PT_QARK 225
Element_QARK::Element_QARK()
{
	Identifier = "DEFAULT_PT_QARK";
	Name = "QARK";
	FullName = "Quark";
	Colour = PIXPACK(0x009900);
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
	Description = "Quarks. The fundamental building blocks of the nuclei of atoms. Currently doesn't bond.";

	Properties = TYPE_ENERGY | PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_QARK::update;
	Graphics = &Element_QARK::graphics;
}

//#TPT-Directive ElementHeader Element_QARK static int update(UPDATE_FUNC_ARGS)
int Element_QARK::update(UPDATE_FUNC_ARGS)
{
	if (parts[i].life <= 0) {
		parts[i].life = RNG::Ref().between(1, 5);
		sim->part_change_type(i, x, y, PT_WBSN);
		return 0;
	}
	int r, rx, ry;
	float s = 5;
	for (ry = -5; ry <= 5; ry++)
		for (rx = -5; rx <= 5; rx++)
			if (BOUNDS_CHECK) {
				r = sim->photons[y + ry][x + rx];
				if (!r || TYP(r) != PT_QARK)continue;

				//update velocity for color force
				if (parts[ID(r)].tmp2 != parts[i].tmp2) {
					float dx = rx - x;
					float dy = ry - y;
					if (dx != 0)
						dx /= (abs(dx) * s);
					if (dy != 0)
						dy /= (abs(dy) * s);
					parts[i].vx += dx;
					parts[i].vy += dy;
					parts[ID(r)].vx -= dx;
					parts[ID(r)].vy -= dy;
				}

				// make hadrons
				//1st bondindex for ups, 3rd is for down, 2nd is variable (this particle)
				//PROT: u-u-d
				//NEUT: u-d-d
				if (ry >= -1 && ry <= 1 && rx >= -1 && rx <= 1) {
					int bi1 = -1;
					int bi2 = -1;
					if (parts[i].tmp == QARK_UP || parts[i].tmp == QARK_DOWN) {
						switch (parts[ID(r)].tmp) {
						case QARK_UP:
							if (bi1 == -1)
								bi1 = ID(r);
							break;
						case QARK_DOWN:
							if (bi2 == -1)
								bi2 = ID(r);
							break;
						}
						if (bi1 != -1 && bi2 != -1 && (parts[i].tmp2 != parts[bi1].tmp2) && (parts[i].tmp2 != parts[bi2].tmp2) && (parts[bi1].tmp2 != parts[bi2].tmp2)) { //can form baryon
							switch (parts[i].tmp) {
							case QARK_UP:
								sim->part_change_type(i, x, y, PT_PROT);
								break;
							case QARK_DOWN:
								sim->part_change_type(i, x, y, PT_NEUT);
								break;
							}
							sim->kill_part(bi1);
							sim->kill_part(bi2);
						}
					}
				}
			}
	parts[i].vx += sim->strongForce[y][x].x;
	parts[i].vy += sim->strongForce[y][x].y;
	return 0;
}

//#TPT-Directive ElementHeader Element_QARK static int graphics(GRAPHICS_FUNC_ARGS)
int Element_QARK::graphics(GRAPHICS_FUNC_ARGS)
{
	int c = 125;
	int t = cpart->tmp2;
	*firea = (int)(((float)quarkGen(cpart->tmp) / 3.0f) * 0xff);
	*firer = *colr = t == CCHARGE_R ? c : 0;
	*fireg = *colg = t == CCHARGE_G ? c : 0;
	*fireb = *colb = t == CCHARGE_B ? c : 0;

	*pixel_mode |= FIRE_BLEND;
	return 0;
}

Element_QARK::~Element_QARK() {}
