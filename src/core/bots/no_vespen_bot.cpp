#include <core/bots.h>
#include <core/util/find.h>
#include <core/util/checker.h>
#include <core/util/types.h>

#include <sc2api/sc2_api.h>
#include <sc2api/sc2_unit_filters.h>

#include <functional>
#include <algorithm>
#include <random>

using namespace sc2;
using namespace core;
using namespace core::util;

struct NoVespenBot : public sc2::Agent {
    virtual void OnGameStart() final {
    }

    virtual void OnStep() final {
        std::cout << Observation()->GetGameLoop() << std::endl;
        SpendMinerals = 0;
        BuildSCV();
    }

    int GetExpectedWorkers(UNIT_TYPEID vespene_building_type) {
        const ObservationInterface* observation = Observation();
        Units bases = observation->GetUnits(Unit::Alliance::Self, IsTownHall());

        int expected_workers = 0;
        for (const auto& base : bases) {
            if (base->build_progress != 1) {
                continue;
            }
            expected_workers += base->ideal_harvesters;
        }

        return expected_workers;
    }

    const Unit* FindNearestMineralPatch(const Point2D& start) {
        using namespace std::placeholders;
        Units units = Observation()->GetUnits(Unit::Alliance::Neutral);
        auto filter = std::bind(IsUnitWithType, UNIT_TYPEID::NEUTRAL_MINERALFIELD, _1);
        return util::FindNearest(filter, start, units);
    }

    void BuildSCV() {
        const ObservationInterface* observation = Observation();
        Units bases = observation->GetUnits(Unit::Alliance::Self, IsTownHall());

        if (observation->GetFoodUsed() >= observation->GetFoodCap()) {
            return;
        }

        if (observation->GetFoodWorkers() > GetExpectedWorkers(UNIT_TYPEID::TERRAN_REFINERY)) {
            return;
        }

        for (const auto& base : bases) {
            //if there is a base with less than ideal workers
            bool hasMinerals = observation->GetMinerals() >= 50 + SpendMinerals;
            bool hasBuildOrder = !base->orders.empty();
            bool hasFood = observation->GetFoodUsed() < observation->GetFoodCap();
            if (base->assigned_harvesters < base->ideal_harvesters && base->build_progress == 1) {
                if (hasMinerals && !hasBuildOrder && hasFood) {
                    SpendMinerals += 50;
                    Actions()->UnitCommand(base, ABILITY_ID::TRAIN_SCV);
                }
            }
        }
    }

    uint64_t SpendMinerals = 0;
};


std::unique_ptr<sc2::Agent> core::CreateNoVespenBot() {
    return std::make_unique<NoVespenBot>();
}