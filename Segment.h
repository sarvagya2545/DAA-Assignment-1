#include <iostream>
#include "utils.h"
#include "Slope.h"
using namespace std;

class Point {
    public:
    float x;
    float y;

    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(float _x, float _y) {
        this->x = _x;
        this->y = _y;
    }
};

class Segment {
    public:
    Point st, en; // start and end points of the segment
    Slope slope;
    static long double sweeplineY; // Y coordinate for the sweep line

    Segment(Point p1, Point p2) {
        if(p1.y > p2.y || (p1.y == p2.y && p1.x < p2.x)) {
            this->st = p1;
            this->en = p2;
        } else {
            this->st = p2;
            this->en = p1;
        }

        this->slope.define(p1.x, p1.y, p2.x, p2.y);
    }

    Segment(float x1, float y1, float x2, float y2) {
        float lo_x, hi_x, lo_y, hi_y;

        if(y1 > y2 || (y1 == y2 && (x1 < x2))) {
            hi_x = x1;
            hi_y = y1;
            lo_x = x2;
            lo_y = y2;
        } else {
            hi_x = x2;
            hi_y = y2;
            lo_x = x1;
            lo_y = y1;
        }

        (this->st).x = hi_x;
        (this->st).y = hi_y;
        (this->en).x = lo_x;
        (this->en).y = lo_y;
        this->slope.define(x1,y1,x2,y2);
    }

    // x coordinate value at a particular y value
    float x(float y) {
        float ratio = (st.x - en.x) / (st.y - en.y);
        return st.x + ratio * (y - st.y);
    }

    int findPoint(Point p) {
        float px = x(p.y);

        if(px == p.x) {
            if(px == st.x) return upper;
            if(px == en.x) return lower;
            return on;
        } else {
            return none;
        }

    }

    bool operator < (Segment& s) {
        float this_x = this->x(sweeplineY);
        float next_x = s.x(sweeplineY);

        if(this_x == next_x) {
            return this->slope < s.slope;
        }

        return this_x < next_x;
    }

    bool operator > (Segment& s) {
        float this_x = this->x(sweeplineY);
        float next_x = s.x(sweeplineY);

        if(this_x == next_x) {
            return this->slope > s.slope;
        }

        return this_x > next_x;
    }
};

// long double Segment::sweeplineY = 3.0;

// int main() {
//     Segment s1(0,1,4,5), s2(0,5,4,1);
//     cout << "Slope of s1 is " << s1.slope.m << " and of s2 is " << s2.slope.m << "\n";

//     if(s1 < s2) {
//         cout << "S1 is lower";
//     } else if(s1 > s2) {
//         cout << "S2 is lower";
//     }
// }