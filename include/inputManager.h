#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>

class inputManager//input manager class, manages input
{
    public:
        inputManager();
        ~inputManager();

        void update(sf::Event event);

        bool keyPressed(int);
        bool keyPressed(std::vector<int> keys);

        bool keyReleased(int key);
        bool keyReleased(std::vector<int> keys);

        bool keyDown(sf::Keyboard::Key key);
        bool keyDown(std::vector<sf::Keyboard::Key> keys);
    protected:
    private:
        sf::Event event;
};

#endif // INPUTMANAGER_H
