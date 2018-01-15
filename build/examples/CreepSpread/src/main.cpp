#include "CreepSpread.h"
#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"


//*************************************************************************************************
int main(int argc, char* argv[]) {
    sc2::Coordinator coordinator;
    if ( !coordinator.LoadSettings(argc, argv) ) {
        return 1;
    }

    // Add the custom bot, it will control the players.
    CreepSpread bot;

    coordinator.SetParticipants({
        CreateParticipant(sc2::Race::Zerg, &bot),
        CreateComputer(sc2::Race::Terran, sc2::Difficulty::VeryEasy)
    });

    // Start the game.
    coordinator.LaunchStarcraft();

    std::vector<std::string> maps;

    //maps.push_back("Ladder2017Season3/OdysseyLE.SC2Map");            // Vespecne Geysers break the expansion query
    maps.push_back("Ladder2017Season3/AbyssalReefLE.SC2Map");
    //maps.push_back("Ladder2017Season3/AcolyteLE.SC2Map");
    //maps.push_back("Ladder2017Season3/AscensiontoAiurLE.SC2Map");
    //maps.push_back("Ladder2017Season3/InterloperLE.SC2Map");
    //maps.push_back("Ladder2017Season3/MechDepotLE.SC2Map");

    //maps.push_back("Ladder2017Season2/AscensiontoAiurLE.SC2Map");
    //maps.push_back("Ladder2017Season2/BloodBoilLE.SC2Map");
    //maps.push_back("Ladder2017Season2/DefendersLandingLE.SC2Map");
    //maps.push_back("Ladder2017Season2/ProximaStationLE.SC2Map");
    //maps.push_back("Ladder2017Season2/SequencerLE.SC2Map");          // Vespecne Geysers break the expansion query 

    //maps.push_back("Ladder2017Season1/AbyssalReefLE.SC2Map");
    //maps.push_back("Ladder2017Season1/PaladinoTerminalLE.SC2Map");
    //maps.push_back("Ladder2017Season1/ProximaStationLE.SC2Map");
    //maps.push_back("Ladder2017Season1/PaladinoTerminalLE.SC2Map");
    //maps.push_back("Ladder2017Season1/AbyssalReefLE.SC2Map");





    while ( true ) {
        std::string map = maps[sc2::GetRandomInteger(0, int(maps.size()) - 1)];
        std::string map_name = map.substr(18);
        map_name = map_name.substr(0, map_name.size() - 7);
        std::cout << "\nMap: " << map_name << std::endl;
        coordinator.StartGame(map.c_str());
        //coordinator.StartGame("Ladder2017Season3/AbyssalReefLE.SC2Map");
        while ( coordinator.Update()) {}
    }

    return 0;
}
