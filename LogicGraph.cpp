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
    newNode->next = NULL;
    if (reqs == NULL) {
        reqs = newNode;
    } else {
        LinkReqNode* lastNode = reqs;
        lastNode = reqs;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
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
