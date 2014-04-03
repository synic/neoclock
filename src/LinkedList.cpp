#include "LinkedList.h"

LinkedList::LinkedList() {
    mSize = 0;
    mLast = 0;
    mFirst = 0;
    mDone = false;
}

LinkedList::~LinkedList() {
    for(int i = 0; i < mSize; i++) {
        Node *item = getNode(i);
        delete item;
    }
    mSize = 0;
    mFirst = 0;
    mLast = 0;
    mLast = 0;
    mDone = false;
}

int LinkedList::size() {
    return mSize;
}

bool LinkedList::add(int led) {
    Node *item = new Node();
    item->mLed = led;
    if(mFirst == 0) {
        mFirst = item;
    }

    if(mLast != 0) {
        item->mPrev = mLast;
        mLast->mNext = item;
    }

    return true;
}

bool LinkedList::done() {
    if(mLast == 0 || mFirst == 0) {
        return false;
    }

    mLast->mNext = mFirst;
    mFirst->mPrev = mLast;
    return true;
}

int LinkedList::get(int index) {
    Node *tmp = getNode(index);
    return tmp->mLed;
}

Node *LinkedList::getNode(int index) {
    Node *tmp = mFirst;

    for(int i = 0; i <= index; i++) {
        tmp = tmp->mNext;
    }

    return tmp;
}

int LinkedList::back(int index, int number) {
    Node *tmp = getNode(index);
    for(int i = 0; i < number; i++) {
        tmp = tmp->mPrev;
    }

    return tmp->mLed;
}

int LinkedList::forward(int index, int number) {
    Node *tmp = getNode(index);
    for(int i = 0; i < number; i++) {
        tmp = tmp->mNext;
    }

    return tmp->mLed;
}
