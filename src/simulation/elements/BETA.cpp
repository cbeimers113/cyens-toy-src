#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_BETA PT_BETA 237
Element_BETA::Element_BETA()
{
	Identifier = "DEFAULT_PT_BETA";
	Name = "BETA";
	Colour = PIXPACK(0xFFFFFF);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	// element properties here

	Update = &Element_BETA::update;
	Graphics = &Element_BETA::graphics;
}

//#TPT-Directive ElementHeader Element_BETA static int update(UPDATE_FUNC_ARGS)
int Element_BETA::update(UPDATE_FUNC_ARGS)
{
	// update code here

	return 0;
}

//#TPT-Directive ElementHeader Element_BETA static int graphics(GRAPHICS_FUNC_ARGS)
int Element_BETA::graphics(GRAPHICS_FUNC_ARGS)
{
	// graphics code here
	// return 1 if nothing dymanic happens here

	return 0;
}

Element_BETA::~Element_BETA() {}
