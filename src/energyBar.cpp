#include "energyBar.h"

energyBar::energyBar()
{
    //ctor
}

energyBar::~energyBar()
{
    //dtor
}

void energyBar::loadContent()
{
    //initialises variables
    totalWidth = 250;
    totalHeight = 10;
    mainColor = sf::Color::Blue;
    title = "EP";
    statusBar::loadContent();
}

void energyBar::unloadContent()
{

}

void energyBar::update(sf::RenderWindow &Window, sf::Vector2f viewPosition, int value)
{
    //sets the position of the bar
    position.x = viewPosition.x - 400 + 50;
    position.y = viewPosition.y - 300 + 30;

    statusBar::update(Window, viewPosition, value);
}

void energyBar::draw(sf::RenderWindow &Window)
{
    statusBar::draw(Window);
}
