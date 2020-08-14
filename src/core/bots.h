#pragma once

#include <sc2api/sc2_agent.h>

#include <memory>

namespace core {

    std::unique_ptr<sc2::Agent> CreateHelloBot();

    std::unique_ptr<sc2::Agent> CreateNoMineralsBot();

}