#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "Object.h"
#include <string>

class ObjectList
{
private:
    Object* head;
    Object* current;

    bool dimension;
public:
    ObjectList(bool dim);

    void reset();
    void add(Object* obj);

    Object* getHead();
    Object* iterate();

    std::string print();
    std::string debug();
};

#endif