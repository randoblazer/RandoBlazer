#ifndef __WORLD_H__
#define __WORLD_H__

#include "Locations.h"
#include "ItemPool.h"
#include "LogicGraph.h"
#include "Filler.h"
#include "Random.h"

class WorldFlags {
public:
    WorldFlags ();
    ~WorldFlags ();

    bool blesterMetal;
    bool dureanMetal;

/*
    // Other ideas?
    bool superHotLava;
    bool swordShuffle;
*/

    void roll (); // pass in rando options later
};

class WorldMap {
public:
    WorldMap ();
    ~WorldMap ();

    WorldFlags* worldFlags;
    LogicMap* map;

    Filler::PlacementSet progressionItems;
    Filler::PlacementSet equipmentItems;
    Filler::PlacementSet extraItems;
    Filler::PlacementSet extraNpcs;

    void createWorld (WorldFlags& creationFlags);
};

void testTheWorld ();

#endif // __WORLD_H__
