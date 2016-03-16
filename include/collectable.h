#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include<SFML/Graphics.hpp>

class collectable//class for objects, meaning health and energy packs and exit door
{
    public:
        collectable();
        ~collectable();

        virtual void loadContent(sf::Vector2f position);
        virtual void draw(sf::RenderWindow &Window);
        sf::Vector2f getPosition();
    protected:
        sf::Vector2f position;
        sf::Texture texture;
        sf::Sprite sprite;
    private:
};

#endif // COLLECTABLE_H
