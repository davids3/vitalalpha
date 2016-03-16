#ifndef HEALTHPACK_H
#define HEALTHPACK_H

#include<SFML/Graphics.hpp>

#include "collectable.h"

class healthPack: public collectable//Health pack class, inherits from collectable
{
    public:
        healthPack();
        ~healthPack();

        void loadContent(sf::Vector2f position);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
};

#endif // HEALTHPACK_H
