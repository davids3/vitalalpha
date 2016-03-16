#include "creditScreen.h"

creditScreen::creditScreen()
{
    //ctor
}

creditScreen::~creditScreen()
{
    //dtor
}

void creditScreen::loadContent()
{
    //adds keys for changing back to titleScreen
    keys.push_back(sf::Keyboard::Space);
    keys.push_back(sf::Keyboard::Return);
    keys.push_back(sf::Keyboard::Escape);

    texture.loadFromFile("Load/credits.png");
    sprite.setTexture(texture);
    sprite.setPosition(0,0);
}

void creditScreen::unloadContent(sf::RenderWindow &Window)
{

}

void creditScreen::updateEvent(sf::Event Event)
{
    if(stopInput == false)
    {
        stopInput = true;
        if(input.keyPressed(keys))
            screenManager::getInstance().addScreen(new titleScreen);
        else
            stopInput = false;
    }
    input.update(Event);
}

void creditScreen::update(sf::RenderWindow &Window)
{

}

void creditScreen::draw(sf::RenderWindow &Window)
{
    Window.draw(sprite);
}
