#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

//#TPT-Directive ElementClass Element_NCTD PT_NCTD 215
Element_NCTD::Element_NCTD()
{
	Identifier = "DEFAULT_PT_NCTD";
	Name = "NCTD";
	FullName = "Nucleotide";
	Colour = PIXPACK(0xD4C890);
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
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 5;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 70;
	Description = "Nucleotide, the basic building block of DNA.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_NCTD::update;
	Graphics = &Element_NCTD::graphics;
}


//#TPT-Directive ElementHeader Element_NCTD static int update(UPDATE_FUNC_ARGS)
int Element_NCTD::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (TYP(r) != PT_NCTD || parts[ID(r)].tmp == NCTD_OTHER_BONDED)
					continue;
				if (parts[i].tmp == NCTD_OTHER_BONDED) {
					sim->kill_part(i);
					return 0;
				}
				//T->A, G->C
				//U is T for RNA
				if (i != ID(r) && parts[i].tmp == NCTD_UNBONDED && parts[ID(r)].tmp == NCTD_UNBONDED && parts[i].temp - 273.15f < 150) {
					int other = parts[ID(r)].life;
					switch (parts[i].life) {
					case ADENINE:
						if (other == THYMINE) {
							parts[i].tmp = NCTD_BONDED_TA;
							parts[ID(r)].tmp = NCTD_OTHER_BONDED;
						}
						else if (other == URACIL) {
							parts[i].tmp = NCTD_BONDED_AU;
							parts[ID(r)].tmp = NCTD_OTHER_BONDED;
						}
						break;
					case GUANINE:
						if (other == CYTOSINE) {
							parts[i].tmp = NCTD_BONDED_GC;
							parts[ID(r)].tmp = NCTD_OTHER_BONDED;
						}
						break;
					case CYTOSINE:
						if (other == GUANINE) {
							parts[i].tmp = NCTD_BONDED_GC;
							parts[ID(r)].tmp = NCTD_OTHER_BONDED;
						}
						break;
					case THYMINE:
						if (other == ADENINE) {
							parts[i].tmp = NCTD_BONDED_TA;
							parts[ID(r)].tmp = NCTD_OTHER_BONDED;
						}
						break;
					case URACIL:
						if (other == ADENINE) {
							parts[i].tmp = NCTD_BONDED_AU;
							parts[ID(r)].tmp = NCTD_OTHER_BONDED;
						}
						break;
					}
				}
				if (parts[i].tmp > NCTD_UNBONDED && parts[i].temp > 273.15f + 150) {
					int base = parts[i].tmp;
					parts[i].tmp = NCTD_UNBONDED;
					int xOffs = 0;
					int yOffs = 0;
					int tryCount = 0;
					while ((xOffs == 0 && yOffs == 0) || parts[ID(pmap[y + yOffs][x + xOffs])].type != PT_NONE) {
						xOffs = rand() % 3 - 1;
						yOffs = rand() % 3 - 1;
						if (!(++tryCount % 64))break;
					}
					int nPart = sim->create_part(-1, x + xOffs, y + yOffs, PT_NCTD);
					parts[nPart].tmp = NCTD_UNBONDED;
					parts[nPart].temp = parts[i].temp;
					switch (parts[i].life) {
					case ADENINE:
						parts[nPart].life = (base == NCTD_BONDED_TA ? THYMINE : URACIL);
						break;
					case GUANINE:
						parts[nPart].life = CYTOSINE;
						break;
					case CYTOSINE:
						parts[nPart].life = GUANINE;
						break;
					case THYMINE:
					case URACIL:
						parts[nPart].life = ADENINE;
						break;
					}
				}
			}
	return 0;
}

//#TPT-Directive ElementHeader Element_NCTD static int graphics(GRAPHICS_FUNC_ARGS)
int Element_NCTD::graphics(GRAPHICS_FUNC_ARGS)
{
	int l = 75 + 3 * cpart->life;

	int r = (float)l / 100.0f * 0xd4;
	int g = (float)l / 100.0f * 0xc8;
	int b = (float)l / 100.0f * 0x90;

	*colr = r;
	*colg = g;
	*colb = b;

	*firea = 0x09;
	*firer = r;
	*fireg = g;
	*fireb = b;

	*pixel_mode |= cpart->tmp > NCTD_UNBONDED ? PMODE_GLOW : PMODE_FLAT;
	return 0;
}

Element_NCTD::~Element_NCTD() {}
