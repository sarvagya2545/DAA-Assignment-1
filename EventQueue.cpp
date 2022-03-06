#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include "EventNodeAVLTree.h"
using namespace std;

// Done: AVL tree implementation
// TODO implement other methods
class EventQueue: public EventAVLTree {
    public:
    EventNode* root;

    EventQueue() {
        this->root = NULL;
    }

    EventQueue(int _x, int _y) {
        // Initialise with the first EventPoint in the queue
        this->root = new EventNode(_x, _y);
    }

    
};