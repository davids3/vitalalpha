#include "inputManager.h"

inputManager::inputManager()
{
    //ctor
}

inputManager::~inputManager()
{
    //dtor
}

void inputManager::update(sf::Event event)
{
    //makes a local copy of the event
    this->event = event;
}

bool inputManager::keyPressed(int key)
{
    if(event.key.code == key && event.type == sf::Event::KeyPressed)
        return true;
    return false;
}

bool inputManager::keyPressed(std::vector<int> keys)
{
    for(int i = 0; i <keys.size(); i++)
    {
        if(keyPressed(keys[i]))
            return true;
    }
    return false;
}

bool inputManager::keyReleased(int key)
{
    if(event.key.code == key && event.type == sf::Event::KeyReleased)
        return true;
    return false;
}

bool inputManager::keyReleased(std::vector<int> keys)
{
    for(int i = 0; i <keys.size(); i++)
    {
        if(keyReleased(keys[i]))
            return true;
    }
    return false;
}

bool inputManager::keyDown(sf::Keyboard::Key key)
{
    if(sf::Keyboard::isKeyPressed((key)))
        return true;
    return false;
}

bool inputManager::keyDown(std::vector<sf::Keyboard::Key> keys)
{
    for(int i = 0; i < keys.size(); i++)
    {
        if(sf::Keyboard::isKeyPressed((keys[i])))
            return true;
    }
    return false;
}
