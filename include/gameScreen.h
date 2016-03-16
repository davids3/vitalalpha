#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include<SFML/Graphics.hpp>
#include "inputManager.h"
#include "fileManager.h"

class gameScreen//base screen class
{
    public:
        gameScreen();
        ~gameScreen();

        virtual void loadContent();
        virtual void unloadContent(sf::RenderWindow &Window);
        virtual void updateEvent(sf::Event Event);
        virtual void update(sf::RenderWindow &Window);
        virtual void draw(sf::RenderWindow &Window);
    protected:
        inputManager input;//instance of inputManager
        std::vector<int> keys;//vector of keys, used as a global input for going to the title screen

        fileManager file;//instance of fileManager
        //2d vectors of strings, used for loading files using fileManager
        std::vector< std::vector<std::string> > attributes;
        std::vector< std::vector<std::string> > contents;

        bool stopInput;//used to stop input from reinitialising a transition after it has started
    private:
};

#endif // GAMESCREEN_H
