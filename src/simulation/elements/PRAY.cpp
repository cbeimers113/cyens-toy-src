#include "simulation/ElementCommon.h"
//#TPT-Directive ElementClass Element_PRAY PT_PRAY 228
Element_PRAY::Element_PRAY()
{
	Identifier = "DEFAULT_PT_PRAY";
	Name = "PRAY";
	FullName = "Particle Ray";
	Colour = PIXPACK(0x82a0b0);
	MenuVisible = 1;
	MenuSection = SC_POWERED;
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

	Flammable = 0;
	Explosive = 0;
	Meltable = 1;
	Hardness = 1;

	Weight = 100;

	Temperature = R_TEMP + 273.15f;
	HeatConduct = 251;
	Description = "Particle ray. Emits subatomic particles with this part\'s properties (experimental)";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_PRAY::update;
	Graphics = &Element_PRAY::graphics;
	CtypeDraw = &Element_PRAY::ctypeDraw;
}

//#TPT-Directive ElementHeader Element_PRAY static int update(UPDATE_FUNC_ARGS)
int Element_PRAY::update(UPDATE_FUNC_ARGS) {
	if (sim->elements[parts[i].ctype].Properties & TYPE_ENERGY) {
		Element_PCLN::update(UPDATE_FUNC_SUBCALL_ARGS);
	}
	else parts[i].ctype = PT_NONE;
	return 0;
}

//#TPT-Directive ElementHeader Element_PRAY static int graphics(GRAPHICS_FUNC_ARGS)
int Element_PRAY::graphics(GRAPHICS_FUNC_ARGS) {
	int lifemod = ((cpart->life > 10 ? 10 : cpart->life) * 10);
	*colr += lifemod;
	*colg += lifemod;
	return 0;
}

//#TPT-Directive ElementHeader Element_PRAY static bool ctypeDraw(CTYPEDRAW_FUNC_ARGS)
bool Element_PRAY::ctypeDraw(CTYPEDRAW_FUNC_ARGS)
{
	if (t == PT_PSCN || t == PT_NSCN)
	{
		return false;
	}
	return Element::ctypeDrawVInTmp(CTYPEDRAW_FUNC_SUBCALL_ARGS);
}

Element_PRAY::~Element_PRAY() {}
