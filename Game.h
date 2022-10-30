#ifndef GAME_H
#define GAME_H

#include <ctype.h>
#include <string>
#include <sstream>

#include "Map.h"
#include "Player.h"
#include "Wall.h"
#include "Floor.h"
#include "MessageQueue.h"
#include "Door.h"
#include "Lamp.h"
#include "Exit.h"

class Game
{
private:
    Map* map;
    Exit* exit;
    Player* player;
    MessageQueue* messages;
public:
    Game(int w, int h, std::string chars);

    std::string display();

    void update(char input);
    void playerInteract(Object* obj);

    ~Game();
};

#endif