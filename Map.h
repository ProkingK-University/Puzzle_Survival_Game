#ifndef MAP_H
#define MAP_H

#include "ObjectList.h"
#include <string>

class Map
{
private:
    int width;
    int height;

    ObjectList* lights;

    ObjectList** rows;
    ObjectList** columns;
public:
    Map(int w, int h);

    std::string print();
    Object* getAt(int x, int y);

    void add(Object* obj);
    void addLight(Object* l);
    void resetEnvironment();
    void updateEnvironment();
    
    ~Map();
};

#endif