#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

#include "gameScreen.h"
#include "fileManager.h"
#include "inputManager.h"

#define BLOCKSIZE 32

class mapManager//map manager class
{
    public:
        mapManager();
        ~mapManager();

        void loadContent(int levelNumber);
        void unloadContent();
        void update(sf::RenderWindow &Window, sf::Vector2f viewPosition);
        void draw(sf::RenderWindow &Window);
        std::vector< std::vector<int> > getMapVector();
    protected:
    private:
        std::vector< std::vector<int> > mapVector;
        std::vector< std::vector<int> > mapVector2;

        fileManager file;

        sf::Texture primarySheet;
        sf::Texture secondarySheet;
        sf::Sprite tile;
        sf::Vector2f tileType[33];
        std::vector<sf::Vector2i> tilesPrint;

        sf::Texture backgroundTexture;
        sf::Sprite background;
};

#endif // MAPMANAGER_H
