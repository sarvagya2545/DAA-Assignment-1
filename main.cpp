#include <vector>
#include <iostream>
#include "utils.h"
#include "Segment.h"
#include "EventQueue.h"

EventQueue initEventQueue(vector<Segment> segmentList) {
    EventQueue event_queue;

    for(int i = 0; i < segmentList.size(); i++) {
        event_queue.insert(segmentList[i].en, segmentList[i]);
        event_queue.insert(segmentList[i].st, segmentList[i]);
    }

    return event_queue;
}

void findIntersections(EventQueue event_q) {
    
}

int main() {
    /*
        Find intersections:
            Input. A set S of line segments in the plane.
            Output. The set of intersection points among the segments in S, with for each intersection point the segments that contain it.
        1. Initialize an empty event queue Q. Next, insert the segment endpoints into Q; when an upper endpoint is inserted, the corresponding segment should be stored with it.
        2. Initialize an empty status structure T.
        3. while Q is not empty
        4.      do Determine the next event point p in Q and delete it.
        5.      HANDLEEVENTPOINT(p)
    */

    cout << "Input the number of segments: ";
    int n;
    cin >> n;
    vector<Segment> segmentList(n);
    double x1, y1, x2, y2;
    cout << "Input the segment endpoints in order (x1,y1,x2,y2) " << n << " times :\n";
    for(int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        segmentList[i].insert(x1,y1,x2,y2);
    }

    EventQueue ev = initEventQueue(segmentList);
    // ev.print();
    findIntersections(ev);
}