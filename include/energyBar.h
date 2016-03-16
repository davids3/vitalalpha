#ifndef ENERGYBAR_H
#define ENERGYBAR_H

#include<SFML/Graphics.hpp>

#include "statusBar.h"

class energyBar: public statusBar//Energy bar class, inherits from statusBar
{
    public:
        energyBar();
        ~energyBar();

        void loadContent();
        void unloadContent();
        void update(sf::RenderWindow &Window, sf::Vector2f viewPosition, int value);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
};

#endif // ENERGYBAR_H
