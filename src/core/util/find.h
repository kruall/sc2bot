#pragma once

#include <sc2api/sc2_unit.h>

#include <functional>


namespace core::util {

    const sc2::Unit* FindNearest(std::function<bool(sc2::Unit*)> predicate,
            const sc2::Point2D &start, const sc2::Units &units);

    const sc2::Unit* FindNearest(const sc2::Point2D &start, const sc2::Units &units);

}