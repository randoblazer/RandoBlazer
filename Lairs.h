#ifndef __LAIRS_H__
#define __LAIRS_H__

#include "Enemies.h"

using namespace std;

#define POSITION_DATA_SIZE  3
#define NUMBER_OF_LAIRS   420

#define MONSTER_LAIR_DATA_ADDRESS 0xBA0D


enum class ActID : unsigned char {
    ACT_1 = 0,
    ACT_2,
    ACT_3,
    ACT_4,
    ACT_5,
    ACT_6,
    ACT_7,
    ACT_MAX
};

enum class LairType : unsigned short {
    LAIR_ONE_BY_ONE      = 0xF3A6,
    LAIR_MULTISPAWN      = 0x1BA7,
    LAIR_ONE_BY_ONE_PROX = 0x13A8,
    LAIR_TWO_UP_TWO_DOWN = 0xD2A7,
    LAIR_ALREADY_THERE   = 0x52A7
};

class Lair {
public:
    Lair();
    ~Lair();

    Lair& operator= (const Lair& OtherLair);
    bool NoFishLairPosition(void);
    bool NoMetalLairPosition(void);
    bool NoGhostLairPosition(void);
    bool MustBeMetalLairPosition(void);
    bool MustBeGhostLairPosition(void);
    bool MustNotRandomizeLairPosition(void);
    bool MustNotBeUpwardsLairPosition(void);

    ActID         Act;                              /* 0A */
    unsigned char PositionData[POSITION_DATA_SIZE]; /* from 0B to 0D */
    LairType Type;                                  /* from 10 to 11 */
    unsigned char NbEnemies;                        /* 13 */
    unsigned char SpawnRate;                        /* 14 */
    EnemyType     Enemy;                            /* 15 */
    unsigned char Orientation;                      /* 17 */
};

class LairList {
public:
    LairList ();
    ~LairList ();

    static Lair originalLairs[NUMBER_OF_LAIRS];
    Lair lairList[NUMBER_OF_LAIRS];

    void readOriginalLairs (fstream &ROMFile);
}


#endif // __LAIRS_H__
