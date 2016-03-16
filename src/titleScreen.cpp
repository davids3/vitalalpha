#include "titleScreen.h"

titleScreen::titleScreen()
{
    //ctor
}

titleScreen::~titleScreen()
{
    //dtor
}
void titleScreen::loadContent()
{
    keys.push_back(sf::Keyboard::Escape); //adds key z to vector keys

    if (!slant.loadFromFile("Fonts/slant.ttf"))
        std::cout << "Could not find the specified font" << std::endl;
    title.setString("VITAL");
    title.setFont(slant);
    title.setCharacterSize(72);
    title.setScale(2, 2);
    title.setPosition(400 - title.getGlobalBounds().width/2, 30);

    menu.loadContent("Title");
}

void titleScreen::unloadContent(sf::RenderWindow &Window)//handles keypresses
{
    gameScreen::unloadContent(Window);
    menu.unloadContent();
}

void titleScreen::updateEvent(sf::Event Event) //handles game elements
{
    menu.updateEvent(input);

    if(stopInput == false)
    {
        stopInput = true;
        if(input.keyPressed(keys))
            screenManager::getInstance().addScreen(new splashScreen);
        else if(menu.newGame == true)
            screenManager::getInstance().addScreen(new levelScreen);
        else if(menu.credits == true)
            screenManager::getInstance().addScreen(new creditScreen);
        else
            stopInput = false;
    }
    input.update(Event);
}

void titleScreen::update(sf::RenderWindow &Window)
{
    menu.update(Window);
}

void titleScreen::draw(sf::RenderWindow &Window)
{
    Window.draw(title);
    menu.draw(Window);
}
