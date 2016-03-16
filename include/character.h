#ifndef CHARACTER_H
#define CHARACTER_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

#include "fileManager.h"

class character//base character class, turret and player inherit from this
{
    public:
        character();
        ~character();

        virtual void loadContent();
        virtual void unloadContent();
        virtual void updateEvent(sf::Event Event);
        virtual void update(sf::RenderWindow &Window);
        virtual void draw(sf::RenderWindow &Window);
        sf::Vector2f getPosition();
    protected:
        std::vector<sf::Image> images;
        std::vector<sf::Vector2f> origins;
        sf::Image tempImage;
        sf::Texture texture;
        sf::Sprite sprite;

        fileManager file;
        std::vector< std::vector<std::string> > attributes;
        std::vector< std::vector<std::string> > contents;

        sf::Vector2f position;
        int imageNumber;
        int lastNumber;
    private:
};

#endif // CHARACTER_H
