#ifndef OBJECT_H
#define OBJECT_H

#include <sstream>

class Object
{
protected:
    char icon;

    int xPos;
    int yPos;

    bool lit;
    bool solid;
public:
    Object* nextHoriz;
    Object* prevHoriz;

    Object* nextVert;
    Object* prevVert;

    Object* above;
    Object* below;
    
    Object(int x, int y);

    char getIcon();

    bool isSolid();

    int getCoord(bool dimension);

    Object* getNext(bool dimension);
    Object* getPrev(bool dimension);

    virtual void update();
    virtual void interact();
    void setNext(Object* obj, bool dim);
    void setPrev(Object* obj, bool dim);
    virtual void updateLight(char direction, int intensity);
};

#endif