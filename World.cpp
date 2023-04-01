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
        ->addItem(ItemIndex::SPIRIT_SWORD);

    Filler::LocationSet emptyLocations;
    Filler::getEmptyLocations(theWorld.map, emptyLocations);
    cout << "Placing " << theWorld.equipmentItems.size << " equipment items" << endl;
    success = Filler::dummyPlacementWithFilter(theWorld.map, theWorld.equipmentItems, emptyLocations);
    cout << "Equipment placement " << (success ? "succeeded" : "failed") << endl;
    logMap(theWorld);

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
