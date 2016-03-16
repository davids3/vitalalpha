#ifndef FADEANIMATION_H
#define FADEANIMATION_H

#include "Animation.h"

class fadeAnimation : public animation//fade animation class, inherits from animation
{
    public:
        fadeAnimation();
        ~fadeAnimation();

        void loadContent(std::string text, sf::Image &image, sf::Vector2f position);
        void loadContent(std::string text, sf::Image &image, sf::Vector2f position, std::string font);
        void unloadContent();
        void update(sf::RenderWindow &Window);
        void draw(sf::RenderWindow &Window);

        void setAlpha(float value);
        void setFadeSpeed (float value);
    protected:
    private:
        bool increase;//for determining if the animation should be fading in or out
        float fadeSpeed;
        std::string font;
};

#endif // FADEANIMATION_H
