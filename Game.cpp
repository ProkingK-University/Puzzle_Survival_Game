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
                    obj = new Exit(j, i);
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
                    obj = new Door(j, i, false);
                }
                else if(chars[k] == '+')
                {
                    obj = new Door(j, i, true);
                }

                map->add(obj);
            }
            
            k++;
        }
    }

    //map->resetEnvironment();
    //map->updateEnvironment();
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
    Message* m = NULL;
    
    if (!player)
    {
        m = new Message("Missing player");

        messages->addMessage(m);

        map->updateEnvironment();
    }
    else if (player)
    {
        int x = 0;
        int y = 0;
        
        Player* check = player;

        if (input == '1')
        {
            x = -1;
            y = 1;
        }
        else if (input == '2')
        {
            y = 1;
        }
        else if (input == '3')
        {
            x = 1;
            y = 1;
        }
        else if (input == '4')
        {
            x = -1;
        }
        else if (input == '6')
        {
            x = 1;
        }
        else if (input == '7')
        {
            x = -1;
            y = -1;
        }
        else if (input == '8')
        {
            y = -1;
        }
        else if (input == '9')
        {
            x = 1;
            y = -1;
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
            playerInteract(nodePtr->nextVert);

            playerInteract(nodePtr->nextHoriz);
            playerInteract(nodePtr->prevHoriz);
        }
        
        check->move(x, y);

        if (check->below->isSolid())
        {
            m = new Message("Walked into something");

            messages->addMessage(m);
        }
        else if(!check->below)
        {
            m = new Message("Out of bounds");

            messages->addMessage(m);
        }
        else
        {
            player->move(x, y);
            std::cout<< "Moved" <<std::endl;
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
        Object* top = obj->above->above;
        
        try
        {
            if (top)
            {
                top->interact();  
            }
        }
        catch(std::string s)
        {
            Message* m = new Message(s);

            messages->addMessage(m);
        }
    }
}

Game::~Game()
{
    delete map;
    delete player;
}