#ifndef GAME_H
#define GAME_H

#include <ctype.h>
#include <string>
#include <sstream>

//Part1
#include "Map.h"
#include "Player.h"
#include "Wall.h"
#include "Floor.h"


//Uncomment for Part 2
//#include "MessageQueue.h"
//#include "Door.h"
//#include "Lamp.h"
//#include "Exit.h"

class Game
{
private:
    Map* map;
    Player* player;
public:
    Game(int w, int h, std::string chars);

    std::string display();
    void update(char input);

    ~Game();
};

#endif