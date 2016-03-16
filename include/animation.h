#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class animation//base animation class for screen transitioning, NOT player animation
{
    public:
        animation();
        ~animation();

        virtual void loadContent(std::string text, sf::Image &image, sf::Vector2f position);
        virtual void loadContent(std::string text, sf::Image &image, sf::Vector2f position, std::string font);
        virtual void unloadContent();
        virtual void update(sf::RenderWindow &Window);
        virtual void draw(sf::RenderWindow &Window);

        virtual void setAlpha(float alpha);
        float &getAlpha();
        bool &getActive();
        float &getScale();
        std::string &getPreText();
        sf::Text &getText();
        sf::Vector2f &getPosition();

        template<typename T>//This template allows the above get functions to set values
        void setValue (T &variable, T value)
        {
            variable = value;
        }

    protected:
        float alpha;//for transperency of the item

        //both text and images can be animated by this class
        std::string preText;
        sf::Text text;
        sf::Texture texture;
        sf::Image image;
        sf::Sprite sprite;
        sf::Vector2f position;

        sf::IntRect sourceRect;
        bool active;//for determining of the animation is active

        float scale;//scale of the image

        std::string preFont;
        sf::Font font;
    private:
};

#endif // ANIMATION_H
