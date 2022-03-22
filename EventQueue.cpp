#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include "EventNodeAVLTree.h"
using namespace std;

class EventQueue {
    public:
    EventAVLTree* tree;

    EventQueue() {
        this->tree = new EventAVLTree();
    }

    EventQueue(int _x, int _y) {
        // Initialise with the first EventPoint in the queue
        this->tree = new EventAVLTree();
        this->tree->insert(_x, _y);
    }

    
};

int main() {
    EventQueue* eq = new EventQueue();
    
    return 0;
}