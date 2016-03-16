#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class bullet//bullet class
{
    public:
        bullet();
        ~bullet();

        void loadContent(sf::Vector2f position, int direction);
        void unloadContent();
        void update(sf::RenderWindow &Window);
        void draw(sf::RenderWindow &Window);
        sf::Vector2f getPosition();

    protected:
    private:
        sf::Vector2f position;
        sf::Texture texture;
        sf::Sprite sprite;
        int moveSpeed;
        int direction;
};

#endif // BULLET_H
