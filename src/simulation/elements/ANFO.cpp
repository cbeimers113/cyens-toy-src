#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_ANFO PT_ANFO 202
Element_ANFO::Element_ANFO()
{
	Identifier = "DEFAULT_PT_ANFO";
	Name = "ANFO";
	FullName = "Ammonium Nitrate Fuel Oil";
	Colour = PIXPACK(0xafafaf);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 500;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 50;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 251;
	Description = "Ammonium Nitrate Fuel Oil (ANFO) explosive.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_ANFO::update;
}

Element_ANFO::~Element_ANFO() {}

//#TPT-Directive ElementHeader Element_ANFO static int update(UPDATE_FUNC_ARGS)
int Element_ANFO::update(UPDATE_FUNC_ARGS) {
int r, rx, ry;
float minvelo = 5.0f;
for (rx = -1; rx < 2; rx++) {
	for (ry = -1; ry < 2; ry++) {
		if (BOUNDS_CHECK && (rx || ry)) {
			r = pmap[y + ry][x + rx];
			if (!r) continue;
			int rt = TYP(r);

			if (rt != PT_ANFO) {
				if (parts[i].tmp > minvelo) {
					sim->pv[y / CELL][x / CELL] += parts[i].tmp * sim->elements[rt].Weight / 70.0f;	//sim->pv[y / CELL][x / CELL] += abs(sqrt(parts[i].vx * parts[i].vx + parts[i].vy * parts[i].vy)) * sim->elements[TYP(r)].Weight / 200;			
				} //Collision detected
			}
		}		
	}
}
	if (parts[i].vx > 10.0f || parts[i].vy > 10.0f)
	{
		sim->pv[y / CELL][x / CELL] += parts[i].vx + parts[i].vy;
		//parts[i].vx * 0.99f;
		//parts[i].vy * 0.99f;
	}
	if (parts[i].temp > 300.0f) {
		sim->pv[y / CELL][x / CELL] += 35.0f;
		sim->create_part(	-1, x + rand() % 3 - 1, y + rand() % 3 - 1, rand() % 10 < 3 ? PT_FIRE : PT_SMKE);
	}
	parts[i].tmp = int(abs(sqrt(parts[i].vx * parts[i].vx + parts[i].vy * parts[i].vy)));
	return 0;
}