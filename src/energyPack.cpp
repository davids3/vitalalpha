#include "energyPack.h"

energyPack::energyPack()
{
    //ctor
}

energyPack::~energyPack()
{
    //dtor
}

void energyPack::loadContent(sf::Vector2f position)
{
    texture.loadFromFile("Sprites/Collectable/energypack.png");
    collectable::loadContent(position);
}

void energyPack::draw(sf::RenderWindow &Window)
{
    collectable::draw(Window);
}
