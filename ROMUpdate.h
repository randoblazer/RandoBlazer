#ifndef __ROMUPDATE_H__
#define __ROMUPDATE_H__

#include "Sprite.h"
#include "Locations.h"
#include "Lairs.h"
#include "ItemPool.h"
#include "TextUpdate.h"

#include <fstream>
#include <vector>

#define CHEST_DATA_ADDRESS        0xAADE

namespace ROMUpdate {
    void ROMUpdateTextAndItems(const LairList& randomizedLairs,
                               const Locations& locations,
                               const ItemPool& itemPool,
                               std::fstream &ROMFile,
                               const std::string& seed);
    void ROMUpdateLairs(const LairList& randomizedLairs,
                        const Locations& locations,
                        const ItemPool& itemPool,
                        std::fstream &ROMFile);
    void ROMUpdateMapSprites(const Sprite randomizedSpriteList[], std::fstream &ROMFile);
}

#endif // __ROMUPDATE_H__
