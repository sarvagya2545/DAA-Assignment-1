#include <iostream>
using namespace std;

enum slope_t { undefined, rational , inf };

class Slope {
    public:
    slope_t t; // type of slope
    double m;
    Slope() {
        slope_t t = undefined;
    };

    Slope(float x0, float y0, float x1, float y1) {
        t = undefined;
        define(x0,y0,x1,y1);
    };

    void define(float x0, float y0, float x1, float y1) {
        if(t == undefined) {
            if(x0 == x1) {
                t = inf;
            } else {
                t = rational;
                m = (y1 - y0) / (x1 - x0);
            }
        } else {
            cout << "Slope already has been defined for this instance. The slope is: " << this->m;
        }
    };

    bool operator > (const Slope& s) {
        if(this->t == inf) {
            return s.t != inf && s.m > 0;
        }

        if(s.t == inf) {
            return this->m < 0;
        }

        bool s_pos = s.m > 0;
        bool this_pos = this->m > 0;

        if(s_pos == this_pos) {
            return this->m > s.m;
        } else {
            return s_pos;
        }
    }

    bool operator < (const Slope& s) {
        if(this->t == inf) {
            return s.t != inf && s.m < 0;
        }

        if(s.t == inf) {
            return this->m > 0;
        }

        bool s_pos = s.m > 0;
        bool this_pos = this->m > 0;

        if(s_pos == this_pos) {
            return this->m < s.m;
        } else {
            return this_pos;
        }
    }
};