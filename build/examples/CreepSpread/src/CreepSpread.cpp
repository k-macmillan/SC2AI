#include "CreepSpread.h"

void CreepSpread::OnGameStart() {
    std::cout << "Starting a new game (" << restarts_ << " restarts)" << std::endl;
    obs_ = Observation();
    action_ = Actions();
    map = new Map(obs_->GetGameInfo().width, obs_->GetGameInfo().height);
};

void CreepSpread::OnStep() {
    // Update globals
    obs_ = Observation();
    action_ = Actions();

    uint32_t game_loop = obs_->GetGameLoop();

    // About every second
    if ( game_loop % 22 == 0 ) {
        map->UpdateMap();
        std::cout << "Coverage: " << map->GetCoverage() * 100 << "%" << std::endl;
    }

};

void CreepSpread::OnGameEnd() {
    ++restarts_;
    std::cout << "Game ended after: " << Observation()->GetGameLoop() << " loops " << std::endl;
    if ( map != nullptr ) {
        delete map;
    }
};