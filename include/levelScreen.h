#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

#include "gameScreen.h"
#include "titleScreen.h"
#include "screenManager.h"
#include "mapManager.h"
#include "playerManager.h"
#include "bullet.h"
#include "turret.h"
#include "healthBar.h"
#include "energyBar.h"
#include "collectable.h"
#include "healthPack.h"
#include "energyPack.h"
#include "door.h"

class levelScreen: public gameScreen
{
    public:
        levelScreen();
        levelScreen(int levelNumber, int lives, int score);
        ~levelScreen();

        void loadContent();
        void unloadContent(sf::RenderWindow &Window);
        void updateEvent(sf::Event Event);
        void update(sf::RenderWindow &Window);
        void draw(sf::RenderWindow &Window);
    protected:
    private:
        int levelNumber;
        int lives;

        mapManager map;
        playerManager player;
        std::vector< std::vector<int> > colVector;

        sf::View view;
        sf::Vector2f viewPosition;

        std::vector<bullet*> bullets;
        std::vector<turret*> turrets;
        std::vector<collectable*> packs;

        std::vector<std::string> type;
        std::vector<sf::Vector2f> position;
        std::vector<int> direction;

        healthBar health;
        energyBar energy;
        float healthValue, energyValue;

        int score, oldScore;
        sf::Text scoreText;
        sf::Vector2f scorePosition;

        //resources for the lives left indicator
        sf::Sprite head;
        sf::Texture headTexture;
        sf::Text livesText;
        sf::Font font;
        sf::Vector2f headPosition, livesPosition;

        door levelExit;
};

#endif // LEVEL_H
