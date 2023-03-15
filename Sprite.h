#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Lairs.h"

#define NUMBER_OF_SPRITES 205

class Sprite {
public:
    Sprite();
    ~Sprite();

    int Address;
    ActID Act;
    unsigned char x;
    unsigned char y;
    unsigned char Orientation;
    EnemyType Enemy;
};

void GetOriginalMapSpriteData (Sprite SpriteList[], std::fstream &ROMFile);

#endif // __SPRITE_H__
