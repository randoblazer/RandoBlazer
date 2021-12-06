#ifndef __ENEMIES_H__
#define __ENEMIES_H__


enum class EnemyType : unsigned char {
    NO_ENEMY           = 0x00,
    SOLID_ARM          = 0x1F,
    ACT1_GOBLIN        = 0x20,
    ACT1_IMP           = 0x21,
    ACT1_FLY           = 0x22,
    ACT1_PLANT         = 0x23,
    ACT1_SLIME         = 0x24,
    ACT1_TORCH         = 0x25,
    ACT1_ARMOR         = 0x26,
    ACT1_SPIKEY        = 0x27,
    ACT1_BIRD          = 0x28,
    ACT1_TORCH2        = 0x29,
    ACT1_BLOCK         = 0x2E,
    ACT2_WATER_DRAGON  = 0x2C,
    ACT2_MUDMAN        = 0x2D,
    ACT2_BUSH          = 0x2E,
    ACT2_STATUE        = 0x2F,
    ACT2_FLOWER        = 0x30,
    ACT2_FIRE_SPIRIT   = 0x33,
    ACT2_GHOST         = 0x35,
    ACT2_LIZARDMAN     = 0x37,
    ACT2_TP_LIZARDMAN  = 0x38,
    ELEMENTAL_STATUE   = 0x3D,
    ACT2_FIREMAN       = 0x48,
    ACT2_SCORPION      = 0x49,
    ACT3_URCHIN        = 0x32,
    ACT3_JELLYFISH     = 0x34,
    ACT3_CRAB          = 0x35,
    ACT3_RAY           = 0x36,
    ACT3_SEAHORSE      = 0x37,
    ACT3_PALM_TREE     = 0x3A,
    ACT3_ROCK          = 0x3B,
    ACT3_FISH          = 0x3C,
    ACT3_GORILLA       = 0x3D,
    ACT3_METAL_GORILLA = 0x3E,
    ACT3_EAGLE         = 0x3F,
    FLOATING_SKULL     = 0x41,
    ACT4_RAT           = 0x2D,
    ACT4_MOOSE         = 0x2E,
    ACT4_YETI          = 0x2F,
    ACT4_BAT           = 0x30,
    ACT4_SNOWBALL      = 0x31,
    ACT4_PURPLE_WIZARD = 0x32,
    ACT4_RED_WIZARD    = 0x33,
    ACT4_ICE_HEAD      = 0x34,
    ACT4_ICE_BLOCK     = 0x35,
    ACT4_CIRCLING_BAT  = 0x36,
    ACT4_SLIME         = 0x37,
    POSEIDON           = 0x38,
    TIN_DOLL           = 0x1E,
    ACT5_METAL_MOUSE   = 0x1F,
    ACT5_BULLDOZER     = 0x20,
    ACT5_HELICOPTER    = 0x21,
    ACT5_WORM          = 0x22,
    ACT5_ROBOT         = 0x24,
    ACT5_MINI_KNIGHT   = 0x25,
    ACT5_MINI_ARCHER   = 0x26,
    ACT5_MINI_HORSEMAN = 0x27,
    ACT5_CATAPULT      = 0x28,
    ACT5_TOWER         = 0x29,
    DEMON_BIRD         = 0x09,
    ACT6_SKULL         = 0x0B,
    ACT6_ORB           = 0x0C,
    ACT6_GHOST         = 0x0D,
    ACT6_SNAKE         = 0x0E,
    ACT6_FIRE          = 0x0F,
    ACT6_SKELETON      = 0x10,
    ACT6_PURPLE_KNIGHT = 0x11,
    ACT6_RED_KNIGHT    = 0x12,
    ACT6_FIRE2         = 0x13,
    ACT6_SKULL2        = 0x14,
    ACT6_MIMIC         = 0x15,
    ACT6_DOLL          = 0x16,
    ACT6_CHESS_KNIGHT  = 0x17,
    ACT7_DEMON         = 0x0A,
    ACT7_FLY           = 0x0B,
    ACT7_BRICK         = 0x0C,
    DREAM_NO_ENEMY     = 0xFF,
};

class Enemies {
public:
    Enemies(EnemyType list[], int listCount);
    ~Enemies();

    EnemyType* enemyList;
    int count;

    static bool isMetal (EnemyType enemy);
    static bool isSpirit (EnemyType enemy);
    static bool isSoul (EnemyType enemy);
    static const char* enemyName (EnemyType enemy);

    EnemyType pickOne ();
};


#endif  // __ENEMIES_H__
