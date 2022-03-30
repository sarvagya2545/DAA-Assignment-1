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

void printIntersections(vector<pair<Point, vector<vector<Segment>>>> intersections) {
    cout << "Printing intersections:\n";
    cout << "\n*** *** *** *** *** *** *** *** *** *** ***\n";
    cout << "\n*** *** *** *** *** *** *** *** *** *** ***\n";
    cout << "\n*** *** *** *** *** *** *** *** *** *** ***\n";
    for(int i = 0; i < intersections.size(); i++) {
        cout << intersections[i].first << "\n";
    }
    cout << "\n*** *** *** *** *** *** *** *** *** *** ***\n";
    cout << "\n*** *** *** *** *** *** *** *** *** *** ***\n";
    cout << "\n*** *** *** *** *** *** *** *** *** *** ***\n";
}

EventQueue initEventQueue(vector<Segment> segmentList) {
    EventQueue event_queue;

    for(int i = 0; i < segmentList.size(); i++) {
        event_queue.insert(segmentList[i].en, segmentList[i]);
        event_queue.insert(segmentList[i].st, segmentList[i]);
    }

    return event_queue;
}

pair<bool, pair<float, float>> intersect(Point A, Point B, Point C, Point D){
    float a1 = B.y - A.y;
    float b1 = A.x - B.x;
    float c1 = a1*(A.x) + b1*(A.y);
 
    float a2 = D.y - C.y;
    float b2 = C.x - D.x;
    float c2 = a1*(C.x) + b1*(C.y);
 
    float determinant = a1*b2 - a2*b1;
 
    if (determinant == 0)          //The lines are parallel
        return make_pair(false, make_pair(FLT_MAX, FLT_MAX));
    
    else{
        float x = (b2*c1 - b1*c2)/determinant;      // x intersection point
        float y = (a1*c2 - a2*c1)/determinant;      // y intersection point
 
        // check if (x, y) lies on both the lines
        if(min(A.x, B.x) <= x <= max (A.x, B.x) && min(A.y, B.y) <= y <= max (A.y, B.y) 
          && min(C.x, D.x) <= x <= max (C.x, D.x) && min(C.x, D.x) <= x <= max (C.x, D.x))
            return make_pair(true, make_pair(x, y));
 
        else
            return make_pair(false, make_pair(FLT_MAX, FLT_MAX));
    }
}

void findNewEvent(Segment s_l, Segment s_r, Point p) {
    cout << "S_l" << s_l;
    cout << "S_r" << s_r;
    pair<bool, pair<float, float>> ans = intersect(s_l.st, s_l.en, s_r.st, s_r.en);
    bool hasIntersection = ans.first;
    pair<float, float> coor = ans.second;
    if(hasIntersection) {
        Point intersection_point(coor.first, coor.second);
        cout << "\nintersection_point\t" << intersection_point;
        // event_queue.insert(intersection_point, s_l);
        // event_queue.insert(intersection_point, s_r);
    }
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

    // cout << "Printing Status Queue...\n";
    // status_queue.print();

    // cout << "Printing intersections...\n" << intersections.size();

    Point p(e.x, e.y);

    if(UCset.size() == 0) {
        cout << "Size 0";
        pair<bool, vector<Segment>> neighbours = status_queue.neighbours(p);

        if(neighbours.first) {
            vector<Segment> neighbourList = neighbours.second;
            // cout << "\n** ** ** ** ** **\n";
            // cout << neighbourList[0] << "\t" << neighbourList[1];
            // cout << "\n** ** ** ** ** **\n";

            findNewEvent(neighbourList[0], neighbourList[1], p);
        }

    } else {

        cout << "Size not 0";
        Segment leftMostSeg = findLeftMostSeg(UCset);
        pair<bool,Segment> p_l = status_queue.leftNeighbour(leftMostSeg);
        Segment s_l = p_l.second;
        if(p_l.first) {
            // cout << "S_l" << s_l;
            findNewEvent(s_l, leftMostSeg, p);
        }

        Segment rightMostSeg = findRightMostSeg(UCset);
        pair<bool,Segment> p_r = status_queue.rightNeighbour(rightMostSeg);
        Segment s_r = p_r.second;
        if(p_r.first) {
            // cout << "S_r" << s_r;
            findNewEvent(s_r, rightMostSeg, p);
        }
    }
}

void findIntersections(EventQueue event_q) {
    // cout << "Inside findIntersections...\n";
    while(!event_q.empty()) {
        // cout << "Event handle...\n";
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
    // event_queue.print();
    // cout << "Find intersections...\n";
    findIntersections(event_queue);

    printIntersections(intersections);

    return 0;
}