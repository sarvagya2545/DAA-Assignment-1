#include <bits/stdc++.h>
#include "utils.h"
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

    Segment(Point p1, Point p2) {
        if(p1.y > p2.y || (p1.y == p2.y && p1.x < p2.x)) {
            this->st = p1;
            this->en = p2;
        } else {
            this->st = p2;
            this->en = p1;
        }
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

    bool operator < (const Segment& s) {
        
    }
};