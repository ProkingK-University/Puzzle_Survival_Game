#include "Player.h"

Player::Player(int x, int y) : Object(x, y) {icon = '&';}

void Player::move(int x, int y)
{
    if ((x==-1 || x==0 || x==1) && (y==-1 || y==0 || y==1))
    {
        Object* xFloor = below;
        Object* yFloor = below;

        xFloor->above = NULL;
        yFloor->above = NULL;

        while (xFloor->below)
            xFloor = xFloor->below;

        if (x == 1)
            xFloor = xFloor->nextHoriz;
        else if (x == -1)
            xFloor = xFloor->prevHoriz;

        if (y == 1)
            yFloor = yFloor->nextVert;
        else if (y == -1)
            yFloor = yFloor->prevVert;
        
        while (yFloor->above)
            yFloor = yFloor->above;

        yFloor->above = this;
        
        xPos += x;
        yPos += y;
    }
}