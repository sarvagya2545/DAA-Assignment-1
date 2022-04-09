#include <vector>
#include <iostream>
#include <limits>
#include "utils.h"
#include "Segment.h"
#include "Event.h"
#include "AVLTree.h"
#include "EventQueue.h"
#include "LineStatus.h"

LineStatus status_queue;
EventQueue event_queue;
vector<pair<Point, vector<vector<Segment>>>> intersections;

// limits
const float FLT_MIN = std::numeric_limits<float>::lowest();
const float FLT_MAX = std::numeric_limits<float>::max();

/// @brief Function to print Intersections
/// @param intersections A vector containing a pair of a point and a segment list containing segments passing through it
void printIntersections(vector<pair<Point, vector<vector<Segment>>>> intersections) {
    cout << "\nPrinting intersections:\n";
    cout << "\n*** *** *** *** *** *** *** *** *** *** ***\n";
    for(int i = 0; i < intersections.size(); i++) {
        cout << intersections[i].first << "\n";
    }
    cout << "\n*** *** *** *** *** *** *** *** *** *** ***\n";
}

/// @brief Function to initialise event queue with the segment endpoints
/// @param segmentList a list of segments
/// @returns An initialised EventQueue object with segment endpoints
EventQueue initEventQueue(vector<Segment> segmentList) {
    EventQueue event_queue;

    for(int i = 0; i < segmentList.size(); i++) {
        event_queue.insert(segmentList[i].en, segmentList[i]);
        event_queue.insert(segmentList[i].st, segmentList[i]);
    }

    return event_queue;
}

/// @brief Function to find the intersection between 2 segments given their points
/// @param p1 Point 1 of Segment 1
/// @param p2 Point 2 of Segment 2
/// @param p3 Point 1 of Segment 1
/// @param p4 Point 2 of Segment 2
/// @returns a pair of a boolean and pair<float, float> to represent whether the segments intersect or not & the coordinates of the intersection point
pair<bool, pair<float, float>> intersect(Point p1, Point p2, Point p3, Point p4){
	float a1 = p2.y - p1.y;
	float b1 = p1.x - p2.x;
	float c1 = a1*(p1.x) + b1*(p1.y);
 
	// Line CD represented as a2x + b2y = c2
	float a2 = p4.y - p3.y;
	float b2 = p3.x - p4.x;
	float c2 = a2*(p3.x)+ b2*(p3.y);
 
    float determinant = a1*b2 - a2*b1;
 
    if (determinant == 0)           //The lines are parallel
        return make_pair(false, make_pair(FLT_MAX, FLT_MAX));
    else{
        float x = (b2*c1 - b1*c2) / determinant;      // x intersection point
        float y = (a1*c2 - a2*c1) / determinant;      // y intersection point
 
        // check if (x, y) lies on both the lines
        if( (min(p1.x, p2.x) <= x && x <= max (p1.x, p2.x)) &&
            (min(p1.y, p2.y) <= y && y <= max (p1.y, p2.y)) && 
            (min(p3.x, p4.x) <= x && x <= max (p3.x, p4.x)) && 
            (min(p3.y, p4.y) <= y && y <= max (p3.y, p4.y))
            ) {
                return make_pair(true, make_pair(x, y));
        }
        else {
            return make_pair(false, make_pair(FLT_MAX, FLT_MAX));
        }
    }
}

/// @brief Function to find a new event as an intersection of 2 neighbouring segments
/// @param s_l Left Segment
/// @param s_r Right Segment
/// @param p Point p
void findNewEvent(Segment s_l, Segment s_r, Point p) {
    pair<bool, pair<float, float>> ans = intersect(s_l.st, s_l.en, s_r.st, s_r.en);
    bool hasIntersection = ans.first;
    pair<float, float> coor = ans.second;
    if(hasIntersection && (coor.second < p.y || (coor.second == p.y && coor.first > p.x))) {
        Point intersection_point(coor.first, coor.second);
        // cout << "\nintersection_point\t" << intersection_point;
        // cout << "\nSegments\t" << s_l << "\t" << s_r << "\n";
        // cout << "\n***Print Event Queue before Intersection***\n";
        // event_queue.print();
        // cout << "\n***Finished Print Event Queue before Intersection***\n";
        event_queue.insert(intersection_point, s_l);
        event_queue.insert(intersection_point, s_r);
    }
}

/// @brief Function to find the left most segment in a line vector
/// @param lineSet a vector<Segment> to represent a set of lines
/// @returns pair<bool, Segment> a pair of a boolean and a Segment: to represent whether a leftmost segment exists or not & the Segment itself
pair<bool,Segment> findLeftMostSeg(vector<Segment> lineSet) {
    // left most segment is the segment with min x coordinate for a particular y
    float min_x = FLT_MAX;
    int mn = -1;

    for(int i = 0; i < lineSet.size(); i++) {
        float x = lineSet[i].x(Segment::sweeplineY);
        if(x < min_x) {
            min_x = x;
            mn = i;
        }
    }
    if(mn == -1) {
        return make_pair(false, lineSet[0]);
    }

    return make_pair(true, lineSet[mn]);
}

/// @brief Function to find the right most segment in a line vector
/// @param lineSet a vector<Segment> to represent a set of lines
/// @returns pair<bool, Segment> a pair of a boolean and a Segment: to represent whether a rightmost segment exists or not & the Segment itself
pair<bool,Segment> findRightMostSeg(vector<Segment> lineSet) {
    // right most segment is the segment with max x coordinate for a particular y
    float max_x = FLT_MIN;
    int mx = -1;

    for(int i = 0; i < lineSet.size(); i++) {
        float x = lineSet[i].x(Segment::sweeplineY);
        if(x > max_x) {
            max_x = x;
            mx = i;
        }
    }

    if(mx == -1) {
        return make_pair(false, lineSet[0]);
    }

    return make_pair(true, lineSet[mx]);
}

/// @brief Function to find the union of 2 line sets (represented as vectors)
/// @param lineSet1 a set of line segments
/// @param lineSet2 a set of line segments
/// @returns a vector of Segments, the union of the 2 sets
vector<Segment> unionOf(vector<Segment> lineSet1, vector<Segment> lineSet2) {
    vector<Segment> unionSet(lineSet1);

    for(int i = 0; i < lineSet2.size(); i++) {
        bool found = true;
        for(int j = 0; j < lineSet1.size(); j++) {
            if(lineSet1[j] == lineSet2[i]) {
                found = false;
                break;
            }
        }

        if(found) {
            unionSet.push_back(lineSet2[i]);
        }
    }

    return unionSet;
}

/// @brief Function to handle an event point
/// @param e The event point which needs to be handled
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
        // cout << "UC set size is 0";
        pair<bool, vector<Segment>> neighbours = status_queue.neighbours(p);

        if(neighbours.first) {
            vector<Segment> neighbourList = neighbours.second;
            // cout << "\n** ** ** ** ** **\n";
            // cout << neighbourList[0] << "\t" << neighbourList[1];
            // cout << "\n** ** ** ** ** **\n";

            findNewEvent(neighbourList[0], neighbourList[1], p);
        }

    } else {
        pair<bool,Segment> leftMost = findLeftMostSeg(UCset);
        Segment leftMostSeg = leftMost.second;
        if(leftMost.first) {
            pair<bool,Segment> p_l = status_queue.leftNeighbour(leftMostSeg);
            Segment s_l = p_l.second;
            if(p_l.first) {
                // cout << "S_l" << s_l;
                findNewEvent(s_l, leftMostSeg, p);
            }
        }

        pair<bool,Segment> rightMost = findRightMostSeg(UCset);
        Segment rightMostSeg = rightMost.second;
        if(rightMost.first) {
            pair<bool,Segment> p_r = status_queue.rightNeighbour(rightMostSeg);
            Segment s_r = p_r.second;
            if(p_r.first) {
                // cout << "S_r" << s_r;
                findNewEvent(s_r, rightMostSeg, p);
            }
        }
    }
}

/// @brief Function to find intersections
/// @param event_q The event queue containing all the endpoints of all the segments
void findIntersections(EventQueue &event_q) {
    // cout << "Inside findIntersections...\n";
    while(!event_q.empty()) {
        // cout << "***Printing Event Queue***" << endl;
        // event_q.print();
        // cout << "***Printing Event Queue***" << endl;
        Event nextEvent = event_q.next();
        // cout << "Event handle...\t" << nextEvent << "\n";
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
    // cout << "\n***Printing Event Queue...\n";
    // event_queue.print();
    // cout << "***Finished Printing Event Queue...\n";
    findIntersections(event_queue);
    printIntersections(intersections);
    return 0;
}