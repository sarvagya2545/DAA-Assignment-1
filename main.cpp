#include <vector>
#include <iostream>
#include <limits.h>
#include "utils.h"
#include "Segment.h"
#include "Event.h"
#include "AVLTree.h"
#include "EventQueue.h"
#include "LineStatus.h"

LineStatus status_queue;
EventQueue event_queue;
vector<pair<Point, vector<vector<Segment>>>> intersections;

EventQueue initEventQueue(vector<Segment> segmentList) {
    EventQueue event_queue;

    for(int i = 0; i < segmentList.size(); i++) {
        event_queue.insert(segmentList[i].en, segmentList[i]);
        event_queue.insert(segmentList[i].st, segmentList[i]);
    }

    return event_queue;
}

void findNewEvent(Segment s_l, Segment s_r, Point p) {
    /*
        1.  if sl and sr intersect below the sweep line, or on it and to the right of the
            current event point p, and the intersection is not yet present as an
            event in Q
        2.  then Insert the intersection point as an event into Q.
    */

    // Steps to figure out whether line segments intersect:
    // 1. 

    cout << "\n************\n";
    cout << "Find new event function";
    cout << "\nSegment left " << s_l;
    cout << "\nSegment right " << s_r;

    cout << "\nPoint " << p;
    cout << "\n************\n";
}

Segment findLeftMostSeg(vector<Segment> lineSet) {
    // left most segment is the segment with min x coordinate for a particular y
    float min_x = lineSet[0].x(Segment::sweeplineY);
    Segment mn = lineSet[0];

    for(int i = 0; i < lineSet.size(); i++) {
        float x = lineSet[i].x(Segment::sweeplineY);
        if(x < min_x) {
            min_x = x;
            mn = lineSet[i];
        }
    }

    return mn;
}

Segment findRightMostSeg(vector<Segment> lineSet) {
    // right most segment is the segment with max x coordinate for a particular y
    float max_x = lineSet[0].x(Segment::sweeplineY);
    Segment mx = lineSet[0];

    for(int i = 0; i < lineSet.size(); i++) {
        float x = lineSet[i].x(Segment::sweeplineY);
        if(x > max_x) {
            max_x = x;
            mx = lineSet[i];
        }
    }

    return mx;
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
    // operations done on the segment just above the intersection
    changeY(e.y + delta);

    for(int i = 0; i < LCset.size(); i++) {
        // delete the segment
        status_queue.remove(LCset[i]);
    }

    // operations done on the segment just below the intersection
    changeY(e.y - delta);

    for(int i = 0; i < UCset.size(); i++) {
        // insert the segment
        status_queue.insert(UCset[i]);
    }

    cout << "Printing Status Queue...\n";
    status_queue.print();

    cout << "Printing intersections...\n" << intersections.size();

    Point p(e.x, e.y);

    if(UCset.size() == 0) {
        cout << "Size 0";
        pair<bool, vector<Segment>> neighbours = status_queue.neighbours(p);

        if(neighbours.first) {
            vector<Segment> neighbourList = neighbours.second;
            cout << "\n** ** ** ** ** **\n";
            cout << neighbourList[0] << "\t" << neighbourList[1];
            cout << "\n** ** ** ** ** **\n";

            findNewEvent(neighbourList[0], neighbourList[1], p);
        }

    } else {

        cout << "Size not 0";
        Segment leftMostSeg = findLeftMostSeg(UCset);
        pair<bool,Segment> p_l = status_queue.leftNeighbour(leftMostSeg);
        Segment s_l = p_l.second;
        if(p_l.first) {
            findNewEvent(s_l, leftMostSeg, p);
        }

        Segment rightMostSeg = findRightMostSeg(UCset);
        pair<bool,Segment> p_r = status_queue.rightNeighbour(rightMostSeg);
        Segment s_r = p_r.second;
        if(p_r.first) {
            findNewEvent(s_r, rightMostSeg, p);
        }
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

    event_queue = initEventQueue(segmentList);
    event_queue.print();
    cout << "Find intersections...\n";
    findIntersections(event_queue);

    return 0;
}