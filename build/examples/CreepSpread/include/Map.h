#pragma once
#include "sc2api/sc2_common.h"
#include "AdditionsTo_s2client-api.h"


class Map {
public:
    Map(unsigned int Width, unsigned int Height);
    ~Map();

    void UpdateMap();
    float GetCoverage();

private:
    struct Node : public sc2::Point2D {
        bool creep = false;
    };

    void BuildNodes();

    Node **nodes_ = nullptr;
    unsigned int map_nodes_;
    const unsigned int width_;
    const unsigned int height_;
    float coverage_ = 0.0f;
};