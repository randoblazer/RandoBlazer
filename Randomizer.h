#ifndef __RANDOMIZER_H__
#define __RANDOMIZER_H__

#include "Lairs.h"
#include "ItemPool.h"
#include "World.h"
#include "ROMCheck.h"

#include <fstream>
#include <string>
#include <vector>

#define HEADER_OFFSET 0x200

namespace Randomizer {
    struct Options {
	Options() {}
	Options(const std::string& options_string);
        bool race = false;
    };

    void randomizeLairs(LairList& lairs, WorldFlags& worldFlags);
    ROMStatus CheckFile(const std::string& Filename);
    bool backupRom (const std::string &InFile, const std::string &OutFile);
    bool Randomize(const std::string& InFile, const std::string& OutFile, unsigned int seed, const Options& options, std::string* seed_name = 0);
}

#endif // __RANDOMIZER_H__
