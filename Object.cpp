#include "Object.h"

Object::Object(int x, int y) : xPos(x), yPos(y)
{
    icon = '?';

    nextHoriz = NULL;
    prevHoriz = NULL;

    nextVert = NULL;
    prevVert = NULL;

    above = NULL;
    below = NULL;
}

char Object::getIcon()
{
    if (above)
        return above->getIcon();
    else
        return icon;
}

int Object::getCoord(bool dimension)
{
    if (dimension)
        return yPos;
    else
        return xPos;
}

Object* Object::getNext(bool dimension)
{
    if (dimension)
        return nextVert;
    else
        return nextHoriz;
}

Object* Object::getPrev(bool dimension)
{
    if (dimension)
        return prevVert;
    else
        return prevHoriz;
}

void Object::setNext(Object* obj, bool dim)
{
    if (obj)
    {
        if (dim)
            nextVert = obj;
        else
            nextHoriz = obj;
    }
}

void Object::setPrev(Object* obj, bool dim)
{
    if (obj)
    {
    if (dim)
        prevVert = obj;
    else
        prevHoriz = obj;
    }
}