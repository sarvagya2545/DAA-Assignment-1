#include <vector>
#include <iostream>
#include "utils.h"
#include "AVLTree.h"
#include "Segment.h"
#include "Event.h"
#include "EventQueue.h"
#include "LineStatus.h"

LineStatus status_queue;
vector<pair<Point, vector<vector<Segment>>>> intersections;

EventQueue initEventQueue(vector<Segment> segmentList) {
    EventQueue event_queue;

    for(int i = 0; i < segmentList.size(); i++) {
        event_queue.insert(segmentList[i].en, segmentList[i]);
        event_queue.insert(segmentList[i].st, segmentList[i]);
    }

    return event_queue;
}

vector<Segment> unionOf(vector<Segment> lineSet1, vector<Segment> lineSet2) {
    vector<Segment> unionSet(lineSet1);

    for(int i = 0; i < lineSet2.size(); i++) {
        bool unique = true;
        for(int j = 0; j < lineSet1.size(); j++) {
            if(lineSet1[j] == lineSet2[i]) {
                unique = false;
                break;
            }
        }

        if(unique) {
            unionSet.push_back(lineSet2[i]);
        }
    }

    return unionSet;
}

void handleEventPoint(Event e) {
    // no. of segments interacting with the event point
    int segment_count = e.segments[L].size() + e.segments[U].size() + e.segments[C].size();

    if(segment_count > 1) {
        Point p(e.x, e.y);
        intersections.push_back(make_pair(p, e.segments));
    }

    // Delete L(p) U C(p) from status structure
    vector<Segment> LCset = unionOf(e.segments[L], e.segments[C]);
    vector<Segment> UCset = unionOf(e.segments[U], e.segments[C]);

    float delta = 0.0001;
    // Segment::sweeplineY = e.y + delta;
    changeY(e.y + delta);

    for(int i = 0; i < LCset.size(); i++) {
        // delete the segment
        status_queue.remove(LCset[i]);
    }

    // Segment::sweeplineY = e.y - delta;
    changeY(e.y - delta);

    for(int i = 0; i < UCset.size(); i++) {
        // insert the segment
        status_queue.insert(UCset[i]);
    }

    // cout << "Printing...\n";
    // status_queue.print();

    // cout << "Printing intersections...\n" << intersections.size();

    if(UCset.size() == 0) {
        // TODO: 1. find left and right neighbours
        //       2. find new event points
        
    } else {

    }
}

void findIntersections(EventQueue event_q) {
    cout << "Inside findIntersections...\n";
    while(!event_q.empty()) {
        cout << "Event handle...\n";
        Event nextEvent = event_q.next();
        handleEventPoint(nextEvent);
    }
}

int main() {
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
    ev.print();
    cout << "Find intersections...\n";
    findIntersections(ev);
}