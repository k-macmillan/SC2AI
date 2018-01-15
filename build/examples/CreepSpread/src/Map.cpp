#include "Map.h"
#include <iostream>

Map::Map(unsigned int Width, unsigned int Height) : width_(Width), height_(Height) {
    BuildNodes();
}


Map::~Map() {
    if ( nodes_ == nullptr )
        return;
    for ( unsigned int i = 0; i < width_; ++i )
        delete[] nodes_[i];
    delete nodes_;
}


void Map::BuildNodes() {
    nodes_ = new Node*[width_];
    for ( unsigned int i = 0; i < width_; ++i )
        nodes_[i] = new Node[height_];
    
    for ( unsigned int i = 0; i < width_; ++i ) {
        for ( unsigned int j = 0; j < height_; ++j ) {
            //sc2::Point2D pt(i + 0.0f, j + 0.0f);	// Deal with unsigned int to float warning.
            nodes_[i][j].x = float(i);
            nodes_[i][j].y = float(j);
            //nodes_[i][j].z = obs_->TerrainHeight(pt);
            //nodes_[i][j].creep = obs_->HasCreep(pt);
        }
    }
}

void Map::UpdateMap() {
    coverage_ = 0.0f;
    // Could potentially be improved by only running on nodes not checked (throw all nodes into a vector, pop on creep = true)
    for ( unsigned int i = 0; i < width_; ++i ) {
        for ( unsigned int j = 0; j < height_; ++j ) {
            //if ( obs_->GetVisibility(nodes_[i][j]) == sc2::Visibility::Visible ) {
                if ( obs_->HasCreep(nodes_[i][j]) ) {
                    nodes_[i][j].creep = true;
                    coverage_ += 1.0f;
                } else {
                    nodes_[i][j].creep = false;
                }
            //}
        }
    }
    coverage_ = coverage_ / (width_ * height_);
}

float Map::GetCoverage() {
    return coverage_;
}