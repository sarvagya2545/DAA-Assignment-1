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

    friend ostream &operator<<(ostream &output, const Point &P) {
        output << "Point: (" << P.x << ", " << P.y << ")";
        return output;
    }
};