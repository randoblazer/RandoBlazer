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

class MapNode {
public:
    MapNode();
    ~MapNode();

    int numLocations;
    int numFilled;
    LocationID* nodeLocations;
    LocationID* filledLocations;
    LocationID* emptyLocations;
};

class MapLink {
public:
    MapLink();
    ~MapLink();

    MapNode* source;
    MapNode* dest;
    LinkRequirement req;
};

void testLogicGraph();


#endif // __LOGICGRAPH_H__
