#include "AdditionsTo_s2client-api.h"

const sc2::ObservationInterface* obs_;
sc2::QueryInterface* query_;
sc2::ActionInterface* action_;

/*! Function to calculate a unit vector and append the source point to the values
*/
const sc2::Point2D UnitVector(const sc2::Point2D &source, const sc2::Point2D &dest, float multiplier) {
    float dist = Distance2D(dest, source);
    sc2::Point2D unit_vector(( dest.x - source.x ) / dist, ( dest.y - source.y ) / dist);
    unit_vector.x = ( unit_vector.x * multiplier ) + source.x;
    unit_vector.y = ( unit_vector.y * multiplier ) + source.y;
    return unit_vector;
}

const sc2::Unit* FindNearestMineralPatch(const sc2::Point2D& start) {
    sc2::Units minerals = obs_->GetUnits(sc2::Unit::Alliance::Neutral, IsMineralField());

    float distance = std::numeric_limits<float>::max();
    const sc2::Unit* target = nullptr;
    for ( const auto& u : minerals ) {
        float d = DistanceSquared2D(u->pos, start);
        if ( d < distance ) {
            distance = d;
            target = u;
        }
    }
    return target;
}

const sc2::Unit* FindNearestGeyser(const sc2::Point2D &position) {
    // Instead use closest to UnitVector(base, expansion)?
    float minimum_distance = 20.0f;
    sc2::Tag closestGeyser = 0;
    for ( const auto& geyser : obs_->GetUnits(sc2::Unit::Alliance::Neutral, IsVespeneGeyser()) ) {
        float current_distance = sc2::Distance2D(position, geyser->pos);
        if ( current_distance < minimum_distance ) {
            if ( query_->Placement(sc2::ABILITY_ID::BUILD_EXTRACTOR, geyser->pos) ) {
                minimum_distance = current_distance;
                closestGeyser = geyser->tag;
            }
        }
    }
    return obs_->GetUnit(closestGeyser);
}

/*! Returns the path distance between a unit and a target Point2D
*/
float PathDist(const sc2::Unit *unit, const sc2::Point2D &target) {
    float ret_val = query_->PathingDistance(unit, target);
    return  ret_val > 0.1f ? ret_val : std::numeric_limits<float>::max();
}

/*! Returns the closest expansion to the given unit by pathing distance
*/
sc2::Point3D ClosestExpansion(const std::vector<sc2::Point3D> &expansions, const sc2::Unit *unit) {
    if ( unit == nullptr )
        return sc2::Point3D(0, 0, 0);

    float minimum_distance = std::numeric_limits<float>::max();
    sc2::Point3D closest_expansion = expansions[0];
    for ( const auto& expansion : expansions ) {
        float current_distance = PathDist(unit, sc2::Point2D(expansion));
        if ( current_distance < .01f ) {
            // Should never make it here...maybe if there is already a base? Should clear expansions of it then...
            continue;
        }

        if ( current_distance < minimum_distance ) {
            if ( query_->Placement(sc2::ABILITY_ID::BUILD_HATCHERY, expansion) ) {
                closest_expansion = expansion;
                minimum_distance = current_distance;
            }
        }
    }
    return closest_expansion;
}





/*! NOT for finding best expansion location, for finding closest expansion zone to the given unit, by pathing distance.
*/
sc2::Point3D ClosestExpansionLocation(const std::vector<sc2::Point3D> &expansions, const sc2::Unit *unit) {
    if ( unit == nullptr )
        return sc2::Point3D(0, 0, 0);

    float minimum_distance = std::numeric_limits<float>::max();
    sc2::Point3D closest_expansion = expansions[0];
    for ( const auto& expansion : expansions ) {
        sc2::Point2D exp_right = expansion;
        exp_right.x += 2.76f;  // Radius of a townhall + .01
        float current_distance = PathDist(unit, exp_right);
        if ( current_distance < .01f ) {
            // Should never make it here...maybe if there is already a base? Should clear expansions of it then...
            continue;
        }

        if ( current_distance > 16.0f && current_distance < minimum_distance ) {
            closest_expansion = expansion;
            minimum_distance = current_distance;
        }
    }
    return closest_expansion;
}






/* Checks to see if a group of units
*/
bool PerformingAbility(const sc2::Units &units, sc2::ABILITY_ID ability) {
    for ( const auto &unit : units ) {
        if ( ContainsOrder(unit, ability) )
            return true;
    }
    return false;
}


/* Determines if a unit has an ability in the orders vector
*/
bool ContainsOrder(const sc2::Unit* unit, const sc2::ABILITY_ID &ability) {
    for ( const auto &item : unit->orders ) {
        if ( item.ability_id == ability )
            return true;
    }
    return false;
}


/* Returns number of specified unit type
*/
size_t CountUnitType(const sc2::UNIT_TYPEID &unit_type) {
    return obs_->GetUnits(sc2::Unit::Alliance::Self, sc2::IsUnit(unit_type)).size();
}

/* Gets the corners of a point given a radius
*/
std::vector<sc2::Point3D> GetCorners(const sc2::Point3D &pos, const float &radius) {
    float dist = sqrt(radius / 2.0f);
    std::vector<sc2::Point3D> corners(4, pos);
    corners[0].x += dist;
    corners[0].y += dist;
    corners[1].x += dist;
    corners[1].y -= dist;
    corners[2].x -= dist;
    corners[2].y += dist;
    corners[3].x -= dist;
    corners[3].y -= dist;
    return corners;
}


const sc2::Unit* NearestUnitOfType(sc2::UNIT_TYPEID type, const sc2::Point2D &point, sc2::Unit::Alliance alliance) {
    sc2::Units units = obs_->GetUnits(alliance, sc2::IsUnit(type));
    float min_dist = std::numeric_limits<float>::max();
    float dist = 0.0f;
    const sc2::Unit* ret_val = nullptr;

    for ( const auto &unit : units ) {
        dist = sc2::Distance2D(unit->pos, point);
        if ( dist < min_dist ) {
            min_dist = dist;
            ret_val = unit;
        }
    }
    return ret_val;
}


const sc2::Unit* NearestUnit(const sc2::Point2D &point, sc2::Unit::Alliance alliance) {
    sc2::Units units = obs_->GetUnits(alliance);
    float min_dist = std::numeric_limits<float>::max();
    float dist = 0.0f;
    const sc2::Unit* ret_val = nullptr;

    for ( const auto &unit : units ) {
        dist = sc2::Distance2D(unit->pos, point);
        if ( dist < min_dist ) {
            min_dist = dist;
            ret_val = unit;
        }
    }
    return ret_val;
}


bool InUnits(const sc2::Units &units, const sc2::Unit* unit) {
    for ( const auto &sc2unit : units ) {
        if ( sc2unit->tag == unit->tag ) {
            return true;
        }
    }
    return false;
}

