#include "Lairs.h"

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

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
        return "Dream, no enemy";
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
        lairList[i].log();
    }
}

void LairList::copyOriginalLairs () {
    for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
        lairList[i] = originalLairs[i];
    }
}
