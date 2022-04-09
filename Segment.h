#include <iostream>
#include "Point.h"
using namespace std;

/// class representation of a segment
class Segment {
    public:
    Point st, en; //!< start and end points of the segment
    static float sweeplineY; //!< Y coordinate for the sweep line

    Segment() {

    }

    /// @brief constructor function that takes in 2 points and creates a line segment
    /// @param p1 
    /// @param p2 
    Segment(Point p1, Point p2) {
        insert(p1.x,p1.y,p2.x,p2.y);
    }

    /// @brief constructor function that takes in 2 points and creates a line segment
    /// @param x1 
    /// @param y1 
    /// @param x2 
    /// @param y2 
    Segment(float x1, float y1, float x2, float y2) {
        insert(x1,y1,x2,y2);
    }

    /// @brief function to initialise segment points
    /// @param x1
    /// @param y1 
    /// @param x2 
    /// @param y2 
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
        // this->slope.define(x1,y1,x2,y2);
    }

    /// @brief find x coordinate value at a particular y value on the segment
    /// @param y a float value for y coordinate
    /// @returns x coordinate at a particular y value on the segment
    float x(float y) {
        float ratio = (st.x - en.x) / (st.y - en.y);
        return st.x + ratio * (y - st.y);
    }


    /// @brief finds and defines the point and segment relationship: whether the point lies in between, does not lie, lies on the start endpoint / ending endpoint
    /// @param p Point p 
    /// @returns an enum point_seg_rel which tells whether the point passes lies in between, does not lie, lies on the start endpoint / ending endpoint
    point_seg_rel findPoint(Point p) {

        if(st.y == en.y) {
            if(p.x == st.x) return U;
            if(p.x == en.x) return L;
            return C;
        }

        float px = x(p.y);

        if(px == p.x) {
            if(px == st.x) return U;
            if(px == en.x) return L;
            return C;
        } else {
            return none;
        }

    }

    /// @brief Operator overloaded for comparison between segments
    /// @param s Segment s 
    /// @returns bool 
    bool operator < (Segment& s) {
        float this_x = this->st.y != this->en.y ? this->x(sweeplineY) : (this->st.x);
        float next_x = s.st.y != s.en.y ? s.x(sweeplineY) : s.st.x;

        // if(this_x == next_x) {
        //     return this->slope < s.slope;
        // }

        return this_x < next_x;
    }

    /// @brief Operator overloaded for comparison between segments
    /// @param s Segment s 
    /// @returns bool 
    bool operator > (Segment& s) {
        float this_x = this->st.y != this->en.y ? this->x(sweeplineY) : this->st.x;
        float next_x = s.st.y != s.en.y ? s.x(sweeplineY) : s.st.x;

        // if(this_x == next_x) {
        //     return this->slope > s.slope;
        // }

        return this_x > next_x;
    }

    /// @brief Operator overloaded for comparison between segments
    /// @param s Segment s 
    /// @returns bool 
    bool operator == (Segment& s) {
        return this->st == s.st && this->en == s.en; 
    }

    /// @brief Operator overloaded for output
    /// @param output ostream 
    /// @param s Segment s 
    /// @returns ostream object
    friend ostream &operator<<(ostream &output, const Segment &S) { 
        output << "endpoints: (" << S.st.x << ", " << S.st.y << ")," << "(" << S.en.x << ", " << S.en.y << ")";
        return output;
    }
};

float Segment::sweeplineY = 0.0;

void changeY(float Y) {
    Segment::sweeplineY = Y;
}