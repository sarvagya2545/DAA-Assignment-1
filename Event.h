#include <bits/stdc++.h>
#include "Segment.h"
#include "utils.h"
using namespace std;

class Event {
    public:
    float x;
    float y;
    // Segment s;
    vector<pair<Segment, int>> segments;

    Event(float _x, float _y) {
        this->x = _x;
        this->y = _y;
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
};

int main() {
    Event *e1 = new Event(1,1);
    Event *e2 = new Event(1,1);

    if(*e1 > *e2) {
        cout << "e1 > e2";
    } else if(*e2 > *e1) {
        cout << "e2 > e1";
    } else {
        cout << "e2 == e1";
    }
}