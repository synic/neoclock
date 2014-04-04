#ifndef __AOLIB_ROUNDCLOCK_H
#define __AOLIB_ROUNDCLOCK_H

/**
 * A simple double linked list to represent a round clock.
 *
 * It allows you to take any point on the clock, and tell it you want
 * <i>n</i> number of elements backward (or forward), and it will loop around
 * the end to get you the values you need.
 */

class Node {
    public:
        int mLed;
        Node *mNext;
        Node *mPrev;
};

class RoundClock {
    protected:
        int mSize;
        Node *mFirst;
        Node *mLast;
        bool mDone;
        virtual Node* getNode(int index);

    public:
        RoundClock();
        ~RoundClock();
        virtual int size();
        virtual bool add(int led);
        virtual bool done();
        virtual int get(int index);
        virtual int back(int index, int number);
        virtual int forward(int index, int number);
};

#endif
