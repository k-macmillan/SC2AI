#pragma once
#include "sc2api/sc2_api.h"   // Link to API
#include "sc2lib/sc2_lib.h"   // FindRandomLocation()
#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_agent.h"

#include "Map.h"

#include <iostream>   // cout statements

class CreepSpread : public sc2::Agent {
public:
    uint32_t restarts_;

    CreepSpread() :
        restarts_(0) {
    }
    ~CreepSpread() {
        if ( map != nullptr ) {
            delete map;
        }
    };

    virtual void OnGameStart() final;

    virtual void OnStep() final;

    virtual void OnGameEnd() final;

private:
    Map *map = nullptr;
};

//#include "sc2api/sc2_interfaces.h"
//#include "sc2api/sc2_agent.h"
//#include "sc2api/sc2_map_info.h"