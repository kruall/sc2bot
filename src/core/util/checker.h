#pragma once

#include <sc2api/sc2_unit.h>


namespace core::util {

    bool IsUnitWithType(sc2::UNIT_TYPEID type, sc2::Unit* unit);

}