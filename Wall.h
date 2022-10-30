#ifndef WALL_H
#define WALL_H

#include "Object.h"

class Wall : public Object
{
public:
    Wall(int  x, int);

    void updateLight(char direction, int intensity);
};

#endif