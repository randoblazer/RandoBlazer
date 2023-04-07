#ifndef __WORLD_H__
#define __WORLD_H__

#include "Locations.h"
#include "ItemPool.h"
#include "LogicGraph.h"
#include "Filler.h"
#include "Random.h"

// Create some location groups for dummy fills
namespace LocationGroups {
    static LocationID BossLocations[6] = {
        LocationID::LAIR_LEOS_PAINTING_BOSS,
        LocationID::LAIR_LIGHT_SHRINE_STATUE_BOSS,
        LocationID::LAIR_GHOST_SHIP_SKULL_BOSS,
        LocationID::LAIR_LUNE_POSEIDON_BOSS,
        LocationID::LAIR_POWER_PLANT_TIN_DOLL_BOSS,
        LocationID::LAIR_RIGHT_TOWER_DEMON_BIRD_BOSS
    };
    static ItemIndex KeyNPCs[12] = {
        ItemIndex::NPC_DANCING_GRANDMA,
        ItemIndex::NPC_DANCING_GRANDMA2,
        ItemIndex::NPC_PATHFINDER_BOY,
        ItemIndex::NPC_GRANDPA_LOGS,
        ItemIndex::NPC_KING_MAGRIDD,
        ItemIndex::NPC_SOLDIER_CASTLE,
        ItemIndex::NPC_BRIDGE_GUARD,
        ItemIndex::NPC_WATER_MILL,
        ItemIndex::NPC_GRANDPA_LUNE,
        ItemIndex::NPC_MODEL_TOWN1,
        ItemIndex::NPC_MODEL_TOWN2,
        ItemIndex::NPC_SOLDIER_RIGHT_TOWER
    };
    static LocationID WaterShrineItems[7] = {
        LocationID::CHEST_WATER_SHRINE_FLOOR1_FAR_SIDE,
        LocationID::CHEST_WATER_SHRINE_FLOOR2_SPEARS,
        LocationID::CHEST_WATER_SHRINE_FLOOR2_WATERFALL,
        LocationID::CHEST_WATER_SHRINE_FLOOR3_SOUTHEAST,
        LocationID::CHEST_WATER_SHRINE_FLOOR3_SOUTHWEST,
        LocationID::SECRET_WATER_SHRINE_BASEMENT,
        LocationID::CRYSTAL_WATER_SHRINE2_SPEARS
    };
    static LocationID WaterShrineLairs[10] = {
        LocationID::LAIR_LOST_MARSH_BEFORE_WATER_1,
        LocationID::LAIR_LOST_MARSH_BEFORE_WATER_2,
        LocationID::LAIR_WATER_SHRINE_B1_CENTER,
        LocationID::LAIR_WATER_SHRINE_B2_1,
        LocationID::LAIR_WATER_SHRINE_B2_BACK,
        LocationID::LAIR_WATER_SHRINE_B2_SPEARS,
        LocationID::LAIR_WATER_SHRINE_B3_1,
        LocationID::LAIR_WATER_SHRINE_B3_STATUE_1,
        LocationID::LAIR_WATER_SHRINE_B3_STATUE_2,
        LocationID::LAIR_LOST_MARSH_BETWEEN_WATER_AND_FIRE
    };
    static LocationID FireShrineLairs[10] = {
        LocationID::LAIR_FIRE_SHRINE_B1,
        LocationID::LAIR_FIRE_SHRINE_B2_SOUTH,
        LocationID::LAIR_FIRE_SHRINE_B2_SOUTHEAST,
        LocationID::LAIR_FIRE_SHRINE_B2_NORTHWEST,
        LocationID::LAIR_FIRE_SHRINE_B2_BACK,
        LocationID::LAIR_FIRE_SHRINE_B3_1,
        LocationID::LAIR_FIRE_SHRINE_B3_2,
        LocationID::LAIR_FIRE_SHRINE_B3_3,
        LocationID::LAIR_FIRE_SHRINE_B3_4,
        LocationID::LAIR_FIRE_SHRINE_B3_5
    };
    static LocationID TortureChamberLairs[12] = {
        LocationID::LAIR_TORTURE_CHAMBER1_CENTER,
        LocationID::LAIR_TORTURE_CHAMBER2_LEFT_1,
        LocationID::LAIR_TORTURE_CHAMBER2_LEFT_2,
        LocationID::LAIR_TORTURE_CHAMBER2_LEFT_3,
        LocationID::LAIR_TORTURE_CHAMBER2_RIGHT_1,
        LocationID::LAIR_TORTURE_CHAMBER2_RIGHT_2,
        LocationID::LAIR_TORTURE_CHAMBER2_RIGHT_3,
        LocationID::LAIR_TORTURE_CHAMBER3_LEFT,
        LocationID::LAIR_TORTURE_CHAMBER3_CENTER_LOWER,
        LocationID::LAIR_TORTURE_CHAMBER3_CENTER_UPPER,
        LocationID::LAIR_TORTURE_CHAMBER3_RIGHT_BOTTOM,
        LocationID::LAIR_TORTURE_CHAMBER3_RIGHT_TOP
    };
    static LocationID MagriddChests[8] = {
        // LocationID::CHEST_TORTURE_CHAMBER1_LEFT,
        // LocationID::CHEST_TORTURE_CHAMBER1_TOP_RIGHT,
        // LocationID::SECRET_TORTURE_CHAMBER1_TOP_RIGHT,
        LocationID::CHEST_TORTURE_CHAMBER2_MIDDLE_INVISIBLE,
        LocationID::CHEST_TORTURE_CHAMBER2_SOUTHWEST_INVISIBLE,
        LocationID::CHEST_TORTURE_CHAMBER2_NORTH_INVISIBLE,
        LocationID::CHEST_TORTURE_CHAMBER3_NORTHWEST,
        LocationID::CHEST_RIGHT_TOWER2_LEFT,
        LocationID::CHEST_RIGHT_TOWER2_RIGHT,
        LocationID::CHEST_RIGHT_TOWER3_BOTTOM_RIGHT,
        LocationID::CHEST_RIGHT_TOWER3_TOP_LEFT
    };
    static LocationID WorldOfEvilChests[6] = {
        LocationID::CHEST_WORLD_OF_EVIL1_LEFT,
        LocationID::CHEST_WORLD_OF_EVIL1_RIGHT,
        LocationID::CHEST_WORLD_OF_EVIL1_TELEPORTER,
        LocationID::CHEST_WORLD_OF_EVIL2_RIGHT,
        LocationID::CHEST_WORLD_OF_EVIL3_LEFT,
        LocationID::CHEST_WORLD_OF_EVIL3_RIGHT
    };
}

class WorldFlags {
public:
    WorldFlags ();
    ~WorldFlags ();

    bool blesterMetal;
    bool dureanMetal;

/*
    // Other ideas?
    bool superHotLava;
    bool swordShuffle;
*/

    void roll (); // pass in rando options later
};

class WorldMap {
public:
    WorldMap ();
    ~WorldMap ();

    WorldFlags* worldFlags;
    LogicMap* map;

    Filler::PlacementSet progressionItems;
    Filler::PlacementSet equipmentItems;
    Filler::PlacementSet extraItems;
    Filler::PlacementSet extraNpcs;

    void createWorld (WorldFlags& creationFlags);
};

void logMap (WorldMap& map);
void testTheWorld (WorldFlags& worldFlags);

#endif // __WORLD_H__
