#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

static int update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_PRFN()
{
	Identifier = "DEFAULT_PT_PRFN";
	Name = "PRFN";
	//FullName = "Solid High Carbon Wax";
	Colour = PIXPACK(0xA0A066);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 75;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 100;

	HeatConduct = 44;
	Description = "Paraffin wax. Melts into OIL.";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;


	Update = &update;
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
	//PRFN is a high carbon solid, it should not have any less than 20 carbons.
	if (parts[i].life < 20)sim->part_change_type(i, x, y, PT_WAX);

	int t = parts[i].temp - sim->pv[y / CELL][x / CELL];	//Pressure affects state transitions
	//Melting
	if (t > (14.3f * sqrt(parts[i].life - 12)) + 273.15)
		sim->part_change_type(i, x, y, PT_OIL);

	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	//Spawns with carbons (20-60)
	sim->parts[i].life = rand() % 41 + 20;
	sim->parts[i].tmp = makeAlk(sim->parts[i].life);
	if (sim->parts[i].tmp < 2 * sim->parts[i].life + 2)sim->parts[i].tmp2 = getBondLoc(sim->parts[i].life);
}

