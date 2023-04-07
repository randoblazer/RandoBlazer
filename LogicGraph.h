#ifndef __LOGICGRAPH_H__
#define __LOGICGRAPH_H__

#include "Locations.h"
#include "ItemPool.h"

using namespace std;


class LinkRequirement {
public:
    LinkRequirement ();
    virtual ~LinkRequirement();

    virtual bool isMet(ItemPool& inventory);
    virtual LinkRequirement* addReq(LinkRequirement* newReq);
    virtual void print ();
};

class LinkReqFree : public LinkRequirement {
public:
    LinkReqFree ();
    ~LinkReqFree ();

    bool isMet(ItemPool& inventory);
    void print ();
};

class LinkReqCheck : public LinkRequirement {
public:
    LinkReqCheck (ItemIndex check);
    ~LinkReqCheck ();

    ItemIndex checkItem;

    bool isMet(ItemPool& inventory);
    LinkRequirement* addReq(LinkRequirement* newReq);
    void print ();
};

struct LinkReqNode {
    LinkRequirement* req;
    LinkReqNode* next;
};

class LinkReqAnd : public LinkRequirement {
public:
    LinkReqAnd ();
    ~LinkReqAnd ();

    LinkReqNode* reqs;

    LinkRequirement* addReq(LinkRequirement* newReq);
    bool isMet(ItemPool& inventory);
    void print ();
};

class LinkReqOr : public LinkReqAnd {
public:
    bool isMet(ItemPool& inventory);
    void print ();
};

class MapLink;

struct MapNodeLocationNode {
    LocationID location;
    MapNodeLocationNode* next;
};
struct MapNodeLinkNode {
    MapLink* link;
    MapNodeLinkNode* next;
};

class MapNode {
public:
    MapNode();
    ~MapNode();

    int numLocations;
    int numFilled;
    MapNodeLocationNode* emptyLocations;
    MapNodeLocationNode* filledLocations;
    MapNodeLinkNode* links;
    bool processed;

    MapNode* addLocation (LocationID newLocation);
    MapNode* addLink (MapLink* newLink);
    void fillLocation (LocationID fillLocation);
    bool locationIsFilled (LocationID fillLocation);
};

class MapLink {
public:
    MapLink();
    MapLink(MapNode* sourceNode, MapNode* destNode, LinkRequirement* linkReq);
    ~MapLink();

    MapNode* source;
    MapNode* dest;
    LinkRequirement* req;
};

class LogicMap {
public:
    LogicMap (MapNode* node);
    ~LogicMap ();

    MapNode* map;
    MapNode* nodeList[ALL_LOCATIONS_SIZE];
    int nodeCount;
    MapNode* locationList[ALL_LOCATIONS_SIZE];

    void printMap (ItemPool& inventory);
    void initNodeListProcessNode (MapNode* node);
    void initNodeList ();
    void initLocationList ();
    void clearProcessed ();
    void fillLocation (LocationID fillLocation);
    bool locationIsFilled (LocationID fillLocation);
    int countEmpty ();
    int countFilled ();
};

void testLogicGraph();
void testMaps(Locations locations);


#endif // __LOGICGRAPH_H__
