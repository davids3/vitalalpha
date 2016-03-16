#include "fadeAnimation.h"

fadeAnimation::fadeAnimation()
{
    //ctor
}

fadeAnimation::~fadeAnimation()
{
    //dtor
}

void fadeAnimation::loadContent(std::string text, sf::Image &image, sf::Vector2f position)
{
    animation::loadContent(text, image, position);//calls the same function in animation
    increase = false;
    fadeSpeed = 0.02f;
}

void fadeAnimation::loadContent(std::string text, sf::Image &image, sf::Vector2f position, std::string font)
{
    animation::loadContent(text, image, position, font);
    increase = false;
    fadeSpeed = 0.02f;
}

void fadeAnimation::unloadContent()
{

}

void fadeAnimation::update(sf::RenderWindow &Window)
{
    if(active)//if the screen is active
    {
        if(!increase)// if not increasing
            alpha -= fadeSpeed;//reduce alpha
        else
            alpha += fadeSpeed;//increase alpha

        if (alpha >= 1.0f)//when alpha is greater or equal to one, stop increasing
        {
            alpha = 1.0f;
            increase = false;
        }
        else if (alpha <= 0.0f)//if alpha is smaller or equal to zero, stop decreasing
        {
            alpha = 0.0f;
            increase = true;
        }
    }
    else
    {
        alpha = 1.0f;
    }

    animation::update(Window);
}

void fadeAnimation::draw(sf::RenderWindow &Window)
{
    animation::draw(Window);
}

void fadeAnimation::setAlpha(float value)
{
    alpha = value;

    if (alpha == 0.0f)
        increase = true;
    else
        increase = false;
}

void fadeAnimation::setFadeSpeed(float value)
{
    fadeSpeed = value;
}
