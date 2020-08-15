#pragma once

#include "types.h"

#include <sc2api/sc2_unit.h>

#include <functional>


namespace core::util {

    template <typename Pred>
    const sc2::Unit* FindNearest(Pred predicate, sc2::Point2D start, const sc2::Units &units)
    {
        float distance = std::numeric_limits<float>::max();
        const sc2::Unit* target = nullptr;
        for (const auto& u : units) {
            if (!predicate(u)) {
                continue;
            }
            float d = DistanceSquared2D(u->pos, start);
            if (d < distance) {
                distance = d;
                target = u;
            }
        }
        //If we never found one return false;
        if (distance == std::numeric_limits<float>::max()) {
            return target;
        }
        return target;
    }

    const sc2::Unit* FindNearest(Predicate<sc2::Unit*> predicate, sc2::Point2D start, const sc2::Units &units);

    const sc2::Unit* FindNearest(sc2::Point2D start, const sc2::Units &units);

    template <typename Pred>
    const sc2::Unit* FindFirst(Pred predicate, const sc2::Units &units) {
        for (const auto &u : units) {
            if (predicate(u)) {
                return u;
            }
        }
        return nullptr;
    }

}