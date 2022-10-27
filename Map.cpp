#include "Map.h"

Map::Map(int w, int h) : width(w), height(h)
{
    rows = new ObjectList*[height];
    columns = new ObjectList*[width];

    for (int i = 0; i < height; i++)
    {
        rows[i] = NULL;
    }

    for (int i = 0; i < width; i++)
    {
        columns[i] = NULL;
    }
}

void Map::add(Object* obj)
{
    rows[obj->getCoord(true)]->add(obj);
    columns[obj->getCoord(false)]->add(obj);
}

std::string Map::print()
{
    std::string s;

    for (int i = 0; i < height; i++)
    {
        s += rows[i]->print();
    }

    for (int j = 0; j < width; j++)
    {
        s += columns[j]->print();
    }

    return s;
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