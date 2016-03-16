#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cmath>
#include<algorithm>

#include "fileManager.h"
#include "inputManager.h"
#include "mapManager.h"
#include "character.h"
#include "bullet.h"
#include "collectable.h"
#include "healthPack.h"
#include "energyPack.h"
#include "turret.h"

class playerManager: public character//player manager class, inherits from character
{
    public:
        playerManager();
        ~playerManager();

        void loadContent();
        void unloadContent();
        void updateMovement(inputManager input);
        void updateCollision(std::vector< std::vector<int> > colVector, std::vector<bullet*> &bullets,
                             std::vector<collectable*> &packs, std::vector<turret*> &turrets,
                             float &healthValue, float &energyValue, int &score);
        void updateAnimation(sf::RenderWindow &Window, float &energyValue);
        void draw(sf::RenderWindow &Window);

    protected:
    private:
        sf::Vector2f velocity;

        const float gravity = 0.2;
        const float slide = 0.05;
        const float jumpSpeed = 8;
        const float moveSpeed = 3;

        bool jump;
        bool attacking;
        bool standAttack;

        float bottom, left, right, top;
        std::vector<sf::Vector2i> tiles;

        int lastDirection;

        int cycle;
        sf::Clock timer;
        bool decrease;
};

#endif // PLAYERMANAGER_H
