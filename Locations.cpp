#include "Locations.h"

#include "ItemPool.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;


Locations::Locations () {};
Locations::~Locations () {};

void resetFlags (Location& flags) {
    flags.isNpc = false;
    flags.isChest = false;
    flags.isLair = false;
    flags.isMissable = false;
    flags.mustBeUnique = false;
}

void Locations::populateLair (LocationID locationIndex, ItemIndex origItemIndex, Location* flags, const char* name) {
    Location *dst = &allLocations[(int)locationIndex];
    memcpy(dst, flags, sizeof(Location));
    dst->isLair = true;
    dst->origItemIndex = origItemIndex;
    strcpy(dst->name, name);

    Item origItem = ItemPool::allItems[(int)(origItemIndex)];
    npcIdMap[(int)(origItem.npcId)] = locationIndex;
}

void Locations::populateChest (LocationID locationIndex, ItemIndex origItemIndex, Location* flags, const char* name, unsigned char chestId) {
    Location *dst = &allLocations[(int)locationIndex];
    memcpy(dst, flags, sizeof(Location));
    dst->isChest = true;
    dst->origItemIndex = origItemIndex;
    dst->chestId = chestId;
    strcpy(dst->name, name);
    chestIdMap[chestId] = locationIndex;
}

void Locations::populateNpcItem (LocationID locationIndex, ItemIndex origItemIndex, Location* flags, const char* name, NpcItemIndex npcItemIndex) {
    Location *dst = &allLocations[(int)locationIndex];
    memcpy(dst, flags, sizeof(Location));
    dst->isChest = true;
    dst->origItemIndex = origItemIndex;
    dst->npcItemIndex = npcItemIndex;
    strcpy(dst->name, name);
}

void Locations::populate () {
    Location normalFlags, missableFlags, mkFlags;
    resetFlags(normalFlags);
    resetFlags(missableFlags);
    missableFlags.isMissable = true;
    resetFlags(mkFlags);
    mkFlags.mustBeUnique = true;

    populateChest(
        LocationID::CHEST_FIRST_SWORD,
        ItemIndex::SWORD_OF_LIFE,
        &normalFlags,
        "Trial Room first chest",
        0
    );
    populateChest(
        LocationID::CHEST_GRASS_VALLEY_HYPE_LEFT,
        ItemIndex::IRON_ARMOR,
        &normalFlags,
        "Grass Valley Hype Cave left chest",
        1
    );
    populateChest(
        LocationID::CHEST_GRASS_VALLEY_HYPE_RIGHT,
        ItemIndex::GEMS_EXP_50,
        &normalFlags,
        "Grass Valley Hype Cave right chest",
        2
    );
    populateChest(
        LocationID::CHEST_UNDERGROUND_CASTLE_FIRST,
        ItemIndex::GEMS_EXP_12,
        &normalFlags,
        "Underground Castle first chest",
        3
    );
    populateChest(
        LocationID::CHEST_UNDERGROUND_CASTLE_SECOND,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Underground Castle second chest",
        4
    );
    populateChest(
        LocationID::CHEST_UNDERGROUND_CASTLE_THIRD,
        ItemIndex::DREAM_ROD,
        &normalFlags,
        "Underground Castle third chest",
        5
    );
    populateChest(
        LocationID::CHEST_UNDERGROUND_CASTLE_LISA,
        ItemIndex::LEOS_BRUSH,
        &normalFlags,
        "Underground Castle Lisa chest",
        6
    );
    populateChest(
        LocationID::CHEST_LEOS_PAINTING_FIRST,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Leo's painting first chest",
        7
    );
    populateChest(
        LocationID::CHEST_LEOS_PAINTING_METAL,
        ItemIndex::TORNADO,
        &normalFlags,
        "Leo's painting metal locked chest",
        8
    );
    populateNpcItem(
        LocationID::NPC_TOOL_SHOP_OWNER,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Grass Valley Tool Shop owner",
        NpcItemIndex::ITEM_TOOL_SHOP_OWNER
    );
    populateNpcItem(
        LocationID::SECRET_SOUTHEAST_IVY,
        ItemIndex::EMBLEM_A,
        &normalFlags,
        "Grass Valley southeast vine secret",
        NpcItemIndex::ITEM_EMBLEM_A
    );
    populateNpcItem(
        LocationID::SECRET_GOAT_PEN,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Goat pen corner secret",
        NpcItemIndex::ITEM_GOAT_PEN
    );
    populateNpcItem(
        LocationID::NPC_TEDDY,
        ItemIndex::GOATS_FOOD,
        &normalFlags,
        "Tool Shop owner's son Teddy",
        NpcItemIndex::ITEM_TEDDY
    );
    populateNpcItem(
        LocationID::SECRET_UNDER_TULIP,
        ItemIndex::PASS,
        &normalFlags,
        "Grass Valley southeast under tulip",
        NpcItemIndex::ITEM_PASS
    );
    populateNpcItem(
        LocationID::SECRET_HIDEOUT,
        ItemIndex::STRANGE_BOTTLE,
        &normalFlags,
        "Grass Valley hideout secret",
        NpcItemIndex::ITEM_SECRET_CAVE_TILE
    );
    populateNpcItem(
        LocationID::NPC_VILLAGE_CHIEF,
        ItemIndex::BROWN_STONE,
        &normalFlags,
        "Grass Valley Village Chief",
        NpcItemIndex::ITEM_VILLAGE_CHIEF
    );
    populateNpcItem(
        LocationID::NPC_TRIAL_MAGICIAN,
        ItemIndex::FLAME_BALL,
        &normalFlags,
        "Trial Room Magician",
        NpcItemIndex::ITEM_MAGICIAN
    );
    populateNpcItem(
        LocationID::CRYSTAL_HIDEOUT,
        ItemIndex::RECOVERY_SWORD,
        &normalFlags,
        "Grass Valley hideout crystal",
        NpcItemIndex::ITEM_CRYSTAL_RECOVERY_SWORD
    );
    populateNpcItem(
        LocationID::CRYSTAL_GRASS_VALLEY_HYPE,
        ItemIndex::GEMS_EXP_80,
        &normalFlags,
        "Grass Valley Hype Cave crystal",
        NpcItemIndex::ITEM_CRYSTAL_GRASS_VALLEY
    );
    populateNpcItem(
        LocationID::CRYSTAL_UNDERGROUND_CASTLE,
        ItemIndex::GEMS_EXP_40,
        &normalFlags,
        "Underground Castle first crystal",
        NpcItemIndex::ITEM_CRYSTAL_UNDERGROUND_CASTLE
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_1,
        ItemIndex::NPC_OLD_WOMAN,
        &normalFlags,
        "Underground Castle first lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_2,
        ItemIndex::NPC_TOOL_SHOP_OWNER,
        &normalFlags,
        "Underground Castle second lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_3,
        ItemIndex::NPC_TULIP,
        &normalFlags,
        "Underground Castle third lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_4,
        ItemIndex::NPC_BRIDGE_GUARD,
        &normalFlags,
        "Underground Castle fourth lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_5,
        ItemIndex::NPC_IVY_CHEST_ROOM,
        &normalFlags,
        "Underground Castle fifth lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_6,
        ItemIndex::NPC_WATER_MILL,
        &normalFlags,
        "Underground Castle last lair before elevator"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_ELEVATOR_TOP,
        ItemIndex::NPC_OLD_MAN2,
        &normalFlags,
        "Underground Castle lair at top of elevator"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_1,
        ItemIndex::NPC_GOAT_HERB,
        &normalFlags,
        "Underground Castle part 2 first lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_2,
        ItemIndex::NPC_LISA,
        &normalFlags,
        "Underground Castle part 2 second lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_3,
        ItemIndex::NPC_TULIP2,
        &normalFlags,
        "Underground Castle part 2 third lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_4,
        ItemIndex::NPC_ARCHITECT,
        &normalFlags,
        "Underground Castle part 2 fourth lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_5,
        ItemIndex::NPC_IVY2,
        &normalFlags,
        "Underground Castle part 2 fifth lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_6,
        ItemIndex::NPC_TEDDY,
        &normalFlags,
        "Underground Castle part 2 sixth lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_7,
        ItemIndex::NPC_GOAT,
        &normalFlags,
        "Underground Castle part 2 seventh lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_8,
        ItemIndex::NPC_TULIP3,
        &normalFlags,
        "Underground Castle part 2 eighth lair"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_9,
        ItemIndex::NPC_LEOS_HOUSE,
        &normalFlags,
        "Underground Castle last lair near crystal"
    );
    populateLair(
        LocationID::LAIR_UNDERGROUND_CASTLE_PART2_LISA,
        ItemIndex::NPC_OLD_MAN,
        &normalFlags,
        "Underground Castle part 2 Lisa locked lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING1_1,
        ItemIndex::NPC_TULIP4,
        &normalFlags,
        "Leo's painting first room bottom lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING1_2,
        ItemIndex::NPC_LONELY_GOAT,
        &normalFlags,
        "Leo's painting first room top lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING2_1,
        ItemIndex::NPC_IVY,
        &normalFlags,
        "Leo's painting second room lair on left"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING3_1,
        ItemIndex::NPC_GOAT2,
        &normalFlags,
        "Leo's painting third room first lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING3_2,
        ItemIndex::NPC_BOY_CABIN,
        &normalFlags,
        "Leo's painting third room second lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING3_3,
        ItemIndex::NPC_TULIP_PASS,
        &normalFlags,
        "Leo's painting third room third lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING3_METAL,
        ItemIndex::NPC_IVY_EMBLEM_A,
        &normalFlags,
        "Leo's painting third room metal locked lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING4_1,
        ItemIndex::NPC_BOY_CAVE,
        &normalFlags,
        "Leo's painting last room left lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING4_METAL,
        ItemIndex::NPC_IVY_RECOVERY_SWORD,
        &normalFlags,
        "Leo's painting last room metal locked lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_PAINTING_BOSS,
        ItemIndex::NPC_VILLAGE_CHIEF,
        &normalFlags,
        "Leo's painting mantis boss lair"
    );
    populateChest(
        LocationID::CHEST_GREENWOOD_ICE_ARMOR,
        ItemIndex::ICE_ARMOR,
        &normalFlags,
        "Greenwood Ice Armor chest",
        9
    );
    populateChest(
        LocationID::CHEST_GREENWOOD_MONMO_TUNNEL,
        ItemIndex::MOLES_RIBBON,
        &normalFlags,
        "Greenwood Monmo's tunnel chest",
        10
    );
    populateChest(
        LocationID::CHEST_WATER_SHRINE_FLOOR1_FAR_SIDE,
        ItemIndex::GEMS_EXP_50,
        &normalFlags,
        "Water Shrine B1 chest on far side",
        11
    );
    populateChest(
        LocationID::CHEST_WATER_SHRINE_FLOOR2_WATERFALL,
        ItemIndex::GEMS_EXP_150,
        &normalFlags,
        "Water Shrine B2 chest behind waterfall",
        12
    );
    populateChest(
        LocationID::CHEST_WATER_SHRINE_FLOOR2_SPEARS,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Water Shrine B2 chest in spear traps",
        13
    );
    populateChest(
        LocationID::CHEST_WATER_SHRINE_FLOOR3_SOUTHWEST,
        ItemIndex::DELICIOUS_SEEDS,
        &normalFlags,
        "Water Shrine B3 southwest chest",
        14
    );
    populateChest(
        LocationID::CHEST_WATER_SHRINE_FLOOR3_SOUTHEAST,
        ItemIndex::GEMS_EXP_50,
        &normalFlags,
        "Water Shrine B3 southeast chest",
        15
    );
    populateChest(
        LocationID::CHEST_FIRE_SHRINE_FLOOR1,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Fire Shrine B1 chest",
        16
    );
    populateChest(
        LocationID::CHEST_FIRE_SHRINE_FLOOR2_DISAPPEARING,
        ItemIndex::NOTHING,
        &missableFlags,
        "Fire Shrine B2 center disappearing chest",
        17
    );
    populateChest(
        LocationID::CHEST_FIRE_SHRINE_FLOOR2_METAL,
        ItemIndex::STRANGE_BOTTLE,
        &normalFlags,
        "Fire Shrine B2 metal locked chest",
        18
    );
    populateChest(
        LocationID::CHEST_FIRE_SHRINE_FLOOR3_FIRST,
        ItemIndex::GEMS_EXP_100,
        &normalFlags,
        "Fire Shrine B3 first chest",
        19
    );
    populateChest(
        LocationID::CHEST_FIRE_SHRINE_FLOOR3_SECOND,
        ItemIndex::GEMS_EXP_60,
        &normalFlags,
        "Fire Shrine B3 second chest",
        20
    );
    populateChest(
        LocationID::CHEST_LIGHT_SHRINE_FLOOR1_SPIRIT,
        ItemIndex::FLAME_PILLAR,
        &normalFlags,
        "Light Shrine B1 Spirit locked chest",
        21
    );
    populateNpcItem(
        LocationID::NPC_RED_HOT_BIRD,
        ItemIndex::RED_HOT_MIRROR,
        &normalFlags,
        "Greenwood Red Hot Bird",
        NpcItemIndex::ITEM_BIRD_RED_HOT_MIRROR
    );
    populateNpcItem(
        LocationID::CRYSTAL_EMBLEM_TRADE,
        ItemIndex::MAGIC_BELL,
        &normalFlags,
        "Greenwood Emblem trade crystal",
        NpcItemIndex::ITEM_CRYSTAL_MAGIC_BELL
    );
    populateNpcItem(
        LocationID::NPC_WOODSTIN_TRIO,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Greenwood Woodstin Trio",
        NpcItemIndex::ITEM_WOODSTIN_TRIO
    );
    populateNpcItem(
        LocationID::NPC_GREENWOOD_GUARDIAN,
        ItemIndex::RED_HOT_MIRROR,
        &normalFlags,
        "Greenwood Red Hot Bird",
        NpcItemIndex::ITEM_BIRD_RED_HOT_MIRROR
    );
    populateNpcItem(
        LocationID::SECRET_TURBOS_GRAVE,
        ItemIndex::RED_HOT_MIRROR,
        &normalFlags,
        "Greenwood Red Hot Bird",
        NpcItemIndex::ITEM_BIRD_RED_HOT_MIRROR
    );


}
