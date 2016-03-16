#include "menuManager.h"

menuManager::menuManager()
{
    //ctor
}

menuManager::~menuManager()
{
    //dtor
}

void menuManager::equaliseMenuItems()
{
    for(int i = 0; i < menuItems.size(); i++)
    {
        if(menuImages.size() == i)
            menuImages.push_back(null);
    }

    for(int i = 0; i < menuImages.size(); i++)
    {
        if(menuItems.size() == i)
            menuItems.push_back("");
    }
}

void menuManager::setAnimations()
{
    for(int i = 0; i < menuItems.size(); i++)
    {
        for(int j = 0; j < animationTypes.size(); j++)
        {
            if(animationTypes[j] == "Fade")
            {
                tempAnimation.push_back(new fadeAnimation);
                tempAnimation[tempAnimation.size()-1]->loadContent(menuItems[i], menuImages[i], position, font);
            }
        }
        currentAnimation.push_back(tempAnimation);
        tempAnimation.clear();
    }
}

void menuManager::setPositions()
{
    sf::Vector2f pos = position;

    for(int i = 0; i < currentAnimation.size(); i++)
    {
        float width = menuImages[i].getSize().x + currentAnimation[i][0]->getText().getGlobalBounds().width;
        float height = menuImages[i].getSize().y + currentAnimation[i][0]->getText().getGlobalBounds().height;

        if (axis == 1)
            pos.x += 10 + width;
        else
        {
            pos.y += 25 + height;
            pos.x = 400 - width/2;
        }
        for(int j = 0; j < currentAnimation[i].size(); j++)
        {
            currentAnimation[i][j]->setValue(currentAnimation[i][j]->getPosition(), pos);
            currentAnimation[i][j]->setValue(currentAnimation[i][j]->getScale(), 1.0f);
        }
    }
}

void menuManager::loadContent(std::string menuID)
{
    close = newGame = credits = false;

    null.loadFromFile("Sprites/null.png");
    itemNumber = 0;

    file.loadContent("Load/menus.txt", attributes, contents, menuID);
    for(int i = 0; i < attributes.size(); i++)
    {
        for(int j = 0; j < attributes[i].size(); j++)
        {
            std::string att = attributes[i][j];
            std::string con = contents[i][j];

            if(att == "Item")
                menuItems.push_back(con);

            else if (att == "Image")
            {
                image.loadFromFile(con);
                menuImages.push_back(image);
            }
            else if(att == "Position")
            {
                std::string pos[2];
                pos[0] = con.substr(0, con.find(','));
                pos[1] = con.substr(con.find(',') + 1);

                position.x = atof(pos[0].c_str());
                position.y = atof(pos[1].c_str());
            }
            else if(att == "Align")
                align = con;

            else if(att == "Axis")
                axis = atoi(con.c_str());

            else if (att == "Animation")
                animationTypes.push_back(con);

            else if (att == "Font")
                font = con;
        }
    }

    equaliseMenuItems();
    setAnimations();
    setPositions();
}

void menuManager::unloadContent()
{
    menuItems.clear();
    menuImages.clear();

    for(int i = 0; i < currentAnimation.size(); i++)
    {
        for(int j = 0; j < currentAnimation[i].size(); j++)
            delete currentAnimation[i][j];
    }

    tempAnimation.clear();

    currentAnimation.clear();
    animationTypes.clear();

    attributes.clear();
    contents.clear();
}

void menuManager::updateEvent(inputManager input)
{
    if(axis == 1)
    {
        if(input.keyPressed(sf::Keyboard::Right) || input.keyPressed(sf::Keyboard::D))
            itemNumber++;
        else if(input.keyPressed(sf::Keyboard::Left) || input.keyPressed(sf::Keyboard::A))
            itemNumber--;
    }
    else
    {
        if(input.keyPressed(sf::Keyboard::Down) || input.keyPressed(sf::Keyboard::S))
            itemNumber++;
        else if(input.keyPressed(sf::Keyboard::Up) || input.keyPressed(sf::Keyboard::W))
            itemNumber--;
    }
    if(input.keyPressed(sf::Keyboard::Return))
    {
        std::cout << currentAnimation[itemNumber][0]->getPreText() << std::endl;
        std::string name = currentAnimation[itemNumber][0]->getPreText();

        if(name == "New Game")
            newGame = true;
        else if(name == "Load Game")
            std::cout << "Feature not in this version." << std::endl;
        else if(name == "Options")
            std::cout << "Feature not in this version." << std::endl;
        else if(name == "Credits")
            credits = true;
        else if(name == "Exit")
            close = true;
    }
}

void menuManager::update(sf::RenderWindow &Window)
{
    if(close == true)
        Window.close();

    if(itemNumber < 0)
        itemNumber = menuItems.size() - 1;
    else if(itemNumber > menuItems.size() - 1)
        itemNumber = 0;

    for(int i = 0; i < currentAnimation.size(); i++)
    {
        for(int j = 0; j < currentAnimation[i].size(); j++)
        {
            currentAnimation[i][j]->setValue(currentAnimation[i][j]->getActive(), false);
            if(i == itemNumber)
                currentAnimation[i][j]->setValue(currentAnimation[i][j]->getActive(), true);

            currentAnimation[i][j]->update(Window);
        }
    }
}

void menuManager::draw(sf::RenderWindow &Window)
{
    for(int i = 0; i < currentAnimation.size(); i++)
    {
        for(int j = 0; j < currentAnimation[i].size(); j++)
            currentAnimation[i][j]->draw(Window);
    }
}
