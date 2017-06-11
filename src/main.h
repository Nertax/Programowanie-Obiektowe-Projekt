
#ifndef OTHERS
#define OTHERS

struct Position {
    float x;
    float y;
};

struct ActiveDirection {
    bool up;
    bool left;
    bool right;
    bool down;
};

class Object {

protected:
    Position objectPosition;

public:
    Position getObjectPosition() { return this->objectPosition; }
    void setObjectPosition(float newXPosition, float newYPosition) { this->objectPosition.x = newXPosition; this->objectPosition.y = newYPosition; }
 
};


#endif
