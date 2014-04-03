#ifndef __AOLIB_LINKEDLIST_H
#define __AOLIB_LINKEDLIST_H

class Node {
    public:
        int mLed;
        Node *mNext;
        Node *mPrev;
};

class LinkedList {
    protected:
        int mSize;
        Node *mFirst;
        Node *mLast;
        bool mDone;
        virtual Node* getNode(int index);

    public:
        LinkedList();
        ~LinkedList();
        virtual int size();
        virtual bool add(int led);
        virtual bool done();
        virtual int get(int index);
        virtual int back(int index, int number);
        virtual int forward(int index, int number);
};

#endif
