#include "Randomizer.h"

#include "ItemPool.h"

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
        ItemPool itemPool;
        itemPool.populate();
        itemPool.logAllItems();

        return true;
    }

    ROMStatus CheckFile(const string &Filename)
    {
        /* Check that the ROM file is there, make the fstream instance */
        fstream ROMFile(Filename, ios::in | ios::out | ios::binary | ios::ate);
        if (!ROMFile.is_open())
        {
            cout << "ROM file \"" << Filename << "\" is not found!\n";
            return UNKNOWN;
        }

        /* Check if this is the headered or the un-headered ROM */
        ROMStatus OriginalROMStatus = CheckOriginalROM(ROMFile);
        if (OriginalROMStatus == UNKNOWN)
        {
            cout << "File \"" << Filename << "\" is not a known original Soul Blazer (U) ROM!\n";
            return UNKNOWN;
        }

        cout << "ROM is valid and " << (OriginalROMStatus == UNHEADERED ? "un-" : "") << "headered.\n";

        return OriginalROMStatus;
    }

    Options::Options(const string &options_string)
    {
        vector<string> options_list;
        boost::algorithm::split(options_list, options_string, boost::is_any_of(","));

        for (const auto &option : options_list)
        {
            if (option == "race")
            {
                race = true;
            }
            else
            {
                cout << "Unknown option: " << option << "\n";
            }
        }
    }
}
