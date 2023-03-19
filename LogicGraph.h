#ifndef __LOGICGRAPH_H__
#define __LOGICGRAPH_H__

#include "Locations.h"
#include "ItemPool.h"

using namespace std;


class LinkRequirement {
public:
    LinkRequirement ();
    virtual ~LinkRequirement();

    virtual bool isMet(ItemPool inventory);
    virtual LinkRequirement* addReq(LinkRequirement* newReq);
};

class LinkReqCheck : public LinkRequirement {
public:
    LinkReqCheck (ItemIndex check);
    ~LinkReqCheck ();

    ItemIndex checkItem;

    bool isMet(ItemPool inventory);
    LinkRequirement* addReq(LinkRequirement* newReq);
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
    bool isMet(ItemPool inventory);
};

class LinkReqOr : public LinkReqAnd {
public:
    bool isMet(ItemPool inventory);
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

    MapNode* addLocation (LocationID newLocation);
    MapNode* addLink (MapLink* newLink);
    void fillLocation (LocationID fillLocation);
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

void testLogicGraph();
void testMaps(Locations locations);


#endif // __LOGICGRAPH_H__
