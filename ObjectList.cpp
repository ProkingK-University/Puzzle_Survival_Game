#include "ObjectList.h"

#include <iostream>

ObjectList::ObjectList(bool dim) : dimension(dim)
{
    head = NULL;
    current = NULL;
}

void ObjectList::reset()
{
    current = head;
}

void ObjectList::add(Object* obj)
{
    if (obj)
    {
        if (!head)
        {
            head = obj;
        }
        else
        {
            Object* nodePtr = head;
            Object* prevPtr = NULL;

            while (nodePtr && nodePtr->getCoord(dimension) < obj->getCoord(dimension))
            {
                prevPtr = nodePtr;
                nodePtr = nodePtr->getNext(dimension);
            }

            if (!nodePtr)
            {
                prevPtr->setNext(obj, dimension);
                obj->setPrev(prevPtr, dimension);
            }
            else if (!prevPtr)
            {
                obj->setNext(head, dimension);
                head->setPrev(obj, dimension);
                head = obj;
            }
            else
            {
                prevPtr->setNext(obj, dimension);
                obj->setPrev(prevPtr, dimension);
                obj->setNext(nodePtr, dimension);
                nodePtr->setPrev(obj, dimension);
            }
        }
    }
}

Object* ObjectList::getHead() {return head;}

Object* ObjectList::iterate()
{
    Object* c = current;

    if (current)
        current = current->getNext(dimension);
    
    return c;
}

std::string ObjectList::print()
{
    std::string s = "";
    Object* nodePtr = head;

    while (nodePtr)
    {
        s += nodePtr->getIcon();

        nodePtr = nodePtr->getNext(dimension); 
    }

    return s;
}

std::string ObjectList::debug()
{
    std::string s = "";

    if (head)
    {
        std::string x;
        std::string y;
        std::string icon;
        std::string top = "Y";
        std::stringstream ss;

        s = "Forward\n";

        Object* nodePtr = head;

        while (nodePtr)
        {
            ss << nodePtr->getCoord(false);
            ss >> x;
            ss.clear();

            ss << nodePtr->getCoord(true);
            ss >> y;
            ss.clear();

            ss << nodePtr->getIcon();
            ss >> icon;
            ss.clear();

            if (nodePtr->above)
                top = 'N';
            
            s +=  "<" + icon + ">" + "at (" + x + ',' + y + ") Top: " + top + '\n';

            if (!nodePtr->getNext(dimension))
                break;
            else
                nodePtr = nodePtr->getNext(dimension);
        }
        
        s += "Back\n";

        while (nodePtr)
        {
            ss << nodePtr->getCoord(false);
            ss >> x;
            ss.clear();

            ss << nodePtr->getCoord(true);
            ss >> y;
            ss.clear();

            ss << nodePtr->getIcon();
            ss >> icon;
            ss.clear();
            
            if (nodePtr->above)
                top = 'N';
            
            s += "<" + icon + ">" + "at (" + x + ',' + y + ") Top: " + top + '\n';

            nodePtr = nodePtr->getPrev(dimension);
        }
    }

    return s;
}