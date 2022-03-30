#include<stdio.h>
#include<stdlib.h>
using namespace std;

class LineStatus {
    public:
    AVLTree<Segment> status;
    long double y; // current y

    LineStatus() {
        
    }

    void insert(Segment s) {
        status.insert(s);
    }

    void remove(Segment s) {
        status.remove(s);
    }

    void print() {
        status.inorder();
    }

    Segment* leftNeighbour(Segment s) {

    }
};