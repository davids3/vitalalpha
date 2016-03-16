#include "playerManager.h"

enum direction { LEFT, RIGHT };

playerManager::playerManager()
{
    //ctor
}

playerManager::~playerManager()
{
    //dtor
}

void playerManager::loadContent()
{
    jump = attacking = standAttack = false;
    position.x = position.y = 100;
    velocity.x = velocity.y = 0;

    file.loadContent("Load/player.txt", attributes, contents);
    character::loadContent();

    imageNumber = 0;
    lastDirection = RIGHT;
}

void playerManager::unloadContent()
{
    tiles.clear();
    images.clear();
    character::unloadContent();
}

void playerManager::updateMovement(inputManager input)
{
    if(standAttack == false)
    {
        if((input.keyDown(sf::Keyboard::Right) && input.keyDown(sf::Keyboard::Left))
           || (input.keyDown(sf::Keyboard::D) && input.keyDown(sf::Keyboard::A)))
            velocity.x = 0;
        else if(input.keyDown(sf::Keyboard::Right) || input.keyDown(sf::Keyboard::D))
            velocity.x = moveSpeed;
        else if(input.keyDown(sf::Keyboard::Left) || input.keyDown(sf::Keyboard::A))
            velocity.x = -moveSpeed;
        else if(jump)
        {
            if(velocity.x > 0.1)
                velocity.x -= slide;
            else if(velocity.x < -0.1)
                velocity.x += slide;
            else if(velocity.x <= 0.1 || velocity.x >= -0.1)
                velocity.x = 0;
        }
    }

    if((input.keyDown(sf::Keyboard::Up) || input.keyDown(sf::Keyboard::W)) && jump)
    {
        velocity.y = -jumpSpeed;
        jump = false;
        standAttack = false;
    }
    if(input.keyDown(sf::Keyboard::Space) && jump == true)
    {
        attacking = true;
    }
    else
        attacking = false;
}

void playerManager::updateCollision(std::vector< std::vector<int> > colVector, std::vector<bullet*> &bullets,
                                    std::vector<collectable*> &packs, std::vector<turret*> &turrets,
                                    float &healthValue, float &energyValue, int &score)
{
    bottom = position.y;//finds the current dimensions of the sprite
    left = position.x - 23;
    right = position.x + 21;
    top = position.y - texture.getSize().y;

    tiles.clear();

    int upperLimit = top / BLOCKSIZE;//fixes crash on exit screen at top
    while(upperLimit < 0)
        upperLimit++;

    int lowerLimit = bottom / BLOCKSIZE;//fixes crash on exit screen at bottom
    while(lowerLimit > colVector.size() - 1)
        lowerLimit--;

    for(int i = upperLimit; i <= lowerLimit; i++)
    {
        for(int j = left / BLOCKSIZE; j <= right / BLOCKSIZE; j++)
            tiles.push_back(sf::Vector2i(j, i));
    }

    for(int i = 0; i < tiles.size(); i++)
    {
        if((colVector[tiles[i].y][tiles[i].x] > 0 && colVector[tiles[i].y][tiles[i].x] < 4)
           || colVector[tiles[i].y][tiles[i].x] == 21 || colVector[tiles[i].y][tiles[i].x] == 22
           || colVector[tiles[i].y][tiles[i].x] == 24)//restricts for platform tiles
        {
            int tileBottom, tileTop, tileLeft, tileRight;
            tileBottom = tiles[i].y * BLOCKSIZE + BLOCKSIZE;
            tileTop = tiles[i].y * BLOCKSIZE;
            tileRight = tiles[i].x * BLOCKSIZE + BLOCKSIZE;
            tileLeft = tiles[i].x * BLOCKSIZE;

            int bCollision, tCollision, lCollision, rCollision;
            bCollision = tileBottom - top;
            tCollision = bottom - tileTop;
            lCollision = right - tileLeft;
            rCollision = tileRight - left;

            if(velocity.y >= 0)
            {
                if(lCollision < rCollision && lCollision < tCollision && lCollision < bCollision)
                {
                    if(velocity.x > 0)
                        velocity.x = 0;
                    position.x = tileLeft - 21;
                }

                if(rCollision < lCollision && rCollision < tCollision && rCollision < bCollision)
                {
                    if(velocity.x < 0)
                        velocity.x = 0;
                    position.x = tileRight + 21;
                }

                if(tCollision < bCollision && tCollision < lCollision && tCollision < rCollision)
                {
                    jump = true;
                    position.y = tileTop;
                    break;
                }
            }
        }
        else
            jump = false;
    }

    if(!jump)
        velocity.y += gravity;
    else
        velocity.y = 0;

    position += velocity;

    if(position.x < 0)
        position.x = 0;
    else if(position.x > (colVector[0].size() - 1) * 32)
        position.x = (colVector[0].size() - 1) * 32;

    for(int i = 0; i < bullets.size(); i++)
    {
        if(bullets[i]->getPosition().x > left && bullets[i]->getPosition().x < right
           && bullets[i]->getPosition().y > top && bullets[i]->getPosition().y < bottom)
        {
            healthValue -= 25;
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            continue;
        }
    }
    for(int i = 0; i < packs.size(); i++)
    {
        if(packs[i]->getPosition().x > left && packs[i]->getPosition().x < right
           && packs[i]->getPosition().y > top && packs[i]->getPosition().y <= bottom)
        {
            //dynamic_cast is used to check the pack type, if it is not the one quiried it returns NULL
            if(dynamic_cast<healthPack*> (packs[i]) != NULL)
            {
                healthValue += 20;
                score += 20;
            }
            else if(dynamic_cast<energyPack*> (packs[i]) != NULL)
            {
                energyValue += 30;
                score += 20;
            }
            delete packs[i];
            packs.erase(packs.begin() + i);
            continue;
        }
    }
    if (imageNumber == 8 || imageNumber == 16)
    {
        for(int i = 0; i < turrets.size(); i++)
        {
            sf::Vector2f bladePosition;
            bladePosition.y = position.y - 30;
            if(imageNumber == 8)
            {
                if(lastDirection == LEFT)
                    bladePosition.x = position.x - 47;
                else
                    bladePosition.x = position.x + 47;
            }
            if(imageNumber == 16)
            {
                if(lastDirection == LEFT)
                    bladePosition.x = position.x - 43;
                else
                    bladePosition.x = position.x + 43;
            }

            float turretLeft = turrets[i]->getPosition().x - 45;
            float turretRight = turrets[i]->getPosition().x + 45;
            float turretTop = turrets[i]->getPosition().y - 64;
            float turretBottom = turrets[i]->getPosition().y;

            if(bladePosition.x < turretRight && bladePosition.x > turretLeft
               && bladePosition.y > turretTop && bladePosition.y < turretBottom)
            {
                delete turrets[i];
                turrets.erase(turrets.begin() + i);
                score += 100;
                continue;
            }
        }
    }
}

void playerManager::updateAnimation(sf::RenderWindow &Window, float &energyValue)
{
    if(velocity.y == 0)//choosing images depending on velocity
    {
        if(velocity.x == 0)
            imageNumber = 0;
        else if(abs(velocity.x) == moveSpeed)
            imageNumber = 9;
        else if(abs(velocity.x) <= moveSpeed/3)
            imageNumber = 12;
        else if(abs(velocity.x) <= moveSpeed/3 * 2)
            imageNumber = 11;
        else if(abs(velocity.x) < moveSpeed)
            imageNumber = 10;
    }
    else
    {
        if(velocity.y >= jumpSpeed/2)
            imageNumber = 6;
        else if(velocity.y >= 0)
            imageNumber = 5;
        else if(velocity.y >= -jumpSpeed/2)
            imageNumber = 4;
        else if(velocity.y >= -jumpSpeed/4 * 3)
            imageNumber = 3;
        else if(velocity.y >= -jumpSpeed)
            imageNumber = 2;
    }

    if(attacking == true)
    {
        if(velocity.x == 0)
            standAttack = true;
        else if(abs(velocity.x) == 3 && energyValue > 0)
        {
            imageNumber = 8;
            energyValue -= 0.4f;
        }
    }

    if (standAttack == true && energyValue >= 5)
    {
        if(cycle == 0)
            imageNumber = 14;
        else if(cycle == 1)
            imageNumber = 17;
        else if(cycle == 2)
            imageNumber = 15;
        else if(cycle == 3)
            imageNumber = 16;

        if(timer.getElapsedTime().asSeconds() > 0.1f)
        {
            if(cycle == 3)
            {
                decrease = true;
                energyValue -= 10;
            }

            if(cycle == 0 && decrease == true)
            {
                standAttack = false;
                decrease = false;
            }

            if(decrease == false)
                cycle++;
            else
                cycle--;

            timer.restart();
        }
    }
    else
    {
        standAttack = false;
        cycle = 0;
    }

    if(lastNumber != imageNumber)//load new image if it has changed
    {
        texture.loadFromImage(images[imageNumber]);
        sprite.setTexture(texture);
    }

    if(velocity.x == 0)//idle animation direction
    {
        if(lastDirection == LEFT)
        {
            sprite.setTextureRect(sf::IntRect(texture.getSize().x, 0, -texture.getSize().x, texture.getSize().y));
            sprite.setOrigin(texture.getSize().x - origins[imageNumber].x, origins[imageNumber].y);
        }
        else if(lastDirection == RIGHT)
        {
            sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
            sprite.setOrigin(origins[imageNumber]);
        }
    }
    else if(velocity.x < 0)//moving left
    {
        sprite.setTextureRect(sf::IntRect(texture.getSize().x, 0, -texture.getSize().x, texture.getSize().y));
        sprite.setOrigin(texture.getSize().x - origins[imageNumber].x, origins[imageNumber].y);
        lastDirection = LEFT;
    }
    else if(velocity.x > 0)//moving right
    {
        sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
        sprite.setOrigin(origins[imageNumber]);
        lastDirection = RIGHT;
    }

    sprite.setPosition(position);
    lastNumber = imageNumber;
}

void playerManager::draw(sf::RenderWindow &Window)
{
    Window.draw(sprite);
}
