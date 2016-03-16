#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <string>
#include <iostream>
#include "gameScreen.h"
#include "splashScreen.h"
#include "titleScreen.h"
#include "levelScreen.h"
#include "fadeAnimation.h"
#include "fileManager.h"

class screenManager//manages the screen states
{
    public:
        ~screenManager();
        static screenManager &getInstance(); //Static functions can be called without there being a object of that class

        void initialise();
        //some of each of the 5 functions below can be found within most classes
        void loadContent();
        void unloadContent();
        void updateEvent(sf::Event Event);
        void update(sf::RenderWindow &Window);
        void draw(sf::RenderWindow &Window);

        void addScreen(gameScreen *screen);

        float getAlpha();

    protected:
    private:
        screenManager();//constructor

        void transition(sf::RenderWindow &Window);
        bool transitionState; //Used to check if the screen is still transitioning

        fadeAnimation fade;
        gameScreen *newScreen;
        fileManager file;
};

#endif // SCREENMANAGER_H
