#include <bits/stdc++.h>
// #include "Segment.h"

using namespace std;

class Event {
    public:
    float x;
    float y;
    // Segment s;
    vector<vector<Segment>> segments = vector<vector<Segment>> (3, vector<Segment>(0)); // index 0 = U, 1 = L, 2 = C 

    Event(float _x, float _y) {
        this->x = _x;
        this->y = _y;
    }

    Event(float _x, float _y, Segment s, point_seg_rel t) {
        this->x = _x;
        this->y = _y;
        this->segments[t].push_back(s);
    }

    void insertSegment(Segment s, point_seg_rel t) {
        segments[t].push_back(s);
    }

    bool operator <(const Event& e) {
        return this->y > e.y || (this->y == e.y && this->x < e.x);
    }

    bool operator >(const Event& e) {
        return this->y < e.y || (this->y == e.y && this->x > e.x);
    }

    bool operator ==(const Event& e) {
        return this->y == e.y && this->x == e.x;
    }

    friend ostream &operator<<(ostream &output, const Event &E) { 
        output << "Event:\nPoint : (" << E.x << ", " << E.y << ")\n";
        for(int i = 0; i < E.segments[U].size(); i++) {
            output << "Segment U " << i << ": " << E.segments[U][i] << "\n";
        }
        for(int i = 0; i < E.segments[L].size(); i++) {
            output << "Segment L " << i << ": " << E.segments[L][i] << "\n";
        }
        for(int i = 0; i < E.segments[C].size(); i++) {
            output << "Segment C " << i << ": " << E.segments[C][i] << "\n";
        }
        return output;
    }
};