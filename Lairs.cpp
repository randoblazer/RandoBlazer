#include "Lairs.h"
#include "Random.h"
#include "World.h"

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

namespace EnemyGroups {
    static EnemyType UndergroundCastleEnemies[6] =
        {EnemyType::ACT1_GOBLIN, EnemyType::ACT1_IMP, EnemyType::ACT1_FLY, EnemyType::ACT1_PLANT, EnemyType::ACT1_SLIME, EnemyType::ACT1_TORCH};
    static EnemyType LeosPaintingsEnemies[4] =
        {EnemyType::ACT1_ARMOR, EnemyType::ACT1_BIRD, EnemyType::ACT1_TORCH2, EnemyType::ACT1_BLOCK};
    static EnemyType WaterShrineEnemies[5] =
        {EnemyType::ACT2_WATER_DRAGON, EnemyType::ACT2_MUDMAN, EnemyType::ACT2_BUSH, EnemyType::ACT2_STATUE, EnemyType::ACT2_FLOWER};
    static EnemyType FireLightShrineEnemies[5] =
        {EnemyType::ACT2_FIRE_SPIRIT, EnemyType::ACT2_GHOST, EnemyType::ACT2_LIZARDMAN, EnemyType::ACT2_TP_LIZARDMAN, EnemyType::ACT2_FIREMAN};
    static EnemyType FireLightShrineEnemiesNoFireSpirit[4] =
        {EnemyType::ACT2_GHOST, EnemyType::ACT2_LIZARDMAN, EnemyType::ACT2_TP_LIZARDMAN, EnemyType::ACT2_FIREMAN};
    static EnemyType SeabedEnemies[5] =
        {EnemyType::ACT3_URCHIN, EnemyType::ACT3_JELLYFISH, EnemyType::ACT3_CRAB, EnemyType::ACT3_RAY, EnemyType::ACT3_SEAHORSE};
    static EnemyType IslandsEnemies[5] =
        {EnemyType::ACT3_PALM_TREE, EnemyType::ACT3_ROCK, EnemyType::ACT3_FISH, EnemyType::ACT3_GORILLA, EnemyType::ACT3_EAGLE};
    static EnemyType IslandsEnemiesNoFish[4] =
        {EnemyType::ACT3_PALM_TREE, EnemyType::ACT3_ROCK, EnemyType::ACT3_GORILLA, EnemyType::ACT3_EAGLE};
    static EnemyType MountainEnemies[5] =
        {EnemyType::ACT4_RAT, EnemyType::ACT4_MOOSE, EnemyType::ACT4_YETI, EnemyType::ACT4_BAT, EnemyType::ACT4_SNOWBALL};
    static EnemyType MountainEnemiesNoSnowball[4] =
        {EnemyType::ACT4_RAT, EnemyType::ACT4_MOOSE, EnemyType::ACT4_YETI, EnemyType::ACT4_BAT};
    static EnemyType LaynoleLuneEnemies[6] =
        {EnemyType::ACT4_PURPLE_WIZARD, EnemyType::ACT4_RED_WIZARD, EnemyType::ACT4_ICE_HEAD, EnemyType::ACT4_ICE_BLOCK, EnemyType::ACT4_CIRCLING_BAT, EnemyType::ACT4_SLIME};
    static EnemyType LaynoleLuneEnemiesNoIceBlock[5] =
        {EnemyType::ACT4_PURPLE_WIZARD, EnemyType::ACT4_RED_WIZARD, EnemyType::ACT4_ICE_HEAD, EnemyType::ACT4_CIRCLING_BAT, EnemyType::ACT4_SLIME};
    static EnemyType LeosBasementEnemies[5] =
        {EnemyType::ACT5_METAL_MOUSE, EnemyType::ACT5_BULLDOZER, EnemyType::ACT5_HELICOPTER, EnemyType::ACT5_WORM, EnemyType::ACT5_ROBOT};
    static EnemyType LeosBasementEnemiesMetalOnly[3] =
        {EnemyType::ACT5_METAL_MOUSE, EnemyType::ACT5_BULLDOZER, EnemyType::ACT5_HELICOPTER};
    static EnemyType LeosBasementEnemiesNoMetal[2] =
        {EnemyType::ACT5_WORM, EnemyType::ACT5_ROBOT};
    static EnemyType ModelTownsEnemies[5] =
        {EnemyType::ACT5_MINI_KNIGHT, EnemyType::ACT5_MINI_ARCHER, EnemyType::ACT5_MINI_HORSEMAN, EnemyType::ACT5_CATAPULT, EnemyType::ACT5_TOWER};
    static EnemyType CastleBasementEnemies[4] =
        {EnemyType::ACT6_ORB, EnemyType::ACT6_GHOST, EnemyType::ACT6_SNAKE, EnemyType::ACT6_SKELETON};
    static EnemyType CastleBasementEnemiesNoGhost[3] =
        {EnemyType::ACT6_ORB, EnemyType::ACT6_SNAKE, EnemyType::ACT6_SKELETON};
    static EnemyType CastleBasementEnemiesFull[6] =
        {EnemyType::ACT6_SKULL, EnemyType::ACT6_ORB, EnemyType::ACT6_GHOST, EnemyType::ACT6_SNAKE, EnemyType::ACT6_FIRE, EnemyType::ACT6_SKELETON};
    static EnemyType CastleTowersEnemies[5] =
        {EnemyType::ACT6_PURPLE_KNIGHT, EnemyType::ACT6_RED_KNIGHT, EnemyType::ACT6_MIMIC, EnemyType::ACT6_DOLL, EnemyType::ACT6_CHESS_KNIGHT};
    static EnemyType CastleTowersEnemiesFull[7] =
        {EnemyType::ACT6_PURPLE_KNIGHT, EnemyType::ACT6_RED_KNIGHT, EnemyType::ACT6_FIRE2, EnemyType::ACT6_SKULL2, EnemyType::ACT6_MIMIC, EnemyType::ACT6_DOLL, EnemyType::ACT6_CHESS_KNIGHT};
    static EnemyType WorldOfEvilEnemies[3] =
        {EnemyType::ACT7_DEMON, EnemyType::ACT7_FLY, EnemyType::ACT7_BRICK};
    static EnemyType WorldOfEvilEnemiesNoBrick[2] =
        {EnemyType::ACT7_DEMON, EnemyType::ACT7_FLY};

    static OrientationType orientationList[4] = {
        OrientationType::DOWN,
        OrientationType::LEFT,
        OrientationType::RIGHT,
        OrientationType::UP
    };
    
    static LairType SpawnTypeList[4] = {
        LairType::LAIR_MULTISPAWN,
        LairType::LAIR_ONE_BY_ONE,
        LairType::LAIR_ONE_BY_ONE_PROX,
        LairType::LAIR_TWO_UP_TWO_DOWN
    };
}

using namespace EnemyGroups;


// static declarations
Lair LairList::originalLairs[NUMBER_OF_LAIRS];

Lair::Lair() {
    act             = ActID::ACT_1;
    positionData[0] = 0;
    positionData[1] = 0;
    positionData[2] = 0;
    spawnType       = LairType::LAIR_ONE_BY_ONE;
    enemy           = EnemyType::NO_ENEMY;
    numEnemies      = 0;
    spawnRate       = 0;
    orientation     = 0;
}

Lair::~Lair() {}

const char* Lair::enemyName () {
    if (enemy == EnemyType::NO_ENEMY) {
        return "No enemy";
    }
    if (enemy == EnemyType::DREAM_NO_ENEMY) {
        return "Dream; no enemy";
    }
    switch (act) {
        case ActID::ACT_1:
            switch (enemy) {
                case EnemyType::NO_ENEMY:
                    return "No enemy";
                case EnemyType::SOLID_ARM:
                    return "Solid Arm";
                case EnemyType::ACT1_GOBLIN:
                    return "Act 1 Goblin";
                case EnemyType::ACT1_IMP:
                    return "Act 1 Imp";
                case EnemyType::ACT1_FLY:
                    return "Act 1 Fly";
                case EnemyType::ACT1_PLANT:
                    return "Act 1 Plant";
                case EnemyType::ACT1_SLIME:
                    return "Act 1 Slime";
                case EnemyType::ACT1_TORCH:
                    return "Act 1 Underground Castle Torch";
                case EnemyType::ACT1_ARMOR:
                    return "Act 1 Armor";
                case EnemyType::ACT1_SPIKEY:
                    return "Act 1 Spikey";
                case EnemyType::ACT1_BIRD:
                    return "Act 1 Bird";
                case EnemyType::ACT1_TORCH2:
                    return "Act 1 Painting Torch";
                case EnemyType::ACT1_BLOCK:
                    return "Act 1 Block";
                default:
                    return "unknown";
            }
        case ActID::ACT_2:
            switch (enemy) {
                case EnemyType::ACT2_WATER_DRAGON:
                    return "Act 2 Water Dragon";
                case EnemyType::ACT2_MUDMAN:
                    return "Act 2 Mudman";
                case EnemyType::ACT2_BUSH:
                    return "Act 2 Bush";
                case EnemyType::ACT2_STATUE:
                    return "Act 2 Statue";
                case EnemyType::ACT2_FLOWER:
                    return "Act 2 Flower";
                case EnemyType::ACT2_FIRE_SPIRIT:
                    return "Act 2 Fire Spirit";
                case EnemyType::ACT2_GHOST:
                    return "Act 2 Ghost";
                case EnemyType::ACT2_LIZARDMAN:
                    return "Act 2 Lizardman";
                case EnemyType::ACT2_TP_LIZARDMAN:
                    return "Act 2 Teleporting Lizardman";
                case EnemyType::ELEMENTAL_STATUE:
                    return "Elemental Statues";
                case EnemyType::ACT2_FIREMAN:
                    return "Act 2 Fireman";
                case EnemyType::ACT2_SCORPION:
                    return "Act 2 Scorpion";
                default:
                    return "unknown";
            }
        case ActID::ACT_3:
            switch (enemy) {
                case EnemyType::ACT3_URCHIN:
                    return "Act 3 Urchin";
                case EnemyType::ACT3_JELLYFISH:
                    return "Act 3 Jellyfish";
                case EnemyType::ACT3_CRAB:
                    return "Act 3 Crab";
                case EnemyType::ACT3_RAY:
                    return "Act 3 Ray";
                case EnemyType::ACT3_SEAHORSE:
                    return "Act 3 Seahorse";
                case EnemyType::ACT3_PALM_TREE:
                    return "Act 3 Palm Tree";
                case EnemyType::ACT3_ROCK:
                    return "Act 3 Rock";
                case EnemyType::ACT3_FISH:
                    return "Act 3 Fish";
                case EnemyType::ACT3_GORILLA:
                    return "Act 3 Gorilla";
                case EnemyType::ACT3_METAL_GORILLA:
                    return "Act 3 Metal Gorilla";
                case EnemyType::ACT3_EAGLE:
                    return "Act 3 Eagle";
                case EnemyType::FLOATING_SKULL:
                    return "Floating Skull";
                default:
                    return "unknown";
            }
        case ActID::ACT_4:
            switch (enemy) {
                case EnemyType::ACT4_RAT:
                    return "Act 4 Rat";
                case EnemyType::ACT4_MOOSE:
                    return "Act 4 Moose";
                case EnemyType::ACT4_YETI:
                    return "Act 4 Yeti";
                case EnemyType::ACT4_BAT:
                    return "Act 4 Bat";
                case EnemyType::ACT4_SNOWBALL:
                    return "Act 4 Snowball";
                case EnemyType::ACT4_PURPLE_WIZARD:
                    return "Act 4 Purple Wizard";
                case EnemyType::ACT4_RED_WIZARD:
                    return "Act 4 Red Wizard";
                case EnemyType::ACT4_ICE_HEAD:
                    return "Act 4 Ice Head";
                case EnemyType::ACT4_ICE_BLOCK:
                    return "Act 4 Ice Block";
                case EnemyType::ACT4_CIRCLING_BAT:
                    return "Act 4 Circling Bat";
                case EnemyType::ACT4_SLIME:
                    return "Act 4 Slime";
                case EnemyType::POSEIDON:
                    return "Poseidon";
                default:
                    return "unknown";
            }
        case ActID::ACT_5:
            switch (enemy) {
                case EnemyType::ACT5_METAL_MOUSE:
                    return "Act 5 Metal Mouse";
                case EnemyType::ACT5_BULLDOZER:
                    return "Act 5 Bulldozer";
                case EnemyType::ACT5_HELICOPTER:
                    return "Act 5 Helicopter";
                case EnemyType::ACT5_WORM:
                    return "Act 5 Worm";
                case EnemyType::ACT5_ROBOT:
                    return "Act 5 Robot";
                case EnemyType::ACT5_MINI_KNIGHT:
                    return "Act 5 Mini Knight";
                case EnemyType::ACT5_MINI_ARCHER:
                    return "Act 5 Mini Archer";
                case EnemyType::ACT5_MINI_HORSEMAN:
                    return "Act 5 Mini Horseman";
                case EnemyType::ACT5_CATAPULT:
                    return "Act 5 Invisible Catapult";
                case EnemyType::ACT5_TOWER:
                    return "Act 5 Invisible Tower";
                case EnemyType::TIN_DOLL:
                    return "Act 5 Tin Doll";
                default:
                    return "unknown";
            }
        case ActID::ACT_6:
            switch (enemy) {
                case EnemyType::ACT6_SKULL:
                    return "Act 6 Skull";
                case EnemyType::ACT6_ORB:
                    return "Act 6 Orb";
                case EnemyType::ACT6_GHOST:
                    return "Act 6 Ghost";
                case EnemyType::ACT6_SNAKE:
                    return "Act 6 Snake";
                case EnemyType::ACT6_FIRE:
                    return "Act 6 Fire";
                case EnemyType::ACT6_SKELETON:
                    return "Act 6 Skeleton";
                case EnemyType::ACT6_PURPLE_KNIGHT:
                    return "Act 6 Purple Knight";
                case EnemyType::ACT6_RED_KNIGHT:
                    return "Act 6 Red Knight";
                case EnemyType::ACT6_FIRE2:
                    return "Act 6 Fire 2";
                case EnemyType::ACT6_SKULL2:
                    return "Act 6 Skull 2";
                case EnemyType::ACT6_MIMIC:
                    return "Act 6 Mimic";
                case EnemyType::ACT6_DOLL:
                    return "Act 6 Doll";
                case EnemyType::ACT6_CHESS_KNIGHT:
                    return "Act 6 Chess Knight";
                case EnemyType::DEMON_BIRD:
                    return "Demon Bird";
                default:
                    return "unknown";
            }
        case ActID::ACT_7:
            switch (enemy) {
                case EnemyType::ACT7_DEMON:
                    return "Act 7 Demon";
                case EnemyType::ACT7_FLY:
                    return "Act 7 Fly";
                case EnemyType::ACT7_BRICK:
                    return "Act 7 Brick";
                default:
                    return "unknown";
            }
    }
    return "unknown";
}

void Lair::log () {
    cout << enemyName();
    cout << " | area " << (int)positionData[0] << " position " << (int)positionData[1] << ", " << (int)positionData[2];
    if (spawnType == LairType::LAIR_ALREADY_THERE) {
        cout << " Already there";
    } else if (spawnType == LairType::LAIR_MULTISPAWN) {
        cout << " Multispawn";
    } else if (spawnType == LairType::LAIR_ONE_BY_ONE) {
        cout << " Single spawn";
    } else if (spawnType == LairType::LAIR_ONE_BY_ONE_PROX) {
        cout << " Single spawn proximity";
    } else if (spawnType == LairType::LAIR_TWO_UP_TWO_DOWN) {
        cout << " Multidirection";
    } else {
        cout << " Unknown spawn type - likely bug!";
    }
    cout << " Count: " << static_cast<int>(numEnemies);
    cout << " Rate: " << static_cast<int>(spawnRate);
    if (orientation == 0) {
        cout << " down";
    } else if (orientation == 1) {
        cout << " left";
    } else if (orientation == 2) {
        cout << " right";
    } else if (orientation == 3) {
        cout << " up";
    }
    if (isMetal()) {
        cout << " [metal]";
    }
    if (isSpirit()) {
        cout << " [spirit]";
    }
    if (isSoul()) {
        cout << " [soul]";
    }
    cout << endl;
}
void Lair::logCsv () {
    // Enemy, Area, x, y, Spawn, Count, Rate, Orientation
    cout << enemyName() << ",";
    cout << (int)positionData[0] << "," << (int)positionData[1] << "," << (int)positionData[2] << ",";
    if (spawnType == LairType::LAIR_ALREADY_THERE) {
        cout << "Already there,";
    } else if (spawnType == LairType::LAIR_MULTISPAWN) {
        cout << "Multispawn,";
    } else if (spawnType == LairType::LAIR_ONE_BY_ONE) {
        cout << "Single spawn,";
    } else if (spawnType == LairType::LAIR_ONE_BY_ONE_PROX) {
        cout << "Single spawn proximity,";
    } else if (spawnType == LairType::LAIR_TWO_UP_TWO_DOWN) {
        cout << "Multidirection,";
    } else {
        cout << "Unknown spawn type - likely bug!,";
    }
    cout << static_cast<int>(numEnemies) << ",";
    cout << static_cast<int>(spawnRate) << ",";
    if (orientation == 0x00) {
        cout << "down";
    } else if (orientation == 0x40) {
        cout << "left";
    } else if (orientation == 0x80) {
        cout << "right";
    } else if (orientation == 0xC0) {
        cout << "up";
    }
    cout << endl;
}

Lair& Lair::operator= (const Lair& otherLair) {
    if (this != &otherLair) {
        act             = otherLair.act;
        positionData[0] = otherLair.positionData[0];
        positionData[1] = otherLair.positionData[1];
        positionData[2] = otherLair.positionData[2];
        spawnType       = otherLair.spawnType;
        enemy           = otherLair.enemy;
        numEnemies      = otherLair.numEnemies;
        spawnRate       = otherLair.spawnRate;
        orientation     = otherLair.orientation;
    }
    return *this;
}

bool Lair::NoFishLairPosition() {
    /* Some monster lairs should not have fish enemies, otherwise it would crash the game */
    return ( (positionData[0] == 0x2E && positionData[1] == 0x23) ||
             (positionData[0] == 0x2F && positionData[1] == 0x14 && positionData[2] == 0x08) ||
             (positionData[0] == 0x2F && positionData[1] == 0x24 && positionData[2] == 0x0F) ||
             (positionData[0] == 0x2F && positionData[1] == 0x1A && positionData[2] == 0x17) ||
             (positionData[0] == 0x2F && positionData[1] == 0x20 && positionData[2] == 0x18) ||
             (positionData[0] == 0x30 && positionData[1] == 0x16 && positionData[2] == 0x11) ||
             (positionData[0] == 0x30 && positionData[1] == 0x0C && positionData[2] == 0x24) ||
             (positionData[0] == 0x30 && positionData[1] == 0x2D && positionData[2] == 0x11) ||
             (positionData[0] == 0x31 && positionData[1] == 0x04 && positionData[2] == 0x11) ||
             (positionData[0] == 0x31 && positionData[1] == 0x39 && positionData[2] == 0x2B) ||
             (positionData[0] == 0x31 && positionData[1] == 0x3B && positionData[2] == 0x1A) ||
             (positionData[0] == 0x31 && positionData[1] == 0x06 && positionData[2] == 0x20) );
}

bool Lair::NoMetalLairPosition() {
    /* Some monster lairs are assumed to be beatable without Zantetsu Sword */
    return ( (positionData[0] == 0x56 && positionData[1] == 0x19 && positionData[2] == 0x23) ||
             (positionData[0] == 0x56 && positionData[1] == 0x02 && positionData[2] == 0x2E) ||
             (positionData[0] == 0x56 && positionData[1] == 0x1D && positionData[2] == 0x11) ||
             (positionData[0] == 0x56 && positionData[1] == 0x2B && positionData[2] == 0x23) ||
             (positionData[0] == 0x58 && positionData[1] == 0x20 && positionData[2] == 0x0A) );
}

bool Lair::NoGhostLairPosition() {
    /* Some monster lairs are assumed to be beatable without Spirit Sword */
    return ( (positionData[0] == 0x66 && positionData[1] == 0x0C && positionData[2] == 0x07) ||
             (positionData[0] == 0x66 && positionData[1] == 0x29 && positionData[2] == 0x09) ||
             (positionData[0] == 0x66 && positionData[1] == 0x09 && positionData[2] == 0x14) );
}

bool Lair::MustBeMetalLairPosition() {
    /* These lairs are supposed to have metal enemies, requiring the Zantetsu Sword to defeat */
    return ( (positionData[0] == 0x56 && positionData[1] == 0x39 && positionData[2] == 0x35) ||
             (positionData[0] == 0x58 && positionData[1] == 0x32 && positionData[2] == 0x2E) );
}

bool Lair::MustBeGhostLairPosition() {
    /* This lair is supposed to have ghost enemies, requiring the Spirit Sword to defeat */
    return (positionData[0] == 0x66 && positionData[1] == 0x2A && positionData[2] == 0x1E);
}

bool Lair::MustNotRandomizeLairPosition() {
    /* These lairs should not be randomized (until I find a better way to deal with them) */
    return ( (positionData[0] == 0x20 && positionData[1] == 0x08 && positionData[2] == 0x27) ||
             (positionData[0] == 0x3E && positionData[1] == 0x0E && positionData[2] == 0x26) ||
             (positionData[0] == 0x3E && positionData[1] == 0x17 && positionData[2] == 0x39) ||
             (positionData[0] == 0x3F && positionData[1] == 0x0A && positionData[2] == 0x27) ||
             (positionData[0] == 0x56 && positionData[1] == 0x2D && positionData[2] == 0x31) ||
             (positionData[0] == 0x58 && positionData[1] == 0x37 && positionData[2] == 0x34) );
}

bool Lair::MustNotBeUpwardsLairPosition() {
    /* This lair cannot have enemies oriented upwards */
    return (positionData[0] == 0x1B && positionData[1] == 0x25 && positionData[2] == 0x05);
}

bool Lair::canRandomizeOrientation (ActID act, EnemyType enemy) {
    return ((act == ActID::ACT_2 && enemy == EnemyType::ACT2_WATER_DRAGON) ||
            (act == ActID::ACT_4 && enemy == EnemyType::ACT4_RAT) ||
            (act == ActID::ACT_4 && enemy == EnemyType::ACT4_SNOWBALL) ||
            (act == ActID::ACT_5 && enemy == EnemyType::ACT5_METAL_MOUSE) ||
            (act == ActID::ACT_5 && enemy == EnemyType::ACT5_ROBOT) ||
            (act == ActID::ACT_5 && enemy == EnemyType::ACT5_WORM) ||
            (act == ActID::ACT_5 && enemy == EnemyType::ACT5_TOWER) ||
            (act == ActID::ACT_6 && enemy == EnemyType::ACT6_SKULL) ||
            (act == ActID::ACT_6 && enemy == EnemyType::ACT6_SNAKE) ||
            (act == ActID::ACT_6 && enemy == EnemyType::ACT6_SKULL2) ||
            (act == ActID::ACT_7 && enemy == EnemyType::ACT7_BRICK) );
}

bool Lair::isMetal() {
    switch (act) {
        case ActID::ACT_1:
            return enemy == EnemyType::ACT1_SPIKEY;
        case ActID::ACT_2:
            return enemy == EnemyType::ACT2_SCORPION;
        case ActID::ACT_3:
            return enemy == EnemyType::ACT3_METAL_GORILLA;
        case ActID::ACT_5:
            switch (enemy) {
                case EnemyType::ACT5_METAL_MOUSE:
                    return true;
                case EnemyType::ACT5_BULLDOZER:
                    return true;
                case EnemyType::ACT5_HELICOPTER:
                    return true;
                case EnemyType::TIN_DOLL:
                    return true;
                default:
                    return false;
            }
        default:
            return false;
    }
}

bool Lair::isSpirit() {
    switch (act) {
        case ActID::ACT_2:
            return enemy == EnemyType::ACT2_FIRE_SPIRIT;
        case ActID::ACT_6:
            return enemy == EnemyType::ACT6_GHOST;
        default:
            return false;
    }
}

bool Lair::isSoul() {
    return act == ActID::ACT_7 && enemy == EnemyType::ACT7_BRICK;
}

LairList::LairList () {}
LairList::~LairList () {}

void LairList::readOriginalLairs (fstream &ROMFile) {
    ROMFile.seekg (MONSTER_LAIR_DATA_ADDRESS, ios::beg);

    for (int i = 0; i < NUMBER_OF_LAIRS; i++) {

        ROMFile.seekg(10, std::ios::cur);

        /* Read the contents of this Monster Lair */
        ROMFile.read((char*)(&(originalLairs[i].act)), 1);
        ROMFile.read((char*)(&(originalLairs[i].positionData[0])), POSITION_DATA_SIZE);
        ROMFile.seekg(2, std::ios::cur);
        unsigned char b1, b2;
        ROMFile.read((char*)&b1, 1);
        ROMFile.read((char*)&b2, 1);
        originalLairs[i].spawnType = static_cast<LairType>((b1 << 8) | b2);
        ROMFile.seekg(1, std::ios::cur);
        ROMFile.read((char*)(&(originalLairs[i].numEnemies)), 1);
        ROMFile.read((char*)(&(originalLairs[i].spawnRate)), 1);
        ROMFile.read((char*)(&(originalLairs[i].enemy)), 1);
        ROMFile.seekg(1, std::ios::cur);
        ROMFile.read((char*)(&(originalLairs[i].orientation)), 1);
        ROMFile.seekg(8, std::ios::cur);
    }
}

void LairList::logLairs () {
    for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
        lairList[i].logCsv();
    }
}

void LairList::copyOriginalLairs () {
    for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
        lairList[i] = originalLairs[i];
    }
}

EnemyType pickEnemyType (Lair& originalLair) {
    if (originalLair.spawnType == LairType::LAIR_TWO_UP_TWO_DOWN ||
        originalLair.MustNotRandomizeLairPosition()
    ) {
        return originalLair.enemy;
    }
    EnemyType* group;
    int groupSize = 0;
    EnemyType origEnemy = originalLair.enemy;

    switch (originalLair.act) {
    case ActID::ACT_1:
        if (origEnemy != EnemyType::ACT1_SPIKEY &&
            origEnemy != EnemyType::SOLID_ARM) {
            if (origEnemy < EnemyType::ACT1_ARMOR) {
                group = UndergroundCastleEnemies;
                groupSize = sizeof(UndergroundCastleEnemies) / sizeof(EnemyType);
            } else {
                group = LeosPaintingsEnemies;
                groupSize = sizeof(LeosPaintingsEnemies) / sizeof(EnemyType);
            }
        }
        break;
    case ActID::ACT_2:
        if (origEnemy != EnemyType::ACT2_SCORPION &&
            origEnemy != EnemyType::ACT2_FIRE_SPIRIT &&
            origEnemy != EnemyType::ELEMENTAL_STATUE) {
            if (origEnemy < EnemyType::ACT2_FIRE_SPIRIT) {
                group = WaterShrineEnemies;
                groupSize = sizeof(WaterShrineEnemies) / sizeof(EnemyType);
            } else {
                group = FireLightShrineEnemiesNoFireSpirit;
                groupSize = sizeof(FireLightShrineEnemiesNoFireSpirit) / sizeof(EnemyType);
            }
        }
        break;
    case ActID::ACT_3:
        if (origEnemy != EnemyType::ACT3_METAL_GORILLA &&
            origEnemy != EnemyType::FLOATING_SKULL) {
            if (origEnemy < EnemyType::ACT3_PALM_TREE) {
                group = SeabedEnemies;
                groupSize = sizeof(SeabedEnemies) / sizeof(EnemyType);
            } else {
                if (originalLair.NoFishLairPosition()) {
                    group = IslandsEnemiesNoFish;
                    groupSize = sizeof(IslandsEnemiesNoFish) / sizeof(EnemyType);
                } else {
                    group = IslandsEnemies;
                    groupSize = sizeof(IslandsEnemies) / sizeof(EnemyType);
                }
            }
        }
        break;
    case ActID::ACT_4:
        if (origEnemy != EnemyType::POSEIDON) {
            if (origEnemy < EnemyType::ACT4_PURPLE_WIZARD) {
                group = MountainEnemiesNoSnowball;
                groupSize = sizeof(MountainEnemiesNoSnowball) / sizeof(EnemyType);
            } else {
                group = LaynoleLuneEnemiesNoIceBlock;
                groupSize = sizeof(LaynoleLuneEnemiesNoIceBlock) / sizeof(EnemyType);
            }
        }
        break;
    case ActID::ACT_5:
        if (origEnemy != EnemyType::TIN_DOLL) {
            if (origEnemy < EnemyType::ACT5_MINI_KNIGHT) {
                /* Lair is in Leo's Lab Basement or Power Plant */
                if (originalLair.NoMetalLairPosition()) {
                    group = LeosBasementEnemiesNoMetal;
                    groupSize = sizeof(LeosBasementEnemiesNoMetal) / sizeof(EnemyType);
                } else if (originalLair.MustBeMetalLairPosition()) {
                    group = LeosBasementEnemiesMetalOnly;
                    groupSize = sizeof(LeosBasementEnemiesMetalOnly) / sizeof(EnemyType);
                } else {
                    group = LeosBasementEnemies;
                    groupSize = sizeof(LeosBasementEnemies) / sizeof(EnemyType);
                }
            } else {
                group = ModelTownsEnemies;
                groupSize = sizeof(ModelTownsEnemies) / sizeof(EnemyType);
            }
        }
        break;
    case ActID::ACT_6:
        if (origEnemy != EnemyType::DEMON_BIRD) {
            if (origEnemy < EnemyType::ACT6_PURPLE_KNIGHT) {
                if (originalLair.NoGhostLairPosition()) {
                    group = CastleBasementEnemiesNoGhost;
                    groupSize = sizeof(CastleBasementEnemiesNoGhost) / sizeof(EnemyType);
                } else if (originalLair.MustBeGhostLairPosition()) {
                    return EnemyType::ACT6_GHOST;
                } else {
                    group = CastleBasementEnemies;
                    groupSize = sizeof(CastleBasementEnemies) / sizeof(EnemyType);
                }
            }
            else {
                group = CastleTowersEnemies;
                groupSize = sizeof(CastleTowersEnemies) / sizeof(EnemyType);
            }
        }
        break;
    case ActID::ACT_7:
        group = WorldOfEvilEnemiesNoBrick;
        groupSize = sizeof(WorldOfEvilEnemiesNoBrick) / sizeof(EnemyType);
        break;
    default:
        /* Should not happen! */
        return origEnemy;
        break;
    }
    if (groupSize == 0) {
        return origEnemy;
    }
    return group[Random::RandomInteger(groupSize)];
}

LairProfile::LairProfile () {}
LairProfile::~LairProfile () {}
void LairProfile::roll (Lair& lair, Lair& originalLair) {
    lair = originalLair;
}

LairProfileA::LairProfileA (WorldFlags& flags) {
    worldFlags = &flags;
    int normalTypeWeights[4] = { 15, 4, 1, 0 };
    normalTypePicker = new Random::WeightedPicker(normalTypeWeights, 3);
    int upDownTypeWeights[4] = { 5, 4, 1, 10 };
    upDownTypePicker = new Random::WeightedPicker(upDownTypeWeights, 4);
    int singleCountWeights[4] = { 5, 4, 1, 10 };
    singleCountPicker = new Random::WeightedPicker(singleCountWeights, 4);
    int multiCountWeights[4] = { 1, 1, 1, 1 };
    multiCountPicker = new Random::WeightedPicker(multiCountWeights, 4);
    // Lairs with more enemies can be weighted towards faster spawning
    int spawnWeights[4][4] = {
        { 1, 1, 1, 1 },   // 4-6 enemies
        { 3, 2, 1, 1 },   // 6-8
        { 8, 4, 2, 1 },   // 8-10
        { 10, 5, 1, 1 }   // 10-12
    };
    for (int i = 0; i < 4; i++) {
        spawnRatePickers[i] = new Random::WeightedPicker(spawnWeights[i], 4);
    }
}
LairProfileA::~LairProfileA () {
    delete normalTypePicker;
    delete upDownTypePicker;
    delete singleCountPicker;
    delete multiCountPicker;
    for (int i = 0; i < 4; i++) {
        delete spawnRatePickers[i];
    }
}
void LairProfileA::roll (Lair& lair, Lair& originalLair) {
    // originalLair.log();
    lair = originalLair;
    if (worldFlags->blesterMetal && lair.positionData[0] == 49 && lair.positionData[1] == 33 && lair.positionData[2] == 41) {
        lair.enemy = EnemyType::ACT3_METAL_GORILLA;
    } else if (worldFlags->dureanMetal && lair.positionData[0] == 48 && lair.positionData[1] == 4 && lair.positionData[2] == 36) {
        lair.enemy = EnemyType::ACT3_METAL_GORILLA;
    } else {
        lair.enemy = pickEnemyType(originalLair);
    }
    if (Lair::canRandomizeOrientation(lair.act, lair.enemy)) {
        if (originalLair.MustNotBeUpwardsLairPosition()) {
            lair.orientation = static_cast<unsigned char>(EnemyGroups::orientationList[Random::RandomInteger(3)]);
        } else {
            lair.orientation = static_cast<unsigned char>(EnemyGroups::orientationList[Random::RandomInteger(4)]);
        }
    } else {
        lair.orientation = 0;
    }
    if (lair.spawnType == LairType::LAIR_ONE_BY_ONE ||
        lair.spawnType == LairType::LAIR_MULTISPAWN ||
        lair.spawnType == LairType::LAIR_ONE_BY_ONE_PROX
    ) {
        lair.spawnType = EnemyGroups::SpawnTypeList[normalTypePicker->pick()];
    } else if (lair.spawnType == LairType::LAIR_TWO_UP_TWO_DOWN) {
        lair.spawnType = EnemyGroups::SpawnTypeList[upDownTypePicker->pick()];
    }
    if (lair.spawnType == LairType::LAIR_ONE_BY_ONE ||
        lair.spawnType == LairType::LAIR_ONE_BY_ONE_PROX
    ) {
        lair.numEnemies = 2 + singleCountPicker->pick();
        lair.spawnRate = 0;
    } else if (lair.spawnType == LairType::LAIR_MULTISPAWN ||
        lair.spawnType == LairType::LAIR_TWO_UP_TWO_DOWN
    ) {
        int countPick = multiCountPicker->pick();
        int spawnRatePick = spawnRatePickers[countPick]->pick();

        lair.numEnemies = 4 + (2 * countPick) + Random::RandomInteger(3);
        lair.spawnRate = 3 + (7 * spawnRatePick) + Random::RandomInteger(7);
    }
}

LairProfileClassic::LairProfileClassic () {
    int typeWeights[4] = { 15, 4, 1, 0 };
    typePicker = new Random::WeightedPicker(typeWeights, 3);
    int typeWeights2[4] = { 1, 1, 1, 1 };
    typePicker2 = new Random::WeightedPicker(typeWeights2, 4);
}

LairProfileClassic::~LairProfileClassic () {
    delete typePicker;
    delete typePicker2;
}
void LairProfileClassic::roll (Lair& lair, Lair& originalLair) {
    lair = originalLair;
    lair.enemy = pickEnemyType(originalLair);
    if (Lair::canRandomizeOrientation(lair.act, lair.enemy)) {
        if (originalLair.MustNotBeUpwardsLairPosition()) {
            lair.orientation = static_cast<unsigned char>(EnemyGroups::orientationList[Random::RandomInteger(3)]);
        } else {
            lair.orientation = static_cast<unsigned char>(EnemyGroups::orientationList[Random::RandomInteger(4)]);
        }
    } else {
        lair.orientation = 0;
    }
    if (lair.spawnType == LairType::LAIR_ONE_BY_ONE ||
        lair.spawnType == LairType::LAIR_MULTISPAWN ||
        lair.spawnType == LairType::LAIR_ONE_BY_ONE_PROX
    ) {
        lair.spawnType = EnemyGroups::SpawnTypeList[typePicker->pick()];
    } else if (lair.spawnType == LairType::LAIR_TWO_UP_TWO_DOWN) {
        lair.spawnType = EnemyGroups::SpawnTypeList[typePicker2->pick()];
    }
    if (lair.spawnType == LairType::LAIR_ONE_BY_ONE ||
        lair.spawnType == LairType::LAIR_ONE_BY_ONE_PROX
    ) {
        lair.numEnemies = Random::RandomIntegerRange(2, 6);
        lair.spawnRate = 0;
    } else if (lair.spawnType == LairType::LAIR_MULTISPAWN ||
        lair.spawnType == LairType::LAIR_TWO_UP_TWO_DOWN
    ) {
        lair.numEnemies = Random::RandomIntegerRange(4, 12);
        lair.spawnRate = Random::RandomIntegerRange(0x03, 0x20);
    }
}

LairProfileTwo::LairProfileTwo () {}
LairProfileTwo::~LairProfileTwo () {}
void LairProfileTwo::roll (Lair& lair, Lair& originalLair) {
    lair = originalLair;
    // lair.log();
    if (originalLair.numEnemies > 2) {
        lair.numEnemies = 2;
        if (originalLair.spawnType != LairType::LAIR_ALREADY_THERE && originalLair.spawnRate > 0x02) {
            lair.spawnRate = 0x03;
        }
    }
}
