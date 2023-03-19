#include "Randomizer.h"

//#include "Log.h"
#include "Random.h"
#include "ROMCheck.h"
#include "ItemPool.h"
#include "Locations.h"
#include "Lairs.h"
#include "Sprite.h"
#include "LogicGraph.h"
#include "ROMUpdate.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/detail/sha1.hpp>

using namespace std;

namespace Randomizer
{
    bool Randomize(const string &InFile, const string &OutFile, unsigned int seed, const Options &options, string *seedName)
    {
        seed = Random::RandomInit(seed);
        std::string seedText = std::to_string(seed);

        /*
            Race mode: we increment the seed a few times from what is actually reported.
            This means that if you take the same seed and give it without race mode
            the result will be different. But the result with race mode will be consistent
            and there is a seed we can report and use as a link.
        */
        if (options.race) {
            std::cout << "Race mode enabled\n";
            seed = Random::RandomInit(seed);
            seed = Random::RandomInit(seed);
            seed = Random::RandomInit(seed);
        }

        bool romCheck = backupRom(InFile, OutFile);
        if (!romCheck) {
            cout << "There was a problem with the ROM file!\n";
            return false;
        }

        std::fstream ROMFile(OutFile, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);

        ItemPool::populate();
        // ItemPool::logAllItems();
        ItemPool itemPool;

        LairList::readOriginalLairs(ROMFile);
        LairList lairs;
        lairs.copyOriginalLairs();
        // lairs.logLairs();

        Locations::populate();
        Locations locations;
        // locations.logAllLocations();

        testMaps(locations);

        // To get started, just set each location to vanilla
        for (int i = 0; i < ALL_LOCATIONS_SIZE; i++) {
            locations.allLocations[i].itemIndex = locations.allLocations[i].origItemIndex;
        }
        // locations.logAllLocations();

        // Randomize stray enemies not associated with a lair
        Sprite randomizedSpriteList[NUMBER_OF_SPRITES];
        GetOriginalMapSpriteData(randomizedSpriteList, ROMFile);

        /* Modify the ROM with the randomized lists */
        ROMUpdate::ROMUpdateLairs(lairs, locations, itemPool, ROMFile);
        ROMUpdate::ROMUpdateMapSprites(randomizedSpriteList, ROMFile);
        ROMUpdate::ROMUpdateTextAndItems(lairs, locations, itemPool, ROMFile, seedText);

        /* Close the ROM file */
        ROMFile.close();
        ROMFile.clear();

        std::cout << " . . . ROM modification complete.\n";

/*  No spoiler log for now, need to avoid duplicate definition for Item
        if (!options.race)
        {
            std::cout << "Starting Spoiler Log creation.\n";

            // Generate the Spoiler Log
            Log::CreateSpoilerLog(RandomizedLairList, RandomizedItemList);

            std::cout << " . . . Spoiler Log created.\n";
        }
*/
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

    Options::Options(const string &options_string)
    {
        vector<string> options_list;
        boost::algorithm::split(options_list, options_string, boost::is_any_of(","));

        for (const auto &option : options_list) {
            if (option == "race") {
                race = true;
            } else {
                cout << "Unknown option: " << option << "\n";
            }
        }
    }
}
