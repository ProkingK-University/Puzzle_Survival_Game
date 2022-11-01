#include "Object.h"

#include <iostream>

Object::Object(int x, int y) : xPos(x), yPos(y)
{
    icon = '?';

    lit = true;
    solid = false;

    nextHoriz = NULL;
    prevHoriz = NULL;

    nextVert = NULL;
    prevVert = NULL;

    above = NULL;
    below = NULL;
}

char Object::getIcon()
{
    if (!lit)
        return ' ';
    else if (above)
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

void Object::update()
{
    lit = false;
}

bool Object::isSolid()
{
    if (above && above->isSolid())
        return true;
    else
        return solid;
}

void Object::interact() {}

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

void Object::updateLight(char direction, int intensity)
{    
    if (intensity == 1 || solid)
    {
        lit = true;
    }
    else
    {
        lit = true;

        if (direction == 'u')
        {
            if (prevHoriz)
                prevHoriz->updateLight(direction, 1);

            if (nextHoriz)
                nextHoriz->updateLight(direction, 1);

            if (prevVert)
                prevVert->updateLight(direction, intensity-1);
        }
        else if (direction == 'd')
        {
            if (prevHoriz)
                prevHoriz->updateLight(direction, 1);

            if (nextHoriz)
                nextHoriz->updateLight(direction, 1);

            if (nextVert)
                nextVert->updateLight(direction, intensity-1);
        }
        else if (direction == 'l')
        {
            if (prevVert)
                prevVert->updateLight(direction, 1);

            if (nextVert)
                nextVert->updateLight(direction, 1);

            if (prevHoriz)
                prevHoriz->updateLight(direction, intensity-1);
        }
        else if (direction == 'r')
        {
            if (prevVert)
                prevVert->updateLight(direction, 1);

            if (nextVert)
                nextVert->updateLight(direction, 1);

            if (nextHoriz)
                nextHoriz->updateLight(direction, intensity-1);
        }
    }
}