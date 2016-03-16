#include "healthPack.h"

healthPack::healthPack()
{
    //ctor
}

healthPack::~healthPack()
{
    //dtor
}

void healthPack::loadContent(sf::Vector2f position)
{
    texture.loadFromFile("Sprites/Collectable/healthpack.png");
    collectable::loadContent(position);
}

void healthPack::draw(sf::RenderWindow &Window)
{
    collectable::draw(Window);
}
