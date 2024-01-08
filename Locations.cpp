#include "Locations.h"

#include "ItemPool.h"

#include <iostream>
#include <cstring>

using namespace std;

// static declarations
Location Locations::allLocations[ALL_LOCATIONS_SIZE];
int Locations::allLocationsCount;
LocationID Locations::npcIdMap[NPC_ID_MAX];
LocationID Locations::chestIdMap[66];

Locations::Locations () {};
Locations::~Locations () {};

void resetFlags (Location& flags) {
    flags.isNpc = false;
    flags.isChest = false;
    flags.isLair = false;
    flags.isMissable = false;
    flags.mustBeUnique = false;
}

void Locations::logAllLocations () {
    cout << allLocationsCount << " locations" << endl;
    for (int i = 0; i < allLocationsCount; i++) {
        logLocation(allLocations[i]);
    }
}

bool Locations::NPCOriginallyGivesEXP (LocationID locationIndex) {
    switch (locationIndex) {
        case LocationID::CRYSTAL_GRASS_VALLEY_HYPE:
        case LocationID::CRYSTAL_UNDERGROUND_CASTLE:
        case LocationID::CRYSTAL_LOST_MARSH_END:
        case LocationID::CRYSTAL_WATER_SHRINE2_SPEARS:
        case LocationID::CRYSTAL_FIRE_SHRINE_FLOOR1_METAL:
        case LocationID::CRYSTAL_MOUNTAIN_SUMMIT:
        case LocationID::CRYSTAL_LUNE:
        case LocationID::CRYSTAL_LEOS_BASEMENT:
        case LocationID::CRYSTAL_MODEL_TOWN1:
        case LocationID::CRYSTAL_POWER_PLANT:
        case LocationID::CRYSTAL_ROCKBIRD:
        case LocationID::CRYSTAL_BLESTER_SEABED_PATH:
        case LocationID::CRYSTAL_DUREAN_SEABED_PATH:
            return true;
            break;
        default:
            return false;
    }
}

void Locations::logLocation (const Location& location) {
    const Item item = ItemPool::getItemByIndex(location.origItemIndex);
    cout << location.name;
    if (location.isMissable) {
        cout << " (missable)";
    }
    if (location.mustBeUnique) {
        cout << " (mustBeUnique)";
    }
    if (location.isLair) {
        cout << " -- lair " << (int)item.npcId;
    }
    if (location.isChest) {
        cout << " -- chest " << (int)location.chestId;
    }
    if (location.isNpc) {
        cout << " -- item from NPC " << (int)location.npcItemIndex;
    }
    cout << " -- " << item.name << endl;
}

Location* Locations::getLocation(LocationID locationId) {
    return &allLocations[static_cast<int>(locationId)];
}

int Locations::itemLocation (ItemIndex itemIndex) {
    for (int i = 0; i < ALL_LOCATIONS_SIZE; i++) {
        if (allLocations[i].itemIndex == itemIndex) {
            return i;
        }
    }
    return -1;
}
int Locations::itemOrigLocation (ItemIndex itemIndex) {
    for (int i = 0; i < ALL_LOCATIONS_SIZE; i++) {
        if (allLocations[i].origItemIndex == itemIndex) {
            return i;
        }
    }
    return -1;
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
    dst->isNpc = true;
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

    /*
        ACT 1
    */
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
        LocationID::CHEST_UNDERGROUND_CASTLE_SECOND,
        ItemIndex::GEMS_EXP_12,
        &normalFlags,
        "Underground Castle second chest",
        3
    );
    populateChest(
        LocationID::CHEST_UNDERGROUND_CASTLE_FIRST,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Underground Castle first chest",
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
    /*
        ACT 2
    */
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
        ItemIndex::GREEN_STONE,
        &normalFlags,
        "Greenwood Guardian",
        NpcItemIndex::ITEM_GREENWOODS_GUARDIAN
    );
    populateNpcItem(
        LocationID::SECRET_TURBOS_GRAVE,
        ItemIndex::GREENWOOD_LEAF,
        &normalFlags,
        "Greenwood Turbo's grave",
        NpcItemIndex::ITEM_GREENWOOD_LEAVES
    );
    populateNpcItem(
        LocationID::NPC_RIBBON_TRADE_MOLE,
        ItemIndex::SHIELD_BRACELET,
        &normalFlags,
        "Greenwood Ribbon trade mole",
        NpcItemIndex::ITEM_MOLE_SHIELD_BRACELET
    );
    populateNpcItem(
        LocationID::NPC_NUT_SQUIRREL_TRADE,
        ItemIndex::PSYCHO_SWORD,
        &normalFlags,
        "Greenwood Delicious Nuts trade squirrel",
        NpcItemIndex::ITEM_SQUIRREL_PSYCHO_SWORD
    );
    populateNpcItem(
        LocationID::NPC_NUT_SQUIRREL_ROOMMATE,
        ItemIndex::EMBLEM_C,
        &normalFlags,
        "Greenwood Nut trade squirrel roommate",
        NpcItemIndex::ITEM_SQUIRREL_EMBLEM_C
    );
    populateNpcItem(
        LocationID::SECRET_WATER_SHRINE_BASEMENT,
        ItemIndex::STRANGE_BOTTLE,
        &normalFlags,
        "Water Shrine B3 secret",
        NpcItemIndex::ITEM_WATER_SHRINE_TILE
    );
    populateNpcItem(
        LocationID::CRYSTAL_FIRE_SHRINE_BASEMENT,
        ItemIndex::LIGHT_ARROW,
        &normalFlags,
        "Fire Shrine B3 Crystal",
        NpcItemIndex::ITEM_CRYSTAL_LIGHT_ARROW
    );
    populateNpcItem(
        LocationID::CRYSTAL_LOST_MARSH_END,
        ItemIndex::GEMS_EXP_150,
        &normalFlags,
        "Lost Marsh Crystal at end near Light Shrine",
        NpcItemIndex::ITEM_CRYSTAL_LOST_MARSH
    );
    populateNpcItem(
        LocationID::CRYSTAL_WATER_SHRINE2_SPEARS,
        ItemIndex::GEMS_EXP_180,
        &normalFlags,
        "Water Shrine B2 in spear trap",
        NpcItemIndex::ITEM_CRYSTAL_WATER_SHRINE
    );
    populateNpcItem(
        LocationID::CRYSTAL_FIRE_SHRINE_FLOOR1_METAL,
        ItemIndex::GEMS_EXP_1,
        &normalFlags,
        "Fire Shrine B1 Crystal",
        NpcItemIndex::ITEM_CRYSTAL_FIRE_SHRINE
    );
    populateLair(
        LocationID::LAIR_LOST_MARSH_BEFORE_WATER_1,
        ItemIndex::NPC_BIRD,
        &normalFlags,
        "Lost Marsh first lair before Water Shrine"
    );
    populateLair(
        LocationID::LAIR_LOST_MARSH_BEFORE_WATER_2,
        ItemIndex::NPC_DOG,
        &normalFlags,
        "Lost Marsh second lair before Water Shrine"
    );
    populateLair(
        LocationID::LAIR_LOST_MARSH_BETWEEN_WATER_AND_FIRE,
        ItemIndex::NPC_DOG2,
        &normalFlags,
        "Lost Marsh lair between Water and Fire Shrines"
    );
    populateLair(
        LocationID::LAIR_LOST_MARSH_AFTER_FIRE_1,
        ItemIndex::NPC_MOLE_SHIELD_BRACELET,
        &normalFlags,
        "Lost Marsh first lair after Fire Shrine"
    );
    populateLair(
        LocationID::LAIR_LOST_MARSH_AFTER_FIRE_2,
        ItemIndex::NPC_DOG3,
        &normalFlags,
        "Lost Marsh second lair after Fire Shrine"
    );
    populateLair(
        LocationID::LAIR_WATER_SHRINE_B1_CENTER,
        ItemIndex::NPC_SQUIRREL_PSYCHO_SWORD,
        &normalFlags,
        "Water Shrine B1 center island lair"
    );
    populateLair(
        LocationID::LAIR_WATER_SHRINE_B2_1,
        ItemIndex::NPC_BIRD2,
        &normalFlags,
        "Water Shrine B2 first lair"
    );
    populateLair(
        LocationID::LAIR_WATER_SHRINE_B2_SPEARS,
        ItemIndex::NPC_MOLE_SOUL_OF_LIGHT,
        &normalFlags,
        "Water Shrine B2 lair in spear trap"
    );
    populateLair(
        LocationID::LAIR_WATER_SHRINE_B2_BACK,
        ItemIndex::NPC_DEER,
        &normalFlags,
        "Water Shrine B2 backdoor lair"
    );
    populateLair(
        LocationID::LAIR_WATER_SHRINE_B3_1,
        ItemIndex::NPC_CROCODILE,
        &normalFlags,
        "Water Shrine B3 first lair"
    );
    populateLair(
        LocationID::LAIR_WATER_SHRINE_B3_STATUE_1,
        ItemIndex::NPC_SQUIRREL,
        &normalFlags,
        "Water Shrine B3 top row of statues lair"
    );
    populateLair(
        LocationID::LAIR_WATER_SHRINE_B3_STATUE_2,
        ItemIndex::NPC_MOLE,
        &normalFlags,
        "Water Shrine B3 right side statue room lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B1,
        ItemIndex::NPC_DOG4,
        &normalFlags,
        "Fire Shrine B1 far right lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B2_SOUTHEAST,
        ItemIndex::NPC_DOG5,
        &normalFlags,
        "Fire Shrine B2 southeast lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B2_SOUTH,
        ItemIndex::NPC_CROCODILE2,
        &normalFlags,
        "Fire Shrine B2 southmost lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B2_NORTHWEST,
        ItemIndex::NPC_SQUIRREL_ICE_ARMOR,
        &normalFlags,
        "Fire Shrine B2 northwest lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B2_BACK,
        ItemIndex::NPC_SQUIRREL2,
        &normalFlags,
        "Fire Shrine B2 backdoor lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B3_1,
        ItemIndex::NPC_MOLE2,
        &normalFlags,
        "Fire Shrine B3 first lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B3_2,
        ItemIndex::NPC_SQUIRREL3,
        &normalFlags,
        "Fire Shrine B3 second lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B3_3,
        ItemIndex::NPC_BIRD_GREENWOOD_LEAF,
        &normalFlags,
        "Fire Shrine B3 third lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B3_4,
        ItemIndex::NPC_MOLE3,
        &normalFlags,
        "Fire Shrine B3 fourth lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B3_5,
        ItemIndex::NPC_DEER_MAGIC_BELL,
        &normalFlags,
        "Fire Shrine B3 fifth lair"
    );
    populateLair(
        LocationID::LAIR_FIRE_SHRINE_B3_METAL,
        ItemIndex::NPC_BIRD3,
        &normalFlags,
        "Fire Shrine B3 metal locked lair"
    );
    populateLair(
        LocationID::LAIR_LIGHT_SHRINE_B1,
        ItemIndex::NPC_SQUIRREL_EMBLEM_C,
        &normalFlags,
        "Light Shrine B1 northwest lair"
    );
    populateLair(
        LocationID::LAIR_LIGHT_SHRINE_B2_1,
        ItemIndex::NPC_CROCODILE3,
        &normalFlags,
        "Light Shrine B2 right side lair"
    );
    populateLair(
        LocationID::LAIR_LIGHT_SHRINE_B2_2,
        ItemIndex::NPC_MONMO,
        &normalFlags,
        "Light Shrine B2 south lair near portal"
    );
    populateLair(
        LocationID::LAIR_LIGHT_SHRINE_B2_SPIRIT,
        ItemIndex::NPC_BIRD_RED_HOT_MIRROR,
        &normalFlags,
        "Light Shrine B3 Spirit locked lair"
    );
    populateLair(
        LocationID::LAIR_LIGHT_SHRINE_STATUE_BOSS,
        ItemIndex::NPC_GREENWOODS_GUARDIAN,
        &normalFlags,
        "Light Shrine three statue boss"
    );
    /*
        ACT 3
    */
    populateChest(
        LocationID::CHEST_ST_ELLES_COMMON_HOUSE,
        ItemIndex::MERMAIDS_TEARS,
        &normalFlags,
        "St Elles common house right side chest",
        22
    );
    populateChest(
        LocationID::CHEST_ST_ELLES_LEFT_DOLPHIN,
        ItemIndex::BIG_PEARL,
        &normalFlags,
        "St Elles left side dolphin push chest",
        23
    );
    populateChest(
        LocationID::CHEST_SEABED_SECRET_TOP_LEFT,
        ItemIndex::EMBLEM_D,
        &normalFlags,
        "St Elles secret cave top left chest",
        24
    );
    populateChest(
        LocationID::CHEST_SEABED_SECRET_TOP_RIGHT,
        ItemIndex::GEMS_EXP_80,
        &normalFlags,
        "St Elles secret cave top right chest",
        25
    );
    populateChest(
        LocationID::CHEST_SEABED_SECRET_BOTTOM_LEFT,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "St Elles secret cave bottom left chest",
        26
    );
    populateChest(
        LocationID::CHEST_SEABED_SECRET_BOTTOM_RIGHT,
        ItemIndex::NOTHING,
        &normalFlags,
        "St Elles secret cave bottom right chest",
        27
    );
    populateChest(
        LocationID::CHEST_SOUTHERTA,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Southerta chest",
        28
    );
    populateChest(
        LocationID::CHEST_ROCKBIRD_LEFT,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Rockbird left chest",
        29
    );
    populateChest(
        LocationID::CHEST_ROCKBIRD_RIGHT,
        ItemIndex::GEMS_EXP_60,
        &normalFlags,
        "Rockbird right chest",
        30
    );
    populateChest(
        LocationID::CHEST_DUREAN_LAVA,
        ItemIndex::CRITICAL_SWORD,
        &normalFlags,
        "Durean chest by lava channel",
        31
    );
    populateChest(
        LocationID::CHEST_DUREAN_RIGHT_SIDE,
        ItemIndex::STRANGE_BOTTLE,
        &normalFlags,
        "Durean right side chest",
        32
    );
    populateChest(
        LocationID::CHEST_GHOST_SHIP_ON_SHIP,
        ItemIndex::GEMS_EXP_1,
        &normalFlags,
        "Ghost Ship chest on ship",
        33
    );
    populateChest(
        LocationID::CHEST_GHOST_SHIP_SEABED_PATH,
        ItemIndex::POWER_BRACELET,
        &normalFlags,
        "Seabed passage to Ghost Ship chest",
        34
    );
    populateNpcItem(
        LocationID::NPC_NORTHEAST_HOUSE_MERMAID,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "St Elles Mermaid in Northeast house",
        NpcItemIndex::ITEM_MERMAID_HERB
    );
    populateNpcItem(
        LocationID::NPC_COMMON_HOUSE_BOTTOM_MERMAID,
        ItemIndex::BUBBLE_ARMOR,
        &normalFlags,
        "St Elles common house mermaid at seabed entrance",
        NpcItemIndex::ITEM_MERMAID_BUBBLE_ARMOR
    );
    populateNpcItem(
        LocationID::NPC_COMMON_HOUSE_LEFT_MERMAID,
        ItemIndex::MAGIC_FLARE,
        &normalFlags,
        "St Elles common house left side mermaid",
        NpcItemIndex::ITEM_MERMAID_MAGIC_FLARE
    );
    populateNpcItem(
        LocationID::NPC_MERMAID_QUEEN,
        ItemIndex::BLUE_STONE,
        &normalFlags,
        "St Elles Mermaid Queen",
        NpcItemIndex::ITEM_MERMAID_QUEEN
    );
    populateNpcItem(
        LocationID::NPC_RED_HOT_MERMAID,
        ItemIndex::RED_HOT_STICK,
        &normalFlags,
        "St Elles common house Red Hot mermaid",
        NpcItemIndex::ITEM_MERMAID_RED_HOT_STICK
    );
    populateNpcItem(
        LocationID::NPC_LUE,
        ItemIndex::THUNDER_RING,
        &normalFlags,
        "St Elles Lue in jail",
        NpcItemIndex::ITEM_LUE
    );
    populateNpcItem(
        LocationID::CRYSTAL_ROCKBIRD,
        ItemIndex::GEMS_EXP_200,
        &normalFlags,
        "Rockbird Crystal Fairy",
        NpcItemIndex::ITEM_CRYSTAL_ROCKBIRD
    );
    populateNpcItem(
        LocationID::CRYSTAL_BLESTER_SEABED_PATH,
        ItemIndex::GEMS_EXP_300,
        &normalFlags,
        "Seabed path to Blester Crystal Fairy",
        NpcItemIndex::ITEM_CRYSTAL_SEABED_NEAR_BLESTER
    );
    populateNpcItem(
        LocationID::CRYSTAL_DUREAN_SEABED_PATH,
        ItemIndex::GEMS_EXP_250,
        &normalFlags,
        "Seabed path to Durean Crystal Fairy",
        NpcItemIndex::ITEM_CRYSTAL_SEABED_NEAR_DUREAN
    );
    populateLair(
        LocationID::LAIR_SOUTHERTA_1,
        ItemIndex::NPC_DOLPHIN_NORTHEAST,
        &normalFlags,
        "Southerta first lair"
    );
    populateLair(
        LocationID::LAIR_SOUTHERTA_2,
        ItemIndex::NPC_MERMAID_DANCE_LEADER,
        &normalFlags,
        "Southerta second lair"
    );
    populateLair(
        LocationID::LAIR_SOUTHERTA_3,
        ItemIndex::NPC_MERMAID5,
        &normalFlags,
        "Southerta third lair"
    );
    populateLair(
        LocationID::LAIR_SOUTHERTA_4,
        ItemIndex::NPC_MERMAID6,
        &normalFlags,
        "Southerta fourth lair"
    );
    populateLair(
        LocationID::LAIR_SOUTHERTA_5,
        ItemIndex::NPC_MERMAID_BUBBLE_ARMOR,
        &normalFlags,
        "Southerta last lair"
    );
    populateLair(
        LocationID::LAIR_SOUTHERTA_BACK,
        ItemIndex::NPC_MERMAID_STATUE_ROCKBIRD,
        &normalFlags,
        "Southerta backdoor lair"
    );
    populateLair(
        LocationID::LAIR_SEABED_TO_ROCKBIRD,
        ItemIndex::NPC_MERMAID9,
        &normalFlags,
        "Seabed lair on way to Rockbird"
    );
    populateLair(
        LocationID::LAIR_ROCKBIRD_LEFT_1,
        ItemIndex::NPC_MERMAID_TEARS,
        &normalFlags,
        "Rockbird left side middle lair"
    );
    populateLair(
        LocationID::LAIR_ROCKBIRD_LEFT_2,
        ItemIndex::NPC_MERMAID_MAGIC_FLARE,
        &normalFlags,
        "Rockbird left side bottom lair"
    );
    populateLair(
        LocationID::LAIR_ROCKBIRD_CENTER_1,
        ItemIndex::NPC_ANGELFISH_SOUL_OF_SHIELD,
        &normalFlags,
        "Rockbird center area bottom lair"
    );
    populateLair(
        LocationID::LAIR_ROCKBIRD_CENTER_2,
        ItemIndex::NPC_MERMAID_STATUE_DUREAN,
        &normalFlags,
        "Rockbird center area top lair"
    );
    populateLair(
        LocationID::LAIR_SEABED_TO_DUREAN,
        ItemIndex::NPC_DOLPHIN_PEARL,
        &normalFlags,
        "Seabed lair on way to Durean"
    );
    populateLair(
        LocationID::LAIR_DUREAN_SOUTH,
        ItemIndex::NPC_LUE,
        &normalFlags,
        "Durean south lair near entrance"
    );
    populateLair(
        LocationID::LAIR_DUREAN_WEST,
        ItemIndex::NPC_MERMAID_PEARL,
        &normalFlags,
        "Durean west side lair"
    );
    populateLair(
        LocationID::LAIR_DUREAN_NORTH,
        ItemIndex::NPC_MERMAID2,
        &normalFlags,
        "Durean north side lair"
    );
    populateLair(
        LocationID::LAIR_DUREAN_NORTHEAST,
        ItemIndex::NPC_MERMAID_NANA,
        &normalFlags,
        "Durean northeast lair"
    );
    populateLair(
        LocationID::LAIR_DUREAN_TIER2_NORTHWEST,
        ItemIndex::NPC_DOLPHIN_SAVES_LUE,
        &normalFlags,
        "Durean tier 2 northwest lair"
    );
    populateLair(
        LocationID::LAIR_DUREAN_TIER2_NORTHEAST,
        ItemIndex::NPC_MERMAID3,
        &normalFlags,
        "Durean tier 2 northeast lair in lava pool"
    );
    populateLair(
        LocationID::LAIR_DUREAN_TIER3,
        ItemIndex::NPC_MERMAID_STATUE_BLESTER,
        &normalFlags,
        "Durean tier 3 lair at corner of lava pool"
    );
    populateLair(
        LocationID::LAIR_DUREAN_TIER2_METAL,
        ItemIndex::NPC_MERMAID_RED_HOT_STICK,
        &normalFlags,
        "Durean tier 2 metal monkey lair"
    );
    populateLair(
        LocationID::LAIR_SEABED_TO_BLESTER_1,
        ItemIndex::NPC_ANGELFISH,
        &normalFlags,
        "Seabed path to Blester first lair"
    );
    populateLair(
        LocationID::LAIR_SEABED_TO_BLESTER_2,
        ItemIndex::NPC_ANGELFISH2,
        &normalFlags,
        "Seabed path to Blester second lair"
    );
    populateLair(
        LocationID::LAIR_SEABED_TO_BLESTER_3,
        ItemIndex::NPC_MERMAID_NORTHEAST,
        &normalFlags,
        "Seabed path to Blester third lair"
    );
    populateLair(
        LocationID::LAIR_BLESTER_BOTTOM_LEFT,
        ItemIndex::NPC_MERMAID7,
        &normalFlags,
        "Blester bottom left lair"
    );
    populateLair(
        LocationID::LAIR_BLESTER_BOTTOM_RIGHT,
        ItemIndex::NPC_ANGELFISH4,
        &normalFlags,
        "Blester bottom right lair"
    );
    populateLair(
        LocationID::LAIR_BLESTER_MIDDLE_LEFT,
        ItemIndex::NPC_MERMAID8,
        &normalFlags,
        "Blester middle left lair"
    );
    populateLair(
        LocationID::LAIR_BLESTER_MIDDLE_RIGHT,
        ItemIndex::NPC_DOLPHIN_SECRET_CAVE,
        &normalFlags,
        "Blester middle right lair"
    );
    populateLair(
        LocationID::LAIR_BLESTER_TOP_LEFT,
        ItemIndex::NPC_MERMAID_STATUE_GHOST_SHIP,
        &normalFlags,
        "Blester top left metal monkey lair"
    );
    populateLair(
        LocationID::LAIR_SEABED_TO_GHOST_SHIP_1,
        ItemIndex::NPC_ANGELFISH3,
        &normalFlags,
        "Seabed path to Ghost Ship bottom left lair"
    );
    populateLair(
        LocationID::LAIR_SEABED_TO_GHOST_SHIP_2,
        ItemIndex::NPC_DOLPHIN,
        &normalFlags,
        "Seabed path to Ghost Ship top lair"
    );
    populateLair(
        LocationID::LAIR_GHOST_SHIP_SKULL_BOSS,
        ItemIndex::NPC_MERMAID_QUEEN,
        &normalFlags,
        "Ghost Ship big skull boss lair"
    );
    /*
        Act 4
    */
    populateChest(
        LocationID::CHEST_MOUNTAIN_SCREEN1,
        ItemIndex::GEMS_EXP_40,
        &normalFlags,
        "Mountain Slope first screen bottom right chest",
        35
    );
    populateChest(
        LocationID::CHEST_MOUNTAIN_HYPE_LEFTMOST,
        ItemIndex::MAGIC_ARMOR,
        &normalFlags,
        "Mountain hype chests left chest",
        36
    );
    populateChest(
        LocationID::CHEST_MOUNTAIN_HYPE_2ND_FROM_LEFT,
        ItemIndex::NOTHING,
        &normalFlags,
        "Mountain hype chests second from left chest",
        37
    );
    populateChest(
        LocationID::CHEST_MOUNTAIN_HYPE_2ND_FROM_RIGHT,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Mountain hype chests second from right chest",
        38
    );
    populateChest(
        LocationID::CHEST_MOUNTAIN_HYPE_RIGHTMOST,
        ItemIndex::GEMS_EXP_50,
        &normalFlags,
        "Mountain hype chests right chest",
        39
    );
    populateChest(
        LocationID::CHEST_LAYNOLE_LUCKY_BLADE,
        ItemIndex::LUCKY_BLADE,
        &normalFlags,
        "Laynole chest across disappearing bridge",
        40
    );
    populateChest(
        LocationID::CHEST_LUNE_PATH_LEFT,
        ItemIndex::STRANGE_BOTTLE,
        &normalFlags,
        "Lune path left chest",
        41
    );
    populateChest(
        LocationID::CHEST_LUNE_PATH_RIGHT,
        ItemIndex::ROTATOR,
        &normalFlags,
        "Lune path right chest",
        42
    );
    populateNpcItem(
        LocationID::NPC_DANCING_GRANDMAS,
        ItemIndex::PHOENIX,
        &mkFlags,
        "Mountain of Souls Dancing Grandmas",
        NpcItemIndex::ITEM_MOUNTAIN_KING
    );
    populateNpcItem(
        LocationID::NPC_MOUNTAIN_MIDDLE_LAKE_BOY,
        ItemIndex::MUSHROOM_SHOES,
        &normalFlags,
        "Mountain of Souls center lake boy",
        NpcItemIndex::ITEM_BOY_MUSHROOM_SHOES
    );
    populateNpcItem(
        LocationID::NPC_NOME,
        ItemIndex::SILVER_STONE,
        &normalFlags,
        "Mountain of Souls Nome",
        NpcItemIndex::ITEM_NOME
    );
    populateNpcItem(
        LocationID::NPC_SNAIL_SECRET_ROOM,
        ItemIndex::EMBLEM_E,
        &normalFlags,
        "Mountain of Souls secret room snail",
        NpcItemIndex::ITEM_SNAIL_EMBLEM_E
    );
    populateNpcItem(
        LocationID::SECRET_LUNE_MUSHROOM_DREAM,
        ItemIndex::EMBLEM_F,
        &normalFlags,
        "Lune Mushroom's dream secret",
        NpcItemIndex::ITEM_EMBLEM_F
    );
    populateNpcItem(
        LocationID::CRYSTAL_MOUNTAIN_SUMMIT,
        ItemIndex::GEMS_EXP_300,
        &normalFlags,
        "Mountain summit Crystal Fairy",
        NpcItemIndex::ITEM_CRYSTAL_MOUNTAIN_OF_SOULS
    );
    populateNpcItem(
        LocationID::CRYSTAL_LUNE,
        ItemIndex::GEMS_EXP_400,
        &normalFlags,
        "Lune Crystal Fairy",
        NpcItemIndex::ITEM_CRYSTAL_LUNE
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_LOWER_1,
        ItemIndex::NPC_GIRL,
        &normalFlags,
        "Mountain Slope first lair near entrance"
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_LOWER_2,
        ItemIndex::NPC_GREETER_GRANDPA,
        &normalFlags,
        "Mountain Slope lower part second lair"
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_LOWER_3,
        ItemIndex::NPC_MUSHROOM,
        &normalFlags,
        "Mountain Slope lower part left side lair"
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_MIDDLE_PATH_LEFT,
        ItemIndex::NPC_SNAIL_JOCKEY,
        &normalFlags,
        "Mountain Slope middle end of path left lair"
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_MIDDLE_PATH_RIGHT,
        ItemIndex::NPC_GRANDPA2,
        &normalFlags,
        "Mountain Slope middle end of path left lair"
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_MIDDLE_TOP,
        ItemIndex::NPC_PATHFINDER_BOY,
        &normalFlags,
        "Mountain Slope middle top lair"
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_SUMMIT_1,
        ItemIndex::NPC_GIRL2,
        &normalFlags,
        "Mountain Slope summit first lair"
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_SUMMIT_2,
        ItemIndex::NPC_BOY_MUSHROOM_SHOES,
        &normalFlags,
        "Mountain Slope summit second lair"
    );
    populateLair(
        LocationID::LAIR_MOUNTAIN_SLOPE_SUMMIT_ICE,
        ItemIndex::NPC_GRANDMA,
        &normalFlags,
        "Mountain Slope summit lair on ice"
    );
    populateLair(
        LocationID::LAIR_ICE_HILL_1,
        ItemIndex::NPC_MUSHROOM_TUNNEL,
        &normalFlags,
        "Ice Hill top lair"
    );
    populateLair(
        LocationID::LAIR_ICE_HILL_2,
        ItemIndex::NPC_SNAIL_RACER,
        &normalFlags,
        "Ice Hill left lair inside wall"
    );
    populateLair(
        LocationID::LAIR_ICE_HILL_3,
        ItemIndex::NPC_SNAIL_RACER2,
        &normalFlags,
        "Ice Hill right lair inside wall"
    );
    populateLair(
        LocationID::LAIR_ICE_HILL_4,
        ItemIndex::NPC_GIRL_TUNNEL,
        &normalFlags,
        "Ice Hill middle of slope lair"
    );
    populateLair(
        LocationID::LAIR_ICE_HILL_5,
        ItemIndex::NPC_SNAIL,
        &normalFlags,
        "Ice Hill bottom left lair"
    );
    populateLair(
        LocationID::LAIR_ICE_HILL_6,
        ItemIndex::NPC_MUSHROOM3,
        &normalFlags,
        "Ice Hill bottom right lair"
    );
    populateLair(
        LocationID::LAIR_LAYNOLE_1,
        ItemIndex::NPC_GRANDPA_LOGS,
        &normalFlags,
        "Laynole first lair near entrance"
    );
    populateLair(
        LocationID::LAIR_LAYNOLE_2,
        ItemIndex::NPC_GRANDPA_LAKE,
        &normalFlags,
        "Laynole middle of ice tunnel lair"
    );
    populateLair(
        LocationID::LAIR_LAYNOLE_3,
        ItemIndex::NPC_SNAIL2,
        &normalFlags,
        "Laynole end of ice tunnel lair"
    );
    populateLair(
        LocationID::LAIR_LAYNOLE_4,
        ItemIndex::NPC_GRANDPA_PRISON,
        &normalFlags,
        "Laynole south disappearing bridge lair"
    );
    populateLair(
        LocationID::LAIR_LAYNOLE_5,
        ItemIndex::NPC_GRANDPA_LUNE,
        &normalFlags,
        "Laynole southwest lair"
    );
    populateLair(
        LocationID::LAIR_LUNE_PATH_1,
        ItemIndex::NPC_BOY2,
        &normalFlags,
        "Lune path first lair"
    );
    populateLair(
        LocationID::LAIR_LUNE_PATH_2,
        ItemIndex::NPC_NOME,
        &normalFlags,
        "Lune path second lair"
    );
    populateLair(
        LocationID::LAIR_LUNE_BOTTOM,
        ItemIndex::NPC_MUSHROOM_EMBLEM_F,
        &normalFlags,
        "Lune bottom lair"
    );
    populateLair(
        LocationID::LAIR_LUNE_MIDDLE_LEFT,
        ItemIndex::NPC_DANCING_GRANDMA,
        &normalFlags,
        "Lune middle left lair"
    );
    populateLair(
        LocationID::LAIR_LUNE_MIDDLE_RIGHT,
        ItemIndex::NPC_DANCING_GRANDMA2,
        &normalFlags,
        "Lune middle right lair"
    );
    populateLair(
        LocationID::LAIR_LUNE_MUSHROOM_DREAM,
        ItemIndex::NPC_SNAIL_EMBLEM_E,
        &normalFlags,
        "Lune Mushroom dream locked lair"
    );
    populateLair(
        LocationID::LAIR_LUNE_POSEIDON_BOSS,
        ItemIndex::NPC_MOUNTAIN_KING,
        &normalFlags,
        "Lune Poseidon boss lair"
    );
    /*
        Act 5
    */
    populateChest(
        LocationID::CHEST_LEOS_LAB_IN_DOOR,
        ItemIndex::ZANTETSU_SWORD,
        &normalFlags,
        "Leo's Lab main room chest inside door",
        43
    );
    populateChest(
        LocationID::CHEST_LEOS_LAB_POWER_PLANT,
        ItemIndex::LIGHT_ARMOR,
        &normalFlags,
        "Power Plant chest",
        44
    );
    populateChest(
        LocationID::CHEST_MODEL_TOWN1_SOUTH,
        ItemIndex::GEMS_EXP_50,
        &normalFlags,
        "Model Town 1 south chest",
        45
    );
    populateChest(
        LocationID::CHEST_MODEL_TOWN1_NORTH_LEFT,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Model Town 1 north left chest",
        46
    );
    populateChest(
        LocationID::CHEST_MODEL_TOWN1_NORTH_RIGHT,
        ItemIndex::GEMS_EXP_80,
        &normalFlags,
        "Model Town 1 north right chest",
        47
    );
    populateChest(
        LocationID::CHEST_MODEL_TOWN2_TOP,
        ItemIndex::STRANGE_BOTTLE,
        &normalFlags,
        "Model Town 2 top chest",
        48
    );
    populateChest(
        LocationID::CHEST_MODEL_TOWN2_BOTTOM,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Model Town 2 bottom chest",
        49
    );
    populateNpcItem(
        LocationID::SECRET_UNDER_DRAWERS_LOCKED_ROOM,
        ItemIndex::EMBLEM_G,
        &normalFlags,
        "Leo's Lab secret under drawers in locked room",
        NpcItemIndex::ITEM_EMBLEM_G
    );
    populateNpcItem(
        LocationID::NPC_DRAWERS_LOCKED_ROOM,
        ItemIndex::MYSTIC_ARMOR,
        &normalFlags,
        "Leo's Lab drawers in locked room",
        NpcItemIndex::ITEM_CHEST_OF_DRAWERS_MYSTIC_ARMOR
    );
    populateNpcItem(
        LocationID::NPC_PLANT_THROUGH_MOUSEHOLE,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Leo's Lab plant through mouse hole",
        NpcItemIndex::ITEM_PLANT_HERB
    );
    populateNpcItem(
        LocationID::NPC_LEOS_CAT_DREAM,
        ItemIndex::DOOR_KEY,
        &normalFlags,
        "Leo's Lab sleeping cat dream",
        NpcItemIndex::ITEM_CAT_DOOR_KEY
    );
    populateNpcItem(
        LocationID::NPC_UPSTAIRS_PLANT,
        ItemIndex::ACTINIDIA_LEAF,
        &normalFlags,
        "Leo's Lab upstairs plant",
        NpcItemIndex::ITEM_PLANT_ACTINIDIA_LEAVES
    );
    populateNpcItem(
        LocationID::NPC_ATTIC_DRAWERS,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Leo's Lab attic drawers",
        NpcItemIndex::ITEM_CHEST_OF_DRAWERS_HERB
    );
    populateNpcItem(
        LocationID::NPC_MARIE,
        ItemIndex::PURPLE_STONE,
        &normalFlags,
        "Leo's Lab attic Marie",
        NpcItemIndex::ITEM_MARIE
    );
    populateNpcItem(
        LocationID::NPC_MOUSE_IN_MOUSEHOLE,
        ItemIndex::SPARK_BOMB,
        &normalFlags,
        "Leo's Lab mouse in mouse hole",
        NpcItemIndex::ITEM_MOUSE_SPARK_BOMB
    );
    populateNpcItem(
        LocationID::CRYSTAL_LEOS_BASEMENT,
        ItemIndex::GEMS_EXP_300,
        &normalFlags,
        "Leo's Basement Crystal Fairy",
        NpcItemIndex::ITEM_CRYSTAL_LEOS_LAB_BASEMENT
    );
    populateNpcItem(
        LocationID::CRYSTAL_MODEL_TOWN1,
        ItemIndex::GEMS_EXP_300,
        &normalFlags,
        "Model Town 1 Crystal Fairy",
        NpcItemIndex::ITEM_CRYSTAL_MODEL_TOWN
    );
    populateNpcItem(
        LocationID::CRYSTAL_POWER_PLANT,
        ItemIndex::GEMS_EXP_300,
        &normalFlags,
        "Power Plant Crystal Fairy",
        NpcItemIndex::ITEM_CRYSTAL_POWER_PLANT
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B1_UP_FIRST_PIPE,
        ItemIndex::NPC_CAT_MOUSEHOLE1,
        &normalFlags,
        "Leo's Basement B1 lair up center pipe"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B1_NORTHWEST,
        ItemIndex::NPC_PLANT_HERB,
        &normalFlags,
        "Leo's Basement B1 northwest lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B1_SOUTHWEST,
        ItemIndex::NPC_PLANT,
        &normalFlags,
        "Leo's Basement B1 southwest lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B1_BUILD_PIPE_RIGHT,
        ItemIndex::NPC_GREAT_DOOR_ZANTETSU_SWORD,
        &normalFlags,
        "Leo's Basement B1 build center pipe right to lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B1_SMALL_ISLAND_RIGHT,
        ItemIndex::NPC_CAT_MOUSEHOLE2,
        &normalFlags,
        "Leo's Basement B1 lair on bottom right small island"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B1_RIGHT_SIDE_BOTTOM,
        ItemIndex::NPC_CAT3,
        &normalFlags,
        "Leo's Basement B1 right side pipe bottom lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B1_RIGHT_SIDE_TOP,
        ItemIndex::NPC_GREAT_DOOR_KITCHEN,
        &normalFlags,
        "Leo's Basement B1 right side pipe top lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B1_TOP,
        ItemIndex::NPC_CHEST_OF_DRAWERS_MYSTIC_ARMOR,
        &normalFlags,
        "Leo's Basement B1 north lair near stairs down"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B2_RIGHT_FIRE_PIPES,
        ItemIndex::NPC_CAT_DOOR_KEY,
        &normalFlags,
        "Leo's Basement B2 right side middle of fire pipe lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B2_INSIDE_PIPE,
        ItemIndex::NPC_MOUSE_HOLE,
        &normalFlags,
        "Leo's Basement B2 right side inside pipe lair"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B2_LEFT_SIDE_1,
        ItemIndex::NPC_STEPS_UPSTAIRS,
        &normalFlags,
        "Leo's Basement B2 left side first lair from bottom"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B2_LEFT_SIDE_2,
        ItemIndex::NPC_GREAT_DOOR_MODEL_TOWNS,
        &normalFlags,
        "Leo's Basement B2 left side second lair from bottom"
    );
    populateLair(
        LocationID::LAIR_LEOS_BASEMENT_B2_LEFT_SIDE_3,
        ItemIndex::NPC_MODEL_TOWN1,
        &normalFlags,
        "Leo's Basement B2 left side top lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_1_SOUTHWEST,
        ItemIndex::NPC_MOUSE2,
        &normalFlags,
        "Model Town 1 southwest lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_1_FAR_WEST,
        ItemIndex::NPC_CHEST_OF_DRAWERS,
        &normalFlags,
        "Model Town 1 lair up far left side"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_1_WEST_POPUP_LEFT,
        ItemIndex::NPC_MOUSE3,
        &normalFlags,
        "Model Town 1 west side left popup lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_1_WEST_POPUP_RIGHT,
        ItemIndex::NPC_MOUSE4,
        &normalFlags,
        "Model Town 1 west side right popup lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_1_WEST_FIELD,
        ItemIndex::NPC_PLANT2,
        &normalFlags,
        "Model Town 1 west side north field lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_1_EAST_POPUP_LEFT,
        ItemIndex::NPC_MOUSE_SPARK_BOMB,
        &normalFlags,
        "Model Town 1 east side left popup lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_1_EAST_POPUP_RIGHT,
        ItemIndex::NPC_STEPS_MARIE,
        &normalFlags,
        "Model Town 1 east side right popup lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_1_SOUTHEAST,
        ItemIndex::NPC_MODEL_TOWN2,
        &normalFlags,
        "Model Town 1 southeast lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_2_SOUTHWEST,
        ItemIndex::NPC_MOUSE5,
        &normalFlags,
        "Model Town 2 southwest lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_2_CENTER_WEST,
        ItemIndex::NPC_CHEST_OF_DRAWERS_ATTIC,
        &normalFlags,
        "Model Town 2 center west lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_2_NORTHWEST,
        ItemIndex::NPC_PLANT_ACTINIDIA_LEAVES,
        &normalFlags,
        "Model Town 2 northwest lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_2_NORTHEAST,
        ItemIndex::NPC_CAT4,
        &normalFlags,
        "Model Town 2 northeast lair"
    );
    populateLair(
        LocationID::LAIR_MODEL_TOWN_2_SOUTHEAST,
        ItemIndex::NPC_STAIRS_POWER_PLANT,
        &normalFlags,
        "Model Town 2 southeast lair"
    );
    populateLair(
        LocationID::LAIR_POWER_PLANT,
        ItemIndex::NPC_DOLL,
        &normalFlags,
        "Power Plant southeast lair"
    );
    populateLair(
        LocationID::LAIR_POWER_PLANT_TIN_DOLL_BOSS,
        ItemIndex::NPC_MARIE,
        &normalFlags,
        "Power Plant Tin Doll boss lair"
    );
    /*
        Act 6
    */
    populateChest(
        LocationID::CHEST_TORTURE_CHAMBER1_LEFT,
        ItemIndex::GEMS_EXP_80,
        &normalFlags,
        "Torture Chamber B1 left chest",
        50
    );
    populateChest(
        LocationID::CHEST_TORTURE_CHAMBER1_TOP_RIGHT,
        ItemIndex::SPIRIT_SWORD,
        &normalFlags,
        "Torture Chamber B1 top right chest",
        51
    );
    populateChest(
        LocationID::CHEST_TORTURE_CHAMBER2_NORTH_INVISIBLE,
        ItemIndex::STRANGE_BOTTLE,
        &normalFlags,
        "Torture Chamber B2 north invisible chest",
        52
    );
    populateChest(
        LocationID::CHEST_TORTURE_CHAMBER2_SOUTHWEST_INVISIBLE,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Torture Chamber B2 southwest invisible chest",
        53
    );
    populateChest(
        LocationID::CHEST_TORTURE_CHAMBER2_MIDDLE_INVISIBLE,
        ItemIndex::GEMS_EXP_100,
        &normalFlags,
        "Torture Chamber B2 center invisible chest",
        54
    );
    populateChest(
        LocationID::CHEST_TORTURE_CHAMBER3_NORTHWEST,
        ItemIndex::EMBLEM_B,
        &normalFlags,
        "Torture Chamber B3 northwest chest",
        55
    );
    populateChest(
        LocationID::CHEST_RIGHT_TOWER2_LEFT,
        ItemIndex::GEMS_EXP_80,
        &normalFlags,
        "Right Tower floor 2 left chest",
        56
    );
    populateChest(
        LocationID::CHEST_RIGHT_TOWER2_RIGHT,
        ItemIndex::GEMS_EXP_80,
        &normalFlags,
        "Right Tower floor 2 right chest",
        57
    );
    populateChest(
        LocationID::CHEST_RIGHT_TOWER3_TOP_LEFT,
        ItemIndex::GEMS_EXP_100,
        &normalFlags,
        "Right Tower floor 3 top left chest",
        58
    );
    populateChest(
        LocationID::CHEST_RIGHT_TOWER3_BOTTOM_RIGHT,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Right Tower floor 3 bottom right chest",
        59
    );
    populateNpcItem(
        LocationID::NPC_SLEEPING_SOLDIER,
        ItemIndex::ELEMENTAL_MAIL,
        &normalFlags,
        "Magridd Castle Sleeping Soldier",
        NpcItemIndex::ITEM_SOLDIER_ELEMENTAL_MAIL
    );
    populateNpcItem(
        LocationID::NPC_QUEEN_MAGRIDD,
        ItemIndex::VIP_CARD,
        &missableFlags,
        "Magridd Castle Queen Magridd",
        NpcItemIndex::ITEM_QUEEN_MAGRIDD
    );
    populateNpcItem(
        LocationID::SECRET_UNDER_QUEEN_MAGRIDD,
        ItemIndex::SUPER_BRACELET,
        &normalFlags,
        "Magridd Castle under Queen Magridd",
        NpcItemIndex::ITEM_SUPER_BRACELET
    );
    populateNpcItem(
        LocationID::SECRET_CONCERT_HALL_SOLDIER,
        ItemIndex::PLATINUM_CARD,
        &normalFlags,
        "Magridd Castle Concert Hall Soldier",
        NpcItemIndex::ITEM_SOLDIER_PLATINUM_CARD
    );
    populateNpcItem(
        LocationID::NPC_SOUTHEAST_MAID_BEHIND_COUNTER,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "Magridd Castle southeast house Maid",
        NpcItemIndex::ITEM_MAID_HERB
    );
    populateNpcItem(
        LocationID::SECRET_OUTSIDE_CASTLE,
        ItemIndex::EMBLEM_H,
        &normalFlags,
        "Magridd Castle secret outside castle",
        NpcItemIndex::ITEM_EMBLEM_H
    );
    populateNpcItem(
        LocationID::NPC_KING_MAGRIDD,
        ItemIndex::BLACK_STONE,
        &normalFlags,
        "Magridd Castle King Magridd",
        NpcItemIndex::ITEM_KING_MAGRIDD
    );
    populateNpcItem(
        LocationID::NPC_LEO_CUTSCENE,
        ItemIndex::MOBILE_KEY,
        &normalFlags,
        "Right Tower Dr Leo cutscene",
        NpcItemIndex::ITEM_DR_LEO
    );
    populateNpcItem(
        LocationID::SECRET_TORTURE_CHAMBER1_TOP_RIGHT,
        ItemIndex::HARP_STRING,
        &normalFlags,
        "Torture Chamber B1 top right skeleton secret",
        NpcItemIndex::ITEM_HARP_STRING
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER1_CENTER,
        ItemIndex::NPC_SOLDIER2,
        &normalFlags,
        "Torture Chamber B1 center lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER1_NORTHWEST,
        ItemIndex::NPC_SOLDIER,
        &normalFlags,
        "Torture Chamber B1 northwest lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER2_RIGHT_1,
        ItemIndex::NPC_SINGER_CONCERT_HALL,
        &normalFlags,
        "Torture Chamber B2 right side bottom lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER2_RIGHT_2,
        ItemIndex::NPC_SOLDIER3,
        &normalFlags,
        "Torture Chamber B2 right side top lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER2_RIGHT_3,
        ItemIndex::NPC_SOLDIER4,
        &normalFlags,
        "Torture Chamber B2 rightmost lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER2_LEFT_1,
        ItemIndex::NPC_SOLDIER5,
        &normalFlags,
        "Torture Chamber B2 left side top lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER2_LEFT_2,
        ItemIndex::NPC_SOLDIER_ELEMENTAL_MAIL,
        &normalFlags,
        "Torture Chamber B2 left side left popup lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER2_LEFT_3,
        ItemIndex::NPC_SOLDIER6,
        &normalFlags,
        "Torture Chamber B2 left side right popup lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER3_LEFT,
        ItemIndex::NPC_MAID,
        &normalFlags,
        "Torture Chamber B3 left side lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER3_CENTER_LOWER,
        ItemIndex::NPC_SOLDIER_DOK,
        &normalFlags,
        "Torture Chamber B3 center lower lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER3_CENTER_UPPER,
        ItemIndex::NPC_SOLDIER_LEFT_TOWER,
        &normalFlags,
        "Torture Chamber B3 center upper lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER3_RIGHT_TOP,
        ItemIndex::NPC_SOLDIER_PLATINUM_CARD,
        &normalFlags,
        "Torture Chamber B3 right side top lair"
    );
    populateLair(
        LocationID::LAIR_TORTURE_CHAMBER3_RIGHT_BOTTOM,
        ItemIndex::NPC_SINGER,
        &normalFlags,
        "Torture Chamber B3 right side bottom lair"
    );
    populateLair(
        LocationID::LAIR_LEFT_TOWER_FLOOR1,
        ItemIndex::NPC_SOLDIER_SOUL_OF_REALITY,
        &normalFlags,
        "Left Tower first floor lair"
    );
    populateLair(
        LocationID::LAIR_LEFT_TOWER_FLOOR2_LEFT,
        ItemIndex::NPC_MAID2,
        &normalFlags,
        "Left Tower second floor left lair"
    );
    populateLair(
        LocationID::LAIR_LEFT_TOWER_FLOOR2_RIGHT,
        ItemIndex::NPC_QUEEN_MAGRIDD,
        &normalFlags,
        "Left Tower second floor right lair"
    );
    populateLair(
        LocationID::LAIR_LEFT_TOWER_FLOOR3_SOUTHEAST,
        ItemIndex::NPC_SOLDIER7,
        &normalFlags,
        "Left Tower third floor southeast lair"
    );
    populateLair(
        LocationID::LAIR_LEFT_TOWER_FLOOR3_PRISON_SOUTHWEST,
        ItemIndex::NPC_DR_LEO,
        &normalFlags,
        "Left Tower third floor prison southwest lair"
    );
    populateLair(
        LocationID::LAIR_LEFT_TOWER_FLOOR3_PRISON_NORTHEAST,
        ItemIndex::NPC_SOLDIER_WITH_LEO,
        &normalFlags,
        "Left Tower third floor prison northeast lair"
    );
    populateLair(
        LocationID::LAIR_LEFT_TOWER_FLOOR3_PRISON_NORTHWEST,
        ItemIndex::NPC_SOLDIER_RIGHT_TOWER,
        &normalFlags,
        "Left Tower third floor prison northwest lair"
    );
    populateLair(
        LocationID::LAIR_RIGHT_TOWER_FLOOR1_NORTHWEST,
        ItemIndex::NPC_SOLDIER8,
        &normalFlags,
        "Right Tower first floor northwest lair"
    );
    populateLair(
        LocationID::LAIR_RIGHT_TOWER_FLOOR1_SOUTHEAST,
        ItemIndex::NPC_MAID_HERB,
        &normalFlags,
        "Right Tower first floor southeast lair"
    );
    populateLair(
        LocationID::LAIR_RIGHT_TOWER_FLOOR1_CENTER,
        ItemIndex::NPC_SOLDIER_CASTLE,
        &normalFlags,
        "Right Tower first floor center lair"
    );
    populateLair(
        LocationID::LAIR_RIGHT_TOWER_FLOOR2_RIGHT,
        ItemIndex::NPC_SOLDIER9,
        &normalFlags,
        "Right Tower second floor right side lair"
    );
    populateLair(
        LocationID::LAIR_RIGHT_TOWER_FLOOR2_CENTER_SECRET,
        ItemIndex::NPC_SOLDIER10,
        &normalFlags,
        "Right Tower second floor center secret room lair"
    );
    populateLair(
        LocationID::LAIR_RIGHT_TOWER_FLOOR3,
        ItemIndex::NPC_SOLDIER11,
        &normalFlags,
        "Right Tower third floor northeast lair"
    );
    populateLair(
        LocationID::LAIR_RIGHT_TOWER_DEMON_BIRD_BOSS,
        ItemIndex::NPC_KING_MAGRIDD,
        &normalFlags,
        "Right Tower Demon Bird boss lair"
    );
    /*
        Act 7
    */
    populateChest(
        LocationID::CHEST_WORLD_OF_EVIL1_RIGHT,
        ItemIndex::MEDICAL_HERB,
        &normalFlags,
        "World of Evil first area right chest",
        60
    );
    populateChest(
        LocationID::CHEST_WORLD_OF_EVIL1_LEFT,
        ItemIndex::GEMS_EXP_200,
        &normalFlags,
        "World of Evil first area left chest",
        61
    );
    populateChest(
        LocationID::CHEST_WORLD_OF_EVIL1_TELEPORTER,
        ItemIndex::RED_HOT_BALL,
        &normalFlags,
        "World of Evil teleporter chest",
        62
    );
    populateChest(
        LocationID::CHEST_WORLD_OF_EVIL2_RIGHT,
        ItemIndex::SOUL_ARMOR,
        &normalFlags,
        "World of Evil second area right side chest",
        63
    );
    populateChest(
        LocationID::CHEST_WORLD_OF_EVIL3_RIGHT,
        ItemIndex::SOUL_BLADE,
        &normalFlags,
        "World of Evil third area right side chest",
        64
    );
    populateChest(
        LocationID::CHEST_WORLD_OF_EVIL3_LEFT,
        ItemIndex::GEMS_EXP_100,
        &normalFlags,
        "World of Evil third area left side chest",
        65
    );

    allLocationsCount = (int)LocationID::CHEST_WORLD_OF_EVIL3_LEFT + 1;
}
