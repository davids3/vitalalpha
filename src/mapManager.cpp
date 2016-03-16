#include "mapManager.h"

mapManager::mapManager()
{
    //ctor
}

mapManager::~mapManager()
{
    //dtor
}

void mapManager::loadContent(int levelNumber)
{
    //loads tilesheets
    if(!primarySheet.loadFromFile("Tiles/main.png"))
        std::cout << "Cannot find tilesheet" << std::endl;

    if(!secondarySheet.loadFromFile("Tiles/secondary.png"))
        std::cout << "Cannot find tilesheet" << std::endl;

    //assigns tileType coordinates within the tilesheet
    int index = 1;
    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < 4; column++)
        {
            tileType[index].x = column;
            tileType[index].y = row;
            index++;
        }
    }

    while(index <= 32)
    {
        tileType[index] = tileType[index - 16];
        index++;
    }

    //loads level depending on levelNumber
    if(levelNumber == 1)
    {
        file.loadMap("Load/level1.txt", mapVector);
        file.loadMap("Load/level1.1.txt", mapVector2);
    }
    else if(levelNumber == 2)
    {
        file.loadMap("Load/level2.txt", mapVector);
        file.loadMap("Load/level2.1.txt", mapVector2);
    }

    backgroundTexture.loadFromFile("Tiles/background.png");
    background.setTexture(backgroundTexture);
    background.setScale(2, 2);
}

void mapManager::unloadContent()
{
    mapVector.clear();
    tilesPrint.clear();
}

void mapManager::update(sf::RenderWindow &Window, sf::Vector2f viewPosition)
{
    background.setPosition(viewPosition.x - 400 - viewPosition.x/10, viewPosition.y - 400 - viewPosition.y/5);

    //determines tiles to draw
    int top = (viewPosition.y - 300)/32;
    int bottom = (viewPosition.y + 300)/32;
    int left = (viewPosition.x - 400)/32;
    int right = (viewPosition.x + 400)/32;

    tilesPrint.clear();

    for(int i = top; i <= bottom; i++)
    {
        for(int j = left; j <= right; j++)
        {
            tilesPrint.push_back(sf::Vector2i(j, i));
        }
    }
}

void mapManager::draw(sf::RenderWindow &Window)
{
    //draws the tiles for both layers
    Window.draw(background);
    for(int i = 0; i < tilesPrint.size(); i++)
    {
        if (mapVector[tilesPrint[i].y][tilesPrint[i].x] > 0)
        {
            if(mapVector[tilesPrint[i].y][tilesPrint[i].x] >= 17)
                tile.setTexture(secondarySheet);
            else
                tile.setTexture(primarySheet);
            sf::Vector2f tilePos = tileType[mapVector[tilesPrint[i].y][tilesPrint[i].x]];
            tile.setTextureRect(sf::IntRect(tilePos.x * BLOCKSIZE, tilePos.y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE));
            tile.setPosition(tilesPrint[i].x * BLOCKSIZE, tilesPrint[i].y * BLOCKSIZE);
            Window.draw(tile);
        }
    }

    if(mapVector2.size() > 0)
    {
        for(int i = 0; i < tilesPrint.size(); i++)
        {
            if (mapVector2[tilesPrint[i].y][tilesPrint[i].x] > 0)
            {
                if(mapVector2[tilesPrint[i].y][tilesPrint[i].x] >= 17)
                    tile.setTexture(secondarySheet);
                else
                    tile.setTexture(primarySheet);
                sf::Vector2f tilePos = tileType[mapVector2[tilesPrint[i].y][tilesPrint[i].x]];
                tile.setTextureRect(sf::IntRect(tilePos.x * BLOCKSIZE, tilePos.y * BLOCKSIZE, BLOCKSIZE, BLOCKSIZE));
                tile.setPosition(tilesPrint[i].x * BLOCKSIZE, tilesPrint[i].y * BLOCKSIZE);
                Window.draw(tile);
            }
        }
    }
}

std::vector< std::vector<int> > mapManager::getMapVector()
{
    return mapVector;
}
