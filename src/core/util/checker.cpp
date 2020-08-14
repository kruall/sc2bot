#include "checker.h"

using namespace core::util;


bool IsUnitWithType(sc2::UNIT_TYPEID t, sc2::Unit* u) {
    return u->unit_type == t;
}
