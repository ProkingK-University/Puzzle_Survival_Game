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
        int k = 0;
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
    Object* head = NULL;
    Object* nodePtr = NULL;
    
    for (int i = 0; i < height; i++)
    {
        if (rows[i]->getHead())
        {
            head = rows[i]->getHead();
            nodePtr = rows[i]->getHead();

            while (nodePtr)
            {
                head = head->getNext(true);
                delete nodePtr;
                nodePtr = head;
            }

            rows = NULL;
        }
    }

    for (int i = 0; i < width; i++)
    {
        if (columns[i]->getHead())
        {
            head = columns[i]->getHead();
            nodePtr = columns[i]->getHead();

            while (nodePtr)
            {
                head = head->getNext(true);
                delete nodePtr;
                nodePtr = head;
            }

            columns = NULL;
        }
    }

    delete head;
}