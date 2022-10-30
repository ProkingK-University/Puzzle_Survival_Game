#ifndef DOOR_H
#define DOOR_H

#include "Object.h"
#include <string>

class Door : public Object
{
private:
    bool open;
public:
    Door(int x, int y, bool open);

    bool unlock();

    void interact();
    void updateLight(char direction, int intensity);
};

#endif