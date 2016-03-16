#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "gameScreen.h"
#include "splashScreen.h"
#include "creditScreen.h"
#include "screenManager.h"
#include "menuManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class titleScreen: public gameScreen//titleScreen class, inherits from gameScreen
{
    public:
        titleScreen();
        ~titleScreen();

        void loadContent();
        void unloadContent(sf::RenderWindow &Window);
        void updateEvent(sf::Event Event);
        void update(sf::RenderWindow &Window);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
        //resources for the game title
        sf::Text title;
        sf::Font slant;

        menuManager menu;
};

#endif // SPLASHSCREEN_H
