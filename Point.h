using namespace std;

/// Class representation of a point
class Point {
    public:
    float x; //!< x coordinate of the point
    float y; //!< y coordinate of the point

    /// constructor to initialise the point
    Point() {
        this->x = 0;
        this->y = 0;
    }

    /// constructor to initialise the point
    /// @param _x x coordinate of the point
    /// @param _y y coordinate of the point
    Point(float _x, float _y) {
        this->x = _x;
        this->y = _y;
    }

    /// Operator overloading to overload the == operator
    bool operator == (Point& p) {
        return this->x == p.x && this->y == p.y;
    }

    /// Operator overloading to overload the ostream << operator
    friend ostream &operator<<(ostream &output, const Point &P) {
        output << "Point: (" << P.x << ", " << P.y << ")";
        return output;
    }
};