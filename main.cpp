#include <iostream>
#include <SFML/Graphics.hpp>
#include "screenManager.h"

#define ScreenWidth 800
#define ScreenHeight 600

using namespace std;

int main()
{
    //Creates the window, all drawing to the screen will require this item
    sf::RenderWindow Window(sf::VideoMode(ScreenWidth, ScreenHeight, 32), "Vital");
    //sets a limit to the framerate so it runs at the same speed on all computers
    Window.setFramerateLimit(60);

    //Initialises a rectangle the same size as the window to use for fading in and out
    sf::RectangleShape fade(sf::Vector2f(10000, 10000));
    fade.setFillColor(sf::Color(255, 255, 255));//black

    screenManager::getInstance().initialise(); //calls the function initialise of screenManager
    screenManager::getInstance().loadContent(); // calls the function loadContent of screenManager

    Window.setKeyRepeatEnabled(false); //Holding down the key does not input the key each cycle

    while(Window.isOpen()) //Begin mainprogram loop
    {
        sf::Event event;//new event
        while(Window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                Window.close(); // If window is closed, or escape is pressed, close the window

            screenManager::getInstance().updateEvent(event);//updates the event
        }

        Window.clear(); //Clears the screen of all elements

        //Updates the current screen state using the screenManager class
        screenManager::getInstance().update(Window);

        //sets the colour of the fade square to 255 times the value returned by get
        fade.setFillColor(sf::Color(0, 0, 0, 255 * screenManager::getInstance().getAlpha()));

        //Calls the current screen state on what to draw on screen useing the screenManager class
        screenManager::getInstance().draw(Window);
        Window.draw(fade);//draws the fading rectangle for screen transitioning

        Window.display(); //Displays the updated window
    }
    return 0;
}
