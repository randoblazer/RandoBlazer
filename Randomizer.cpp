#include "Randomizer.h"

#include "Random.h"
#include "ROMCheck.h"
#include "ItemPool.h"
#include "Locations.h"
#include "Lairs.h"
#include "LogicGraph.h"
#include "ROMUpdate.h"
#include "Filler.h"
#include "World.h"
#include "SpoilerLog.h"
#include "IpsPatch.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/detail/sha1.hpp>

using namespace std;
using namespace LocationGroups;

namespace Randomizer {

// seedName is used by the web build to return the seed
// The CLI version just returns 0 or 1

bool Randomize(const string &InFile, const string &OutFile,
        unsigned int seed, const Options &options, string *seedName)
{
    seed = Random::RandomInit(seed);
    *seedName = std::to_string(seed);
    std::string seedText = *seedName;

    cout << "Options: "
        << (options.race ? "race, " : "")
        << (options.full ? "full" : "short")
        << ", " << (options.fastrom ? "fastrom" : "nofastrom")
        << endl;

    /*
        Race mode: we increment the seed a few times from what is actually reported.
        This means that if you take the same seed and give it without race mode
        the result will be different. But the result with race mode will be consistent
        and there is a seed we can report and use as a link.
    */
    if (options.race) {
        seed = Random::RandomInit(seed);
        seed = Random::RandomInit(seed);
        seed = Random::RandomInit(seed);
    } else {
        cout << "Seed is " << seedText << endl;
    }

    string OutFileName = OutFile;
    if (OutFileName == "Soul Blazer Randomized.smc") {
        OutFileName = "Soul Blazer Randomized (Beta)-" + seedText + ".smc";
    }

    bool romCheck = backupRom(InFile, OutFileName);
    if (!romCheck) {
        cout << "There was a problem with the ROM file!\n";
        return false;
    }

    /*
        Fastrom patch by kando
        Patreon: kandowontu - https://www.patreon.com/Kandowontu
        Twitter: @kandowontu
    */
    if (options.fastrom) {
        bool patchSuccess = applyPatch(OutFileName, FastRomPatchBuffer);
        if (patchSuccess) {
            cout << "Applied FastRom patch" << endl;
        }
    }

    std::fstream ROMFile(OutFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);

    ItemPool::populate();
    // ItemPool::logAllItems();

    LairList::readOriginalLairs(ROMFile);
    LairList lairs;
    // lairs.copyOriginalLairs();
    // lairs.logLairs();
    // lairs.lairStats();

    Locations::populate();
    // Locations::logAllLocations();

    WorldFlags worldFlags;
    worldFlags.roll();
    worldFlags.race = options.race;

    // This will set all locations vanilla
    // for (int i = 0; i < ALL_LOCATIONS_SIZE; i++) {
        // Locations::allLocations[i].itemIndex = Locations::allLocations[i].origItemIndex;
    // }
    // Locations::logAllLocations();

    // For testing
    // Locations locations;
    // testMaps(locations);
    // Filler::testPlacement();
    // testTheWorld(worldFlags);

    randomizeLairs(lairs, worldFlags);

    /*
    // Show original and modified lair info for debugging
    for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
        lairs.originalLairs[i].log();
        cout << ">>";
        lairs.lairList[i].log();
        cout << endl;
    }
    */

    // Randomize stray enemies not associated with a lair
    Lair sprites[NUMBER_OF_SPRITES];
    readOriginalSprites(sprites, ROMFile);
    randomizeSprites(sprites, worldFlags);

    // lairs.logLairs();
    // lairs.lairStats();

    int testPlaceTotal = 1;
    int totalPlaceAttempts = 0;
    int maxAttempts = 0;
    for (int testPlacementCount = 0; testPlacementCount < testPlaceTotal; testPlacementCount++) {
        bool placementSuccess = false;
        int placementCount = 0;
        while (!placementSuccess && placementCount < 10) {
            placementCount++;
            placementSuccess = randomizePlacement(worldFlags, seedText);
        }
        if (placementSuccess) {
            totalPlaceAttempts += placementCount;
            if (placementCount > maxAttempts) {
                maxAttempts = placementCount;
            }
            cout << "Placement succeeded in " << placementCount << (placementCount == 1 ? " try" : " tries") << endl;
        } else {
            cout << "Placement failed after " << placementCount << (placementCount == 1 ? " try" : " tries") << endl;
            return false;
        }
    }
    /*
    // Statistics
    cout << "Total: " << totalPlaceAttempts <<
            " Average: " << (float)totalPlaceAttempts / testPlaceTotal <<
            " Max: " << maxAttempts <<
            endl;
    */

    /* Modify the ROM with the randomized lists */
    ROMUpdate::ROMUpdateLairs(lairs, ROMFile);
    ROMUpdate::ROMUpdateMapSprites(sprites, ROMFile);
    ROMUpdate::ROMUpdateTextAndItems(lairs, ROMFile, seedText);

    /* Close the ROM file */
    ROMFile.close();
    ROMFile.clear();

    std::cout << " . . . ROM modification complete.\n";

    return true;
}

void randomizeLairs (LairList& lairs, WorldFlags& worldFlags) {
    LairProfileA profileA(worldFlags);
    LairProfileA profileAReduced(worldFlags);
    LairProfileA profileAProx(worldFlags);
    profileAReduced.reduced = true;
    profileAProx.forceProx = true;
    // LairProfileClassic classicProfile;
    // LairProfileTwo twoProfile;
    Lair* origLair;

    cout << "Randomizing lairs" << endl;

    for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
        origLair = &lairs.originalLairs[i];
        if (origLair->enemy == EnemyType::DREAM_NO_ENEMY ||
            origLair->enemy == EnemyType::NO_ENEMY
        ) {
            lairs.lairList[i] = *origLair;
        } else if (origLair->area == 106) {
            // Reduce lag in Left tower with a few tweaks
            if (origLair->x == 16 && origLair->y == 27) {
                profileAProx.roll(lairs.lairList[i], *origLair);
            } else {
                profileAReduced.roll(lairs.lairList[i], *origLair);
            }
        } else if (worldFlags.blesterMetal && origLair->area == 49) {
            // Reduce lower blester lairs to avoid sprite overload that can interfere with thunder ring
            if ((origLair->x == 33 && origLair->y == 41) ||
                (origLair->x == 25 && origLair->y == 49) ||
                (origLair->x == 42 && origLair->y == 49)
            ) {
                profileAReduced.roll(lairs.lairList[i], *origLair);
            } else {
                profileA.roll(lairs.lairList[i], *origLair);
            }
        } else {
            profileA.roll(lairs.lairList[i], *origLair);
            // classicProfile.roll(lairs.lairList[i], lairs.originalLairs[i]);
        }
    }
}

void randomizeSprites (Lair sprites[], WorldFlags& worldFlags) {
    LairProfileSprite profile;
    cout << "Randomizing sprites" << endl;
    Lair newSprite;
    for (int i = 0; i < NUMBER_OF_SPRITES; i++) {
        profile.roll(newSprite, sprites[i]);
        sprites[i] = newSprite;
    }
}

/*
    High level code for item and soul placement.
    Prefills solve several problems:
    - Avoid having too much good stuff in endgame areas
    - Devalue some areas that have a large number of checks
    - Ensure equipment upgrades by the end of Greenwood
    - Make some bosses required
    Dummy fill happens first, then progression placement.
    After that we handle any remaining locations that must have unique items (Dancing Grandmas reward)
    Then we fill the rest of spots with non-progression items and npcs.
*/
bool randomizePlacement (WorldFlags& worldFlags, string& seedText) {
    cout << "Randomizing items and souls" << endl;

    WorldMap theWorld;
    theWorld.createWorld(worldFlags);

    // Save a copy of the progression items for later
    // Filler::PlacementSet progressionList;
    // progressionList.copyFrom(&theWorld.progressionItems);

    // cout << "Progression: " << theWorld.progressionItems.size << endl;
    // cout << "Equipment: " << theWorld.equipmentItems.size << endl;
    // cout << "Extra items: " << theWorld.extraItems.size << endl;
    // cout << "Extra npcs: " << theWorld.extraNpcs.size << endl;

    // For printMap later
    // ItemPool progressionPool;
    // for (int i = 0; i < theWorld.progressionItems.size; i++) {
        // progressionPool.addItem(theWorld.progressionItems.set[i]);
    // }

    theWorld.progressionItems.shuffle();
    theWorld.equipmentItems.shuffle();
    theWorld.extraItems.shuffle();
    theWorld.extraNpcs.shuffle();

    // The first trial room chest always has Sword of Life. For now.
    Locations::allLocations[static_cast<int>(LocationID::CHEST_FIRST_SWORD)].itemIndex = ItemIndex::SWORD_OF_LIFE;

    // cout << "Empty locations: " << theWorld.map->countEmpty() << endl;

    Filler::LocationSet dummyLocations;
    Filler::PlacementSet dummyPlacementItems;

    // Don't skip the boss! One boss has vanilla release
    Filler::LocationSet bossLocationSet;
    bossLocationSet.clear();
    for (int i = 0; i < sizeof(BossLocations) / sizeof(LocationID); i++) {
        bossLocationSet.add(BossLocations[i]);
    }
    LocationID vanillaBossLocation = bossLocationSet.take();
    ItemIndex vanillaBossNpc = Locations::allLocations[static_cast<int>(vanillaBossLocation)].origItemIndex;
    theWorld.progressionItems.removeItem(vanillaBossNpc);
    Locations::allLocations[static_cast<int>(vanillaBossLocation)].itemIndex = vanillaBossNpc;
    theWorld.map->fillLocation(vanillaBossLocation);

    // cout << "Boss fill 1 done" << endl;

    // Wait, there's more - two other bosses get key NPCs
    // This could create an invalid placement, for example bridge guard on act 1 boss
    // We will verify and redo if necessary further down
    dummyPlacementItems.clear();
    for (int i = 0; i < sizeof(KeyNPCs) / sizeof(ItemIndex); i++) {
        dummyPlacementItems.add(KeyNPCs[i]);
    }
    dummyPlacementItems.shuffle();
    for (int i = 0; i < 2; i++) {
        LocationID keyNpcBossLocation = bossLocationSet.take();
        ItemIndex keyNpc = dummyPlacementItems.take();
        theWorld.progressionItems.removeItem(keyNpc);
        Locations::allLocations[static_cast<int>(keyNpcBossLocation)].itemIndex = keyNpc;
        theWorld.map->fillLocation(keyNpcBossLocation);
    }

    // cout << "Boss fill 2 done" << endl;
    // cout << "After boss fill" << endl;
    // logMap(theWorld);

    // Water shrine gets prefilled with one piece of equipment and two junk items
    dummyLocations.clear();
    for (int i = 0; i < sizeof(WaterShrineItems) / sizeof(LocationID); i++) {
        dummyLocations.add(WaterShrineItems[i]);
    }
    dummyPlacementItems.clear();
    dummyPlacementItems.add(theWorld.equipmentItems.take());
    dummyPlacementItems.add(theWorld.extraItems.take());
    dummyPlacementItems.add(theWorld.extraItems.take());
    Filler::dummyPlacement(theWorld.map, dummyPlacementItems, dummyLocations);

    // Prefill a few lairs in fire and water shrines with junk for balance
    dummyLocations.clear();
    for (int i = 0; i < sizeof(WaterShrineLairs) / sizeof(LocationID); i++) {
        dummyLocations.add(WaterShrineLairs[i]);
    }
    dummyPlacementItems.clear();
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    Filler::dummyPlacement(theWorld.map, dummyPlacementItems, dummyLocations);
    dummyLocations.clear();
    for (int i = 0; i < sizeof(FireShrineLairs) / sizeof(LocationID); i++) {
        dummyLocations.add(FireShrineLairs[i]);
    }
    dummyPlacementItems.clear();
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    Filler::dummyPlacement(theWorld.map, dummyPlacementItems, dummyLocations);

    // Magridd basement has a lot of lairs
    dummyLocations.clear();
    for (int i = 0; i < sizeof(TortureChamberLairs) / sizeof(LocationID); i++) {
        dummyLocations.add(TortureChamberLairs[i]);
    }
    dummyPlacementItems.clear();
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    dummyPlacementItems.add(theWorld.extraNpcs.take());
    Filler::dummyPlacement(theWorld.map, dummyPlacementItems, dummyLocations);
    
    // Prefill some act 6 chests to avoid it getting too loaded
    dummyLocations.clear();
    for (int i = 0; i < sizeof(MagriddChests) / sizeof(LocationID); i++) {
        dummyLocations.add(MagriddChests[i]);
    }
    dummyPlacementItems.clear();
    dummyPlacementItems.add(theWorld.extraItems.take());
    dummyPlacementItems.add(theWorld.extraItems.take());
    dummyPlacementItems.add(theWorld.extraItems.take());
    dummyPlacementItems.add(theWorld.extraItems.take());
    Filler::dummyPlacement(theWorld.map, dummyPlacementItems, dummyLocations);

    // Same with World of Evil
    dummyLocations.clear();
    for (int i = 0; i < sizeof(WorldOfEvilChests) / sizeof(LocationID); i++) {
        dummyLocations.add(WorldOfEvilChests[i]);
    }
    dummyPlacementItems.clear();
    dummyPlacementItems.add(theWorld.extraItems.take());
    dummyPlacementItems.add(theWorld.extraItems.take());
    Filler::dummyPlacement(theWorld.map, dummyPlacementItems, dummyLocations);

/*
    cout << "After all dummy fill there should be 25 filled" << endl;
    cout << "Progression: " << theWorld.progressionItems.size << endl;
    cout << "Equipment: " << theWorld.equipmentItems.size << endl;
    cout << "Extra items: " << theWorld.extraItems.size << endl;
    cout << "Extra npcs: " << theWorld.extraNpcs.size << endl;
    logMap(theWorld);
*/

    // Place progression items, this is where the real magic happens
    theWorld.progressionItems.shuffle();
    ItemPool inventory;
    inventory.addItem(ItemIndex::SWORD_OF_LIFE);
    bool success = Filler::placeItems(theWorld.map, theWorld.progressionItems, inventory);
    if (!success) {
        cout << "Placement failed" << endl;
        return false;
    }
    // cout << "Progression placement done" << endl;
    // logMap(theWorld);

    // Fill up the rest of the lairs and chests
    Filler::LocationSet emptyLocations;

    Filler::getEmptyLocations(theWorld.map, emptyLocations);
    success = Filler::mustBeUniquePlacement(theWorld.map, theWorld.equipmentItems, theWorld.extraItems, emptyLocations);

    // cout << "Placing " << theWorld.equipmentItems.size << " equipment items" << endl;
    Filler::getEmptyLocations(theWorld.map, emptyLocations);
    success = Filler::dummyPlacementWithFilter(theWorld.map, theWorld.equipmentItems, emptyLocations);
    // logMap(theWorld);

    // cout << "Placing " << theWorld.extraItems.size << " extra items" << endl;
    Filler::getEmptyLocations(theWorld.map, emptyLocations);
    success = Filler::dummyPlacementWithFilter(theWorld.map, theWorld.extraItems, emptyLocations);
    // logMap(theWorld);

    // cout << "Placing " << theWorld.extraNpcs.size << " extra npcs" << endl;
    Filler::getEmptyLocations(theWorld.map, emptyLocations);
    success = Filler::dummyPlacementWithFilter(theWorld.map, theWorld.extraNpcs, emptyLocations);
    // logMap(theWorld);

    // theWorld.map->printMap(progressionPool);
    // logMap(theWorld);

    // If we somehow fail to fill all the locations it is Very Bad.
    // There will most likely be a segfault during rom update.
    Filler::getEmptyLocations(theWorld.map, emptyLocations);
    if (emptyLocations.size > 0) {
        cout << "WARNING - failed to fill a location!" << endl;
        cout << "Empty location is " << Locations::getLocation(emptyLocations.set[0])->name << endl;
        return false;
    }

    if (worldFlags.race) {
        if (!Filler::verifyAllReachable(theWorld.map)) {
            cout << "Placement failed, could not reach all locations" << endl;
            return false;
        }
    } else {
        cout << "Writing spoiler log" << endl;
        int progressionLocations[PROGRESSION_LOCATIONS_SIZE];
        if (!Filler::createProgressionList(theWorld.map, progressionLocations)) {
            cout << "Placement failed, could not reach all locations" << endl;
            return false;
        }
        createSpoilerLog(theWorld, progressionLocations, seedText);
    }
    return true;
}

ROMStatus CheckFile (const string &Filename)
{
    /* Check that the ROM file is there, make the fstream instance */
    fstream ROMFile(Filename, ios::in | ios::out | ios::binary | ios::ate);
    if (!ROMFile.is_open())
    {
        cout << "ROM file \"" << Filename << "\" is not found!\n";
        return UNKNOWN;
    }

    /* Check if this is the headered or the un-headered ROM */
    ROMStatus originalROMStatus = CheckOriginalROM(ROMFile);
    if (originalROMStatus == UNKNOWN)
    {
        cout << "File \"" << Filename << "\" is not a known original Soul Blazer (U) ROM!\n";
        return UNKNOWN;
    }

    cout << "ROM is valid and " << (originalROMStatus == UNHEADERED ? "un-" : "") << "headered.\n";

    return originalROMStatus;
}

bool backupRom (const std::string &InFile, const std::string &OutFile)
{
    ROMStatus originalRomStatus = Randomizer::CheckFile(InFile);
    if (originalRomStatus == UNKNOWN) {
        return false;
    }

    std::ifstream ROMFileOriginal(InFile, std::ios::binary);
    std::ofstream ROMFileCopy(OutFile, std::ios::binary);

    ROMFileOriginal.seekg(0, std::ios::end);
    long ROMFileSize = ROMFileOriginal.tellg();
    if (originalRomStatus == HEADERED) {
        /* For headered ROM, ignore the first 512 bytes */
        ROMFileSize -= HEADER_OFFSET;
    }

    if (ROMFileOriginal.is_open() && ROMFileCopy.is_open()) {
        unsigned char *DataBuffer = new unsigned char[ROMFileSize];
        if (originalRomStatus == HEADERED) {
            /* For headered ROM, ignore the first 512 bytes */
            ROMFileOriginal.seekg(HEADER_OFFSET, std::ios::beg);
        } else {
            ROMFileOriginal.seekg(0, std::ios::beg);
        }
        ROMFileOriginal.read((char *)DataBuffer, ROMFileSize);
        ROMFileCopy.write((char *)DataBuffer, ROMFileSize);
        delete[] DataBuffer;
    } else if (!ROMFileCopy.is_open()) {
        std::cout << "Failure backing up the ROM!\n";
        return false;
    } else if (!ROMFileOriginal.is_open()) {
        std::cout << "Failure opening the original ROM for copying!\n";
        return false;
    }

    ROMFileOriginal.close();
    ROMFileCopy.close();
    ROMFileOriginal.clear();
    ROMFileCopy.clear();

    return true;
}

Options::Options(const string &options_string) {
    add(options_string);
}
void Options::add(const string &options_string) {
    vector<string> options_list;
    boost::algorithm::split(options_list, options_string, boost::is_any_of(","));

    for (const auto &option : options_list) {
        if (option == "race") {
            race = true;
        } else if (option == "full") {
            full = true;
        } else if (option == "short") {
            full = false;
        } else if (option == "nofastrom") {
            fastrom = false;
        } else if (option != "") {
            cout << "Unknown option: " << option << "\n";
        }
    }
}

}
