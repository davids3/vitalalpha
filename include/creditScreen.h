#ifndef CREDITSCREEN_H
#define CREDITSCREEN_H

#include<SFML/Graphics.hpp>

#include "screenManager.h"
#include "gameScreen.h"

class creditScreen: public gameScreen//credit screen, loads credits from file
{
    public:
        creditScreen();
        ~creditScreen();

        void loadContent();
        void unloadContent(sf::RenderWindow &Window);
        void updateEvent(sf::Event Event);
        void update(sf::RenderWindow &Window);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // CREDITSCREEN_H
