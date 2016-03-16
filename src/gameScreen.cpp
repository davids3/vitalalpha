#include "gameScreen.h"

gameScreen::gameScreen()
{
    stopInput = false;
}

gameScreen::~gameScreen()
{
    //dtor
}

void gameScreen::loadContent()
{

}

void gameScreen::unloadContent(sf::RenderWindow &Window)
{
    //clears each vector to assure no memory leaks
    keys.clear();
    attributes.clear();
    contents.clear();
}

void gameScreen::updateEvent(sf::Event Event)
{

}

void gameScreen::update(sf::RenderWindow &Window)
{

}

void gameScreen::draw(sf::RenderWindow &Window)
{

}
