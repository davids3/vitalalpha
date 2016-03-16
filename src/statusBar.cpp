#include "statusBar.h"

statusBar::statusBar()
{
    //ctor
}

statusBar::~statusBar()
{
    //dtor
}
void statusBar::loadContent()
{
    backColor = sf::Color(40, 60, 121);
    borderColor = sf::Color::Black;
    borderThickness = 3;

    background.setSize(sf::Vector2f(totalWidth, totalHeight));
    background.setFillColor(backColor);
    background.setOutlineColor(borderColor);
    background.setOutlineThickness(borderThickness);

    foreground.setSize(sf::Vector2f(totalWidth, totalHeight));
    foreground.setFillColor(mainColor);

    percentWidth = totalWidth;

    font.loadFromFile("Fonts/visitor1.ttf");
    text.setFont(font);
    text.setString(title);
}

void statusBar::unloadContent()
{

}

void statusBar::update(sf::RenderWindow &Window, sf::Vector2f viewPosition, int value)
{
    titlePosition.x = position.x - 40;
    titlePosition.y = position.y - 18;

    if(value >= 0 && value <= 100)
    {
        percentWidth = totalWidth / 100 * value;
        foreground.setSize(sf::Vector2f(percentWidth, totalHeight));
    }

    background.setPosition(position);
    foreground.setPosition(position);

    text.setPosition(titlePosition);
}

void statusBar::draw(sf::RenderWindow &Window)
{
    Window.draw(background);
    Window.draw(foreground);
    Window.draw(text);
}
