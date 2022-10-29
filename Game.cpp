#include "Game.h"

Game::Game(int w, int h, std::string chars)
{
    int k = 0;
    player = NULL;

    map = new Map(w, h);

    for (int i = 0; i < h; i++)
    {        
        for (int j = 0; j < w; j++)
        {
            Object* obj;

            if (chars[k] == '.' || chars[k] == '#' || chars[k] == '&' || chars[k] == '?')
            {
                
                if (chars[k] == '.')
                {
                    obj = new Floor(j, i);
                }
                else if(chars[k] == '#')
                {
                    obj = new Wall(j, i);
                }
                else if(chars[k] == '&')
                {
                    obj = new Floor(j, i);
                    player = new Player(j, i);

                    obj->above = player;
                    player->below = obj;
                }
                else if(chars[k] == '?')
                {
                    obj = new Object(j, i);
                }

                map->add(obj);
            }
            
            k++;
        }
    }
}

std::string Game::display(){return map->print();}

void Game::update(char input)
{    
    if (player)
    {
        if (input == '1')
        {
            player->move(-1, 1);
        }
        else if (input == '2')
        {
            player->move(0, 1);
        }
        else if (input == '3')
        {
            player->move(1, 1);
        }
        else if (input == '4')
        {
            player->move(-1, 0);
        }
        else if (input == '6')
        {
            player->move(1, 0);
        }
        else if (input == '7')
        {
            player->move(-1, -1);
        }
        else if (input == '8')
        {
            player->move(0, -1);
        }
        else if (input == '9')
        {
            player->move(1, -1);
        }
    }
}

Game::~Game()
{
    delete map;
    delete player;
}