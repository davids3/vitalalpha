#include "animation.h"

animation::animation()
{
    //ctor
}

animation::~animation()
{
    //dtor
}

void animation::loadContent(std::string text, sf::Image &image, sf::Vector2f position)
{
    //these functions make a local copy of the variable passed
    this->preText = text;
    this->image = image;
    this->position = position;

    alpha = 1.0f;
    if(image.getSize().y > 0)// if width is greater then 0, so if image exists
    {
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    this->text.setString(text);
    active = false;
}

//overload for loadContent for when a font is passed as well
void animation::loadContent(std::string text, sf::Image &image, sf::Vector2f position, std::string font)
{
    this->preText = text;
    this->image = image;
    this->position = position;

    if(!this->font.loadFromFile(font))
        std::cout << "Could not find the specified font" << std::endl;
    this->text.setFont(this->font);

    alpha = 1.0f;
    if(image.getSize().y > 0)
    {
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
    this->text.setString(text);
    active = false;
}

void animation::unloadContent()
{

}

void animation::update(sf::RenderWindow &Window)
{

}

void animation::draw(sf::RenderWindow &Window)
{
    std::string str = text.getString();

    if (str !="") //Draws text if it is passes text
    {
        text.setColor(sf::Color(255, 255, 255, 255 * alpha));
        text.setPosition(position);
        text.setScale(scale, scale);
        Window.draw(text);
    }
    if (sprite.getTexture() != NULL) // draws the sprite if it is passed a sprite
    {
        sprite.setColor(sf::Color(255, 255, 255, 255 * alpha));
        sprite.setPosition(position);
        sprite.setScale(scale, scale);
        Window.draw(sprite);
    }
}

float &animation::getAlpha()
{
    return alpha;
}

bool &animation::getActive()
{
    return active;
}

float &animation::getScale()
{
    return scale;
}

sf::Vector2f &animation::getPosition()
{
    return position;
}

std::string &animation::getPreText()
{
    return preText;
}

sf::Text &animation::getText()
{
    return text;
}

void animation::setAlpha(float value)
{
    alpha = value;
}
