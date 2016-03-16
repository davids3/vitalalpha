#include "levelScreen.h"

enum direction { LEFT, RIGHT };

levelScreen::levelScreen()
{
    //default values of these variables
    levelNumber = 1;
    lives = 3;
    score = oldScore = 0;
}

levelScreen::levelScreen(int levelNumber, int lives, int score)
{
    //creates a local copy of the variables
    this->levelNumber = levelNumber;
    this->lives = lives;
    this->score = score;
    oldScore = score;
}

levelScreen::~levelScreen()
{
    //dtor
}
void levelScreen::loadContent()
{
    stopInput = false;

    keys.push_back(sf::Keyboard::Escape);

    map.loadContent(levelNumber);
    player.loadContent();

    colVector = map.getMapVector();

    view.reset(sf::FloatRect(0, 0, 800, 600));

    //determines the level to load for the objects in the level
    if(levelNumber == 1)
        file.loadContent("Load/level1.2.txt", attributes, contents);
    if(levelNumber == 2)
        file.loadContent("Load/level2.2.txt", attributes, contents);

    //converts attributes and contents into usable items
    for(int i = 0; i < attributes.size(); i++)
    {
        for(int j = 0; j < attributes[i].size(); j++)
        {
            if (attributes[i][j] == "type")
                type.push_back(contents[i][j]);

            else if(attributes[i][j] == "position")
            {
                std::string con = contents[i][j];
                std::string pos[2];
                sf::Vector2f tempPos;
                pos[0] = con.substr(0, con.find(','));
                pos[1] = con.substr(con.find(',') + 1);

                tempPos.x = atof(pos[0].c_str()) * 32;
                tempPos.y = atof(pos[1].c_str()) * 32;

                position.push_back(tempPos);
            }

            else if(attributes[i][j] == "direction")
            {
                if(contents[i][j] == "left")
                    direction.push_back(LEFT);
                else
                    direction.push_back(RIGHT);
            }
        }
    }

    //creates the items from the above file
    for(int i = 0; i < type.size(); i++)
    {
        if(type[i] == "turret")
        {
            turrets.push_back(new turret);
            turrets[turrets.size()-1]->loadContent(position[i], direction[i]);
        }
        if(type[i] == "health")
        {
            packs.push_back(new healthPack);
            packs[packs.size()-1]->loadContent(position[i]);
        }
        if(type[i] == "energy")
        {
            packs.push_back(new energyPack);
            packs[packs.size()-1]->loadContent(position[i]);
        }
        if(type[i] == "door")
        {
            levelExit.loadContent(position[i]);
        }
    }

    //load the bars
    health.loadContent();
    energy.loadContent();

    healthValue = energyValue = 100;

    //initialising the lives counter
    headTexture.loadFromFile("Sprites/Player/head.png");
    head.setTexture(headTexture);
    font.loadFromFile("Fonts/visitor1.ttf");

    //determines the text for the lives counter
    std::stringstream stream;
    std::string times  = "x";
    stream << times << lives;
    sf::String livesString = stream.str();

    livesText.setString(livesString);
    livesText.setFont(font);

    scoreText.setFont(font);
}

void levelScreen::unloadContent(sf::RenderWindow &Window)
{
    //clears the vectors
    Window.setView(Window.getDefaultView());

    for(int i = 0; i < bullets.size(); i++)
        delete bullets[i];
    for(int i = 0; i < turrets.size(); i++)
    {
        turrets[i]->unloadContent();
        delete turrets[i];
    }
    for(int i = 0; i < packs.size(); i++)
        delete packs[i];

    bullets.clear();
    turrets.clear();
    packs.clear();
    colVector.clear();
    type.clear();
    position.clear();
    direction.clear();
    map.unloadContent();
    player.unloadContent();
    gameScreen::unloadContent(Window);
}

void levelScreen::updateEvent(sf::Event Event)
{
    if(stopInput == false)
    {
        stopInput = true;
        //loads a new screen
        if(input.keyPressed(keys))
            screenManager::getInstance().addScreen(new titleScreen);
        else if(input.keyPressed(sf::Keyboard::R))
            screenManager::getInstance().addScreen(new levelScreen(levelNumber, lives, score));
        else if(input.keyPressed(sf::Keyboard::N) && levelNumber == 1)
            screenManager::getInstance().addScreen(new levelScreen(levelNumber + 1, lives, score));
        else if(input.keyPressed(sf::Keyboard::B) && levelNumber == 2)
            screenManager::getInstance().addScreen(new levelScreen(levelNumber - 1, lives, score));
        else
            stopInput = false;
        input.update(Event);
    }
}

void levelScreen::update(sf::RenderWindow &Window)
{
    //updates the turrets and bullets
    for(int i = 0; i < turrets.size(); i++)
        turrets[i]->update(Window, viewPosition, bullets);
    for(int i = 0; i < bullets.size(); i++)
        bullets[i]->update(Window);

    //updates the player
    player.updateMovement(input);
    player.updateCollision(colVector, bullets, packs, turrets, healthValue, energyValue, score);
    player.updateAnimation(Window, energyValue);

    //verfies that the health is not below 0 or above 100
    //if the health = 0, restart the level with one less life
    if(healthValue <= 0 || player.getPosition().y > (colVector.size() - 1) * 32)
    {
        lives--;
        if(lives == 0)
            screenManager::getInstance().addScreen(new titleScreen);
        else
        screenManager::getInstance().addScreen(new levelScreen(levelNumber, lives, oldScore));
    }
    else if(healthValue > 100)
        healthValue = 100;

    //if the player exits the bottom of the screen, restart level with one less life
    if(player.getPosition().x < levelExit.getPosition().x + 22
       && player.getPosition().x > levelExit.getPosition().x - 22
       && player.getPosition().y <= levelExit.getPosition().y
       && player.getPosition().y > levelExit.getPosition().y - 64)
       {
            if(levelNumber == 2)
                screenManager::getInstance().addScreen(new titleScreen);
            else
                screenManager::getInstance().addScreen(new levelScreen(levelNumber + 1, lives, score));
       }

    //ensures energy level is between 0 and 100
    if(energyValue <= 0)
        energyValue = 0;
    if(energyValue > 100)
        energyValue = 100;

    //determines view position and makes sure it stays within the levels sctreen
    viewPosition.x = player.getPosition().x;
    viewPosition.y = player.getPosition().y;

    if(viewPosition.x < 400)
        viewPosition.x = 400;
    if(viewPosition.y < 300)
        viewPosition.y = 300;
    if(viewPosition.x > (colVector[0].size()-1) * 32 - 400)
        viewPosition.x = (colVector[0].size()-1) * 32 - 400;
    if(viewPosition.y > (colVector.size()-2) * 32 - 300)
        viewPosition.y = (colVector.size()-2) * 32 - 300;

    //updates the map
    map.update(Window, viewPosition);

    view.setCenter(viewPosition.x, viewPosition.y);
    Window.setView(view);

    //deletes the bullet if it exits the screen
    for(int i = 0; i < bullets.size(); i++)
    {
        if(bullets[i]->getPosition().x < viewPosition.x - 400
           || bullets[i]->getPosition().x > viewPosition.x + 400)
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            continue;
        }
    }

    //updates bars
    health.update(Window, viewPosition, healthValue);
    energy.update(Window, viewPosition, energyValue);

    //updates lives coubter
    headPosition.x = viewPosition.x - 40;
    headPosition.y = viewPosition.y - 300 + 5;

    livesPosition.x = headPosition.x + 50;
    livesPosition.y = headPosition.y;

    head.setPosition(headPosition);
    livesText.setPosition(livesPosition);

    scorePosition.x = viewPosition.x + 180;
    scorePosition.y = viewPosition.y - 300 + 5;

    std::stringstream stream;
    std::string text = "SCORE: ";
    stream << text << score;
    sf::String scoreString = stream.str();

    scoreText.setString(scoreString);
    scoreText.setPosition(scorePosition);
}

void levelScreen::draw(sf::RenderWindow &Window)
{
    //draws everything
    map.draw(Window);
    levelExit.draw(Window);
    for(int i = 0; i < turrets.size(); i++)
        turrets[i]->draw(Window);
    for(int i = 0; i < packs.size(); i++)
        packs[i]->draw(Window);
    player.draw(Window);
    for(int i = 0; i < bullets.size(); i++)
        bullets[i]->draw(Window);

    health.draw(Window);
    energy.draw(Window);
    Window.draw(head);
    Window.draw(livesText);
    Window.draw(scoreText);
}
