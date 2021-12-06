#include "Enemies.h"
#include "Random.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;


Enemies::Enemies (EnemyType initList[], int initCount) {
    count = initCount;
    enemyList = new EnemyType [count];
    for (int i = 0; i < count; i++) {
        enemyList[i] = initList[i];
    }
}

Enemies::~Enemies () {
    delete enemyList;
}

bool Enemies::isMetal (EnemyType enemy) {
    return enemy == EnemyType::ACT1_SPIKEY
        || enemy == EnemyType::ACT2_SCORPION
        || enemy == EnemyType::ACT3_METAL_GORILLA
        || enemy == EnemyType::ACT5_METAL_MOUSE
        || enemy == EnemyType::ACT5_BULLDOZER
        || enemy == EnemyType::ACT5_HELICOPTER
        || enemy == EnemyType::TIN_DOLL;
}

bool Enemies::isSpirit (EnemyType enemy) {
    return enemy == EnemyType::ACT2_FIRE_SPIRIT
        || enemy == EnemyType::ACT6_GHOST;
}

bool Enemies::isSoul (EnemyType enemy) {
    return enemy == EnemyType::ACT7_BRICK;
}

const char* Enemies::enemyName (EnemyType enemy) {
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
    }
}

EnemyType Enemies::pickOne () {
    return enemyList[Random::RandomInteger(count)];
}

