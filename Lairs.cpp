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
    area            = 0;
    x               = 0;
    y               = 0;
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
    cout << " | area " << (int)area << " position " << (int)x << ", " << (int)y;
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
    cout << (int)area << "," << (int)x << "," << (int)y << ",";
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
        area = otherLair.area;
        x = otherLair.x;
        y = otherLair.y;
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
    return ( (area == 0x2E && x == 0x23) ||
             (area == 0x2F && x == 0x14 && y == 0x08) ||
             (area == 0x2F && x == 0x24 && y == 0x0F) ||
             (area == 0x2F && x == 0x1A && y == 0x17) ||
             (area == 0x2F && x == 0x20 && y == 0x18) ||
             (area == 0x30 && x == 0x16 && y == 0x11) ||
             (area == 0x30 && x == 0x0C && y == 0x24) ||
             (area == 0x30 && x == 0x2D && y == 0x11) ||
             (area == 0x31 && x == 0x04 && y == 0x11) ||
             (area == 0x31 && x == 0x39 && y == 0x2B) ||
             (area == 0x31 && x == 0x3B && y == 0x1A) ||
             (area == 0x31 && x == 0x06 && y == 0x20) );
}

bool Lair::NoMetalLairPosition() {
    /* Some monster lairs are assumed to be beatable without Zantetsu Sword */
    return ( (area == 0x56 && x == 0x19 && y == 0x23) ||
             (area == 0x56 && x == 0x02 && y == 0x2E) ||
             (area == 0x56 && x == 0x1D && y == 0x11) ||
             (area == 0x56 && x == 0x2B && y == 0x23) ||
             (area == 0x58 && x == 0x20 && y == 0x0A) );
}

bool Lair::NoGhostLairPosition() {
    /* Some monster lairs are assumed to be beatable without Spirit Sword */
    return ( (area == 0x66 && x == 0x0C && y == 0x07) ||
             (area == 0x66 && x == 0x29 && y == 0x09) ||
             (area == 0x66 && x == 0x09 && y == 0x14) );
}

bool Lair::MustBeMetalLairPosition() {
    /* These lairs are supposed to have metal enemies, requiring the Zantetsu Sword to defeat */
    return ( (area == 0x56 && x == 0x39 && y == 0x35) ||
             (area == 0x58 && x == 0x32 && y == 0x2E) );
}

bool Lair::MustBeGhostLairPosition() {
    /* This lair is supposed to have ghost enemies, requiring the Spirit Sword to defeat */
    return (area == 0x66 && x == 0x2A && y == 0x1E);
}

bool Lair::MustNotRandomizeLairPosition() {
    /* These lairs should not be randomized (until I find a better way to deal with them) */
    return ( (area == 0x20 && x == 0x08 && y == 0x27) ||
             (area == 0x3E && x == 0x0E && y == 0x26) ||
             (area == 0x3E && x == 0x17 && y == 0x39) ||
             (area == 0x3F && x == 0x0A && y == 0x27) ||
             (area == 0x56 && x == 0x2D && y == 0x31) ||
             (area == 0x58 && x == 0x37 && y == 0x34) );
}

bool Lair::MustNotBeUpwardsLairPosition() {
    /* This lair cannot have enemies oriented upwards */
    return (area == 0x1B && x == 0x25 && y == 0x05);
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
        ROMFile.read((char*)(&(originalLairs[i].area)), 1);
        ROMFile.read((char*)(&(originalLairs[i].x)), 1);
        ROMFile.read((char*)(&(originalLairs[i].y)), 1);
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
        // lairList[i].logCsv();
        lairList[i].log();
    }
}

void LairList::copyOriginalLairs () {
    for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
        lairList[i] = originalLairs[i];
    }
}

void LairList::lairStats () {
    int singleLairs = 0;
    int singleEnemies = 0;
    int proxLairs = 0;
    int proxEnemies = 0;
    int multiLairs = 0;
    int multiEnemies = 0;
    int multiSpawnRate = 0;

    for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
        if (lairList[i].spawnType == LairType::LAIR_ONE_BY_ONE) {
            singleLairs++;
            singleEnemies += lairList[i].numEnemies;
        }
        if (lairList[i].spawnType == LairType::LAIR_ONE_BY_ONE_PROX) {
            proxLairs++;
            proxEnemies += lairList[i].numEnemies;
        }
        if (lairList[i].spawnType == LairType::LAIR_MULTISPAWN) {
            multiLairs++;
            multiEnemies += lairList[i].numEnemies;
            multiSpawnRate += lairList[i].spawnRate;
        }
    }
    cout << "Single spawn: " << singleLairs << " with " << ((float)singleEnemies) / singleLairs << endl;
    cout << "Prox spawn: " << proxLairs << " with " << ((float)proxEnemies) / proxLairs << endl;
    cout << "Multi spawn: " << multiLairs << " with " << ((float)multiEnemies) / multiLairs <<
        " at " << ((float)multiSpawnRate / multiLairs) << endl;
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

EnemyType pickSpriteEnemy (Lair& originalLair) {
    EnemyType* group;
    int groupSize = 0;
    EnemyType origEnemy = originalLair.enemy;

    switch (originalLair.act) {
    case ActID::ACT_1:
        if (origEnemy < EnemyType::ACT1_ARMOR) {
            group = UndergroundCastleEnemies;
            groupSize = sizeof(UndergroundCastleEnemies) / sizeof(EnemyType);
        } else {
            group = LeosPaintingsEnemies;
            groupSize = sizeof(LeosPaintingsEnemies) / sizeof(EnemyType);
        }
        break;
    case ActID::ACT_2:
        if (origEnemy < EnemyType::ACT2_FIRE_SPIRIT) {
            group = WaterShrineEnemies;
            groupSize = sizeof(WaterShrineEnemies) / sizeof(EnemyType);
        } else {
            group = FireLightShrineEnemies;
            groupSize = sizeof(FireLightShrineEnemies) / sizeof(EnemyType);
        }
        break;
    case ActID::ACT_3:
        if (origEnemy < EnemyType::ACT3_PALM_TREE) {
            group = SeabedEnemies;
            groupSize = sizeof(SeabedEnemies) / sizeof(EnemyType);
        } else {
            group = IslandsEnemies;
            groupSize = sizeof(IslandsEnemies) / sizeof(EnemyType);
        }
        break;
    case ActID::ACT_4:
        if (origEnemy < EnemyType::ACT4_PURPLE_WIZARD) {
            group = MountainEnemies;
            groupSize = sizeof(MountainEnemies) / sizeof(EnemyType);
        } else {
            group = LaynoleLuneEnemies;
            groupSize = sizeof(LaynoleLuneEnemies) / sizeof(EnemyType);
        }
        break;
    case ActID::ACT_5:
        if (origEnemy < EnemyType::ACT5_MINI_KNIGHT) {
            group = LeosBasementEnemies;
            groupSize = sizeof(LeosBasementEnemies) / sizeof(EnemyType);
        } else {
            group = ModelTownsEnemies;
            groupSize = sizeof(ModelTownsEnemies) / sizeof(EnemyType);
        }
        break;
    case ActID::ACT_6:
        if (origEnemy < EnemyType::ACT6_PURPLE_KNIGHT) {
            group = CastleBasementEnemiesFull;
            groupSize = sizeof(CastleBasementEnemiesFull) / sizeof(EnemyType);
        }
        else {
            group = CastleTowersEnemiesFull;
            groupSize = sizeof(CastleTowersEnemiesFull) / sizeof(EnemyType);
        }
        break;
    case ActID::ACT_7:
        group = WorldOfEvilEnemies;
        groupSize = sizeof(WorldOfEvilEnemies) / sizeof(EnemyType);
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
    reduced = false;
    forceProx = false;
    int normalTypeWeights[4] = { 17, 2, 1, 0 };
    normalTypePicker = new Random::WeightedPicker(normalTypeWeights, 3);
    int upDownTypeWeights[4] = { 5, 4, 1, 10 };
    upDownTypePicker = new Random::WeightedPicker(upDownTypeWeights, 4);
    int singleCountWeights[4] = { 5, 4, 2, 1 };
    singleCountPicker = new Random::WeightedPicker(singleCountWeights, 4);
    int multiCountWeights[4] = { 1, 1, 1, 1 };
    multiCountPicker = new Random::WeightedPicker(multiCountWeights, 4);
    int multiCountReducedWeights[4] = { 1, 2, 0, 0 };
    multiCountReducedPicker = new Random::WeightedPicker(multiCountReducedWeights, 4);
    // Lairs with more enemies can be weighted towards faster spawning
    int spawnWeights[4][4] = {
        { 1, 2, 4, 4 },    // 4-6 enemies
        { 1, 1, 1, 1 },    // 6-8
        { 2, 10, 7, 5 },  // 8-10
        { 1, 10, 5, 1 }   // 10-12
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
    delete multiCountReducedPicker;
    for (int i = 0; i < 4; i++) {
        delete spawnRatePickers[i];
    }
}
void LairProfileA::roll (Lair& lair, Lair& originalLair) {
    // originalLair.log();
    lair = originalLair;
    if (!originalLair.MustNotRandomizeLairPosition() &&
        originalLair.enemy != EnemyType::DREAM_NO_ENEMY &&
        originalLair.enemy != EnemyType::NO_ENEMY
    ) {
        if (worldFlags->blesterMetal && lair.area == 49 && lair.x == 33 && lair.y == 41) {
            lair.enemy = EnemyType::ACT3_METAL_GORILLA;
        } else if (worldFlags->dureanMetal && lair.area == 48 && lair.x == 45 && lair.y == 55) {
            lair.enemy = EnemyType::ACT3_METAL_GORILLA;
        } else {
            lair.enemy = pickEnemyType(originalLair);
        }
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
        if (forceProx) {
            lair.spawnType = LairType::LAIR_ONE_BY_ONE_PROX;
        } else {
            lair.spawnType = EnemyGroups::SpawnTypeList[normalTypePicker->pick()];
        }
    } else if (lair.spawnType == LairType::LAIR_TWO_UP_TWO_DOWN) {
        if (forceProx) {
            lair.spawnType = LairType::LAIR_ONE_BY_ONE_PROX;
        } else {
            lair.spawnType = EnemyGroups::SpawnTypeList[upDownTypePicker->pick()];
        }
    }
    if (lair.spawnType == LairType::LAIR_ONE_BY_ONE ||
        lair.spawnType == LairType::LAIR_ONE_BY_ONE_PROX
    ) {
        lair.numEnemies = 2 + singleCountPicker->pick();
        lair.spawnRate = 0;
    } else if (lair.spawnType == LairType::LAIR_MULTISPAWN ||
               lair.spawnType == LairType::LAIR_TWO_UP_TWO_DOWN
    ) {
        int countPick;
        // Keeping old hack for reduced multispawn mimics
        // Other reasons for reduced count include less lag and making some areas faster
        if (reduced || lair.enemy == EnemyType::ACT6_MIMIC) {
            countPick = multiCountReducedPicker->pick();
        } else {
            countPick = multiCountPicker->pick();
        }
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
    if (!originalLair.MustNotRandomizeLairPosition() &&
        originalLair.enemy != EnemyType::DREAM_NO_ENEMY &&
        originalLair.enemy != EnemyType::NO_ENEMY
    ) {
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

LairProfileSprite::LairProfileSprite () {}
LairProfileSprite::~LairProfileSprite () {}
void LairProfileSprite::roll (Lair& lair, Lair& originalLair) {
    lair = originalLair;
    lair.enemy = pickSpriteEnemy(originalLair);
    if (Lair::canRandomizeOrientation(lair.act, lair.enemy)) {
        lair.orientation = static_cast<unsigned char>(EnemyGroups::orientationList[Random::RandomInteger(4)]) + 1;
    } else {
        lair.orientation = 0x01;
    }
}

int SpriteDataAddressList[7][63] = {
    {0x9CCA, 0x9CCE, 0x9CD2, 0x9CD6, 0x9CDA, 0x9CDE, 0x9CE2, 0x9CE6, 0x9CEA, 0x9CEE,
     0x9CF2, 0x9D1B, 0x9D1F, 0x9D23, 0x9D27, 0x9D2B, 0x9D2F, 0x9D33, 0x9D37, 0x9D3B,
     0x9D3F, 0x9D43, 0x9D47, 0x9D4B, 0x9D4F, 0x9D53, 0x9D57},
    {0x9F01, 0x9F05, 0x9F09, 0x9F0D, 0x9F11, 0x9F15, 0x9F19, 0x9F1D, 0x9F21, 0x9F25,
     0x9F29, 0x9F2D, 0x9F31, 0x9F35, 0x9F6A, 0x9F6E, 0x9F72, 0x9F76, 0x9F93, 0x9F97,
     0x9F9B, 0x9F9F, 0x9FA3, 0x9FA7, 0x9FAB},
    {0xA11C, 0xA120, 0xA124, 0xA128, 0xA12C, 0xA130, 0xA194, 0xA198, 0xA19C, 0xA1A0,
     0xA1A4, 0xA1A8, 0xA1AC, 0xA1B0, 0xA1B4, 0xA1B8, 0xA1D1, 0xA1D5, 0xA1D9, 0xA1DD,
     0xA1E1, 0xA1E5, 0xA1E9, 0xA1ED, 0xA202, 0xA206, 0xA20A, 0xA20E, 0xA212, 0xA243,
     0xA247, 0xA24B, 0xA24F, 0xA253, 0xA28C, 0xA290, 0xA294, 0xA298},
    {0xA3B9, 0xA3BD, 0xA3C1, 0xA3C5, 0xA3C9, 0xA407, 0xA40B, 0xA40F, 0xA413, 0xA42C,
     0xA430, 0xA434, 0xA438, 0xA47B, 0xA47F, 0xA498, 0xA49C, 0xA4A0, 0xA4A4, 0xA4C5,
     0xA4C9, 0xA4CD, 0xA4D1, 0xA4D5, 0xA4D9, 0xA4DD, 0xA4E1},
    {0xA608, 0xA60C, 0xA610, 0xA614, 0xA618, 0xA61C, 0xA63D, 0xA641, 0xA645, 0xA649,
     0xA64D, 0xA651},
    {0xA6CB, 0xA6CF, 0xA6D3, 0xA6D7, 0xA6DB, 0xA6DF, 0xA6E3, 0xA6E7, 0xA6EB, 0xA6EF,
     0xA6F3, 0xA708, 0xA70C, 0xA710, 0xA714, 0xA718, 0xA71C, 0xA751, 0xA755, 0xA759,
     0xA75D, 0xA761, 0xA765, 0xA77F, 0xA783, 0xA787, 0xA78B, 0xA78F, 0xA793, 0xA797,
     0xA79B, 0xA79F, 0xA7A3, 0xA7A7, 0xA7AB, 0xA7BC, 0xA7C0, 0xA7C4, 0xA7C8, 0xA7CC,
     0xA7D0, 0xA7D4, 0xA7D8, 0xA7F6, 0xA7FA, 0xA7FE, 0xA802, 0xA806, 0xA80A, 0xA81B,
     0xA81F, 0xA823, 0xA827, 0xA834, 0xA838, 0xA83C, 0xA840, 0xA844, 0xA848, 0xA84C,
     0xA850, 0xA861, 0xA865},                                /* leave these 3 bricks for grinding */
    {0xA946, 0xA94A, 0xA94E, 0xA952, 0xA956, 0xA95A, 0xA95E, /*0xA987, 0xA98B, 0xA98F,*/
     0xA993, 0xA997, 0xA99B, 0xA99F, 0xA9A3, 0xA9A7}
};

void readOriginalSprites (Lair sprites[], fstream &ROMFile) {
    int count = 0;
    for (int act = static_cast<int>(ActID::ACT_1); act < static_cast<int>(ActID::ACT_MAX); act++) {
        for (int address = 0; address < 63; address++) {
            if (SpriteDataAddressList[act][address] == 0) {
                break;
            }
            sprites[count].address = SpriteDataAddressList[act][address];
            sprites[count].act = (ActID)act;

            ROMFile.seekg(SpriteDataAddressList[act][address], std::ios::beg);
            ROMFile.read((char*)(&(sprites[count].x)), 1);
            ROMFile.read((char*)(&(sprites[count].y)), 1);
            ROMFile.read((char*)(&(sprites[count].orientation)), 1);
            ROMFile.read((char*)(&(sprites[count].enemy)), 1);
            count++;
        }
    }
}
