#ifndef __TEXTUPDATE_H__
#define __TEXTUPDATE_H__

#include "Locations.h"
#include "Lairs.h"
#include "ItemPool.h"

#include <fstream>
#include <vector>

#define NUMBER_OF_CHESTS     66
#define NUMBER_OF_NPC_ITEMS  60 
#define NUMBER_OF_ITEMS     126
#define NUMBER_OF_LAIRS     420

namespace ROMUpdate {
    int ConvertToBCD(int dec);
    void NPCTextUpdateMain(const LairList& randomizedLairs,
                           std::fstream &ROMFile,
                           const std::string& seed);
    void GeneralTextUpdate(const LairList& randomizedLairs,
                           std::fstream &ROMFile,
                           const std::string& seed);
    void NPCItemTextUpdate(int npcItemIndex,
                           int itemIndex,
                           std::fstream &ROMFile);
}

#endif // __TEXTUPDATE_H__
