#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include<SFML/Graphics.hpp>

#include "statusBar.h"

class healthBar: public statusBar//Health bar class, inherits from statusBar
{
    public:
        healthBar();
        ~healthBar();

        void loadContent();
        void unloadContent();
        void update(sf::RenderWindow &Window, sf::Vector2f viewPosition, int value);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
};

#endif // HEALTHBAR_H
