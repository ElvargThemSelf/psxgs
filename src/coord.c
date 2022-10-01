#include "functions_pub.h"
#include "globals_pub.h"
#include "types_pub.h"

void GsInitCoordinate(GsCOORDINATE *super, GsCOORDINATE *base) {
    base->super = super;
    base->coord = GsIDMATRIX;
    super->sub = base;
}