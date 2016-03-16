#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "gameScreen.h"
#include "titleScreen.h"
#include "screenManager.h"
#include "fadeAnimation.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class splashScreen: public gameScreen //splashScreen, inherits from gameScreen
{
    public:
        splashScreen();
        ~splashScreen();

        void loadContent();
        void unloadContent(sf::RenderWindow &Window);
        void updateEvent(sf::Event Event);
        void update(sf::RenderWindow &Window);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
        sf::Image image;
        //vector of fadeAnimations, which contains and controls the individual splash images
        std::vector<fadeAnimation*> fade;

        int imageNumber;
        bool change;
};

#endif // SPLASHSCREEN_H
