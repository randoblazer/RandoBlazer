#include "Filler.h"

#include "Locations.h"
#include "ItemPool.h"
#include "LogicGraph.h"
#include "Random.h"

#include <iostream>

namespace Filler {

PlacementSet::PlacementSet () {
    size = 0;
}
PlacementSet::~PlacementSet () {}

void PlacementSet::init (ItemIndex* initItems, int count) {
    for (int i = 0; i < count; i++) {
        set[i] = initItems[i];
    }
    size = count;
}

void PlacementSet::shuffle () {
    Random::shuffleArray(set, size);
}

ItemIndex PlacementSet::take () {
    size--;
    return set[size];
}

LocationSet::LocationSet () {
    size = 0;
}
LocationSet::~LocationSet () {}

void LocationSet::clear () {
    size = 0;
}
void LocationSet::add (LocationID location) {
    set[size] = location;
    size++;
}
void LocationSet::filter (ItemIndex itemIndex) {
    // std::cout << "Before filter " << size << " possible locations" << endl;
    // for (int i = 0; i < size; i++) {
        // cout << "  " << Locations::allLocations[static_cast<int>(set[i])].name << endl;
    // }
    int start = size - 1;
    Location location;
    Item item = ItemPool::allItems[static_cast<int>(itemIndex)];
    for (int i = start; i > 0; i--) {
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
    // int pick = Random::RandomIntegerRange(0, size);
    // cout << "Pick index " << pick << endl;
    // return set[pick];
    return set[Random::RandomInteger(size)];
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

bool placeItems (LogicMap& map, PlacementSet& placementSet, ItemPool& initialInventory) {
    LinkSet linkSet;
    LocationSet locationSet;
    ItemPool inventory;
    MapNode* nextNode;
    MapLink* nextLink;
    LocationID placementLocation;

    while (placementSet.size > 0) {
        locationSet.clear();
        linkSet.clear();
        map.clearProcessed();

        inventory.copyFrom(&initialInventory);
        ItemIndex placementItem = placementSet.take();
        for (int i = 0; i < placementSet.size; i++) {
            inventory.addItem(placementSet.set[i]);
        }
        // std::cout << "Placing " << ItemPool::allItems[static_cast<int>(placementItem)].name << endl;

        nextNode = map.map;
        while (nextNode != NULL) {
            processNode(nextNode, locationSet, linkSet, inventory);
            nextLink = linkSet.pick(inventory);
            nextNode = nextLink == NULL ? NULL : nextLink->dest;
        }

        // std::cout << "Before filter " << locationSet.size << " possible locations" << endl;
        locationSet.filter(placementItem);
        // std::cout << "After filter " << locationSet.size << " possible locations" << endl;
        if (locationSet.size == 0) {
            return false; // we failed...
        }
        placementLocation = locationSet.pick();

        // std::cout << "Placing " << ItemPool::allItems[static_cast<int>(placementItem)].name <<
            // " at " << Locations::allLocations[static_cast<int>(placementLocation)].name << endl;
        // std::cout << endl;

        map.fillLocation(placementLocation);
        Locations::allLocations[static_cast<int>(placementLocation)].itemIndex = placementItem;
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

    bool result = placeItems (miningSiteTestMap, placementSet, initialInventory);

    ItemPool testInventory;
    for (int i = 0; i < 7; i++) {
        testInventory.addItem(itemsArray[i]);
    }
    miningSiteTestMap.printMap(testInventory);

    delete miningSite;
}

}
