#include <core/bots.h>
#include <sc2api/sc2_api.h>

#include <iostream>


using namespace sc2;


int main(int argc, char* argv[]) {
    Coordinator coordinator;
    coordinator.LoadSettings(argc, argv);

    std::unique_ptr<Agent> bot = core::CreateHelloBot();
    coordinator.SetParticipants({
        CreateParticipant(Race::Terran, bot.get()),
        CreateComputer(Race::Zerg)
    });

    coordinator.LaunchStarcraft();
    coordinator.StartGame();

    while (coordinator.Update()) {
    }

    return 0;
}