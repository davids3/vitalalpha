#include "turret.h"

enum direction { LEFT, RIGHT };

turret::turret()
{
    //ctor
}

turret::~turret()
{
    //dtor
}

void turret::loadContent(sf::Vector2f position, int direction)
{
    file.loadContent("Load/turret.txt", attributes, contents);
    character::loadContent();
    this->position = position;
    this->direction = direction;
    imageNumber = 0;
}

void turret::unloadContent()
{
    character::unloadContent();
}

void turret::update(sf::RenderWindow &Window, sf::Vector2f viewPosition, std::vector<bullet*> &bullets)
{
    if(timer.getElapsedTime().asSeconds() > 0.5f
       && ((direction == LEFT && viewPosition.x < position.x && position.x < viewPosition.x + 400)
       || (direction == RIGHT && viewPosition.x > position.x && position.x > viewPosition.x - 400)))
    {
        if(imageNumber == 0)
        {
            imageNumber = 1;
            fire = true;
        }
        else
            imageNumber = 0;
        timer.restart();
    }

    if(fire == true)
    {
        bullets.push_back(new bullet);
        bullets[bullets.size()-1]->loadContent(sf::Vector2f(position.x, position.y - 26), direction);
        fire = false;
    }

    texture.loadFromImage(images[imageNumber]);
    sprite.setTexture(texture);

    if(direction == LEFT)
    {
        sprite.setTextureRect(sf::IntRect(texture.getSize().x, 0, -texture.getSize().x, texture.getSize().y));
        sprite.setOrigin(texture.getSize().x - origins[imageNumber].x, origins[imageNumber].y);
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
        sprite.setOrigin(origins[imageNumber]);
    }

    sprite.setPosition(position);
}

void turret::draw(sf::RenderWindow &Window)
{
    Window.draw(sprite);
}
