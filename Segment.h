#include <iostream>
#include "Slope.h"
#include "Point.h"
using namespace std;

class Segment {
    public:
    Point st, en; // start and end points of the segment
    Slope slope;
    static long double sweeplineY; // Y coordinate for the sweep line

    Segment() {

    }

    Segment(Point p1, Point p2) {
        insert(p1.x,p1.y,p2.x,p2.y);
    }

    Segment(float x1, float y1, float x2, float y2) {
        insert(x1,y1,x2,y2);
    }

    void insert(float x1, float y1, float x2, float y2) {
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

        // cout << "hi_x: " << hi_x << " lo_x: " << lo_x << " hi_y: " << hi_y << " lo_y: " << lo_y;

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

    point_seg_rel findPoint(Point p) {
        float px = x(p.y);

        if(px == p.x) {
            if(px == st.x) return U;
            if(px == en.x) return L;
            return C;
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

    bool operator == (Segment& s) {
        return this->st == s.st && this->en == s.en; 
    }

    friend ostream &operator<<(ostream &output, const Segment &S) { 
        output << "endpoints: (" << S.st.x << ", " << S.st.y << ")," << "(" << S.en.x << ", " << S.en.y << ")";
        return output;
    }
};

long double Segment::sweeplineY = 0.0;

void changeY(long double Y) {
    Segment::sweeplineY = Y;
}