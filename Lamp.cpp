#include "Lamp.h"

Lamp::Lamp(int x, int y) : Object(x, y) 
{
    icon = '^';
}
    
void Lamp::update()
{
    updateLight('u', 20);
    updateLight('d', 20);
    updateLight('l', 20);
    updateLight('r', 20);
}