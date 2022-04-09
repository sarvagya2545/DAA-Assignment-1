#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;

/// @brief Implementation of Event Queue using AVLtree
class EventQueue {
    public:
    /// @brief event queue represented using AVL tree of node type Event
    AVLTree<Event> event_q;

    EventQueue() {
        
    }

    /// @brief Utility function to check whether the queue is empty or not
    bool empty() {
        return event_q.root == NULL;
    }

    /// @brief Function to find the next point in the event queue 
    /// @returns Event object which will come next for execution
    Event next() {
        // returns next event & removes it from the event queue
        AVLTreeNode<Event>* node = event_q.minNode();

        Event e = node->val;
        remove(e);
        return e;
    }

    /// @brief Function to remove an event from the event queue
    void remove(Event e) {
        event_q.remove(e);
    }

    /// @brief Function to remove an event from the event queue
    /// @param p A point P which will be inserted into the event queue
    /// @param s The segment which will be inserted with the point
    void insert(Point p, Segment s) {
        // insert a point with segments passing through it
        point_seg_rel type = s.findPoint(p);
        Event e(p.x, p.y, s, type);

        cout << "Event\t " << e << endl;

        cout << "\nPrinting inside before inserting event;\n";
        event_q.inorder();
        cout << "\nFinished Printing inside before inserting event;\n";

        AVLTreeNode<Event>* res = this->event_q.search(e);
        if(res == NULL) {
            cout << "Inserting new event";
            // if no event matched, insert a new event
            this->event_q.insert(e);
        } else {
            cout << "Result" << res->val;
            // insert the segments to the current event
            res->val.insertSegment(s, type);

            cout << "Result After\t" << res->val;
        }

        cout << "\nPrinting inside after inserting event;\n";
        event_q.inorder();
        cout << "\nFinished Printing inside after inserting event;\n";
    }

    /// @brief Function to print the event queue in inorder fashion
    void print() {
        this->event_q.inorder();
    }
};