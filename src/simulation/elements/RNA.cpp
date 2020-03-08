#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

int Element_RNA_update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_RNA()
{
	Identifier = "DEFAULT_PT_RNA";
	Name = "RNA";
	FullName = "RNA";
	Colour = PIXPACK(0xD4FF90);
	MenuVisible = 0;
	MenuSection = SC_BIOLOGY;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.0f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 0;

	HeatConduct = 70;
	Description = "Ribonucleic acid, the precursor to DNA.";

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

int Element_RNA_update(UPDATE_FUNC_ARGS)
{
	if (parts[i].tmp2 == -1) {
		sim->kill_part(i);
		return 0;
	}
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (i == ID(r))continue;
				if (TYP(r) == parts[i].type)
					if (parts[ID(r)].tmp == STRAND_DETACHED) {
						if (parts[i].tmp == STRAND_HEAD && parts[i].flags < 5) {
							sim->kill_part(ID(r));
							parts[i].flags++;
						}
						else if (parts[i].tmp == STRAND_ATTACHED && parts[parts[ID(r)].sHeadIndex].flags < 5) {
							parts[parts[ID(r)].sHeadIndex].flags++;
							sim->kill_part(ID(r));
						}
						else if (parts[i].tmp == STRAND_DETACHED && parts[i].flags < 5) {
							sim->kill_part(ID(r));
							parts[i].tmp = STRAND_HEAD;
							parts[i].flags++;
						}
					}
			}
	if (parts[i].tmp == STRAND_HEAD) {
		parts[i].tmp2 = getDir(parts[i].vx, parts[i].vy);
		for (int j = 1; j <= parts[i].flags; j++) {
			v2i offs = getStrandOffset(parts[i].tmp2);
			offs.x *= j;
			offs.y *= j;
			if (isInRange(x + offs.x, 0, XRES) && isInRange(y + offs.y, 0, YRES) && !TYP(pmap[y + offs.y][x + offs.x])) {
				int indx = sim->create_part(-1, x + offs.x, y + offs.y, parts[i].type);
				parts[indx].tmp2 = -1;
				parts[indx].tmp = STRAND_ATTACHED;
			}
		}
	}
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	sim->parts[i].sHeadIndex = -1;
}