#include "simulation/ElementCommon.h"

//#TPT-Directive ElementClass Element_ALPH PT_ALPH 238
Element_ALPH::Element_ALPH()
{
	Identifier = "DEFAULT_PT_ALPH";
	Name = "ALPH";
	Colour = PIXPACK(0xFFFFFF);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	// element properties here

	Update = &Element_ALPH::update;
	Graphics = &Element_ALPH::graphics;
}

//#TPT-Directive ElementHeader Element_ALPH static int update(UPDATE_FUNC_ARGS)
int Element_ALPH::update(UPDATE_FUNC_ARGS)
{
	// update code here

	return 0;
}

//#TPT-Directive ElementHeader Element_ALPH static int graphics(GRAPHICS_FUNC_ARGS)
int Element_ALPH::graphics(GRAPHICS_FUNC_ARGS)
{
	// graphics code here
	// return 1 if nothing dymanic happens here

	return 0;
}

Element_ALPH::~Element_ALPH() {}
