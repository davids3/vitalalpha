#ifndef ENERGYPACK_H
#define ENERGYPACK_H

#include<SFML/Graphics.hpp>

#include "collectable.h"

class energyPack: public collectable//energyPack, inherits from collectable
{
    public:
        energyPack();
        ~energyPack();

        void loadContent(sf::Vector2f position);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
};

#endif // ENERGYPACK_H
