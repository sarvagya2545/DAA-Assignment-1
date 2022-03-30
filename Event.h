#include <iostream>

using namespace std;

/// @brief Implementation of Event class
class Event {
    public:
    
    float x; //!< x coordinate
    float y; //!< y coordinate
    vector<vector<Segment>> segments = vector<vector<Segment>> (3, vector<Segment>(0)); //!< list of segments passing through the point 

    /// @brief Constructor function for the event
    /// @param _x floating point value for the x coordinate
    /// @param _y floating point value for the y coordinate
    Event(float _x, float _y) {
        this->x = _x;
        this->y = _y;
    }

    /// @brief Constructor function for the event
    /// @param _x floating point value for the x coordinate
    /// @param _y floating point value for the y coordinate
    /// @param s Segment which passes through the coordinate
    /// @param t enum value for relationship between point and segment
    Event(float _x, float _y, Segment s, point_seg_rel t) {
        this->x = _x;
        this->y = _y;
        this->segments[t].push_back(s);
    }

    /// @brief Function which inserts the segment into the segment list
    /// @param s Segment which passes through the coordinate
    /// @param t enum value for relationship between point and segment
    void insertSegment(Segment s, point_seg_rel t) {
        segments[t].push_back(s);
    }

    /// @brief overloaded function for < for comparing events in the AVL tree
    bool operator <(const Event& e) {
        return this->y > e.y || (this->y == e.y && this->x < e.x);
    }

    /// @brief overloaded function for > for comparing events in the AVL tree
    bool operator >(const Event& e) {
        return this->y < e.y || (this->y == e.y && this->x > e.x);
    }

    /// @brief overloaded function for == for comparing events in the AVL tree
    bool operator ==(const Event& e) {
        return this->y == e.y && this->x == e.x;
    }

    /// @brief overloaded print operator for debugging
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