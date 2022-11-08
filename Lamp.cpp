#include "Lamp.h"

#include <iostream>

Lamp::Lamp(int x, int y) : Object(x, y) 
{
    icon = '^';
}
    
void Lamp::update()
{    
    below->updateLight('u', 21);
    below->updateLight('d', 21);
    below->updateLight('l', 21);
    below->updateLight('r', 21);
}