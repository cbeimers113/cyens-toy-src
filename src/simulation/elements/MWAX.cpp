#include "simulation/ElementCommon.h"
#include "../CyensTools.h"

static int update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_MWAX()
{
	Identifier = "DEFAULT_PT_MWAX";
	Name = "MWAX";
	FullName = "Melted Hydrocarbon Wax";
	Colour = PIXPACK(0xE0E0AA);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.3f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.95f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.15f;
	Diffusion = 0.00f;
	HotAir = 0.000001f * CFDS;
	Falldown = 2;

	Flammable = 5;
	Explosive = 0;
	Meltable = 0;
	Hardness = 2;

	Weight = 25;

	DefaultProperties.temp = R_TEMP + 28.0f + 273.15f;
	HeatConduct = 44;
	Description = "Melted hydrocarbon wax.";

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
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS) {
	//MWAX is a low carbon powder, it should not have any more than 7 carbons.
	if (parts[i].life > 7)sim->part_change_type(i, x, y, PT_DESL);

	int t = parts[i].temp - sim->pv[y / CELL][x / CELL];	//Pressure affects state transitions
	//Freezing into WAX
	if ((parts[i].life < 5 && t <= (-200 + 273.15)) || (parts[i].life > 5 && t <= (14.3f * sqrt((parts[i].life - 12))) + 273.15))
		sim->part_change_type(i, x, y, PT_WAX);
	//Boiling into GAS
	if ((parts[i].life == 1 && t > (-180 + 273.15)) || (parts[i].life == 2 && t > (-100 + 273.15)) || (parts[i].life == 3 && t > -50 + 273.15) || (parts[i].life >= 4 && t > (4 * sqrt(500 * (parts[i].life - 4))) + 273.15))
		sim->part_change_type(i, x, y, PT_GAS);

	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS) {
	//Spawns with carbons (5-7)
	sim->parts[i].life = rand() % 3 + 5;
	sim->parts[i].tmp = makeAlk(sim->parts[i].life);
	if (sim->parts[i].tmp < 2 * sim->parts[i].life + 2)sim->parts[i].tmp2 = getBondLoc(sim->parts[i].life);
}