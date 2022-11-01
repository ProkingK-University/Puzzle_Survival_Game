#include "Lamp.h"

#include <iostream>

Lamp::Lamp(int x, int y) : Object(x, y) 
{
    icon = '^';
}
    
void Lamp::update()
{    
    below->updateLight('u', 20);
    below->updateLight('d', 20);
    below->updateLight('l', 20);
    below->updateLight('r', 20);
}