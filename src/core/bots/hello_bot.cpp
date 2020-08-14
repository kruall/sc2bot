#include <core/bots.h>
#include <sc2api/sc2_api.h>

#include <iostream>


struct HelloBot : public sc2::Agent {
    virtual void OnGameStart() final {
        std::cout << "Hello, World!" << std::endl;
    }

    virtual void OnStep() final {
        std::cout << Observation()->GetGameLoop() << std::endl;
    }
};


std::unique_ptr<sc2::Agent> core::CreateHelloBot() {
    return std::make_unique<HelloBot>();
}