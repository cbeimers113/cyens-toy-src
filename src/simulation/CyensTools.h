#include <cmath>
#include "Particle.h"
#include "Simulation.h"
#include "../../generated/ElementClasses.h"

#define ADENINE 0
#define GUANINE 1
#define CYTOSINE 2
#define THYMINE 3
#define URACIL 4

#define NCTD_OTHER_BONDED -1
#define NCTD_UNBONDED 0
#define NCTD_BONDED_TA 1
#define NCTD_BONDED_GC 2
#define NCTD_BONDED_AU 3

#define STRAND_DETACHED 0
#define STRAND_ATTACHED 1
#define STRAND_HEAD 2

#define DIR_N 0
#define DIR_NE 1
#define DIR_E 2
#define DIR_SE 3
#define DIR_S 4
#define DIR_SW 5
#define DIR_W 6
#define DIR_NW 7

#define PHOS_WHITE 0
#define PHOS_RED 1

#define WSTE_SDM_ACETATE 0
#define WSTE_TRSDM_PHOSPHATE 1

#define SUGR_GLUCOSE 0
#define SUGR_RIBOSE 1
#define SUGR_DEOXYRIBOSE 2

#define QARK_UP 0
#define QARK_DOWN 1
#define QARK_CHARM 2
#define QARK_STRANGE 3
#define QARK_TOP 4
#define QARK_BOTTOM 5

#define GLUON_RC 0
#define GLUON_GM 1
#define GLUON_GY 2
#define GLUON_BM 3

#define CCHARGE_R 0
#define CCHARGE_G 1
#define CCHARGE_B 2

#define SF_MAX 10

int makeAlk(int c);
int getBondLoc(int c);
int getDir(float hvx, float hvy);
int quarkGen(int flavor);
float clamp(float f, float min, float max);
float mag(v2f v);
bool isAlkane(int c, int h);
bool isAlkene(int c, int h);
bool isAlkyne(int c, int h);
bool isInRange(float n, float lBound, float uBound);

v2i getStrandOffset(int d);

String getWasteName(int w);
String vectorToString(v2i v);
String vectorToString(v2f v);
String getGluonCharge(char c);

void ClampOrganic(Particle* p);