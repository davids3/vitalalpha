#include "splashScreen.h"

splashScreen::splashScreen()
{
    //ctor
}

splashScreen::~splashScreen()
{
    //dtor
}
void splashScreen::loadContent()
{
    //assigning keys for skipping the splash screen
    keys.push_back(sf::Keyboard::Space);
    keys.push_back(sf::Keyboard::Return);
    keys.push_back(sf::Keyboard::Escape);

    imageNumber = 0;

    file.loadContent("Load/splash.txt", attributes, contents);

    for(int i = 0; i < attributes.size(); i++)
    {
        for(int j = 0; j < attributes[i].size(); j++)
        {
            if (attributes[i][j] == "image")
            {
                image.loadFromFile(contents[i][j]);
                fade.push_back(new fadeAnimation);
                sf::Vector2f pos(400 - image.getSize().x/2, 300 - image.getSize().y/2);
                fade[fade.size()-1]->loadContent("", image, pos);
                fade[fade.size()-1]->setValue(fade[fade.size()-1]->getActive(), true);
                fade[fade.size()-1]->setValue(fade[fade.size()-1]->getScale(), 1.0f);
                fade[fade.size()-1]->setAlpha(0.0f);
            }
        }
    }
}

void splashScreen::unloadContent(sf::RenderWindow &Window)
{
    gameScreen::unloadContent(Window);
    for(int i = 0; i < fade.size(); i++)
    {
        fade[i]->unloadContent();
        delete fade[i];
    }
    fade.clear();
}

void splashScreen::updateEvent(sf::Event Event)
{
    if(stopInput == false)
    {
        stopInput = true;
        if(input.keyPressed(keys))
            screenManager::getInstance().addScreen(new titleScreen);
        else
            stopInput = false;
    }
    input.update(Event);
}

void splashScreen::update(sf::RenderWindow &Window)
{
    if(fade[imageNumber]->getAlpha() <= 0.0f && change == true)
    {
        imageNumber++;
        change = false;
    }

    fade[imageNumber]->update(Window);

    if(fade[imageNumber]->getAlpha() >= 1.0f)
        change = true;

    //testing if the change screen key is pressed, or the array is out of images
    if(input.keyPressed(keys) || (imageNumber >= fade.size() - 1 && change == true))
        screenManager::getInstance().addScreen(new titleScreen);
}

void splashScreen::draw(sf::RenderWindow &Window)
{
    fade[imageNumber]->draw(Window);
}
