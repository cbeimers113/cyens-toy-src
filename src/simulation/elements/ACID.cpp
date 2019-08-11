#include "simulation/ElementCommon.h"
#include "simulation/CyensTools.h"
//#TPT-Directive ElementClass Element_ACID PT_ACID 21
Element_ACID::Element_ACID()
{
	Identifier = "DEFAULT_PT_ACID";
	Name = "HCL";
	FullName = "Hydrochloric Acid";
	Colour = PIXPACK(0xED55FF);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 40;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;
	PhotonReflectWavelengths = 0x1FE001FE;

	Weight = 10;

	Temperature = R_TEMP + 0.0f + 273.15f;
	HeatConduct = 34;
	Description = "Hydrochloric acid. Dissolves almost everything.";

	Properties = TYPE_LIQUID | PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_ACID::update;
	Graphics = &Element_ACID::graphics;
}

//#TPT-Directive ElementHeader Element_ACID static int update(UPDATE_FUNC_ARGS)
int Element_ACID::update(UPDATE_FUNC_ARGS)
{
	int dissolve = 1;
	switch (parts[i].type) {
	case PT_ACTA:
		dissolve = 1000;
		break;
	case PT_PHAC:
		dissolve = 500;
		break;
	case PT_HNO3:
		dissolve = 100;
		break;
	}
	bool hasWater = false;
	int r, rx, ry, trade;
	for (rx = -2; rx < 3; rx++)
		for (ry = -2; ry < 3; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				int rt = TYP(r);
				if (rt == PT_WATR || rt == PT_DSTW || rt == PT_SLTW || rt == PT_CBNW) hasWater = true;
				if (rt == PT_SDHX) {
					int ot = parts[i].type;
					sim->part_change_type(i, x, y, ot == PT_ACID ? PT_SALT : ot == PT_HNO3 ? PT_SDNT : PT_WSTE);
					sim->part_change_type(ID(r), x + rx, y + ry, PT_WTRV);
					if (ot == PT_PHAC)parts[i].tmp2 = WSTE_TRSDM_PHOSPHATE;
					else if (ot == PT_ACTA)parts[i].tmp2 = WSTE_SDM_ACETATE;
				}
				if (parts[i].type == PT_ACID && hasWater && rt == PT_ISCY) {
					sim->part_change_type(i, x, y, PT_FRMD);
					sim->kill_part(ID(r));
				}
				else if (parts[i].type == PT_ACTA && hasWater)
					sim->part_change_type(i, x, y, PT_VNGR);
				if (rt == PT_PLEX || rt == PT_NITR || rt == PT_GUNP || rt == PT_RBDM || rt == PT_LRBD)
				{
					sim->part_change_type(i, x, y, PT_FIRE);
					sim->part_change_type(ID(r), x + rx, y + ry, PT_FIRE);
					parts[i].life = 4;
					parts[ID(r)].life = 4;
				}
				//This needs to be removed
				else if (parts[i].type == PT_ACID && (rt == PT_WTRV || rt == PT_WATR || rt == PT_CBNW || rt == PT_SLTW || rt == PT_DSTW))
				{
					if (RNG::Ref().chance(1, 250))
					{
						sim->part_change_type(i, x, y, PT_CAUS);
						parts[i].life = RNG::Ref().between(25, 74);
						sim->kill_part(ID(r));
					}
					else
						sim->part_change_type(ID(r), x + rx, y + ry, rt == PT_CBNW ? PT_CO2 : PT_SALT);
				}
				if ((rand() % dissolve == 0) && (sim->elements[parts[ID(r)].type].Properties&TYPE_SOLID || sim->elements[parts[ID(r)].type].Properties&TYPE_PART))
				{
					if (rt != PT_CLNE && rt != PT_PCLN && parts[i].life >= 50 && RNG::Ref().chance(sim->elements[rt].Hardness, 1000.0))
					{
						if (parts[i].life&&sim->parts_avg(i, ID(r), PT_GLAS) != PT_GLAS)//GLAS protects stuff from acid
						{
							float newtemp = ((60.0f - (float)sim->elements[rt].Hardness))*7.0f;
							if (newtemp < 0) {
								newtemp = 0;
							}
							parts[i].temp += newtemp;
							parts[i].life--;
							sim->kill_part(ID(r));
						}
					}
				}
			}
	for (trade = 0; trade < 2; trade++)
	{
		rx = RNG::Ref().between(-2, 2);
		ry = RNG::Ref().between(-2, 2);
		if (BOUNDS_CHECK && (rx || ry))
		{
			r = pmap[y + ry][x + rx];
			if (!r)
				continue;
			if ((TYP(r) == PT_ACID || TYP(r) == PT_ACTA || TYP(r) == PT_PHAC || TYP(r) == PT_HNO3) && (parts[i].life > parts[ID(r)].life) && parts[i].life > 0)//diffusion
			{
				int temp = parts[i].life - parts[ID(r)].life;
				if (temp == 1)
				{
					parts[ID(r)].life++;
					parts[i].life--;
				}
				else if (temp > 0)
				{
					parts[ID(r)].life += temp / 2;
					parts[i].life -= temp / 2;
				}
			}
		}
	}
	return 0;
}


//#TPT-Directive ElementHeader Element_ACID static int graphics(GRAPHICS_FUNC_ARGS)
int Element_ACID::graphics(GRAPHICS_FUNC_ARGS)
{
	int s = cpart->life;
	if (s > 75) s = 75; //These two should not be here.
	if (s < 49) s = 49;
	s = (s - 49) * 3;
	if (s == 0) s = 1;
	*colr += s * 4;
	*colg += s * 1;
	*colb += s * 2;
	*pixel_mode |= PMODE_BLUR;
	return 0;
}

Element_ACID::~Element_ACID() {}
