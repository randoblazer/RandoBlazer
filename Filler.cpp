#include "Filler.h"

#include "Locations.h"
#include "ItemPool.h"
#include "LogicGraph.h"
#include "Random.h"

#include <iostream>

namespace Filler {

PlacementSet::PlacementSet () {
    this->clear();
}
PlacementSet::~PlacementSet () {}

void PlacementSet::init (ItemIndex* initItems, int count) {
    for (int i = 0; i < count; i++) {
        set[i] = initItems[i];
    }
    size = count;
}
void PlacementSet::clear () {
    size = 0;
}
PlacementSet* PlacementSet::add (ItemIndex itemIndex) {
    set[size] = itemIndex;
    size++;
    return this;
}
void PlacementSet::shuffle () {
    Random::shuffleArray(set, size);
}
ItemIndex PlacementSet::take () {
    size--;
    return set[size];
}
void PlacementSet::removeItem (ItemIndex itemIndex) {
    for (int i = 0; i < size; i++) {
        if (set[i] == itemIndex) {
            size--;
            set[i] = set[size];
            break;
        }
    }
}

LocationSet::LocationSet () {
    size = 0;
}
LocationSet::~LocationSet () {}

void LocationSet::clear () {
    size = 0;
}
void LocationSet::copyFrom (LocationSet* source) {
    size = source->size;
    for (int i = 0; i < size; i++) {
        set[i] = source->set[i];
    }
}
LocationSet* LocationSet::add (LocationID location) {
    set[size] = location;
    size++;
    return this;
}
void LocationSet::filter (ItemIndex itemIndex) {
    // std::cout << "Before filter " << size << " possible locations" << endl;
    // for (int i = 0; i < size; i++) {
        // cout << "  " << Locations::allLocations[static_cast<int>(set[i])].name << endl;
    // }
    int start = size - 1;
    Location location;
    Item item = ItemPool::allItems[static_cast<int>(itemIndex)];
    for (int i = start; i >= 0; i--) {
        location = Locations::allLocations[static_cast<int>(set[i])];
        if (item.isNPC) {
            if (!location.isLair) {
                size--;
                set[i] = set[size];
            }
        } else {
            if (location.isLair || 
                (location.isMissable && item.isProgression) ||
                (location.mustBeUnique && !item.isUnique)) {
                    size--;
                    set[i] = set[size];
                }
        }
    }
    // std::cout << "After filter " << size << " possible locations" << endl;
    // for (int i = 0; i < size; i++) {
        // cout << "  " << Locations::allLocations[static_cast<int>(set[i])].name << endl;
    // }
}
LocationID LocationSet::pick () {
    return set[Random::RandomInteger(size)];
}
LocationID LocationSet::take () {
    int pickIndex = Random::RandomInteger(size);
    LocationID pickLocation = set[pickIndex];
    size--;
    set[pickIndex] = set[size];
    return pickLocation;
}
void LocationSet::removeLocation (LocationID location) {
    for (int i = 0; i < size; i++) {
        if (set[i] == location) {
            size--;
            set[i] = set[size];
            break;
        }
    }
}
void LocationSet::print () {
    for (int i = 0; i < size; i++) {
        std::cout << "  " << Locations::allLocations[static_cast<int>(set[i])].name << std::endl;
    }
}

LinkSet::LinkSet () {
    size = 0;
}
LinkSet::~LinkSet () {}

void LinkSet::clear () {
    size = 0;
}
void LinkSet::add (MapLink* link) {
    set[size] = link;
    size++;
}
MapLink* LinkSet::pick (ItemPool inventory) {
    MapLink* pick;
    for (int i = 0; i < size; i++) {
        if (set[i]->req->isMet(inventory)) {
            pick = set[i];
            size--;
            set[i] = set[size];
            return pick;
        }
    }
    return NULL;
}

void getEmptyLocations (LogicMap* map, LocationSet& locationSet) {
    MapNodeLocationNode* lnode;
    locationSet.clear();
    int nodeCount = map->nodeCount;
    for (int i = 0; i < nodeCount; i++) {
        lnode = map->nodeList[i]->emptyLocations;
        while (lnode != NULL) {
            locationSet.add(lnode->location);
            lnode = lnode->next;
        }
    }
}

void processNode (MapNode* node, LocationSet& locationSet, LinkSet& linkSet, ItemPool& inventory) {
    if (!node->processed) {
        MapNodeLocationNode* locNode = node->emptyLocations;
        while (locNode != NULL) {
            locationSet.add(locNode->location);
            locNode = locNode->next;
        }
        locNode = node->filledLocations;
        while (locNode != NULL) {
            inventory.addItem(Locations::allLocations[static_cast<int>(locNode->location)].itemIndex);
            locNode = locNode->next;
        }
        MapNodeLinkNode* linkNode = node->links;
        while (linkNode != NULL) {
            linkSet.add(linkNode->link);
            linkNode = linkNode->next;
        }
        node->processed = true;
    }
}

bool placeItems (LogicMap* map, PlacementSet& placementSet, ItemPool& initialInventory) {
    LinkSet linkSet;
    LocationSet locationSet;
    ItemPool inventory;
    MapNode* nextNode;
    MapLink* nextLink;
    LocationID placementLocation;

    while (placementSet.size > 0) {
        locationSet.clear();
        linkSet.clear();
        map->clearProcessed();

        inventory.copyFrom(&initialInventory);
        ItemIndex placementItem = placementSet.take();
        for (int i = 0; i < placementSet.size; i++) {
            inventory.addItem(placementSet.set[i]);
        }
        // std::cout << "Placing " << ItemPool::allItems[static_cast<int>(placementItem)].name << endl;

        nextNode = map->map;
        while (nextNode != NULL) {
            processNode(nextNode, locationSet, linkSet, inventory);
            nextLink = linkSet.pick(inventory);
            nextNode = nextLink == NULL ? NULL : nextLink->dest;
        }

        // std::cout << "Before filter " << locationSet.size << " possible locations" << endl;
        locationSet.filter(placementItem);
        // std::cout << "After filter " << locationSet.size << " possible locations" << endl;
        // locationSet.print();
        if (locationSet.size == 0) {
            return false; // we failed...
        }
        placementLocation = locationSet.pick();

        // if (ItemPool::allItems[static_cast<int>(Locations::allLocations[static_cast<int>(placementLocation)].origItemIndex)].isNPC &&
            // !ItemPool::allItems[static_cast<int>(placementItem)].isNPC) {
            // std::cout << "Placing " << ItemPool::allItems[static_cast<int>(placementItem)].name <<
                // " at " << Locations::allLocations[static_cast<int>(placementLocation)].name << endl;
            // std::cout << endl;
        // }

        map->fillLocation(placementLocation);
        Locations::allLocations[static_cast<int>(placementLocation)].itemIndex = placementItem;
    }
    return true;
}

/*
    Dummy Placement
    All of the placement items will be placed at randomly picked locations from the locationSet.
    There is no validity check i.e. lairs vs items.
    The idea is that this happens before logical placement so empty/filled state is not a concern
    and with items and locations such that any of the items can go in any location.
*/
bool dummyPlacement (LogicMap* map, PlacementSet& placementSet, LocationSet& locationSet) {
    // cout << "Dummy placement: " << placementSet.size << " items " << locationSet.size << " locations" << endl;
    ItemIndex placementItem;
    LocationID placementLocation;
    while (placementSet.size > 0) {
        placementItem = placementSet.take();
        placementLocation = locationSet.take();
        Locations::allLocations[static_cast<int>(placementLocation)].itemIndex = placementItem;
        // cout << "  fillLocation" << endl;
        map->fillLocation(placementLocation);
    }
    return true;
}
bool dummyPlacementWithFilter (LogicMap* map, PlacementSet& placementSet, LocationSet& locationSet) {
    ItemIndex placementItem;
    LocationID placementLocation;
    LocationSet filteredLocationSet;

    // cout << "dummyPlacementWithFilter: " << placementSet.size << " items in " << locationSet.size << " locations" << endl;

    while (placementSet.size > 0) {
        placementItem = placementSet.take();
        filteredLocationSet.copyFrom(&locationSet);
        filteredLocationSet.filter(placementItem);
        if (filteredLocationSet.size == 0) {
            return false;
        }
        placementLocation = filteredLocationSet.pick();
        locationSet.removeLocation(placementLocation);
        Locations::allLocations[static_cast<int>(placementLocation)].itemIndex = placementItem;
        map->fillLocation(placementLocation);
    }
    return true;
}
/*
    Placement pass for locations labelled 'mustBeUnique'
    Currently just the dancing grandmas reward - vanilla Phoenix
    Still, it should be useful to have a general process.
    Only removes placed items from the placement set.
*/
bool mustBeUniquePlacement (LogicMap* map, PlacementSet& placementSet1, PlacementSet& placementSet2, LocationSet& locationSet) {
    LocationSet uniqueLocations;
    uniqueLocations.clear();
    PlacementSet uniqueItems;
    uniqueItems.clear();
    LocationID location;
    ItemIndex itemIndex;
    for (int i = 0; i < placementSet1.size; i++) {
        if (ItemPool::allItems[static_cast<int>(placementSet1.set[i])].isUnique) {
            uniqueItems.add(placementSet1.set[i]);
        }
    }
    for (int i = 0; i < placementSet2.size; i++) {
        if (ItemPool::allItems[static_cast<int>(placementSet2.set[i])].isUnique) {
            uniqueItems.add(placementSet2.set[i]);
        }
    }
    uniqueItems.shuffle();
    for (int i = locationSet.size - 1; i >= 0; i--) {
        location = locationSet.set[i];
        if (Locations::allLocations[static_cast<int>(location)].mustBeUnique) {
            if (uniqueItems.size == 0) {
                return false; // No unique items left, we failed...
            }
            itemIndex = uniqueItems.take();
            Locations::allLocations[static_cast<int>(location)].itemIndex = itemIndex;
            map->fillLocation(location);
            locationSet.size--;
            locationSet.set[i] = locationSet.set[locationSet.size];
            placementSet1.removeItem(itemIndex);
            placementSet2.removeItem(itemIndex);
        }
    }
    return true;
}

void testPlacement () {
    MapNode* miningSite = (new MapNode())
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_FIRST)
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_SECOND)
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_THIRD)
        ->addLocation(LocationID::CRYSTAL_UNDERGROUND_CASTLE)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_1)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_2)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_3)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_4)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_5)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_6);
    MapNode* miningSite2 = (new MapNode())
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_ELEVATOR_TOP)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_1)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_2)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_3)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_4)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_5)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_6)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_7)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_8)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_9);
    MapNode* miningSite2Lisa = (new MapNode())
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_LISA)
        ->addLocation(LocationID::LAIR_UNDERGROUND_CASTLE_PART2_LISA);
    miningSite->addLink((new MapLink(miningSite, miningSite2, 
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_BRIDGE_GUARD))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_WATER_MILL))
    )));
    miningSite2->addLink((new MapLink(miningSite2, miningSite2Lisa, 
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_LISA))
            ->addReq(new LinkReqCheck(ItemIndex::DREAM_ROD))
    )));
    miningSite->addLink(new MapLink(miningSite, 
        (new MapNode())->addLocation(LocationID::NPC_TOOL_SHOP_OWNER),
        (new LinkReqCheck(ItemIndex::NPC_TOOL_SHOP_OWNER))
    ));
    miningSite->addLink(new MapLink(miningSite, 
        (new MapNode())->addLocation(LocationID::NPC_VILLAGE_CHIEF),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_VILLAGE_CHIEF))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_OLD_WOMAN))
    ));

    ItemPool initialInventory;
    initialInventory.addItem(ItemIndex::SWORD_OF_LIFE);

    ItemIndex itemsArray[] = {
        ItemIndex::NPC_BRIDGE_GUARD,
        ItemIndex::NPC_WATER_MILL,
        ItemIndex::NPC_OLD_WOMAN,
        ItemIndex::NPC_VILLAGE_CHIEF,
        ItemIndex::NPC_TOOL_SHOP_OWNER,
        ItemIndex::NPC_LISA,
        ItemIndex::DREAM_ROD
    };
    PlacementSet placementSet;
    placementSet.init(itemsArray, 7);
    placementSet.shuffle();

    LogicMap miningSiteTestMap(miningSite);

    bool result = placeItems (&miningSiteTestMap, placementSet, initialInventory);

    ItemPool testInventory;
    for (int i = 0; i < 7; i++) {
        testInventory.addItem(itemsArray[i]);
    }
    miningSiteTestMap.printMap(testInventory);

    delete miningSite;
}

}
