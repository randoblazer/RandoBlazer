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

EnemyType Enemies::pickOne () {
    return enemyList[Random::RandomInteger(count)];
}

