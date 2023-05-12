#include "SpoilerLog.h"
#include "World.h"
#include "Filler.h"
#include "Lairs.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdio.h>

#define LOCATION_NAME_SIZE    55
#define NPC_NAME_SIZE         45
#define ITEM_NAME_SIZE        40

using namespace std;
using namespace Filler;

const char* getLairAreaName(int lairArea) {
    switch (lairArea) {
    case 0x05:
        return "Underground Castle 1st screen";
    case 0x06:
        return "Underground Castle 2nd screen";
    case 0x07:
        return "Leo's Paintings 1st screen";
    case 0x08:
        return "Leo's Paintings 2nd screen";
    case 0x09:
        return "Leo's Paintings 3rd screen";
    case 0x0B:
        return "Leo's Paintings 4th screen";
    case 0x0C:
        return "Solid Arm's Lair";
    case 0x0D:
        return "Trial Room (start of the game)";
    case 0x19:
        return "Lost Marshes";
    case 0x1A:
        return "Water Shrine 1st screen";
    case 0x1B:
        return "Water Shrine 2nd screen";
    case 0x1C:
        return "Water Shrine 3rd screen";
    case 0x1D:
        return "Fire Shrine 1st screen";
    case 0x1E:
        return "Fire Shrine 2nd screen";
    case 0x1F:
        return "Fire Shrine 3rd screen";
    case 0x20:
        return "Light Shrine 1st screen";
    case 0x21:
        return "Light Shrine 2nd screen";
    case 0x22:
        return "Elemental Statues' Lair";
    case 0x2A:
        return "Seabed (south screen)";
    case 0x2E:
        return "Southerta";
    case 0x2F:
        return "Rockbird";
    case 0x30:
        return "Durean";
    case 0x31:
        return "Blester";
    case 0x32:
        return "Floating Skull's Lair";
    case 0x34:
        return "Seabed (north screen)";
    case 0x3E:
        return "Mountain of Souls 1st screen";
    case 0x3F:
        return "Mountain of Souls 2nd screen";
    case 0x41:
        return "Lune 1st screen";
    case 0x42:
        return "Lune 2nd screen";
    case 0x44:
        return "Poseidon's Lair";
    case 0x45:
        return "Mountain of Souls 3rd screen";
    case 0x46:
        return "Laynole 1st screen";
    case 0x47:
        return "Laynole 2nd screen";
    case 0x56:
        return "Leo's Lab Basement 1st screen";
    case 0x57:
        return "Leo's Lab Basement 2nd screen";
    case 0x58:
        return "Leo's Lab Power Plant";
    case 0x59:
        return "Tin Doll's Lair";
    case 0x5B:
        return "Leo's Lab Model Town 1";
    case 0x5C:
        return "Leo's Lab Model Town 2";
    case 0x66:
        return "Magridd Castle Basement 1st screen";
    case 0x67:
        return "Magridd Castle Basement 2nd screen";
    case 0x68:
        return "Magridd Castle Basement 3rd screen";
    case 0x6A:
        return "Magridd Castle Left Tower 1st screen";
    case 0x6B:
        return "Magridd Castle Left Tower 2nd screen";
    case 0x6C:
        return "Magridd Castle Left Tower 3rd screen";
    case 0x6D:
        return "Magridd Castle Right Tower 1st screen";
    case 0x6E:
        return "Magridd Castle Right Tower 2nd screen";
    case 0x6F:
        return "Magridd Castle Right Tower 3rd screen";
    case 0x72:
        return "Demon Bird's Lair";
    default:
        /* Should not happen */
        return "";
    }
}

int getActNumber (int locationId) {
    if (locationId <= static_cast<int>(LocationID::LAIR_LEOS_PAINTING_BOSS)) {
        return 1;
    }
    if (locationId <= static_cast<int>(LocationID::LAIR_LIGHT_SHRINE_STATUE_BOSS)) {
        return 2;
    }
    if (locationId <= static_cast<int>(LocationID::LAIR_GHOST_SHIP_SKULL_BOSS)) {
        return 3;
    }
    if (locationId <= static_cast<int>(LocationID::LAIR_LUNE_POSEIDON_BOSS)) {
        return 4;
    }
    if (locationId <= static_cast<int>(LocationID::LAIR_POWER_PLANT_TIN_DOLL_BOSS)) {
        return 5;
    }
    if (locationId <= static_cast<int>(LocationID::LAIR_RIGHT_TOWER_DEMON_BIRD_BOSS)) {
        return 6;
    }
    return 7;
}

void printAct (std::ofstream& LogFile, int act) {
    switch (act) {
    case 1:
        LogFile << "Act 1: Grass Valley";
        break;
    case 2:
        LogFile << "Act 2: Greenwood";
        break;
    case 3:
        LogFile << "Act 3: St Elles";
        break;
    case 4:
        LogFile << "Act 4: Mountain of Souls";
        break;
    case 5:
        LogFile << "Act 5: Leo's Lab";
        break;
    case 6:
        LogFile << "Act 6: Magridd Castle";
        break;
    default:
        LogFile << "Act 7: World of Evil";
        break;
    }
}

void createSpoilerLog(WorldMap& theWorld, int progressionLocations[], string& seedText) {
    string fileName = "SpoilerLog-" + seedText + ".txt";
    std::ofstream LogFile(fileName, std::ios::binary);
    Location* locationData;
    Location* origLocation;
    Item* itemData;
    int lastAct;
    int act;

    LogFile << "\r\n";
    LogFile << "     /=============================\\" << "\r\n";
    LogFile << "     |   RandoBlazer Spoiler Log   |"  << "\r\n";
    LogFile << "     \\=============================/" << "\r\n";
    LogFile << "\r\n";
    LogFile << "\r\n";
    
    LogFile << "Seed: " << seedText << "\r\n";
    LogFile << "\r\n";

    LogFile << "  ----- Progression -----" << "\r\n";
    LogFile << "\r\n";

    /*
        Use a progression list created by theWorld to show all key item locations grouped by sphere.
    */
    for (int i = 0; i < ALL_LOCATIONS_SIZE + 100; i++) {
        if (progressionLocations[i] == -1) {
            LogFile << "\r\n";
            if (progressionLocations[i + 1] == -2)  {
                break;
            }
            continue;
        }
        locationData = &Locations::allLocations[progressionLocations[i]];
        itemData = &ItemPool::allItems[static_cast<int>(locationData->itemIndex)];
        LogFile << std::setw(LOCATION_NAME_SIZE) << std::left << locationData->name
                << itemData->name << "\r\n";
    }

    LogFile << "  ----- All NPCs and key items -----" << "\r\n";

    lastAct = 0;
    for (int locationId = 0; locationId < Locations::allLocationsCount; locationId++) {
        act = getActNumber(locationId);
        if (act > lastAct) {
            LogFile << "\r\n";
            printAct(LogFile, act);
            LogFile << "\r\n";
            lastAct = act;
        }
        origLocation = &Locations::allLocations[locationId];
        itemData = &ItemPool::allItems[static_cast<int>(origLocation->origItemIndex)];

        if (!itemData->isConsumable && !itemData->isExperience) {
            locationData = &Locations::allLocations[Locations::itemLocation(origLocation->origItemIndex)];
            LogFile << std::setw(ITEM_NAME_SIZE) << std::left << itemData->name
                    << locationData->name << "\r\n";
        }
    }

    LogFile << "\r\n";
    LogFile << "  ----- All locations -----" << "\r\n";

    lastAct = 0;
    for (int locationId = 0; locationId < Locations::allLocationsCount; locationId++) {
        act = getActNumber(locationId);
        if (act > lastAct) {
            LogFile << "\r\n";
            printAct(LogFile, act);
            LogFile << "\r\n";
            lastAct = act;
        }
        locationData = &Locations::allLocations[locationId];
        itemData = &ItemPool::allItems[static_cast<int>(locationData->itemIndex)];
        LogFile << std::setw(LOCATION_NAME_SIZE) << std::left << locationData->name
                << itemData->name << "\r\n";
    }

    LogFile.close();
}
