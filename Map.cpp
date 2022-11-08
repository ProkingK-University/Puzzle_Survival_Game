#include "Map.h"
#include <iostream>

Map::Map(int w, int h) : width(w), height(h)
{
    lights = new ObjectList(false);
    
    rows = new ObjectList*[height];
    columns = new ObjectList*[width];

    for (int i = 0; i < height; i++)
    {
        rows[i] = new ObjectList(false);
    }

    for (int i = 0; i < width; i++)
    {
        columns[i] = new ObjectList(true);
    }
}

void Map::add(Object* obj)
{
    if (obj)
    {
        rows[obj->getCoord(true)]->add(obj);
        columns[obj->getCoord(false)]->add(obj);
    }
}

std::string Map::print()
{
    std::string s = "";

    for (int i = 0; i < height; i++)
    {
        s += rows[i]->print() + '\n';
    }

    return s;
}

Object* Map::getAt(int x, int y)
{
    Object* nodePtr = rows[y]->getHead();

    for (int i = 0; i < x; i++)
    {
        if (nodePtr)
            nodePtr = nodePtr->getNext(false);
    }

    if(nodePtr == rows[y]->getHead() && x != 0)
        return NULL;
    else
        return nodePtr;
}

void Map::addLight(Object* light)
{
    if (light)
    {
        lights->add(light);
    }
}

void Map::resetEnvironment()
{
    for (int i = 0; i < height; i++)
    {
        Object* nodePtr = rows[i]->getHead();
        
        while (nodePtr)
        {
            nodePtr->update();
            
            nodePtr = nodePtr->nextHoriz;
        }
    }
}

void Map::updateEnvironment()
{
    Object* nodePtr = lights->getHead();

    while (nodePtr)
    {
        nodePtr->update();

        nodePtr = nodePtr->nextHoriz;
    }
}

Map::~Map()
{
    for (int i = 0; i < height; i++)
    {
        Object* nextPtr = NULL;
        Object* nodePtr = rows[i]->getHead();

        while (nodePtr)
        {
            nextPtr = nodePtr->getNext(false);
            delete nodePtr;
            nodePtr = nextPtr;
        }

        rows[i] = NULL;
    }

    rows = NULL;
}