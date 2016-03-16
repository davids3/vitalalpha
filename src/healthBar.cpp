#include "healthBar.h"

healthBar::healthBar()
{
    //ctor
}

healthBar::~healthBar()
{
    //dtor
}

void healthBar::loadContent()
{
    //initialises variables
    totalWidth = 300;
    totalHeight = 12;
    mainColor = sf::Color::Red;
    title = "HP";
    statusBar::loadContent();
}

void healthBar::unloadContent()
{

}

void healthBar::update(sf::RenderWindow &Window, sf::Vector2f viewPosition, int value)
{
    //sets the position of the bar
    position.x = viewPosition.x - 400 + 50;
    position.y = viewPosition.y - 300 + 10;

    statusBar::update(Window, viewPosition, value);
}

void healthBar::draw(sf::RenderWindow &Window)
{
    statusBar::draw(Window);
}
