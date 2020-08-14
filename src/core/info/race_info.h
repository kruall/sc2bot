#pragma once

#include <sc2api/sc2_typeenums.h>


namespace core::info {

    struct IRace {
        virtual sc2::UNIT_TYPEID GetWorker() const = 0;
    };

#ifdef DESCRIBE_UNIT
    static_assert(false);
#else
    #define DESCRIBE_UNIT(name, type) \
        static constexpr sc2::UNIT_TYPEID name = sc2::UNIT_TYPEID::type; \
        virtual sc2::UNIT_TYPEID Get##name() const final { return name; }
#endif

    struct TerranRace : public IRace {
        DESCRIBE_UNIT(Worker, TERRAN_SCV)
    };

    struct ProtossRace : public IRace {
        DESCRIBE_UNIT(Worker, PROTOSS_PROBE)
    };

    struct ZergRace : public IRace {
        DESCRIBE_UNIT(Worker, ZERG_DRONE)
    };

#undef DESCRIBE_UNIT

}