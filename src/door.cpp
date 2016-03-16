#include "door.h"

door::door()
{
    //ctor
}

door::~door()
{
    //dtor
}

void door::loadContent(sf::Vector2f position)
{
    texture.loadFromFile("Sprites/door.png");
    collectable::loadContent(position);
}

void door::draw(sf::RenderWindow &Window)
{
    collectable::draw(Window);
}
