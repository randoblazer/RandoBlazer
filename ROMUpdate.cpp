#include "ROMUpdate.h"
#include "TextUpdate.h"
#include "Lairs.h"
#include "Locations.h"
#include "ItemPool.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>


namespace ROMUpdate {
    void ROMUpdateTextAndItems(const LairList& randomizedLairs,
                               const Locations& locations,
                               const ItemPool& itemPool,
                               std::fstream &ROMFile,
                               const std::string& seed) {
        unsigned char Byte;

        /*************************/
        /* Update Chest contents */
        /*************************/

        ROMFile.seekp (CHEST_DATA_ADDRESS, std::ios::beg);
        bool doubledChestDone = false;
        for (int i = 0; i < NUMBER_OF_CHESTS; i++) {
            /* Put the cursor on the contents data for this chest */
            ROMFile.seekp (3, std::ios::cur);

            /* Update the contents */
            // ItemID ItemID = RandomizedItemList[i].Contents;
            Item* item = &ItemPool::allItems[(int)locations.allLocations[(int)locations.chestIdMap[i]].itemIndex];

            ROMFile.put((char)item->itemId);
            ROMFile.put(ConvertToBCD(item->ExpAmount % 100));
            ROMFile.put(ConvertToBCD(item->ExpAmount / 100));

            /* Chest at index 22 is doubled, so we have to double its replacing one */
            if (i == 22 && doubledChestDone == false) {
                i--;
                doubledChestDone = true;
            }

            /* Skip over FF bytes */
            /* Synchronize read position with write position */
            ROMFile.seekg (ROMFile.tellp(), std::ios::beg);
            do {
                ROMFile.read ((char*)(&Byte), 1);
            }
            while (Byte == 0xFF);
            ROMFile.seekp (-1, std::ios::cur);
        }

        /*************************************/
        /* Full update of text and NPC items */
        /*************************************/

        NPCTextUpdateMain(randomizedLairs, locations, itemPool, ROMFile, seed);
    }

    void ROMUpdateLairs(const LairList& randomizedLairs,
                        const Locations& locations,
                        const ItemPool& itemPool,
                        std::fstream &ROMFile) {
        ROMFile.seekp (MONSTER_LAIR_DATA_ADDRESS, std::ios::beg);

        /*
            At this point randomizedLairs has enemies randomized. However we need to swap them
            around to change what NPCs get released. That info is in locations.
        */

        LairList outputLairs;
        for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
            outputLairs.lairList[i] = randomizedLairs.lairList[i];
        }

        Location* location;
        NpcId origNpcId, newNpcId;
        for (int i = 0; i < locations.allLocationsCount; i++) {
            location = &locations.allLocations[i];
            if (location->isLair) {
                origNpcId = itemPool.allItems[(int)location->origItemIndex].npcId;
                newNpcId = itemPool.allItems[(int)location->itemIndex].npcId;
                outputLairs.lairList[(int)origNpcId] = randomizedLairs.lairList[(int)newNpcId];
            }
        }

        Lair* lair;
        for (int i = 0; i < NUMBER_OF_LAIRS; i++) {
            ROMFile.seekg(10, std::ios::cur);

            /* Update the contents of this Monster Lair */
            lair = &outputLairs.lairList[i];
            ROMFile.write((char*)(&(lair->act)), 1);
            ROMFile.write((char*)(&(lair->positionData[0])), POSITION_DATA_SIZE);
            ROMFile.seekp(2, std::ios::cur);
            unsigned char lairType[2] = {
                static_cast<unsigned char>((static_cast<unsigned int>(lair->spawnType) >> 8) & 0xFF),
                static_cast<unsigned char>(static_cast<unsigned int>(lair->spawnType) & 0xFF)
            };
            ROMFile.write((char*)&lairType, sizeof(lairType));
            ROMFile.seekp(1, std::ios::cur);
            ROMFile.write((char*)(&(lair->numEnemies)), 1);
            ROMFile.write((char*)(&(lair->spawnRate)), 1);
            ROMFile.write((char*)(&(lair->enemy)), 1);
            ROMFile.seekp(1, std::ios::cur);
            ROMFile.write((char*)(&(lair->orientation)), 1);
            ROMFile.seekp(8, std::ios::cur);
        }
        // std::cout << "Updated lairs" << endl;
    }

    void ROMUpdateMapSprites(const Sprite randomizedSpriteList[], std::fstream &ROMFile) {
        int address;
        for (int spriteIndex = 0; spriteIndex < NUMBER_OF_SPRITES; ++spriteIndex) {
            /* Get the ROM address of this sprite data */
            address = randomizedSpriteList[spriteIndex].Address;

            /* Update the contents of this Sprite */
            ROMFile.seekp (address, std::ios::beg);
            ROMFile.write((char*)(&randomizedSpriteList[spriteIndex].x), 1);
            ROMFile.write((char*)(&randomizedSpriteList[spriteIndex].y), 1);
            ROMFile.write((char*)(&randomizedSpriteList[spriteIndex].Orientation), 1);
            ROMFile.write((char*)(&randomizedSpriteList[spriteIndex].Enemy), 1);
        }
        std::cout << "Updated sprites" << endl;
    }
}
