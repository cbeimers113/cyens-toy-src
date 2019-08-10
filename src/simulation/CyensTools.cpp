#include "CyensTools.h"

void ClampOrganic(Particle *p)
{
	int t = p->type;
	if (t == PT_NCTD && p->life > 4)//this looks like outdated code to keep nucleotides in the proper 5 bases
		p->life = rand() % 4;
	if (t != PT_GAS && t != PT_MWAX && t != PT_PRFN && t != PT_WAX && t != PT_OIL && t != PT_DESL && t != PT_ALCL)return;

	//Update alkanes/enes/ynes to prevent nonsense like C2H16 or C0H4 from forming using the console or prop tool
	if (p->life <= 1) {	//It's methane or the carbons were set to 0 or less
		p->life = 1;
		p->tmp = 4;
		p->tmp2 = 0;	//There's no double or triple bond in methane
	}
	else if (p->life > 60) {	//If it's too long make it into generic kerosene
		p->life = 60;
		p->tmp = 122;
		p->tmp2 = 0;
	}
	else {	//In the case that it's a proper number of carbons, check the amount of hydrogens to make sure it's good, then check bonds

		//If there are too many or too little hydrogens for the amount of carbons, fix it by randomly generating a proper molecule
		if (p->tmp > 2 * p->life + 2 || p->tmp < 2 * p->life - 2)
			p->tmp = makeAlk(p->life);

		//Get rid of special bonds where they don't belong otherwise check to make sure the bond is in an allowed position
		if (isAlkane(p->life, p->tmp))
			p->tmp2 = 0;
		else {
			if (p->tmp2 > p->life / 2)	//These simple hydrocarbons are like palindromes: 1-pentene is the same as 4-pentene, 
									//so always use the lesser number for the bond location
				p->tmp2 = getBondLoc(p->life);
		}
	}

	//Make sure the hydroxyl and special bond aren't in the same location
	if (p->type == PT_ALCL) {
		if (p->ctype<1 || p->ctype>p->life)
			p->ctype = 1;
		if (p->ctype == p->tmp2)
			p->ctype++;
	}
}


//Tells an RNA or DNA strand bit how to move
v2i getStrandOffset(int d) {
	int destX, destY;
	switch (d) {
	case DIR_N:
		destX = 0;
		destY = -1;
		break;
	case DIR_NE:
		destX = 1;
		destY = -1;
		break;
	case DIR_E:
		destX = 1;
		destY = 0;
		break;
	case DIR_SE:
		destX = 1;
		destY = 1;
		break;
	case DIR_S:
		destX = 0;
		destY = 1;
		break;
	case DIR_SW:
		destX = -1;
		destY = 1;
		break;
	case DIR_W:
		destX = -1;
		destY = 0;
		break;
	case DIR_NW:
		destX = -1;
		destY = -1;
		break;
	}
	return v2i{ destX, destY };
}

//gets the cardinal direction opposite of the head of the strand's direction
int getDir(float hvx, float hvy) {
	if (sqrt(hvx*hvx + hvy * hvy) < 0.0625f)return DIR_S;
	float theta = atan2(hvy, hvx) * (180.0f / M_PI); //convert it to degrees for my sanity
	return
		isInRange(theta, 0, 15) ? DIR_W :
		isInRange(theta, 15, 75) ? DIR_SW :
		isInRange(theta, 75, 105) ? DIR_S :
		isInRange(theta, 105, 165) ? DIR_SE :
		isInRange(theta, 165, 195) ? DIR_E :
		isInRange(theta, 195, 255) ? DIR_NE :
		isInRange(theta, 255, 285) ? DIR_N :
		isInRange(theta, 285, 345) ? DIR_NW : DIR_W;
}

//Gets the HUD name for waste particles
char const*getWasteName(int w) {
	switch (w) {
	case WSTE_SDM_ACETATE:
		return "Sodium Acetate";
	}
	return "Chemical Waste";
}

//Generates a random hydrocarbon type (alkane/ene/yne) with given number of carbons, returns number of hydrogens
int makeAlk(int c) {
	int alkType = rand() % 3;
	return alkType == 0 ? (2 * c + 2) : alkType == 1 ? (2 * c) : (2 * c - 2);
}

//Gets the bond location randomly for alkenes and alkynes
int getBondLoc(int c) {
	return (rand() % (c / 2)) + 1;
}

bool isAlkane(int c, int h) {
	return h == c * 2 + 2;
}

bool isAlkene(int c, int h) {
	return h == c * 2;
}

bool isAlkyne(int c, int h) {
	return h == c * 2 - 2;
}

bool isInRange(float n, float lBound, float uBound) {
	return n >= lBound && n < uBound;
}
