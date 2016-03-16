#include "character.h"

character::character()
{
    //ctor
}

character::~character()
{
    //dtor
}

void character::loadContent()
{
    //converts the attributes and contents vectors into usable resources
    for(int i = 0; i < attributes.size(); i++)
    {
        for(int j = 0; j < attributes[i].size(); j++)
        {
            if (attributes[i][j] == "image")
            {
                if(!tempImage.loadFromFile(contents[i][j]))
                   std::cout << "Cannot find sprite" << contents[i][j] << std::endl;
                images.push_back(tempImage);
            }
            else if(attributes[i][j] == "coordinate")
            {
                std::string con = contents[i][j];
                std::string pos[2];
                sf::Vector2f tempPos;
                pos[0] = con.substr(0, con.find(','));
                pos[1] = con.substr(con.find(',') + 1);

                tempPos.x = atof(pos[0].c_str());
                tempPos.y = atof(pos[1].c_str());

                origins.push_back(tempPos);
            }
        }
    }
}

void character::unloadContent()
{
    //clears the vectors to prevent a memory leak
    images.clear();
    origins.clear();
    attributes.clear();
    contents.clear();
}

void character::updateEvent(sf::Event Event)
{

}

void character::update(sf::RenderWindow &Window)
{

}

void character::draw(sf::RenderWindow &Window)
{

}

sf::Vector2f character::getPosition()
{
    return position;
}
