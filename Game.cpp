#include "Game.h"

#include <iostream>

Game::Game(int w, int h, std::string chars)
{
    int k = 0;

    exit = NULL;
    player = NULL;

    messages = new MessageQueue(4);

    map = new Map(w, h);

    for (int i = 0; i < h; i++)
    {        
        for (int j = 0; j < w; j++)
        {
            Object* obj;

            if (chars[k] == '.' || chars[k] == '#' || chars[k] == '&' || chars[k] == '?' || 
                chars[k] == '@' || chars[k] == '=' || chars[k] == '+' || chars[k] == '^')
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
                else if(chars[k] == '@')
                {
                    exit = new Exit(j, i);
                    obj = exit;
                }
                else if(chars[k] == '^')
                {
                    Lamp* l = new Lamp(j, i);
                    obj = new Floor(j, i);
                    
                    l->below = obj;
                    obj->above = l;

                    map->addLight(l);
                }
                else if(chars[k] == '=')
                {
                    obj = new Door(j, i, true);
                }
                else if(chars[k] == '+')
                {
                    obj = new Door(j, i, false);
                }

                map->add(obj);
            }
            
            k++;
        }
    }

    map->resetEnvironment();
    map->updateEnvironment();
}

std::string Game::display()
{
    std::string s = "";

    s += messages->print();
    s += map->print();

    return s;
}

void Game::update(char input)
{        
    if (!player)
    {
        messages->addMessage(new Message("Missing player"));

        map->updateEnvironment();
    }
    else if (player)
    {
        int x = 0;
        int y = 0;
        
        Object* check = player->below;

        while (check->below)
        {
            check = check->below;
        }
        
        if (input == '1')
        {
            x = -1;
            y = 1;

            check = check->prevHoriz;
            check = check->nextVert;
        }
        else if (input == '2')
        {
            y = 1;

            check = check->nextVert;
        }
        else if (input == '3')
        {
            x = 1;
            y = 1;

            check = check->nextHoriz;
            check = check->nextVert;
        }
        else if (input == '4')
        {
            x = -1;

            check = check->prevHoriz;
        }
        else if (input == '6')
        {
            x = 1;

            check = check->nextHoriz;
        }
        else if (input == '7')
        {
            x = -1;
            y = -1;

            check = check->prevHoriz;
            check = check->prevVert;
        }
        else if (input == '8')
        {
            y = -1;

            check = check->prevVert;
        }
        else if (input == '9')
        {
            x = 1;
            y = -1;

            check = check->nextHoriz;
            check = check->prevVert;
        }
        else if (input == 'e')
        {
            Object* nodePtr = player->below;

            while (nodePtr->below)
            {
                nodePtr = nodePtr->below;
            }

            //Check for NULL
            
            playerInteract(nodePtr->above);
            playerInteract(nodePtr->below);

            playerInteract(nodePtr->nextVert);
            playerInteract(nodePtr->prevVert);

            playerInteract(nodePtr->nextHoriz);
            playerInteract(nodePtr->prevHoriz);
        }
        
        //check->move(x, y);

        if (check->isSolid())
        {
            messages->addMessage(new Message("Walked into something"));
        }
        else if(!check)
        {
            messages->addMessage(new Message("Out of bounds"));
        }
        else
        {
            player->move(x, y);
        }

        map->resetEnvironment();
        map->updateEnvironment();

        if (player->below == exit)
        {
            std::string s = "You reached the exit";

            throw s;
        }
    }
}

void Game::playerInteract(Object* obj)
{
    if (obj)
    {
        try
        {
            obj->interact();
        }
        catch(std::string s)
        {
            messages->addMessage(new Message(s));
        }
    }
}

Game::~Game()
{
    delete map;
    delete player;
}