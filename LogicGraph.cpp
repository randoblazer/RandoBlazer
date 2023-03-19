#include "LogicGraph.h"

#include "ItemPool.h"

#include <iostream>

using namespace std;

LinkRequirement::LinkRequirement() {};
LinkRequirement::~LinkRequirement() {};
bool LinkRequirement::isMet(ItemPool inventory) {
    return false;
};
LinkRequirement* LinkRequirement::addReq(LinkRequirement* newReq) {
    return this;
};

LinkReqCheck::LinkReqCheck (ItemIndex check) {
    checkItem = check;
}
LinkReqCheck::~LinkReqCheck () {}
LinkRequirement* LinkReqCheck::addReq(LinkRequirement* newReq) {
    return this;
};
bool LinkReqCheck::isMet (ItemPool inventory) {
    return inventory.itemList[static_cast<int>(checkItem)] > 0;
}

LinkReqAnd::LinkReqAnd () {
    reqs = NULL;
}
LinkRequirement* LinkReqAnd::addReq(LinkRequirement* newReq) {
    LinkReqNode* newNode = new LinkReqNode;
    newNode->req = newReq;
    newNode->next = reqs;
    reqs = newNode;
    return this;
}
LinkReqAnd::~LinkReqAnd () {
    LinkReqNode* node = reqs;
    LinkReqNode* nextNode;
    while (node != NULL) {
        nextNode = node->next;
        delete node->req;
        delete node;
        node = nextNode;
    }
}
bool LinkReqAnd::isMet (ItemPool inventory) {
    LinkReqNode* node = reqs;
    while (node != NULL) {
        if (!node->req->isMet(inventory)) {
            return false;
        }
        node = node->next;
    }
    return true;
}

bool LinkReqOr::isMet (ItemPool inventory) {
    LinkReqNode* node = reqs;
    while (node != NULL) {
        if (node->req->isMet(inventory)) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void testLogicGraph() {
    ItemPool inventory;
    inventory.addItem(ItemIndex::NPC_LISA);
    inventory.addItem(ItemIndex::NPC_DR_LEO);
    inventory.addItem(ItemIndex::DREAM_ROD);

    // std::cout << "Lisa is " << static_cast<int>(ItemIndex::NPC_LISA) << std::endl;

    LinkReqCheck lisaCheck(ItemIndex::NPC_LISA);
    std::cout << (lisaCheck.isMet(inventory) ? "We have Lisa" : "No Lisa") << endl;
    LinkReqCheck leoCheck(ItemIndex::NPC_DR_LEO);
    std::cout << (leoCheck.isMet(inventory) ? "We have Dr. Leo" : "No Leo") << endl;

    LinkRequirement* andCheck = (new LinkReqAnd())
        ->addReq(new LinkReqCheck(ItemIndex::NPC_LISA))
        ->addReq(new LinkReqCheck(ItemIndex::NPC_DR_LEO));

    std::cout << (andCheck->isMet(inventory) ? "We have both Lisa and Leo" : "Do not have both Lisa and Leo") << endl;
    delete andCheck;

    LinkRequirement* complexCheck = (new LinkReqAnd())
        ->addReq((new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_LISA))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_DR_LEO))
        )->addReq((new LinkReqOr())
            ->addReq(new LinkReqCheck(ItemIndex::DREAM_ROD))
            ->addReq(new LinkReqCheck(ItemIndex::LEOS_BRUSH))
        );
    std::cout << (complexCheck->isMet(inventory) ? "We have both Lisa and Leo and rod or brush" : "Do not meet") << endl;
    delete complexCheck;
}

MapNode::MapNode() {
    numLocations = 0;
    numFilled = 0;
    emptyLocations = NULL;
    filledLocations = NULL;
    links = NULL;
}
MapNode::~MapNode() {
    MapNodeLocationNode* node = emptyLocations;
    MapNodeLocationNode* nextNode;
    while (node != NULL) {
        nextNode = node->next;
        delete node;
        node = nextNode;
    }
    node = filledLocations;
    while (node != NULL) {
        nextNode = node->next;
        delete node;
        node = nextNode;
    }
    MapNodeLinkNode* lnode = links;
    MapNodeLinkNode* nextLnode;
    while (lnode != NULL) {
        nextLnode = lnode->next;
        delete lnode->link;
        delete lnode;
        lnode = nextLnode;
    }
}
MapNode* MapNode::addLocation (LocationID newLocation) {
    MapNodeLocationNode* newNode = new MapNodeLocationNode();
    newNode->location = newLocation;
    newNode->next = emptyLocations;
    emptyLocations = newNode;
    numLocations++;
    return this;
}
MapNode* MapNode::addLink (MapLink* newLink) {
    MapNodeLinkNode* newNode = new MapNodeLinkNode();
    newNode->link = newLink;
    newNode->next = links;
    links = newNode;
    return this;
}
void MapNode::fillLocation (LocationID fillLocation) {
    MapNodeLocationNode* node;
    MapNodeLocationNode* nextNode;
    if (emptyLocations == NULL) {
        return;
    }
    node = emptyLocations;
    if (node->location == fillLocation) {
        emptyLocations = node->next;
    } else {
        nextNode = node->next;
        while (nextNode != NULL && nextNode->location != fillLocation) {
            node = nextNode;
            nextNode = node->next;
        }
        if (nextNode == NULL) {
            return;
        } else {
            node->next = nextNode->next;
            node = nextNode;
        }
    }
    node->next = filledLocations;
    filledLocations = node;
    numFilled++;
}

MapLink::MapLink () {
    source = NULL;
    dest = NULL;
    req = NULL;
};
MapLink::MapLink (MapNode* sourceNode, MapNode* destNode, LinkRequirement* linkReq) {
    source = sourceNode;
    dest = destNode;
    req = linkReq;
};
MapLink::~MapLink () {
    if (req != NULL) {
        delete req;
    }
};

void printEmptyLocationsRec (MapNode* startNode, ItemPool inventory, Locations locations) {
    // This is a simplified test that only considers a static inventory.
    // If we 'pick up' things on the way it gets a lot more complicated.

    std::cout << (startNode->numLocations - startNode->numFilled) << " empty locations:" << std::endl;
    MapNodeLocationNode* node = startNode->emptyLocations;
    LocationID location;
    while (node != NULL) {
        locations.logLocation(locations.allLocations[static_cast<int>(node->location)]);
        node = node->next;
    }
    MapNodeLinkNode* lnode = startNode->links;
    while (lnode != NULL) {
        if (lnode->link != NULL && lnode->link->req->isMet(inventory)) {
            printEmptyLocationsRec(lnode->link->dest, inventory, locations);
        } else {
            std::cout << "link requirement not met" << std::endl;
        }
        lnode = lnode->next;
    }
}
void printEmptyLocationsMain (MapNode* startNode, Locations locations) {
    ItemPool inventory;
    inventory.addItem(ItemIndex::NPC_BRIDGE_GUARD);
    inventory.addItem(ItemIndex::NPC_WATER_MILL);
    inventory.addItem(ItemIndex::NPC_LISA);
    inventory.addItem(ItemIndex::NPC_DR_LEO);
    // inventory.addItem(ItemIndex::DREAM_ROD);
    inventory.addItem(ItemIndex::NPC_TOOL_SHOP_OWNER);

    printEmptyLocationsRec(startNode, inventory, locations);
}

void testMaps (Locations locations) {
    MapNode* miningSite = (new MapNode())
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_FIRST)
        ->addLocation(LocationID::CHEST_UNDERGROUND_CASTLE_SECOND)
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
        (new MapNode())->addLocation(LocationID::NPC_TOOL_SHOP_OWNER),
        (new LinkReqAnd())
            ->addReq(new LinkReqCheck(ItemIndex::NPC_VILLAGE_CHIEF))
            ->addReq(new LinkReqCheck(ItemIndex::NPC_OLD_WOMAN))
    ));

    printEmptyLocationsMain(miningSite, locations);
    delete miningSite;
}
