#include "RoundClock.h"

/**
 * Constructor
 */
RoundClock::RoundClock() {
    mSize = 0;
    mLast = 0;
    mFirst = 0;
    mDone = false;
}

/**
 * Destructor
 */
RoundClock::~RoundClock() {
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

/**
 * Returns the current size of the linked list contained here
 */
int RoundClock::size() {
    return mSize;
}

/**
 * Adds an item to the list
 */
bool RoundClock::add(int led) {
    if(mDone) return false;

    Node *item = new Node();
    item->mLed = led;
    if(mFirst == 0) {
        mFirst = item;
    }

    if(mLast != 0) {
        item->mPrev = mLast;
        mLast->mNext = item;
    }

    mLast = item;

    return true;
}

/**
 * Tells the class that you're done adding items, and to link the first and
 * the last elements.
 */
bool RoundClock::done() {
    if(mLast == 0 || mFirst == 0) {
        return false;
    }

    mLast->mNext = mFirst;
    mFirst->mPrev = mLast;
    mDone = true;
    return true;
}

/**
 * Gets the LED number at the specified index
 */
int RoundClock::get(int index) {
    Node *tmp = getNode(index);
    return tmp->mLed;
}

/**
 * Gets the Node at the specified index
 */
Node *RoundClock::getNode(int index) {
    Node *tmp = mFirst;

    for(int i = 0; i <= index; i++) {
        tmp = tmp->mNext;
    }

    return tmp;
}

/**
 * Returns the LED marked that is `number` items backward from index
 */
int RoundClock::back(int index, int number) {
    Node *tmp = getNode(index);
    for(int i = 0; i <= number; i++) {
        tmp = tmp->mPrev;
    }

    return tmp->mLed;
}

/**
 * Returns the LED marked that is `number` items forward from index.  Performs
 * looping if necessary.
 */
int RoundClock::forward(int index, int number) {
    Node *tmp = getNode(index);
    for(int i = 0; i <= number; i++) {
        tmp = tmp->mNext;
    }

    return tmp->mLed;
}
