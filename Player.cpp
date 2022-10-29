#include "Player.h"

Player::Player(int x, int y) : Object(x, y) {icon = '&';}

void Player::move(int x, int y)
{
    if ((x==-1 || x==0 || x==1) && (y==-1 || y==0 || y==1))
    {
        Object* oldPos = below;
        Object* newPos = oldPos;

        while (oldPos->below)
            oldPos = oldPos->below;
        
        if (newPos)
        {
            if (x == 1)
                newPos = newPos->nextHoriz;
            else if (x == -1)
                newPos = newPos->prevHoriz;

            if (y == 1)
                newPos = newPos->nextVert;
            else if (y == -1)
                newPos = newPos->prevVert;
            
            oldPos->above = NULL;
            newPos->above = this;
            this->below = newPos;
            
            xPos += x;
            yPos += y;
        }
    }
}