#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include "AVLTree.h"
#include "Event.h"
using namespace std;

class EventQueue {
    public:
    AVLTree<Event> event_q;
    EventQueue() {
        
    }

    Event next() {
        // returns next event
    }

    void remove() {

    }

    void insert(Point p, Segment s) {
        // insert a point with segments passing through it
        point_seg_rel type = s.findPoint(p);
        Event e(p.x, p.y, s, type);
        AVLTreeNode<Event>* res = this->event_q.search(e);
        if(res == NULL) {
            // if no event matched, insert a new event
            event_q.insert(e);
        } else {
            // insert the segments to the current event
            res->val.insertSegment(s, type);
        }
    }

    void print() {
        this->event_q.inorder();
    }
};