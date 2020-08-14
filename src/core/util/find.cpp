#include "find.h"

#include <sc2api/sc2_api.h>

using namespace sc2;


const Unit* core::util::FindNearest(std::function<bool(Unit*)> predicate,
        const Point2D &start, const Units &units)
{
    float distance = std::numeric_limits<float>::max();
    const Unit* target = nullptr;
    for (const auto& u : units) {
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

const sc2::Unit* core::util::FindNearest(const sc2::Point2D &start, const Units &units) {
    return FindNearest([](auto){ return true; }, start, units);
}