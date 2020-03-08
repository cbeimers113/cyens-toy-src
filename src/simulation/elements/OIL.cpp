#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

static int update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_OIL()
{
	Identifier = "DEFAULT_PT_OIL";
	Name = "OIL";
	FullName = "Hydrocarbon Oil";
	Colour = PIXPACK(0x404010);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
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

	Flammable = 20;
	Explosive = 0;
	Meltable = 0;
	Hardness = 5;

	Weight = 20;

	HeatConduct = 42;
	Description = "Hydrocarbon oil. Freezes quickly at room temperature. Can be formed with NEUT and NITR.";

	Properties = TYPE_LIQUID | PROP_NEUTPASS;

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

static int update(UPDATE_FUNC_ARGS) {
	//OIL is a high carbon liquid, it should not have any less than 20 carbons.
	if (parts[i].life < 20)sim->part_change_type(i, x, y, PT_DESL);

	int t = parts[i].temp - sim->pv[y / CELL][x / CELL];	//Pressure affects state transitions
	//Freezing into PRFN
	if (t <= (14.3f * sqrt((parts[i].life - 12))) + 273.15)
		sim->part_change_type(i, x, y, PT_PRFN);
	//Boiling into GAS
	if (t > (4 * sqrt(500 * (parts[i].life - 4))) + 273.15)
		sim->part_change_type(i, x, y, PT_GAS);

	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	//Spawns with carbons (20-60), temp must be min 42 ?C
	sim->parts[i].life = rand() % 41 + 20;
	sim->parts[i].tmp = makeAlk(sim->parts[i].life);
	if (sim->parts[i].tmp < 2 * sim->parts[i].life + 2)sim->parts[i].tmp2 = getBondLoc(sim->parts[i].life);
	//Essentially this is creating PRFN then melting it right away
	sim->parts[i].temp = 14.3f * sqrt(sim->parts[i].life - 12) + 273.15f + 20.0f;
}