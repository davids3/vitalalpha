#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include<SFML/Graphics.hpp>
#include "animation.h"
#include "fadeAnimation.h"
#include "inputManager.h"
#include "fileManager.h"

class menuManager//menu manager class
{
    public:
        menuManager();
        ~menuManager();

        void loadContent(std::string menuID);
        void unloadContent();
        void updateEvent(inputManager input);
        void update(sf::RenderWindow &Window);
        void draw(sf::RenderWindow &Window);

        bool newGame, credits;
    protected:
    private:
        std::vector< std::vector<std::string> > attributes;
        std::vector< std::vector<std::string> > contents;

        fileManager file;

        std::vector< std::vector<animation*> > currentAnimation;
        std::vector<animation*> tempAnimation;

        sf::Image image;
        std::vector<sf::Image> menuImages;

        std::vector<std::string> menuItems;

        sf::Vector2f position;
        int axis;
        std::string align;
        std::vector<std::string> animationTypes;

        void equaliseMenuItems();
        void setAnimations();
        void setPositions();

        sf::Image null;

        int itemNumber;
        std::string font;

        bool close;
};

#endif // MENUMANAGER_H
