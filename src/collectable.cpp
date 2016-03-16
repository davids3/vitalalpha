#include "collectable.h"

collectable::collectable()
{
    //ctor
}

collectable::~collectable()
{
    //dtor
}

void collectable::loadContent(sf::Vector2f position)
{
    //sets the texute, origin and position of the sprite
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x/2, texture.getSize().y));
    sprite.setPosition(position);
    this->position = position;
}

void collectable::draw(sf::RenderWindow &Window)
{
    Window.draw(sprite);
}

sf::Vector2f collectable::getPosition()
{
    return position;
}
