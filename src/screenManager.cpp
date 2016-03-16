#include "screenManager.h"

gameScreen *currentScreen, *newScreen; //Creates 2 pointers to gameScreen

//Singleton Class, creates a static instance of screenManager and returns it
//this means that the class can beused as a function to call other functions
screenManager &screenManager::getInstance()
{
    static screenManager instance;
    return instance;
}

screenManager::screenManager()
{
    //ctor
}

screenManager::~screenManager()
{
    //dtor
}

float screenManager::getAlpha() //returns the alpha value of the object fade of class fadeAnimation
{
    return fade.getAlpha();
}

void screenManager::transition(sf::RenderWindow &Window)//for transitioning between screens
{
    if (transitionState) //If transitionState is true...
    {
        fade.update(Window);
        if (fade.getAlpha() >= 1.0f)//if the transparency of the fade rect is greater or equal to one:
        {
            currentScreen->unloadContent(Window); //calls unloadContent of the current screen
            delete currentScreen;
            currentScreen = newScreen; //Assigns the screen passed by the function as the new currentScreen
            currentScreen->loadContent(); //calls the loadContent function of the new screen
            newScreen = NULL;//empties new screen
        }
        else if (fade.getAlpha() <= 0.0f)
        {
            transitionState = false;
            fade.setValue(fade.getActive(), false);
        }
    }
}

void screenManager::addScreen(gameScreen *screen)
{
    transitionState = true;
    newScreen = screen;
    fade.setValue(fade.getActive(), true);
    fade.setAlpha(0.0f);
}

void screenManager::initialise()//called before main loop to set first screen
{
    //Creates an instance of splashScreen, the first screen to be loaded by the application
    currentScreen = new splashScreen;
    transitionState = false;
}

void screenManager::loadContent()
{
    currentScreen->loadContent(); //calls load content of the current screen

    sf::Image image;
    sf::Vector2f pos;
    fade.loadContent("", image, pos);
    fade.setAlpha(0.0f); //set alpha to 0, therefore the fade rectangle is invisible
}

void screenManager::unloadContent()
{

}

void screenManager::updateEvent(sf::Event Event)
{
    currentScreen->updateEvent(Event);
}

void screenManager::update(sf::RenderWindow &Window)
{
    if (!transitionState) // if transition state is false
        currentScreen->update(Window); //calls the function update of the current screen
    else
        transition(Window);//transitions the window;
}

void screenManager::draw(sf::RenderWindow &Window)
{
    currentScreen->draw(Window); //calls the function draw of the current screen
}
