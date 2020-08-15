#include "find.h"

#include <sc2api/sc2_api.h>

using namespace sc2;
using namespace core::util;

const Unit* core::util::FindNearest(Predicate<const Unit*> predicate, Point2D start, const Units &units)
{
    return FindNearest<Predicate<const Unit*>>(predicate, start, units);
}

const sc2::Unit* core::util::FindNearest(Point2D start, const Units &units) {
    return FindNearest([](auto){ return true; }, start, units);
}