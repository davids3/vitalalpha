#include "bullet.h"

enum direction { LEFT, RIGHT };

bullet::bullet()
{
    //ctor
}

bullet::~bullet()
{
    //dtor
}

void bullet::loadContent(sf::Vector2f position, int direction)
{
    //loads the texure and sets it
    texture.loadFromFile("Sprites/Turret/bullet.png");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);

    //flips image if bullet direction is left
    if(direction == LEFT)
        sprite.setTextureRect(sf::IntRect(texture.getSize().x, 0, -texture.getSize().x, texture.getSize().y));

    //creates a local copy of the position and direction
    this->position = position;
    this->direction = direction;

    moveSpeed = 5;
}

void bullet::unloadContent()
{

}

void bullet::update(sf::RenderWindow &Window)
{
    //moves the player depending on the direction
    if(direction == LEFT)
        position.x -= moveSpeed;
    else
        position.x += moveSpeed;
    sprite.setPosition(position);
}

void bullet::draw(sf::RenderWindow &Window)
{
    Window.draw(sprite);
}

sf::Vector2f bullet::getPosition()
{
    return position;
}
