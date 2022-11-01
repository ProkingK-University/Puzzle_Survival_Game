#include "Door.h"

Door::Door(int x, int y, bool open) : Object(x, y)
{
    this->open = open;

    if (open)
    {
        solid = false;
        icon = '=';
    }
    else
    {
        solid = true;
        icon = '+';
    }
}

void Door::interact()
{
    if (open)
    {
        icon = '+';
        open = false;
        solid = true;

        std::string s = "You closed the door";
        throw s;
    }
    else
    {
        icon = '=';
        open = true;
        solid = false;

        std::string s = "You opened the door";
        throw s;
    }
}

void Door::updateLight(char direction, int intensity)
{
    Object::updateLight(direction, intensity);
}

