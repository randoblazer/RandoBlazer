#include "World.h"

#include "Locations.h"
#include "ItemPool.h"
#include "LogicGraph.h"
#include "Filler.h"
#include "Random.h"

#include <iostream>

using namespace std;

WorldFlags::WorldFlags () {}
WorldFlags::~WorldFlags () {}

void WorldFlags::roll () {
    blesterMetal = Random::RandomInteger(5) != 0;
    dureanMetal = Random::RandomInteger(3) == 0;
}

WorldMap::WorldMap () {
    worldFlags = NULL;
    map = NULL;
    progressionItems.clear();
    equipmentItems.clear();
    extraItems.clear();
    extraNpcs.clear();
}
WorldMap::~WorldMap () {
    if (map != NULL) {
        delete map->map;
        delete map;
    }
}

void WorldMap::createWorld (WorldFlags& creationFlags) {
    worldFlags = &creationFlags;

    /*
        Act I: Grass Valley
    */
    MapNode* grassValley = (new MapNode())
        ->addLocation(LocationID::NPC_TRIAL_MAGICIAN)
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_FIRST)
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_SECOND)
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_THIRD)
        ->addLocation(LocationID::CRYSTAL_UNDERGROUND_CASTLE)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_1)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_2)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_3)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_4)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_5)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_6);
    MapNode* miningSite2 = (new MapNode())
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_ELEVATOR_TOP)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_1)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_2)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_3)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_4)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_5)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_6)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_7)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_8)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_9);
    MapNode* miningSite2Lisa = (new MapNode())
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_LISA)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_LISA);
    MapNode* leosPainting = (new MapNode())
        ->addLocation(LocationID::CHEST_LEOS_PAINTING_FIRST)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING1_1)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING1_2)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING2_1)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING3_1)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING3_2)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING3_3)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING4_1)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING_BOSS);
    MapNode* leosPaintingMetal = (new MapNode())
        ->addLocation(LocationID::CHEST_LEOS_PAINTING_METAL)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING3_METAL)
        ->addLocation(LocationID::LAIR_LEOS_PAINTING4_METAL);

    equipmentItems.add(ItemIndex::IRON_ARMOR);
    extraItems.add(ItemIndex::GEMS_EXP_50);
    extraItems.add(ItemIndex::GEMS_EXP_12);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    progressionItems.add(ItemIndex::DREAM_ROD);
    progressionItems.add(ItemIndex::LEOS_BRUSH);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    equipmentItems.add(ItemIndex::TORNADO);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    progressionItems.add(ItemIndex::EMBLEM_A);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    extraItems.add(ItemIndex::GOATS_FOOD);
    progressionItems.add(ItemIndex::PASS);
    extraItems.add(ItemIndex::STRANGE_BOTTLE);
    progressionItems.add(ItemIndex::BROWN_STONE);
    equipmentItems.add(ItemIndex::FLAME_BALL);
    equipmentItems.add(ItemIndex::RECOVERY_SWORD);
    extraItems.add(ItemIndex::GEMS_EXP_80);
    extraItems.add(ItemIndex::GEMS_EXP_40);
    progressionItems.add(ItemIndex::NPC_OLD_WOMAN);
    progressionItems.add(ItemIndex::NPC_TOOL_SHOP_OWNER);
    extraNpcs.add(ItemIndex::NPC_TULIP);
    progressionItems.add(ItemIndex::NPC_BRIDGE_GUARD);
    progressionItems.add(ItemIndex::NPC_IVY_CHEST_ROOM);
    progressionItems.add(ItemIndex::NPC_WATER_MILL);
    extraNpcs.add(ItemIndex::NPC_OLD_MAN2);
    progressionItems.add(ItemIndex::NPC_GOAT_HERB);
    progressionItems.add(ItemIndex::NPC_LISA);
    extraNpcs.add(ItemIndex::NPC_TULIP2);
    progressionItems.add(ItemIndex::NPC_ARCHITECT);
    extraNpcs.add(ItemIndex::NPC_IVY2);
    progressionItems.add(ItemIndex::NPC_TEDDY);
    extraNpcs.add(ItemIndex::NPC_GOAT);
    extraNpcs.add(ItemIndex::NPC_TULIP3);
    progressionItems.add(ItemIndex::NPC_LEOS_HOUSE);
    extraNpcs.add(ItemIndex::NPC_OLD_MAN);
    extraNpcs.add(ItemIndex::NPC_TULIP4);
    extraNpcs.add(ItemIndex::NPC_LONELY_GOAT);
    progressionItems.add(ItemIndex::NPC_IVY);
    extraNpcs.add(ItemIndex::NPC_GOAT2);
    extraNpcs.add(ItemIndex::NPC_BOY_CABIN);
    progressionItems.add(ItemIndex::NPC_TULIP_PASS);
    progressionItems.add(ItemIndex::NPC_IVY_EMBLEM_A);
    progressionItems.add(ItemIndex::NPC_BOY_CAVE);
    progressionItems.add(ItemIndex::NPC_IVY_RECOVERY_SWORD);
    progressionItems.add(ItemIndex::NPC_VILLAGE_CHIEF);

    // Combat area links
    MapNode* acrossBridge = (new MapNode());
    grassValley->addLink(new MapLink(grassValley, acrossBridge,
        (new LinkReqCheck(ItemIndex::NPC_BRIDGE_GUARD))
    ));
    grassValley->addLink((new MapLink(grassValley, miningSite2, 
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_BRIDGE_GUARD))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_WATER_MILL))
    )));
    miningSite2->addLink((new MapLink(miningSite2, miningSite2Lisa, 
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_LISA))
            ->addReq(new LinkReqCheck(ItemIndex::DREAM_ROD))
    )));
    acrossBridge->addLink((new MapLink(acrossBridge, leosPainting, 
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_ARCHITECT))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_LEOS_HOUSE))
            ->addReq(new LinkReqCheck(ItemIndex::LEOS_BRUSH))
    )));
    leosPainting->addLink((new MapLink(leosPainting, leosPaintingMetal, 
        (new LinkReqCheck(ItemIndex::ZANTETSU_SWORD))
    )));

    // NPC item links
    grassValley->addLink(new MapLink(grassValley, 
        (new MapNode())->addLocation(LocationID::NPC_VILLAGE_CHIEF),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_VILLAGE_CHIEF))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_OLD_WOMAN))
    ));
    grassValley->addLink(new MapLink(grassValley, 
        (new MapNode())->addLocation(LocationID::NPC_TOOL_SHOP_OWNER),
        (new LinkReqCheck(ItemIndex::NPC_TOOL_SHOP_OWNER))
    ));
    grassValley->addLink(new MapLink(grassValley, 
        (new MapNode())->addLocation(LocationID::NPC_TEDDY),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_TOOL_SHOP_OWNER))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_TEDDY))
    ));
    acrossBridge->addLink(new MapLink(acrossBridge,
        (new MapNode())
            ->addLocation(LocationID::CHEST_GRASS_VALLEY_HYPE_LEFT)
            ->addLocation(LocationID::CHEST_GRASS_VALLEY_HYPE_RIGHT)
            ->addLocation(LocationID::CRYSTAL_GRASS_VALLEY_HYPE),
        (new LinkReqCheck(ItemIndex::NPC_IVY_CHEST_ROOM))
    ));
    acrossBridge->addLink(new MapLink(acrossBridge, 
        (new MapNode())->addLocation(LocationID::SECRET_HIDEOUT),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_BOY_CAVE))
            ->addReq(new LinkReqCheck(ItemIndex::PASS))
    ));
    acrossBridge->addLink(new MapLink(acrossBridge, 
        (new MapNode())->addLocation(LocationID::CRYSTAL_HIDEOUT),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_BOY_CAVE))
            ->addReq(new LinkReqCheck(ItemIndex::PASS))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_IVY_RECOVERY_SWORD))
    ));
    acrossBridge->addLink(new MapLink(acrossBridge, 
        (new MapNode())->addLocation(LocationID::SECRET_GOAT_PEN),
        (new LinkReqCheck(ItemIndex::NPC_GOAT_HERB))
    ));
    acrossBridge->addLink(new MapLink(acrossBridge, 
        (new MapNode())->addLocation(LocationID::SECRET_UNDER_TULIP),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_IVY))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_TULIP_PASS))
    ));
    acrossBridge->addLink(new MapLink(acrossBridge, 
        (new MapNode())->addLocation(LocationID::SECRET_SOUTHEAST_IVY),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_IVY))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_IVY_EMBLEM_A))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_WATER_MILL))
    ));

    /*
        Act II: Greenwood
    */
    MapNode* greenwood = (new MapNode())
        ->addLocation(LocationID::LAIR_LOST_MARSH_BEFORE_WATER_1)
        ->addLocation(LocationID::LAIR_LOST_MARSH_BEFORE_WATER_2)
        ->addLocation(LocationID::LAIR_WATER_SHRINE_B1_CENTER)
        ->addLocation(LocationID::LAIR_WATER_SHRINE_B2_1)
        ->addLocation(LocationID::LAIR_WATER_SHRINE_B2_SPEARS)
        ->addLocation(LocationID::LAIR_WATER_SHRINE_B2_BACK)
        ->addLocation(LocationID::LAIR_WATER_SHRINE_B3_1)
        ->addLocation(LocationID::LAIR_WATER_SHRINE_B3_STATUE_1)
        ->addLocation(LocationID::LAIR_WATER_SHRINE_B3_STATUE_2)
        ->addLocation(LocationID::CHEST_WATER_SHRINE_FLOOR1_FAR_SIDE)
        ->addLocation(LocationID::CHEST_WATER_SHRINE_FLOOR2_WATERFALL)
        ->addLocation(LocationID::CHEST_WATER_SHRINE_FLOOR2_SPEARS)
        ->addLocation(LocationID::CHEST_WATER_SHRINE_FLOOR3_SOUTHWEST)
        ->addLocation(LocationID::CHEST_WATER_SHRINE_FLOOR3_SOUTHEAST)
        ->addLocation(LocationID::SECRET_WATER_SHRINE_BASEMENT)
        ->addLocation(LocationID::CRYSTAL_WATER_SHRINE2_SPEARS);
    MapNode* fireShrine = (new MapNode())
        ->addLocation(LocationID::LAIR_LOST_MARSH_BETWEEN_WATER_AND_FIRE)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B1)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B2_NORTHWEST)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B2_SOUTH)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B2_SOUTHEAST)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B2_BACK)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B3_1)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B3_2)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B3_3)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B3_4)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B3_5)
        ->addLocation(LocationID::CHEST_FIRE_SHRINE_FLOOR1)
        ->addLocation(LocationID::CHEST_FIRE_SHRINE_FLOOR2_DISAPPEARING)
        ->addLocation(LocationID::CHEST_FIRE_SHRINE_FLOOR3_FIRST)
        ->addLocation(LocationID::CHEST_FIRE_SHRINE_FLOOR3_SECOND)
        ->addLocation(LocationID::CRYSTAL_FIRE_SHRINE_BASEMENT);
    MapNode* fireShrineMetal = (new MapNode())
        ->addLocation(LocationID::CRYSTAL_FIRE_SHRINE_FLOOR1_METAL)
        ->addLocation(LocationID::CHEST_FIRE_SHRINE_FLOOR2_METAL)
        ->addLocation(LocationID::LAIR_FIRE_SHRINE_B3_METAL);
    MapNode* lightShrine = (new MapNode())
        ->addLocation(LocationID::LAIR_LOST_MARSH_AFTER_FIRE_1)
        ->addLocation(LocationID::LAIR_LOST_MARSH_AFTER_FIRE_2)
        ->addLocation(LocationID::LAIR_LIGHT_SHRINE_B1)
        ->addLocation(LocationID::LAIR_LIGHT_SHRINE_B2_1)
        ->addLocation(LocationID::LAIR_LIGHT_SHRINE_B2_2)
        ->addLocation(LocationID::LAIR_LIGHT_SHRINE_STATUE_BOSS)
        ->addLocation(LocationID::CRYSTAL_LOST_MARSH_END);
    MapNode* lightShrineSpirit = (new MapNode())
        ->addLocation(LocationID::LAIR_LIGHT_SHRINE_B2_SPIRIT)
        ->addLocation(LocationID::CHEST_LIGHT_SHRINE_FLOOR1_SPIRIT);

    equipmentItems.add(ItemIndex::ICE_ARMOR);
    progressionItems.add(ItemIndex::MOLES_RIBBON);
    extraItems.add(ItemIndex::GEMS_EXP_50);
    extraItems.add(ItemIndex::GEMS_EXP_150);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    progressionItems.add(ItemIndex::DELICIOUS_SEEDS);
    extraItems.add(ItemIndex::GEMS_EXP_50);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    extraItems.add(ItemIndex::NOTHING);
    extraItems.add(ItemIndex::STRANGE_BOTTLE);
    extraItems.add(ItemIndex::GEMS_EXP_100);
    extraItems.add(ItemIndex::GEMS_EXP_60);
    equipmentItems.add(ItemIndex::FLAME_PILLAR);
    progressionItems.add(ItemIndex::RED_HOT_MIRROR);
    equipmentItems.add(ItemIndex::MAGIC_BELL);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    progressionItems.add(ItemIndex::GREEN_STONE);
    progressionItems.add(ItemIndex::GREENWOOD_LEAF);
    equipmentItems.add(ItemIndex::SHIELD_BRACELET);
    equipmentItems.add(ItemIndex::PSYCHO_SWORD);
    progressionItems.add(ItemIndex::EMBLEM_C);
    extraItems.add(ItemIndex::STRANGE_BOTTLE);
    equipmentItems.add(ItemIndex::LIGHT_ARROW);
    extraItems.add(ItemIndex::GEMS_EXP_150);
    extraItems.add(ItemIndex::GEMS_EXP_180);
    extraItems.add(ItemIndex::GEMS_EXP_1);
    extraNpcs.add(ItemIndex::NPC_BIRD);
    extraNpcs.add(ItemIndex::NPC_DOG);
    extraNpcs.add(ItemIndex::NPC_DOG2);
    progressionItems.add(ItemIndex::NPC_MOLE_SHIELD_BRACELET);
    progressionItems.add(ItemIndex::NPC_DOG3);
    progressionItems.add(ItemIndex::NPC_SQUIRREL_PSYCHO_SWORD);
    extraNpcs.add(ItemIndex::NPC_BIRD2);
    progressionItems.add(ItemIndex::NPC_MOLE_SOUL_OF_LIGHT);
    progressionItems.add(ItemIndex::NPC_DEER);
    progressionItems.add(ItemIndex::NPC_CROCODILE);
    extraNpcs.add(ItemIndex::NPC_SQUIRREL);
    progressionItems.add(ItemIndex::NPC_MOLE);
    extraNpcs.add(ItemIndex::NPC_DOG4);
    extraNpcs.add(ItemIndex::NPC_DOG5);
    progressionItems.add(ItemIndex::NPC_CROCODILE2);
    progressionItems.add(ItemIndex::NPC_SQUIRREL_ICE_ARMOR);
    extraNpcs.add(ItemIndex::NPC_SQUIRREL2);
    extraNpcs.add(ItemIndex::NPC_MOLE2);
    progressionItems.add(ItemIndex::NPC_SQUIRREL3);
    progressionItems.add(ItemIndex::NPC_BIRD_GREENWOOD_LEAF);
    progressionItems.add(ItemIndex::NPC_MOLE3);
    progressionItems.add(ItemIndex::NPC_DEER_MAGIC_BELL);
    extraNpcs.add(ItemIndex::NPC_BIRD3);
    progressionItems.add(ItemIndex::NPC_SQUIRREL_EMBLEM_C);
    progressionItems.add(ItemIndex::NPC_CROCODILE3);
    progressionItems.add(ItemIndex::NPC_MONMO);
    progressionItems.add(ItemIndex::NPC_BIRD_RED_HOT_MIRROR);
    progressionItems.add(ItemIndex::NPC_GREENWOODS_GUARDIAN);
    
    // combat area links
    grassValley->addLink(new MapLink(grassValley, greenwood,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_VILLAGE_CHIEF))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_OLD_WOMAN))
    ));
    greenwood->addLink(new MapLink(greenwood, fireShrine,
        (new LinkReqFree())
    ));
    fireShrine->addLink(new MapLink(fireShrine, fireShrineMetal,
        (new LinkReqCheck(ItemIndex::ZANTETSU_SWORD))
    ));
    fireShrine->addLink(new MapLink(fireShrine, lightShrine,
        (new LinkReqCheck(ItemIndex::GREENWOOD_LEAF))
    ));
    lightShrine->addLink(new MapLink(lightShrine, lightShrineSpirit,
        (new LinkReqCheck(ItemIndex::SPIRIT_SWORD))
    ));

    // NPC item links
    greenwood->addLink(new MapLink(greenwood, 
        (new MapNode())->addLocation(LocationID::NPC_GREENWOOD_GUARDIAN),
        (new LinkReqCheck(ItemIndex::NPC_GREENWOODS_GUARDIAN))
    ));
    greenwood->addLink(new MapLink(greenwood, 
        (new MapNode())->addLocation(LocationID::NPC_RED_HOT_BIRD),
        (new LinkReqCheck(ItemIndex::NPC_BIRD_RED_HOT_MIRROR))
    ));
    greenwood->addLink(new MapLink(greenwood,
        (new MapNode())->addLocation(LocationID::NPC_WOODSTIN_TRIO),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DEER))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_SQUIRREL3))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DOG3))
    ));
    greenwood->addLink(new MapLink(greenwood,
        (new MapNode())->addLocation(LocationID::NPC_NUT_SQUIRREL_TRADE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_SQUIRREL_PSYCHO_SWORD))
            ->addReq(new LinkReqCheck(ItemIndex::DELICIOUS_SEEDS))
    ));
    greenwood->addLink(new MapLink(greenwood,
        (new MapNode())->addLocation(LocationID::NPC_NUT_SQUIRREL_ROOMMATE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_SQUIRREL_PSYCHO_SWORD))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_SQUIRREL_EMBLEM_C))
    ));
    greenwood->addLink(new MapLink(greenwood,
        (new MapNode())->addLocation(LocationID::CHEST_GREENWOOD_MONMO_TUNNEL),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MONMO))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOLE3))
    ));
    greenwood->addLink(new MapLink(greenwood,
        (new MapNode())->addLocation(LocationID::NPC_RIBBON_TRADE_MOLE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::MOLES_RIBBON))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOLE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOLE_SHIELD_BRACELET))
    ));
    greenwood->addLink(new MapLink(greenwood,
        (new MapNode())->addLocation(LocationID::CHEST_GREENWOOD_ICE_ARMOR),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOLE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_SQUIRREL_ICE_ARMOR))
            ->addReq(new LinkReqCheck(ItemIndex::DREAM_ROD))
    ));
    greenwood->addLink(new MapLink(greenwood,
        (new MapNode())->addLocation(LocationID::SECRET_TURBOS_GRAVE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CROCODILE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CROCODILE2))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_BIRD_GREENWOOD_LEAF))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOLE_SOUL_OF_LIGHT))
            ->addReq(new LinkReqCheck(ItemIndex::DREAM_ROD))
    ));
    greenwood->addLink(new MapLink(greenwood,
        (new MapNode())->addLocation(LocationID::CRYSTAL_EMBLEM_TRADE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DEER_MAGIC_BELL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CROCODILE3))
            ->addReq(new LinkReqCheck(ItemIndex::EMBLEM_A))
            ->addReq(new LinkReqCheck(ItemIndex::EMBLEM_B))
            ->addReq(new LinkReqCheck(ItemIndex::EMBLEM_C))
            ->addReq(new LinkReqCheck(ItemIndex::EMBLEM_D))
            ->addReq(new LinkReqCheck(ItemIndex::EMBLEM_E))
            ->addReq(new LinkReqCheck(ItemIndex::EMBLEM_F))
            ->addReq(new LinkReqCheck(ItemIndex::EMBLEM_G))
            ->addReq(new LinkReqCheck(ItemIndex::EMBLEM_H))
    ));

    /*
        Act III: St Elles
    */
    MapNode* stElles = (new MapNode())
        ->addLocation(LocationID::LAIR_SOUTHERTA_1)
        ->addLocation(LocationID::LAIR_SOUTHERTA_2)
        ->addLocation(LocationID::LAIR_SOUTHERTA_3)
        ->addLocation(LocationID::LAIR_SOUTHERTA_4)
        ->addLocation(LocationID::LAIR_SOUTHERTA_5)
        ->addLocation(LocationID::CHEST_SOUTHERTA);
    MapNode* southertaBack = (new MapNode())
        ->addLocation(LocationID::LAIR_SOUTHERTA_BACK);
    MapNode* rockbird = (new MapNode())
        ->addLocation(LocationID::LAIR_SEABED_TO_ROCKBIRD)
        ->addLocation(LocationID::LAIR_ROCKBIRD_CENTER_1)
        ->addLocation(LocationID::LAIR_ROCKBIRD_CENTER_2)
        ->addLocation(LocationID::LAIR_ROCKBIRD_LEFT_1)
        ->addLocation(LocationID::LAIR_ROCKBIRD_LEFT_2)
        ->addLocation(LocationID::CHEST_ROCKBIRD_LEFT)
        ->addLocation(LocationID::CHEST_ROCKBIRD_RIGHT)
        ->addLocation(LocationID::CRYSTAL_ROCKBIRD);
    MapNode* durean = (new MapNode())
        ->addLocation(LocationID::LAIR_SEABED_TO_DUREAN)
        ->addLocation(LocationID::LAIR_DUREAN_SOUTH)
        ->addLocation(LocationID::LAIR_DUREAN_WEST)
        ->addLocation(LocationID::LAIR_DUREAN_NORTH)
        ->addLocation(LocationID::LAIR_DUREAN_NORTHEAST)
        ->addLocation(LocationID::LAIR_DUREAN_TIER2_NORTHWEST)
        ->addLocation(LocationID::LAIR_DUREAN_TIER2_NORTHEAST)
        ->addLocation(LocationID::LAIR_DUREAN_TIER3)
        ->addLocation(LocationID::CHEST_DUREAN_RIGHT_SIDE)
        ->addLocation(LocationID::CHEST_DUREAN_LAVA)
        ->addLocation(LocationID::CRYSTAL_DUREAN_SEABED_PATH);
    MapNode* dureanMetal = (new MapNode())
        ->addLocation(LocationID::LAIR_DUREAN_TIER2_METAL);
    MapNode* blester = (new MapNode())
        ->addLocation(LocationID::LAIR_SEABED_TO_BLESTER_1)
        ->addLocation(LocationID::LAIR_SEABED_TO_BLESTER_2)
        ->addLocation(LocationID::LAIR_SEABED_TO_BLESTER_3)
        ->addLocation(LocationID::LAIR_BLESTER_BOTTOM_LEFT)
        ->addLocation(LocationID::LAIR_BLESTER_BOTTOM_RIGHT)
        ->addLocation(LocationID::CRYSTAL_BLESTER_SEABED_PATH);
    MapNode* blesterMiddle = (new MapNode())
        ->addLocation(LocationID::LAIR_BLESTER_MIDDLE_LEFT)
        ->addLocation(LocationID::LAIR_BLESTER_MIDDLE_RIGHT);
    MapNode* blesterTop = (new MapNode())
        ->addLocation(LocationID::LAIR_BLESTER_TOP_LEFT);
    MapNode* ghostShip = (new MapNode())
        ->addLocation(LocationID::LAIR_SEABED_TO_GHOST_SHIP_1)
        ->addLocation(LocationID::LAIR_SEABED_TO_GHOST_SHIP_2)
        ->addLocation(LocationID::LAIR_GHOST_SHIP_SKULL_BOSS)
        ->addLocation(LocationID::CHEST_GHOST_SHIP_SEABED_PATH)
        ->addLocation(LocationID::CHEST_GHOST_SHIP_ON_SHIP);
    MapNode* secretSeaCave = (new MapNode())
        ->addLocation(LocationID::CHEST_SEABED_SECRET_BOTTOM_LEFT)
        ->addLocation(LocationID::CHEST_SEABED_SECRET_BOTTOM_RIGHT)
        ->addLocation(LocationID::CHEST_SEABED_SECRET_TOP_LEFT)
        ->addLocation(LocationID::CHEST_SEABED_SECRET_TOP_RIGHT);

    extraItems.add(ItemIndex::MERMAIDS_TEARS);
    progressionItems.add(ItemIndex::BIG_PEARL);
    progressionItems.add(ItemIndex::EMBLEM_D);
    extraItems.add(ItemIndex::GEMS_EXP_80);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    extraItems.add(ItemIndex::NOTHING);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    extraItems.add(ItemIndex::GEMS_EXP_60);
    equipmentItems.add(ItemIndex::CRITICAL_SWORD);
    extraItems.add(ItemIndex::STRANGE_BOTTLE);
    extraItems.add(ItemIndex::GEMS_EXP_1);
    equipmentItems.add(ItemIndex::POWER_BRACELET);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    progressionItems.add(ItemIndex::BUBBLE_ARMOR);
    equipmentItems.add(ItemIndex::MAGIC_FLARE);
    progressionItems.add(ItemIndex::BLUE_STONE);
    progressionItems.add(ItemIndex::RED_HOT_STICK);
    progressionItems.add(ItemIndex::THUNDER_RING);
    extraItems.add(ItemIndex::GEMS_EXP_200);
    extraItems.add(ItemIndex::GEMS_EXP_300);
    extraItems.add(ItemIndex::GEMS_EXP_250);
    progressionItems.add(ItemIndex::NPC_DOLPHIN_NORTHEAST);
    progressionItems.add(ItemIndex::NPC_MERMAID_DANCE_LEADER);
    extraNpcs.add(ItemIndex::NPC_MERMAID5);
    extraNpcs.add(ItemIndex::NPC_MERMAID6);
    progressionItems.add(ItemIndex::NPC_MERMAID_BUBBLE_ARMOR);
    progressionItems.add(ItemIndex::NPC_MERMAID_STATUE_ROCKBIRD);
    extraNpcs.add(ItemIndex::NPC_MERMAID9);
    extraNpcs.add(ItemIndex::NPC_MERMAID_TEARS);
    progressionItems.add(ItemIndex::NPC_MERMAID_MAGIC_FLARE);
    extraNpcs.add(ItemIndex::NPC_ANGELFISH_SOUL_OF_SHIELD);
    progressionItems.add(ItemIndex::NPC_MERMAID_STATUE_DUREAN);
    progressionItems.add(ItemIndex::NPC_DOLPHIN_PEARL);
    progressionItems.add(ItemIndex::NPC_LUE);
    progressionItems.add(ItemIndex::NPC_MERMAID_PEARL);
    extraNpcs.add(ItemIndex::NPC_MERMAID2);
    extraNpcs.add(ItemIndex::NPC_MERMAID_NANA);
    progressionItems.add(ItemIndex::NPC_DOLPHIN_SAVES_LUE);
    extraNpcs.add(ItemIndex::NPC_MERMAID3);
    progressionItems.add(ItemIndex::NPC_MERMAID_STATUE_BLESTER);
    progressionItems.add(ItemIndex::NPC_MERMAID_RED_HOT_STICK);
    extraNpcs.add(ItemIndex::NPC_ANGELFISH);
    extraNpcs.add(ItemIndex::NPC_ANGELFISH2);
    progressionItems.add(ItemIndex::NPC_MERMAID_NORTHEAST);
    extraNpcs.add(ItemIndex::NPC_MERMAID7);
    extraNpcs.add(ItemIndex::NPC_ANGELFISH4);
    extraNpcs.add(ItemIndex::NPC_MERMAID8);
    progressionItems.add(ItemIndex::NPC_DOLPHIN_SECRET_CAVE);
    progressionItems.add(ItemIndex::NPC_MERMAID_STATUE_GHOST_SHIP);
    extraNpcs.add(ItemIndex::NPC_ANGELFISH3);
    extraNpcs.add(ItemIndex::NPC_DOLPHIN);
    progressionItems.add(ItemIndex::NPC_MERMAID_QUEEN);

    // combat area links
    greenwood->addLink(new MapLink(greenwood, stElles,
        (new LinkReqCheck(ItemIndex::NPC_GREENWOODS_GUARDIAN))
    ));
    stElles->addLink(new MapLink(stElles, southertaBack,
        (new LinkReqCheck(ItemIndex::NPC_MERMAID_BUBBLE_ARMOR))
    ));
    stElles->addLink(new MapLink(stElles, rockbird,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::BUBBLE_ARMOR))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_STATUE_ROCKBIRD))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_BUBBLE_ARMOR))
    ));
    rockbird->addLink(new MapLink(rockbird, durean,
        (new LinkReqCheck(ItemIndex::NPC_MERMAID_STATUE_DUREAN))
    ));
    durean->addLink(new MapLink(durean, dureanMetal,
        (new LinkReqCheck(ItemIndex::ZANTETSU_SWORD))
    ));
    stElles->addLink(new MapLink(stElles, blester,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::BUBBLE_ARMOR))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_STATUE_BLESTER))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_BUBBLE_ARMOR))
    ));
    // TODO: set up bridge to top as extra metal lair 
    blester->addLink(new MapLink(blester, blesterMiddle,
        (new LinkReqFree())
    ));
    // blester->addLink(new MapLink(blester, blesterMiddle,
        // (new LinkReqOr())
            // ->addReq(new LinkReqCheck(ItemIndex::THUNDER_RING))
            // ->addReq(new LinkReqCheck(ItemIndex::ZANTETSU_SWORD))
    // ));
    blester->addLink(new MapLink(blesterMiddle, blesterTop,
        (new LinkReqOr())
            ->addReq(new LinkReqCheck(ItemIndex::THUNDER_RING))
            ->addReq(new LinkReqCheck(ItemIndex::ZANTETSU_SWORD))
    ));
    rockbird->addLink(new MapLink(rockbird, ghostShip,
        (new LinkReqCheck(ItemIndex::NPC_MERMAID_STATUE_GHOST_SHIP))
    ));
    ghostShip->addLink(new MapLink(ghostShip, secretSeaCave,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::DREAM_ROD))
            ->addReq(new LinkReqCheck(ItemIndex::BIG_PEARL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_PEARL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DOLPHIN_SECRET_CAVE))
            ->addReq((new LinkReqOr())
                ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_DANCE_LEADER))
                ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_BUBBLE_ARMOR))
            )
    ));

    // NPC item links
    MapNode* mermaidCommonHouse = (new MapNode())
        ->addLocation(LocationID::CHEST_ST_ELLES_COMMON_HOUSE)
        ->addLocation(LocationID::NPC_COMMON_HOUSE_BOTTOM_MERMAID);
    stElles->addLink(new MapLink(stElles, mermaidCommonHouse,
        (new LinkReqCheck(ItemIndex::NPC_MERMAID_BUBBLE_ARMOR))
    ));
    MapNode* stEllesLeftSide = (new MapNode());
    stElles->addLink(new MapLink(stElles, stEllesLeftSide,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_PEARL))
            ->addReq((new LinkReqOr())
                ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_DANCE_LEADER))
                ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_BUBBLE_ARMOR))
            )
    ));
    stEllesLeftSide->addLink(new MapLink(stEllesLeftSide,
        (new MapNode())->addLocation(LocationID::CHEST_ST_ELLES_LEFT_DOLPHIN),
        (new LinkReqCheck(ItemIndex::NPC_DOLPHIN_PEARL))
    ));
    stEllesLeftSide->addLink(new MapLink(stEllesLeftSide,
        (new MapNode())->addLocation(LocationID::NPC_COMMON_HOUSE_LEFT_MERMAID),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DOLPHIN_PEARL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_MAGIC_FLARE))
    ));
    stEllesLeftSide->addLink(new MapLink(stEllesLeftSide,
        (new MapNode())->addLocation(LocationID::NPC_LUE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_LUE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DOLPHIN_SAVES_LUE))
    ));
    stElles->addLink(new MapLink(stElles,
        (new MapNode())->addLocation(LocationID::NPC_NORTHEAST_HOUSE_MERMAID),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MERMAID_NORTHEAST))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DOLPHIN_NORTHEAST))
    ));
    mermaidCommonHouse->addLink(new MapLink(mermaidCommonHouse,
        (new MapNode())->addLocation(LocationID::NPC_RED_HOT_MERMAID),
        (new LinkReqCheck(ItemIndex::NPC_MERMAID_RED_HOT_STICK))
    ));
    stElles->addLink(new MapLink(stElles,
        (new MapNode())->addLocation(LocationID::NPC_MERMAID_QUEEN),
        (new LinkReqCheck(ItemIndex::NPC_MERMAID_QUEEN))
    ));

    /*
        Act IV: Mountain of Souls
    */
    MapNode* mountainHome = (new MapNode())
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_LOWER_1)
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_LOWER_2)
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_LOWER_3)
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_MIDDLE_PATH_LEFT)
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_MIDDLE_PATH_RIGHT)
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_MIDDLE_TOP)
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_SUMMIT_1)
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_SUMMIT_2)
        ->addLocation(LocationID::CHEST_MOUNTAIN_SCREEN1)
        ->addLocation(LocationID::CHEST_MOUNTAIN_HYPE_LEFTMOST)
        ->addLocation(LocationID::CHEST_MOUNTAIN_HYPE_2ND_FROM_LEFT)
        ->addLocation(LocationID::CHEST_MOUNTAIN_HYPE_2ND_FROM_RIGHT)
        ->addLocation(LocationID::CHEST_MOUNTAIN_HYPE_RIGHTMOST)
        ->addLocation(LocationID::CRYSTAL_MOUNTAIN_SUMMIT);
    MapNode* laynole = (new MapNode())
        ->addLocation(LocationID::LAIR_MOUNTAIN_SLOPE_SUMMIT_ICE)
        ->addLocation(LocationID::LAIR_ICE_HILL_1)
        ->addLocation(LocationID::LAIR_ICE_HILL_2)
        ->addLocation(LocationID::LAIR_ICE_HILL_3)
        ->addLocation(LocationID::LAIR_ICE_HILL_4)
        ->addLocation(LocationID::LAIR_ICE_HILL_5)
        ->addLocation(LocationID::LAIR_ICE_HILL_6)
        ->addLocation(LocationID::LAIR_LAYNOLE_1)
        ->addLocation(LocationID::LAIR_LAYNOLE_2)
        ->addLocation(LocationID::LAIR_LAYNOLE_3)
        ->addLocation(LocationID::LAIR_LAYNOLE_4)
        ->addLocation(LocationID::LAIR_LAYNOLE_5)
        ->addLocation(LocationID::CHEST_LAYNOLE_LUCKY_BLADE);
    MapNode* lune = (new MapNode())
        ->addLocation(LocationID::LAIR_LUNE_PATH_1)
        ->addLocation(LocationID::LAIR_LUNE_PATH_2)
        ->addLocation(LocationID::LAIR_LUNE_BOTTOM)
        ->addLocation(LocationID::LAIR_LUNE_MIDDLE_LEFT)
        ->addLocation(LocationID::LAIR_LUNE_MIDDLE_RIGHT)
        ->addLocation(LocationID::LAIR_LUNE_POSEIDON_BOSS)
        ->addLocation(LocationID::CHEST_LUNE_PATH_LEFT)
        ->addLocation(LocationID::CHEST_LUNE_PATH_RIGHT)
        ->addLocation(LocationID::CRYSTAL_LUNE);
    MapNode* luneMushroomDream = (new MapNode())
        ->addLocation(LocationID::LAIR_LUNE_MUSHROOM_DREAM)
        ->addLocation(LocationID::SECRET_LUNE_MUSHROOM_DREAM);

    extraItems.add(ItemIndex::GEMS_EXP_40);
    equipmentItems.add(ItemIndex::MAGIC_ARMOR);
    extraItems.add(ItemIndex::NOTHING);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    extraItems.add(ItemIndex::GEMS_EXP_50);
    extraItems.add(ItemIndex::GEMS_EXP_300);
    progressionItems.add(ItemIndex::LUCKY_BLADE);
    extraItems.add(ItemIndex::STRANGE_BOTTLE);
    equipmentItems.add(ItemIndex::ROTATOR);
    extraItems.add(ItemIndex::GEMS_EXP_400);
    progressionItems.add(ItemIndex::MUSHROOM_SHOES);
    progressionItems.add(ItemIndex::EMBLEM_E);
    progressionItems.add(ItemIndex::EMBLEM_F);
    progressionItems.add(ItemIndex::PHOENIX);
    progressionItems.add(ItemIndex::SILVER_STONE);
    extraNpcs.add(ItemIndex::NPC_GIRL);
    progressionItems.add(ItemIndex::NPC_GREETER_GRANDPA);
    extraNpcs.add(ItemIndex::NPC_MUSHROOM);
    extraNpcs.add(ItemIndex::NPC_SNAIL_JOCKEY);
    extraNpcs.add(ItemIndex::NPC_GRANDPA2);
    progressionItems.add(ItemIndex::NPC_PATHFINDER_BOY);
    extraNpcs.add(ItemIndex::NPC_GIRL2);
    progressionItems.add(ItemIndex::NPC_BOY_MUSHROOM_SHOES);
    extraNpcs.add(ItemIndex::NPC_GRANDMA);
    progressionItems.add(ItemIndex::NPC_MUSHROOM_TUNNEL);
    extraNpcs.add(ItemIndex::NPC_SNAIL_RACER);
    extraNpcs.add(ItemIndex::NPC_SNAIL_RACER2);
    progressionItems.add(ItemIndex::NPC_GIRL_TUNNEL);
    extraNpcs.add(ItemIndex::NPC_SNAIL);
    extraNpcs.add(ItemIndex::NPC_MUSHROOM3);
    progressionItems.add(ItemIndex::NPC_GRANDPA_LOGS);
    progressionItems.add(ItemIndex::NPC_GRANDPA_LAKE);
    extraNpcs.add(ItemIndex::NPC_SNAIL2);
    progressionItems.add(ItemIndex::NPC_GRANDPA_PRISON);
    progressionItems.add(ItemIndex::NPC_GRANDPA_LUNE);
    extraNpcs.add(ItemIndex::NPC_BOY2);
    progressionItems.add(ItemIndex::NPC_NOME);
    progressionItems.add(ItemIndex::NPC_MUSHROOM_EMBLEM_F);
    progressionItems.add(ItemIndex::NPC_DANCING_GRANDMA);
    progressionItems.add(ItemIndex::NPC_DANCING_GRANDMA2);
    progressionItems.add(ItemIndex::NPC_SNAIL_EMBLEM_E);
    progressionItems.add(ItemIndex::NPC_MOUNTAIN_KING);

    // combat area links
    stElles->addLink(new MapLink(stElles, mountainHome,
        (new LinkReqCheck(ItemIndex::NPC_MERMAID_QUEEN))
    ));
    mountainHome->addLink(new MapLink(mountainHome, laynole,
        (new LinkReqCheck(ItemIndex::MUSHROOM_SHOES))
    ));
    mountainHome->addLink(new MapLink(mountainHome, lune,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::LUCKY_BLADE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GIRL_TUNNEL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GRANDPA_LAKE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GRANDPA_LUNE))
    ));
    mountainHome->addLink(new MapLink(lune, luneMushroomDream,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MUSHROOM_TUNNEL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GRANDPA_PRISON))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MUSHROOM_EMBLEM_F))
            ->addReq(new LinkReqCheck(ItemIndex::DREAM_ROD))
    ));

    // NPC item links
    mountainHome->addLink(new MapLink(mountainHome,
        (new MapNode())->addLocation(LocationID::NPC_MOUNTAIN_MIDDLE_LAKE_BOY),
        (new LinkReqCheck(ItemIndex::NPC_BOY_MUSHROOM_SHOES))
    ));
    mountainHome->addLink(new MapLink(mountainHome,
        (new MapNode())->addLocation(LocationID::NPC_SNAIL_SECRET_ROOM),
        (new LinkReqCheck(ItemIndex::NPC_SNAIL_EMBLEM_E))
    ));
    mountainHome->addLink(new MapLink(mountainHome,
        (new MapNode())->addLocation(LocationID::NPC_DANCING_GRANDMAS),
        (new LinkReqAnd())
            ->addReq((new LinkReqOr())
                ->addReq(new LinkReqCheck(ItemIndex::NPC_GREETER_GRANDPA))
                ->addReq(new LinkReqCheck(ItemIndex::NPC_BOY_MUSHROOM_SHOES))
            )
            ->addReq(new LinkReqCheck(ItemIndex::NPC_PATHFINDER_BOY))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GRANDPA_LOGS))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOUNTAIN_KING))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DANCING_GRANDMA))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DANCING_GRANDMA2))
            ->addReq(new LinkReqCheck(ItemIndex::RED_HOT_BALL))
            ->addReq(new LinkReqCheck(ItemIndex::RED_HOT_MIRROR))
            ->addReq(new LinkReqCheck(ItemIndex::RED_HOT_STICK))
    ));
    mountainHome->addLink(new MapLink(mountainHome,
        (new MapNode())->addLocation(LocationID::NPC_NOME),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GIRL_TUNNEL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GRANDPA_LAKE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MUSHROOM_TUNNEL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GRANDPA_PRISON))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOUNTAIN_KING))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_NOME))
    ));

    /*
        Act V: Leo's House
    */
    MapNode* leosHouse = (new MapNode())
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B1_UP_FIRST_PIPE)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B1_SOUTHWEST)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B1_BUILD_PIPE_RIGHT);
    MapNode* leosBasementMetal = (new MapNode())
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B1_NORTHWEST)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B1_SMALL_ISLAND_RIGHT)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B1_RIGHT_SIDE_BOTTOM)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B1_RIGHT_SIDE_TOP)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B1_TOP)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B2_RIGHT_FIRE_PIPES)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B2_INSIDE_PIPE)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B2_LEFT_SIDE_1)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B2_LEFT_SIDE_2)
        ->addLocation(LocationID::LAIR_LEOS_BASEMENT_B2_LEFT_SIDE_3)
        ->addLocation(LocationID::CRYSTAL_LEOS_BASEMENT);
    MapNode* modelTown1 = (new MapNode())
        ->addLocation(LocationID::LAIR_MODEL_TOWN_1_SOUTHWEST)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_1_FAR_WEST)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_1_WEST_POPUP_LEFT)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_1_WEST_POPUP_RIGHT)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_1_WEST_FIELD)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_1_EAST_POPUP_LEFT)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_1_EAST_POPUP_RIGHT)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_1_SOUTHEAST)
        ->addLocation(LocationID::CHEST_MODEL_TOWN1_NORTH_LEFT)
        ->addLocation(LocationID::CHEST_MODEL_TOWN1_NORTH_RIGHT)
        ->addLocation(LocationID::CHEST_MODEL_TOWN1_SOUTH)
        ->addLocation(LocationID::CRYSTAL_MODEL_TOWN1);
    MapNode* modelTown2 = (new MapNode())
        ->addLocation(LocationID::LAIR_MODEL_TOWN_2_SOUTHWEST)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_2_NORTHWEST)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_2_CENTER_WEST)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_2_NORTHEAST)
        ->addLocation(LocationID::LAIR_MODEL_TOWN_2_SOUTHEAST)
        ->addLocation(LocationID::CHEST_MODEL_TOWN2_BOTTOM)
        ->addLocation(LocationID::CHEST_MODEL_TOWN2_TOP);
    MapNode* powerPlantFree = (new MapNode())
        ->addLocation(LocationID::CHEST_LEOS_LAB_POWER_PLANT);
    MapNode* powerPlantMetal = (new MapNode())
        ->addLocation(LocationID::LAIR_POWER_PLANT)
        ->addLocation(LocationID::LAIR_POWER_PLANT_TIN_DOLL_BOSS)
        ->addLocation(LocationID::CRYSTAL_POWER_PLANT);

    extraItems.add(ItemIndex::GEMS_EXP_300);
    extraItems.add(ItemIndex::GEMS_EXP_50);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    extraItems.add(ItemIndex::GEMS_EXP_80);
    extraItems.add(ItemIndex::GEMS_EXP_300);
    extraItems.add(ItemIndex::STRANGE_BOTTLE);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    equipmentItems.add(ItemIndex::LIGHT_ARMOR);
    extraItems.add(ItemIndex::GEMS_EXP_300);
    progressionItems.add(ItemIndex::ZANTETSU_SWORD);
    progressionItems.add(ItemIndex::DOOR_KEY);
    progressionItems.add(ItemIndex::EMBLEM_G);
    equipmentItems.add(ItemIndex::MYSTIC_ARMOR);
    progressionItems.add(ItemIndex::ACTINIDIA_LEAF);
    equipmentItems.add(ItemIndex::SPARK_BOMB);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    extraItems.add(ItemIndex::MEDICAL_HERB);
    progressionItems.add(ItemIndex::PURPLE_STONE);

    progressionItems.add(ItemIndex::NPC_CAT_MOUSEHOLE1);
    progressionItems.add(ItemIndex::NPC_PLANT_HERB);
    extraNpcs.add(ItemIndex::NPC_PLANT);
    progressionItems.add(ItemIndex::NPC_GREAT_DOOR_ZANTETSU_SWORD);
    progressionItems.add(ItemIndex::NPC_CAT_MOUSEHOLE2);
    extraNpcs.add(ItemIndex::NPC_CAT3);
    progressionItems.add(ItemIndex::NPC_GREAT_DOOR_KITCHEN);
    progressionItems.add(ItemIndex::NPC_CHEST_OF_DRAWERS_MYSTIC_ARMOR);
    progressionItems.add(ItemIndex::NPC_CAT_DOOR_KEY);
    progressionItems.add(ItemIndex::NPC_MOUSE_HOLE);
    progressionItems.add(ItemIndex::NPC_STEPS_UPSTAIRS);
    progressionItems.add(ItemIndex::NPC_GREAT_DOOR_MODEL_TOWNS);
    progressionItems.add(ItemIndex::NPC_MODEL_TOWN1);
    extraNpcs.add(ItemIndex::NPC_MOUSE2);
    extraNpcs.add(ItemIndex::NPC_CHEST_OF_DRAWERS);
    extraNpcs.add(ItemIndex::NPC_MOUSE3);
    extraNpcs.add(ItemIndex::NPC_MOUSE4);
    extraNpcs.add(ItemIndex::NPC_PLANT2);
    progressionItems.add(ItemIndex::NPC_MOUSE_SPARK_BOMB);
    progressionItems.add(ItemIndex::NPC_STEPS_MARIE);
    progressionItems.add(ItemIndex::NPC_MODEL_TOWN2);
    extraNpcs.add(ItemIndex::NPC_MOUSE5);
    progressionItems.add(ItemIndex::NPC_CHEST_OF_DRAWERS_ATTIC);
    progressionItems.add(ItemIndex::NPC_PLANT_ACTINIDIA_LEAVES);
    extraNpcs.add(ItemIndex::NPC_CAT4);
    progressionItems.add(ItemIndex::NPC_STAIRS_POWER_PLANT);
    extraNpcs.add(ItemIndex::NPC_DOLL);
    progressionItems.add(ItemIndex::NPC_MARIE);

    // combat area links
    mountainHome->addLink(new MapLink(mountainHome, leosHouse,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GIRL_TUNNEL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GRANDPA_LAKE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MUSHROOM_TUNNEL))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GRANDPA_PRISON))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOUNTAIN_KING))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_NOME))
    ));
    leosHouse->addLink(new MapLink(leosHouse, leosBasementMetal,
        (new LinkReqCheck(ItemIndex::ZANTETSU_SWORD))
    ));
    MapNode* leosBedroom = (new MapNode());
    leosHouse->addLink(new MapLink(leosHouse, leosBedroom,
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_STEPS_UPSTAIRS))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GREAT_DOOR_MODEL_TOWNS))
    ));
    leosBedroom->addLink(new MapLink(leosBedroom, modelTown1,
        (new LinkReqCheck(ItemIndex::NPC_MODEL_TOWN1))
    ));
    leosBedroom->addLink(new MapLink(leosBedroom, modelTown2,
        (new LinkReqCheck(ItemIndex::NPC_MODEL_TOWN2))
    ));
    leosHouse->addLink(new MapLink(leosHouse, powerPlantFree,
        (new LinkReqCheck(ItemIndex::NPC_STAIRS_POWER_PLANT))
    ));
    powerPlantFree->addLink(new MapLink(powerPlantFree, powerPlantMetal,
        (new LinkReqCheck(ItemIndex::ZANTETSU_SWORD))
    ));

    // NPC item links
    leosHouse->addLink(new MapLink(leosHouse,
        (new MapNode())->addLocation(LocationID::CHEST_LEOS_LAB_IN_DOOR),
        (new LinkReqCheck(ItemIndex::NPC_GREAT_DOOR_ZANTETSU_SWORD))
    ));
    leosHouse->addLink(new MapLink(leosHouse,
        (new MapNode())->addLocation(LocationID::NPC_MOUSE_IN_MOUSEHOLE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GREAT_DOOR_ZANTETSU_SWORD))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CAT_MOUSEHOLE1))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CAT_MOUSEHOLE2))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOUSE_HOLE))
            ->addReq(new LinkReqCheck(ItemIndex::ACTINIDIA_LEAF))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOUSE_SPARK_BOMB))
    ));
    leosHouse->addLink(new MapLink(leosHouse,
        (new MapNode())->addLocation(LocationID::NPC_PLANT_THROUGH_MOUSEHOLE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GREAT_DOOR_ZANTETSU_SWORD))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CAT_MOUSEHOLE1))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CAT_MOUSEHOLE2))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MOUSE_HOLE))
            ->addReq(new LinkReqCheck(ItemIndex::ACTINIDIA_LEAF))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_PLANT_HERB))
    ));
    leosHouse->addLink(new MapLink(leosHouse,
        (new MapNode())
            ->addLocation(LocationID::NPC_DRAWERS_LOCKED_ROOM)
            ->addLocation(LocationID::SECRET_UNDER_DRAWERS_LOCKED_ROOM),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GREAT_DOOR_ZANTETSU_SWORD))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_GREAT_DOOR_KITCHEN))
            ->addReq(new LinkReqCheck(ItemIndex::DOOR_KEY))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CHEST_OF_DRAWERS_MYSTIC_ARMOR))
    ));
    leosBedroom->addLink(new MapLink(leosBedroom,
        (new MapNode())->addLocation(LocationID::NPC_LEOS_CAT_DREAM),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CAT_DOOR_KEY))
            ->addReq(new LinkReqCheck(ItemIndex::DREAM_ROD))
    ));
    leosBedroom->addLink(new MapLink(leosBedroom,
        (new MapNode())->addLocation(LocationID::NPC_UPSTAIRS_PLANT),
        (new LinkReqCheck(ItemIndex::NPC_PLANT_ACTINIDIA_LEAVES))
    ));
    leosBedroom->addLink(new MapLink(leosBedroom,
        (new MapNode())->addLocation(LocationID::NPC_ATTIC_DRAWERS),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_STEPS_MARIE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_CHEST_OF_DRAWERS_ATTIC))
    ));
    leosBedroom->addLink(new MapLink(leosBedroom,
        (new MapNode())->addLocation(LocationID::NPC_MARIE),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_STEPS_MARIE))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_MARIE))
    ));

    map = new LogicMap(grassValley);
}

void logMap (WorldMap& map) {
    std::cout << map.map->countFilled() << " filled locations" << std::endl;
    std::cout << map.map->countEmpty() << " empty locations" << std::endl;
    Filler::LocationSet emptyLocations;
    Filler::getEmptyLocations(map.map, emptyLocations);
    emptyLocations.filter(ItemIndex::NPC_KING_MAGRIDD);
    std::cout << emptyLocations.size << " empty lairs\n" << std::endl;
}

void testTheWorld (WorldFlags& worldFlags) {
    WorldMap theWorld;

    theWorld.createWorld(worldFlags);

    cout << "Progression: " << theWorld.progressionItems.size << endl;
    cout << "Equipment: " << theWorld.equipmentItems.size << endl;
    cout << "Extra items: " << theWorld.extraItems.size << endl;
    cout << "Extra npcs: " << theWorld.extraNpcs.size << endl;

    logMap(theWorld);

    Filler::LocationSet dummyLocations;
    dummyLocations.clear();
    dummyLocations
        .add(LocationID::CHEST_WATER_SHRINE_FLOOR1_FAR_SIDE)
        ->add(LocationID::CHEST_WATER_SHRINE_FLOOR2_SPEARS)
        ->add(LocationID::CHEST_WATER_SHRINE_FLOOR2_WATERFALL)
        ->add(LocationID::CHEST_WATER_SHRINE_FLOOR3_SOUTHEAST)
        ->add(LocationID::CHEST_WATER_SHRINE_FLOOR3_SOUTHWEST)
        ->add(LocationID::SECRET_WATER_SHRINE_BASEMENT)
        ->add(LocationID::CRYSTAL_WATER_SHRINE2_SPEARS);

    Filler::PlacementSet dummyPlacementItems;
    dummyPlacementItems.clear();
    dummyPlacementItems.add(theWorld.equipmentItems.take());
    dummyPlacementItems.add(theWorld.extraItems.take());
    dummyPlacementItems.add(theWorld.extraItems.take());

    Filler::dummyPlacement(theWorld.map, dummyPlacementItems, dummyLocations);

    cout << "After dummy placement" << endl;
    logMap(theWorld);

    ItemPool progressionPool;
    for (int i = 0; i < theWorld.progressionItems.size; i++) {
        progressionPool.addItem(theWorld.progressionItems.set[i]);
    }
    theWorld.progressionItems.shuffle();

    ItemPool inventory;
    inventory.addItem(ItemIndex::SWORD_OF_LIFE);

    bool success = Filler::placeItems(theWorld.map, theWorld.progressionItems, inventory);
    cout << "Progression placement " << (success ? "succeeded" : "failed") << endl;
    logMap(theWorld);

    progressionPool
        .addItem(ItemIndex::EMBLEM_B)
        ->addItem(ItemIndex::EMBLEM_D)
        ->addItem(ItemIndex::EMBLEM_E)
        ->addItem(ItemIndex::EMBLEM_F)
        ->addItem(ItemIndex::EMBLEM_G)
        ->addItem(ItemIndex::EMBLEM_H)
        ->addItem(ItemIndex::ZANTETSU_SWORD)
        ->addItem(ItemIndex::SPIRIT_SWORD)
        ->addItem(ItemIndex::RED_HOT_BALL)
        ->addItem(ItemIndex::RED_HOT_STICK)
        ->addItem(ItemIndex::RED_HOT_MIRROR);

    Filler::LocationSet emptyLocations;
    Filler::getEmptyLocations(theWorld.map, emptyLocations);
    cout << "Filling mustBeUnique locations" << endl;
    success = Filler::mustBeUniquePlacement(theWorld.map, theWorld.equipmentItems, theWorld.extraItems, emptyLocations);
    cout << "mustBeUnique placement " << (success ? "succeeded" : "failed") << endl;
    logMap(theWorld);

    Filler::getEmptyLocations(theWorld.map, emptyLocations);
    cout << "Placing " << theWorld.equipmentItems.size << " equipment items" << endl;
    success = Filler::dummyPlacementWithFilter(theWorld.map, theWorld.equipmentItems, emptyLocations);
    cout << "Equipment placement " << (success ? "succeeded" : "failed") << endl;
    logMap(theWorld);

    // TODO: We need to make a "unique fill pass" for mountain king at least
    cout << "Placing " << theWorld.extraItems.size << " extra items" << endl;
    success = Filler::dummyPlacementWithFilter(theWorld.map, theWorld.extraItems, emptyLocations);
    cout << "Extra item placement " << (success ? "succeeded" : "failed") << endl;
    logMap(theWorld);

    cout << "Placing " << theWorld.extraNpcs.size << " extra NPCs" << endl;
    success = Filler::dummyPlacementWithFilter(theWorld.map, theWorld.extraNpcs, emptyLocations);
    cout << "Extra NPC placement " << (success ? "succeeded" : "failed") << endl;
    logMap(theWorld);

    emptyLocations.print();

    theWorld.map->printMap(progressionPool);
}
