#ifndef STATUSBAR_H
#define STATUSBAR_H

#include<SFML/Graphics.hpp>

class statusBar//base status bar class, healthBar and energyBar inherit from this
{
    public:
        statusBar();
        ~statusBar();

        virtual void loadContent();
        virtual void unloadContent();
        virtual void update(sf::RenderWindow &Window, sf::Vector2f viewPosition, int value);
        virtual void draw(sf::RenderWindow &Window);
    protected:
        float totalWidth, totalHeight, percentWidth;
        float borderThickness;
        sf::Color mainColor, backColor, borderColor;

        sf::RectangleShape background;
        sf::RectangleShape foreground;

        sf::Vector2f position, titlePosition;

        sf::Text text;
        sf::Font font;
        sf::String title;
    private:
};

#endif // STATUSBAR_H
