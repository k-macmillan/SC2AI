#ifndef ADDITIONSTO_S2CLIENT_API_H
#define ADDITIONSTO_S2CLIENT_API_H

#include "sc2api/sc2_api.h"

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////// GLOBALS //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/* ! Link to the ObservationInterface global */
extern const sc2::ObservationInterface* obs_;

/* ! Link to the QueryInterface global */
extern sc2::QueryInterface* query_;

/* ! Link to the ActionInterface global */
extern sc2::ActionInterface* action_;

/////////////////////////////////////////////////////////////////////////////


/*! Takes two points and returns a unit vector from the source location. Could Overload to skip multiplier.
*/
const sc2::Point2D UnitVector(const sc2::Point2D &source, const sc2::Point2D &dest, float multiplier = 1.0f);

/*! Finds the mineral patch nearest a Point2D
*/
const sc2::Unit* FindNearestMineralPatch(const sc2::Point2D& start);

/*! Finds the vespene geyser nearest a Point2D
*/
const sc2::Unit* FindNearestGeyser(const sc2::Point2D &position);

/*! Returns the path distance between a unit and a target Point2D
*/
float PathDist(const sc2::Unit *unit, const sc2::Point2D &target);

/*! Returns the closest expansion to the given unit by pathing distance
*/
sc2::Point3D ClosestExpansion(const std::vector<sc2::Point3D> &expansions, const sc2::Unit *unit);
sc2::Point3D ClosestExpansionLocation(const std::vector<sc2::Point3D> &expansions, const sc2::Unit *unit);



/* Checks to see if a group of units
*/
bool PerformingAbility(const sc2::Units &units, sc2::ABILITY_ID ability);

/* Determines if a unit has an ability in the orders vector
*/
bool ContainsOrder(const sc2::Unit* unit, const sc2::ABILITY_ID &ability);

/* Returns number of specified unit type
*/
size_t CountUnitType(const sc2::UNIT_TYPEID &unit_type);

/* Gets the corners of a point given a radius
*/
std::vector<sc2::Point3D> GetCorners(const sc2::Point3D &pos, const float &radius);

/* ! Gets closest unit of type to a point
*/
const sc2::Unit* NearestUnitOfType(sc2::UNIT_TYPEID type, const sc2::Point2D &point, sc2::Unit::Alliance alliance = sc2::Unit::Alliance::Self);

/* ! Finds nearest unit regardless of type
*/
const sc2::Unit* NearestUnit(const sc2::Point2D &point, sc2::Unit::Alliance alliance = sc2::Unit::Alliance::Self);

/* ! Returns true if unit is in units
*/
bool InUnits(const sc2::Units &units, const sc2::Unit* unit);



struct IsTownHall {
    bool operator()(const sc2::Unit& unit) {
        switch ( unit.unit_type.ToType() ) {
        case sc2::UNIT_TYPEID::ZERG_HATCHERY: return true;
        case sc2::UNIT_TYPEID::ZERG_LAIR: return true;
        case sc2::UNIT_TYPEID::ZERG_HIVE: return true;
        case sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER: return true;
        case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND: return true;
        case sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING: return true;
        case sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS: return true;
        case sc2::UNIT_TYPEID::PROTOSS_NEXUS: return true;
        default: return false;
        }
    }
};


struct IsVespeneGeyser {
    bool operator()(const sc2::Unit& unit) {
        switch ( unit.unit_type.ToType() ) {
        case sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_PURIFIERVESPENEGEYSER: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_SHAKURASVESPENEGEYSER: return true;
        default: return false;
        }
    }
};

struct IsMineralField {
    bool operator()(const sc2::Unit& unit) {
        switch ( unit.unit_type.ToType() ) {
        case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD: return true;
        case sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD750: return true;
        default: return false;
        }
    }
};

struct IsWorker {
    bool operator()(const sc2::Unit& unit) {
        switch ( unit.unit_type.ToType() ) {
        case sc2::UNIT_TYPEID::ZERG_DRONE: return true;
        case sc2::UNIT_TYPEID::PROTOSS_PROBE: return true;
        case sc2::UNIT_TYPEID::TERRAN_SCV: return true;
        default: return false;
        }
    }
};

struct IsZerg {
    bool operator()(const sc2::Unit& unit) {
        switch ( unit.unit_type.ToType() ) {
        case sc2::UNIT_TYPEID::ZERG_DRONE: return true;
        case sc2::UNIT_TYPEID::ZERG_ZERGLING: return true;
        case sc2::UNIT_TYPEID::ZERG_OVERLORD: return true;
        case sc2::UNIT_TYPEID::ZERG_HATCHERY: return true;
            // etc...
        default: return false;
        }
    }
};


#endif
