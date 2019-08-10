#include "simulation/Elements.h"
#include "simulation/CyensTools.h"

//#TPT-Directive ElementClass Element_RNA PT_RNA 216
Element_RNA::Element_RNA()
{
	Identifier = "DEFAULT_PT_RNA";
	Name = "RNA";
	FullName = "RNA";
	Colour = PIXPACK(0xD4FF90);
	MenuVisible = 1;
	MenuSection = SC_BIOLOGY;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.0f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 30;

	Weight = 0;

	Temperature = R_TEMP + 273.15f;
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

	Update = &Element_RNA::update;
}


//#TPT-Directive ElementHeader Element_RNA static int update(UPDATE_FUNC_ARGS)
int Element_RNA::update(UPDATE_FUNC_ARGS) {
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


/*
int Element_RNA::update(UPDATE_FUNC_ARGS)
{
	int emptyCount = 0;
	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				if (i == ID(r))continue;
				if (TYP(r) == PT_NONE)emptyCount++;
				else if (TYP(r) == parts[i].type && parts[i].tmp == STRAND_DETACHED && parts[ID(r)].flags < 3) {
					switch (parts[ID(r)].tmp) {
					case STRAND_ATTACHED:
						parts[i].tmp = STRAND_ATTACHED;
						parts[i].sHeadIndex = parts[ID(r)].sHeadIndex;
						parts[i].flags = ++parts[parts[i].sHeadIndex].flags;
						break;
					case STRAND_DETACHED:
						parts[ID(r)].tmp = STRAND_HEAD;
					case STRAND_HEAD:
						parts[i].tmp = STRAND_ATTACHED;
						parts[i].sHeadIndex = ID(r);
						parts[i].flags = ++parts[ID(r)].flags;
						break;
					}
				}
			}
	if (emptyCount == 8 && parts[i].tmp == STRAND_HEAD) {
		parts[i].tmp = STRAND_DETACHED;
		parts[i].tmp2 = 0;
		parts[i].flags = 0;
	}
	else if (emptyCount == 8) {
		if (++parts[i].tmp2 == 30) {
			parts[parts[i].sHeadIndex].flags--;
			parts[i].tmp = STRAND_DETACHED;
			parts[i].sHeadIndex = -1;
			parts[i].flags = 0;
			parts[i].tmp2 = 0;
		}
	}
	if (parts[i].tmp == STRAND_HEAD) {
		parts[i].tmp2 = getDir(parts[i].vx, parts[i].vy);
	}
	if (parts[i].tmp == STRAND_ATTACHED && parts[i].sHeadIndex != -1) {
		Particle head = parts[parts[i].sHeadIndex];
		setStrandDest(parts, i);
		v2i dest = parts[i].vector2i;
		//parts[i].vx = head.vx * 0 + (((dest.x + head.x) - x) / abs(((dest.x + head.x) - x)))*.05f;
		//parts[i].vy = head.vy * 0 + (((dest.y + head.y) - y) / abs(((dest.y + head.y) - y)))*.05f;
		//parts[i].vx = head.vx;
		//parts[i].vy = head.vy;
		int xOffs = head.x + dest.x;
		int yOffs = head.y + dest.y;
		if (isInRange(xOffs, 0, XRES) && isInRange(yOffs, 0, YRES)) {
			if (TYP(pmap[yOffs][xOffs]) == PT_NONE) {
				parts[i].x = xOffs;
				parts[i].y = yOffs;
			}
		}
	}
	return 0;
}
*/

Element_RNA::~Element_RNA() {}
