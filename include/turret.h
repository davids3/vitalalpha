#ifndef TURRET_H
#define TURRET_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cmath>
#include<algorithm>

#include "character.h"
#include "bullet.h"

class turret: public character
{
    public:
        turret();
        ~turret();

        void loadContent(sf::Vector2f position, int direction);
        void unloadContent();
        void update(sf::RenderWindow &Window, sf::Vector2f viewPosition, std::vector<bullet*> &bullets);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
        int direction;

        sf::Clock timer;
        bool fire;
};

#endif // TURRET_H
