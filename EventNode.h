#include<stdio.h>
#include<stdlib.h>
using namespace std;

// This is the node of the events
class EventNode {
    public:
    int x;
    int y;
    int height; // height because AVL tree used
    EventNode* left;
    EventNode* right;

    EventNode() {
        this->x = 0;
        this->y = 0;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }

    EventNode(int _x, int _y) {
        // initialize a new event with x & y coordinates
        this->x = _x;
        this->y = _y;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};
