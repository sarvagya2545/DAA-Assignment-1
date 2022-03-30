#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;

class EventQueue {
    public:
    AVLTree<Event> event_q;
    EventQueue() {
        
    }

    bool empty() {
        return event_q.root == NULL;
    }

    Event next() {
        // returns next event & removes it from the event queue
        AVLTreeNode<Event>* node = event_q.minNode();

        Event e = node->val;
        remove(e);
        return e;
    }

    void remove(Event e) {
        event_q.remove(e);
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