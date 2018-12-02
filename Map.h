#ifndef __MAP_H__
#define __MAP_H__

#include <list>
#include <vector>


#define LAIR 0
#define ITEM 1

#define NUMBER_OF_REGIONS   79
#define NUMBER_OF_GOALS     78

#define GOAL_TO_FIRST_REGION 255


enum {
    CHEST_SWORD_OF_LIFE                = 0,
    CHEST_DREAM_ROD                    = 5,
    CHEST_LEOS_BRUSH                   = 6,
    CHEST_MOLES_RIBBON                 = 10,
    CHEST_DELICIOUS_SEEDS              = 14,
    CHEST_BIG_PEARL                    = 23,
    CHEST_EMBLEM_D                     = 24,
    CHEST_LUCKY_BLADE                  = 40,
    CHEST_ZANTETSU_SWORD               = 43,
    CHEST_SPIRIT_SWORD                 = 51,
    CHEST_EMBLEM_B                     = 55,
    CHEST_RED_HOT_BALL                 = 62,
    CHEST_SOUL_ARMOR                   = 63,
    CHEST_SOUL_BLADE                   = 64,
    ITEM_TOOL_SHOP_OWNER               = 66,
    ITEM_EMBLEM_A                      = 67,
    ITEM_GOAT_PEN                      = 68,
    ITEM_TEDDY                         = 69,
    ITEM_PASS                          = 70,
    ITEM_SECRET_CAVE_TILE              = 71,
    ITEM_VILLAGE_CHIEF                 = 72,
    ITEM_MAGICIAN                      = 73,
    ITEM_CRYSTAL_RECOVERY_SWORD        = 74,
    ITEM_CRYSTAL_GRASS_VALLEY          = 75,
    ITEM_CRYSTAL_UNDERGROUND_CASTLE    = 76,
    ITEM_BIRD_RED_HOT_MIRROR           = 77,
    ITEM_CRYSTAL_MAGIC_BELL            = 78,
    ITEM_WOODSTIN_TRIO                 = 79,
    ITEM_GREENWOODS_GUARDIAN           = 80,
    ITEM_GREENWOOD_LEAVES              = 81,
    ITEM_MOLE_SHIELD_BRACELET          = 82,
    ITEM_SQUIRREL_PSYCHO_SWORD         = 83,
    ITEM_SQUIRREL_EMBLEM_C             = 84,
    ITEM_WATER_SHRINE_TILE             = 85,
    ITEM_CRYSTAL_LIGHT_ARROW           = 86,
    ITEM_CRYSTAL_LOST_MARSH            = 87,
    ITEM_CRYSTAL_WATER_SHRINE          = 88,
    ITEM_CRYSTAL_FIRE_SHRINE           = 89,
    ITEM_MOUNTAIN_KING                 = 90,
    ITEM_BOY_MUSHROOM_SHOES            = 91,
    ITEM_NOME                          = 92,
    ITEM_SNAIL_EMBLEM_E                = 93,
    ITEM_EMBLEM_F                      = 94,
    ITEM_CRYSTAL_MOUNTAIN_OF_SOULS     = 95,
    ITEM_CRYSTAL_LUNE                  = 96,
    ITEM_EMBLEM_G                      = 97,
    ITEM_CHEST_OF_DRAWERS_MYSTIC_ARMOR = 98,
    ITEM_PLANT_HERB                    = 99,
    ITEM_CAT_DOOR_KEY                  = 100,
    ITEM_PLANT_ACTINIDIA_LEAVES        = 101,
    ITEM_CHEST_OF_DRAWERS_HERB         = 102,
    ITEM_MARIE                         = 103,
    ITEM_MOUSE_SPARK_BOMB              = 104,
    ITEM_CRYSTAL_LEOS_LAB_BASEMENT     = 105,
    ITEM_CRYSTAL_MODEL_TOWN            = 106,
    ITEM_CRYSTAL_POWER_PLANT           = 107,
    ITEM_SOLDIER_ELEMENTAL_MAIL        = 108,
    ITEM_SUPER_BRACELET                = 109,
    ITEM_QUEEN_MAGRIDD                 = 110,
    ITEM_SOLDIER_PLATINUM_CARD         = 111,
    ITEM_MAID_HERB                     = 112,
    ITEM_EMBLEM_H                      = 113,
    ITEM_KING_MAGRIDD                  = 114,
    ITEM_DR_LEO                        = 115,
    ITEM_HARP_STRING                   = 116,
    ITEM_MERMAID_HERB                  = 117,
    ITEM_MERMAID_BUBBLE_ARMOR          = 118,
    ITEM_MERMAID_MAGIC_FLARE           = 119,
    ITEM_MERMAID_QUEEN                 = 120,
    ITEM_MERMAID_RED_HOT_STICK         = 121,
    ITEM_LUE                           = 122,
    ITEM_CRYSTAL_ROCKBIRD              = 123,
    ITEM_CRYSTAL_SEABED_NEAR_BLESTER   = 124,
    ITEM_CRYSTAL_SEABED_NEAR_DUREAN    = 125
};

//enum {
//    NPC_OLD_WOMAN                     = 2,
//    NPC_TOOL_SHOP_OWNER               = 6,
//    NPC_TULIP                         = 7,
//    NPC_BRIDGE_GUARD                  = 8,
//    NPC_VILLAGE_CHIEF                 = 9,
//    NPC_IVY_CHEST_ROOM                = 13,
//    NPC_WATER_MILL                    = 14,
//    NPC_GOAT_HERB                     = 15,
//    NPC_LISA                          = 16,
//    NPC_TULIP2                        = 17,
//    NPC_ARCHITECT                     = 18,
//    NPC_IVY                           = 19,
//    NPC_GOAT                          = 21,
//    NPC_TEDDY                         = 22,
//    NPC_TULIP3                        = 24,
//    NPC_LEOS_HOUSE                    = 26,
//    NPC_LONELY_GOAT                   = 29,
//    NPC_TULIP_PASS                    = 34,
//    NPC_BOY_CABIN                     = 35,
//    NPC_BOY_CAVE                      = 37,
//    NPC_OLD_MAN                       = 38,
//    NPC_OLD_MAN2                      = 39,
//    NPC_IVY2                          = 40,
//    NPC_IVY_EMBLEM_A                  = 41,
//    NPC_IVY_RECOVERY_SWORD            = 42,
//    NPC_TULIP4                        = 43,
//    NPC_GOAT2                         = 44,
//    NPC_BIRD_RED_HOT_MIRROR           = 50,
//    NPC_BIRD                          = 51,
//    NPC_DOG                           = 55,
//    NPC_DOG2                          = 56,
//    NPC_DOG3                          = 58,
//    NPC_MOLE_SHIELD_BRACELET          = 59,
//    NPC_SQUIRREL_EMBLEM_C             = 60,
//    NPC_SQUIRREL_PSYCHO_SWORD         = 62,
//    NPC_BIRD2                         = 65,
//    NPC_MOLE_SOUL_OF_LIGHT            = 68,
//    NPC_DEER                          = 69,
//    NPC_CROCODILE                     = 73,
//    NPC_SQUIRREL                      = 74,
//    NPC_GREENWOODS_GUARDIAN           = 75,
//    NPC_MOLE                          = 76,
//    NPC_DOG4                          = 81,
//    NPC_SQUIRREL_ICE_ARMOR            = 83,
//    NPC_SQUIRREL2                     = 84,
//    NPC_DOG5                          = 85,
//    NPC_CROCODILE2                    = 86,
//    NPC_MOLE2                         = 87,
//    NPC_SQUIRREL3                     = 88,
//    NPC_BIRD_GREENWOOD_LEAF           = 92,
//    NPC_MOLE3                         = 93,
//    NPC_DEER_MAGIC_BELL               = 94,
//    NPC_BIRD3                         = 95,
//    NPC_CROCODILE3                    = 106,
//    NPC_MONMO                         = 109,
//    NPC_DOLPHIN                       = 116,
//    NPC_ANGELFISH                     = 123,
//    NPC_MERMAID                       = 124,
//    NPC_ANGELFISH2                    = 126,
//    NPC_MERMAID_PEARL                 = 130,
//    NPC_MERMAID2                      = 131,
//    NPC_DOLPHIN_SAVES_LUE             = 132,
//    NPC_MERMAID_STATUE_BLESTER        = 133,
//    NPC_MERMAID_RED_HOT_STICK         = 134,
//    NPC_LUE                           = 135,
//    NPC_MERMAID3                      = 138,
//    NPC_MERMAID_NANA                  = 141,
//    NPC_MERMAID4                      = 145,
//    NPC_DOLPHIN2                      = 147,
//    NPC_MERMAID_STATUE_ROCKBIRD       = 149,
//    NPC_MERMAID_BUBBLE_ARMOR          = 153,
//    NPC_MERMAID5                      = 156,
//    NPC_MERMAID6                      = 157,
//    NPC_MERMAID_TEARS                 = 159,
//    NPC_MERMAID_STATUE_DUREAN         = 163,
//    NPC_ANGELFISH3                    = 165,
//    NPC_ANGELFISH_SOUL_OF_SHIELD      = 169,
//    NPC_MERMAID_MAGIC_FLARE           = 173,
//    NPC_MERMAID_QUEEN                 = 174,
//    NPC_MERMAID_STATUE_GHOST_SHIP     = 177,
//    NPC_DOLPHIN_SECRET_CAVE           = 179,
//    NPC_MERMAID7                      = 181,
//    NPC_ANGELFISH4                    = 182,
//    NPC_MERMAID8                      = 184,
//    NPC_DOLPHIN_PEARL                 = 185,
//    NPC_MERMAID9                      = 186,
//    NPC_GRANDPA                       = 193,
//    NPC_GIRL                          = 194,
//    NPC_MUSHROOM                      = 195,
//    NPC_BOY                           = 196,
//    NPC_GRANDPA2                      = 203,
//    NPC_SNAIL_JOCKEY                  = 204,
//    NPC_NOME                          = 206,
//    NPC_BOY2                          = 207,
//    NPC_MUSHROOM_EMBLEM_F             = 213,
//    NPC_DANCING_GRANDMA               = 217,
//    NPC_DANCING_GRANDMA2              = 222,
//    NPC_SNAIL_EMBLEM_E                = 223,
//    NPC_BOY_MUSHROOM_SHOES            = 224,
//    NPC_GRANDMA                       = 225,
//    NPC_GIRL2                         = 226,
//    NPC_MUSHROOM2                     = 229,
//    NPC_SNAIL_RACER                   = 230,
//    NPC_SNAIL_RACER2                  = 231,
//    NPC_GIRL3                         = 233,
//    NPC_MUSHROOM3                     = 237,
//    NPC_SNAIL                         = 238,
//    NPC_GRANDPA3                      = 239,
//    NPC_SNAIL2                        = 241,
//    NPC_GRANDPA4                      = 243,
//    NPC_GRANDPA_LUNE                  = 245,
//    NPC_GRANDPA5                      = 246,
//    NPC_MOUNTAIN_KING                 = 250,
//    NPC_PLANT_HERB                    = 251,
//    NPC_PLANT                         = 253,
//    NPC_CHEST_OF_DRAWERS_MYSTIC_ARMOR = 254,
//    NPC_CAT                           = 255,
//    NPC_GREAT_DOOR_ZANTETSU_SWORD     = 260,
//    NPC_CAT2                          = 262,
//    NPC_GREAT_DOOR                    = 268,
//    NPC_CAT3                          = 269,
//    NPC_MODEL_TOWN1                   = 272,
//    NPC_GREAT_DOOR_MODEL_TOWNS        = 274,
//    NPC_STEPS_UPSTAIRS                = 276,
//    NPC_CAT_DOOR_KEY                  = 280,
//    NPC_MOUSE                         = 283,
//    NPC_MARIE                         = 287,
//    NPC_DOLL                          = 294,
//    NPC_CHEST_OF_DRAWERS              = 295,
//    NPC_PLANT2                        = 297,
//    NPC_MOUSE2                        = 299,
//    NPC_MOUSE_SPARK_BOMB              = 300,
//    NPC_MOUSE3                        = 302,
//    NPC_GREAT_DOOR_SOUL_OF_DETECTION  = 306,
//    NPC_MODEL_TOWN2                   = 309,
//    NPC_MOUSE4                        = 313,
//    NPC_STEPS_MARIE                   = 314,
//    NPC_CHEST_OF_DRAWERS2             = 315,
//    NPC_PLANT_ACTINIDIA_LEAVES        = 316,
//    NPC_MOUSE5                        = 321,
//    NPC_CAT4                          = 322,
//    NPC_STAIRS_POWER_PLANT            = 324,
//    NPC_SOLDIER                       = 326,
//    NPC_SOLDIER2                      = 327,
//    NPC_SOLDIER3                      = 332,
//    NPC_SOLDIER_ELEMENTAL_MAIL        = 334,
//    NPC_SOLDIER4                      = 335,
//    NPC_SOLDIER5                      = 339,
//    NPC_SINGER_CONCERT_HALL           = 340,
//    NPC_SOLDIER6                      = 341,
//    NPC_MAID                          = 344,
//    NPC_SOLDIER_LEFT_TOWER            = 346,
//    NPC_SOLDIER_DOK                   = 347,
//    NPC_SOLDIER_PLATINUM_CARD         = 349,
//    NPC_SINGER                        = 351,
//    NPC_SOLDIER_SOUL_OF_REALITY       = 358,
//    NPC_MAID2                         = 363,
//    NPC_QUEEN_MAGRIDD                 = 364,
//    NPC_SOLDIER_WITH_LEO              = 366,
//    NPC_SOLDIER_RIGHT_TOWER           = 367,
//    NPC_DR_LEO                        = 368,
//    NPC_SOLDIER7                      = 370,
//    NPC_SOLDIER8                      = 371,
//    NPC_MAID_HERB                     = 372,
//    NPC_SOLDIER_CASTLE                = 377,
//    NPC_SOLDIER9                      = 378,
//    NPC_SOLDIER10                     = 380,
//    NPC_SOLDIER11                     = 383,
//    NPC_KING_MAGRIDD                  = 385,
//};


enum {
    NPC_OLD_WOMAN                     = 2,
    NPC_TOOL_SHOP_OWNER               = 6,
    NPC_TULIP                         = 7,
    NPC_BRIDGE_GUARD                  = 8,
    NPC_VILLAGE_CHIEF                 = 9,
    NPC_IVY_CHEST_ROOM                = 13,
    NPC_WATER_MILL                    = 14,
    NPC_GOAT_HERB                     = 15,
    NPC_LISA                          = 16,
    NPC_TULIP2                        = 17,
    NPC_ARCHITECT                     = 18,
    NPC_IVY                           = 19,
    NPC_GOAT                          = 21,
    NPC_TEDDY                         = 22,
    NPC_TULIP3                        = 24,
    NPC_LEOS_HOUSE                    = 26,
    NPC_LONELY_GOAT                   = 29,
    NPC_TULIP_PASS                    = 34,
    NPC_BOY_CABIN                     = 35,
    NPC_BOY_CAVE                      = 37,
    NPC_OLD_MAN                       = 40,
    NPC_OLD_MAN2                      = 41,
    NPC_IVY2                          = 42,
    NPC_IVY_EMBLEM_A                  = 43,
    NPC_IVY_RECOVERY_SWORD            = 44,
    NPC_TULIP4                        = 46,
    NPC_GOAT2                         = 47,
    NPC_BIRD_RED_HOT_MIRROR           = 55,
    NPC_BIRD                          = 56,
    NPC_DOG                           = 60,
    NPC_DOG2                          = 61,
    NPC_DOG3                          = 63,
    NPC_MOLE_SHIELD_BRACELET          = 64,
    NPC_SQUIRREL_EMBLEM_C             = 65,
    NPC_SQUIRREL_PSYCHO_SWORD         = 67,
    NPC_BIRD2                         = 70,
    NPC_MOLE_SOUL_OF_LIGHT            = 73,
    NPC_DEER                          = 74,
    NPC_CROCODILE                     = 78,
    NPC_SQUIRREL                      = 79,
    NPC_GREENWOODS_GUARDIAN           = 80,
    NPC_MOLE                          = 81,
    NPC_DOG4                          = 86,
    NPC_SQUIRREL_ICE_ARMOR            = 88,
    NPC_SQUIRREL2                     = 89,
    NPC_DOG5                          = 90,
    NPC_CROCODILE2                    = 91,
    NPC_MOLE2                         = 92,
    NPC_SQUIRREL3                     = 93,
    NPC_BIRD_GREENWOOD_LEAF           = 97,
    NPC_MOLE3                         = 98,
    NPC_DEER_MAGIC_BELL               = 99,
    NPC_BIRD3                         = 100,
    NPC_CROCODILE3                    = 111,
    NPC_MONMO                         = 114,
    NPC_DOLPHIN                       = 124,
    NPC_ANGELFISH                     = 131,
    NPC_MERMAID                       = 132,
    NPC_ANGELFISH2                    = 134,
    NPC_MERMAID_PEARL                 = 138,
    NPC_MERMAID2                      = 139,
    NPC_DOLPHIN_SAVES_LUE             = 140,
    NPC_MERMAID_STATUE_BLESTER        = 141,
    NPC_MERMAID_RED_HOT_STICK         = 142,
    NPC_LUE                           = 143,
    NPC_MERMAID3                      = 146,
    NPC_MERMAID_NANA                  = 149,
    NPC_MERMAID4                      = 153,
    NPC_DOLPHIN2                      = 155,
    NPC_MERMAID_STATUE_ROCKBIRD       = 157,
    NPC_MERMAID_BUBBLE_ARMOR          = 161,
    NPC_MERMAID5                      = 164,
    NPC_MERMAID6                      = 165,
    NPC_MERMAID_TEARS                 = 167,
    NPC_MERMAID_STATUE_DUREAN         = 171,
    NPC_ANGELFISH3                    = 173,
    NPC_ANGELFISH_SOUL_OF_SHIELD      = 177,
    NPC_MERMAID_MAGIC_FLARE           = 181,
    NPC_MERMAID_QUEEN                 = 182,
    NPC_MERMAID_STATUE_GHOST_SHIP     = 185,
    NPC_DOLPHIN_SECRET_CAVE           = 187,
    NPC_MERMAID7                      = 189,
    NPC_ANGELFISH4                    = 190,
    NPC_MERMAID8                      = 192,
    NPC_DOLPHIN_PEARL                 = 193,
    NPC_MERMAID9                      = 194,
    NPC_GRANDPA                       = 201,
    NPC_GIRL                          = 202,
    NPC_MUSHROOM                      = 203,
    NPC_BOY                           = 204,
    NPC_GRANDPA2                      = 211,
    NPC_SNAIL_JOCKEY                  = 212,
    NPC_NOME                          = 214,
    NPC_BOY2                          = 215,
    NPC_MUSHROOM_EMBLEM_F             = 221,
    NPC_DANCING_GRANDMA               = 225,
    NPC_DANCING_GRANDMA2              = 230,
    NPC_SNAIL_EMBLEM_E                = 232,
    NPC_BOY_MUSHROOM_SHOES            = 233,
    NPC_GRANDMA                       = 234,
    NPC_GIRL2                         = 235,
    NPC_MUSHROOM2                     = 238,
    NPC_SNAIL_RACER                   = 239,
    NPC_SNAIL_RACER2                  = 240,
    NPC_GIRL3                         = 242,
    NPC_MUSHROOM3                     = 246,
    NPC_SNAIL                         = 247,
    NPC_GRANDPA3                      = 248,
    NPC_SNAIL2                        = 250,
    NPC_GRANDPA4                      = 252,
    NPC_GRANDPA_LUNE                  = 254,
    NPC_GRANDPA5                      = 255,
    NPC_MOUNTAIN_KING                 = 259,
    NPC_PLANT_HERB                    = 265,
    NPC_PLANT                         = 267,
    NPC_CHEST_OF_DRAWERS_MYSTIC_ARMOR = 268,
    NPC_CAT                           = 269,
    NPC_GREAT_DOOR_ZANTETSU_SWORD     = 274,
    NPC_CAT2                          = 276,
    NPC_GREAT_DOOR                    = 282,
    NPC_CAT3                          = 283,
    NPC_MODEL_TOWN1                   = 286,
    NPC_GREAT_DOOR_MODEL_TOWNS        = 288,
    NPC_STEPS_UPSTAIRS                = 290,
    NPC_CAT_DOOR_KEY                  = 294,
    NPC_MOUSE                         = 297,
    NPC_MARIE                         = 303,
    NPC_DOLL                          = 310,
    NPC_CHEST_OF_DRAWERS              = 311,
    NPC_PLANT2                        = 313,
    NPC_MOUSE2                        = 315,
    NPC_MOUSE_SPARK_BOMB              = 316,
    NPC_MOUSE3                        = 318,
    NPC_GREAT_DOOR_SOUL_OF_DETECTION  = 322,
    NPC_MODEL_TOWN2                   = 325,
    NPC_MOUSE4                        = 330,
    NPC_STEPS_MARIE                   = 331,
    NPC_CHEST_OF_DRAWERS2             = 332,
    NPC_PLANT_ACTINIDIA_LEAVES        = 333,
    NPC_MOUSE5                        = 338,
    NPC_CAT4                          = 339,
    NPC_STAIRS_POWER_PLANT            = 341,
    NPC_SOLDIER                       = 345,
    NPC_SOLDIER2                      = 346,
    NPC_SOLDIER3                      = 351,
    NPC_SOLDIER_ELEMENTAL_MAIL        = 353,
    NPC_SOLDIER4                      = 354,
    NPC_SOLDIER5                      = 358,
    NPC_SINGER_CONCERT_HALL           = 359,
    NPC_SOLDIER6                      = 360,
    NPC_MAID                          = 363,
    NPC_SOLDIER_LEFT_TOWER            = 365,
    NPC_SOLDIER_DOK                   = 366,
    NPC_SOLDIER_PLATINUM_CARD         = 368,
    NPC_SINGER                        = 370,
    NPC_SOLDIER_SOUL_OF_REALITY       = 377,
    NPC_MAID2                         = 382,
    NPC_QUEEN_MAGRIDD                 = 383,
    NPC_SOLDIER_WITH_LEO              = 385,
    NPC_SOLDIER_RIGHT_TOWER           = 386,
    NPC_DR_LEO                        = 387,
    NPC_SOLDIER7                      = 389,
    NPC_SOLDIER8                      = 390,
    NPC_MAID_HERB                     = 391,
    NPC_SOLDIER_CASTLE                = 396,
    NPC_SOLDIER9                      = 397,
    NPC_SOLDIER10                     = 399,
    NPC_SOLDIER11                     = 402,
    NPC_KING_MAGRIDD                  = 405,
};

class Element {
public:
    Element(int NewType, int NewIndex);
    ~Element();
    int Type;
    int Index;
};

class Region {
public:
    Region();
    ~Region();
    void InsertElement(int Type, int Index);
    void InsertGoal(int Index);
    std::list<Element> Contents;
    std::list<int> NextGoals;
};

class Goal {
public:
    Goal();
    ~Goal();
    void InsertElement(int Type, int Index);
    std::list<Element> Requirements;
    int Target;
    int Weight;
};


namespace Map {
    void InitMap(std::vector<Region> &RegionList, std::vector<Goal> &GoalList);
    void InitMap_v2(std::vector<Region> &RegionList, std::vector<Goal> &GoalList);
    void CalculateWeights(std::vector<Region> &RegionList, std::vector<Goal> &GoalList, int GoalIndex);
    void GetNonKeyNPCList(std::vector<int> &NonKeyNPCList);
    void GetNonKeyNPCList_v2(std::vector<int> &NonKeyNPCList);
    void GetNonKeyItemList(std::vector<int> &NonKeyChestList);
    void GetNonKeyItemList_v2(std::vector<int> &NonKeyChestList);
}

#endif // __MAP_H__
