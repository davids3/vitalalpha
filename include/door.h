#ifndef DOOR_H
#define DOOR_H

#include<SFML/Graphics.hpp>

#include "collectable.h"

class door: public collectable//door for changing level
{
    public:
        door();
        ~door();

        void loadContent(sf::Vector2f position);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
};

#endif // DOOR_H
