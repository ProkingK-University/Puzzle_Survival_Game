#include "ObjectList.h"

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
    if (!head)
    {
        head = obj;
    }
    else
    {
        Object* nodePtr = head;

        while (nodePtr && nodePtr->getCoord(dimension) <= obj->getCoord(dimension))
        {
            nodePtr = nodePtr->getNext(dimension);
        }

        if (!nodePtr->getPrev(dimension))
        {
            obj->setNext(nodePtr, dimension);
            nodePtr->setPrev(obj, dimension);
            head = obj;
        }
        else if(!nodePtr->getNext(dimension))
        {
            nodePtr->setNext(obj, dimension);
            obj->setPrev(nodePtr, dimension);
        }
        else
        {
            nodePtr->getPrev(dimension)->setNext(obj, dimension);
            obj->setPrev(nodePtr->getPrev(dimension), dimension);
            obj->setNext(nodePtr, dimension);
            nodePtr->setPrev(obj, dimension);
        }
    }
}

Object* ObjectList::getHead() {return head;}

Object* ObjectList::iterate()
{
    current = current->getNext(dimension);

    return current;
}

std::string ObjectList::print()
{
    std::string s;
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
        Object* nodePtr = head;

        char x;
        char y;

        std::string top = "Y";
        std::string icon = ""+nodePtr->getIcon();

        s = "Forward\n";

        while (nodePtr)
        {
            x = (int) nodePtr->getCoord(false);
            y = (int) nodePtr->getCoord(true);
            
            if (nodePtr->above)
                top = 'N';
            
            s += icon + "at (" + x + ',' + y + ") Top: " + top + '\n';

            if (nodePtr->getNext(dimension))
                nodePtr = nodePtr->getNext(dimension);
        }
        
        s += "Back\n";
        
        while (nodePtr)
        {
            x = (int) nodePtr->getCoord(false);
            y = (int) nodePtr->getCoord(true);
            
            if (nodePtr->above)
                top = 'N';
            
            s += icon + "at (" + x + ',' + y + ") Top: " + top + '\n';

            nodePtr = nodePtr->getPrev(dimension);
        }
    }

    return s;
}