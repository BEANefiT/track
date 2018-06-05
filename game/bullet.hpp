#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include "gameobj.hpp"

class bullet: public gameobj
{
    public:
        bullet (sf::Texture* t, float x, float y, float width, float height, float vx, float vy):
            gameobj (t, width, height, x, y, vx, vy, 0, 0)
        {};

        void move (float time) override
        {
            _x += _vx * time;
            _y += _vy * time;

            _sprite.setPosition (_x, _y);
            _sprite.setTextureRect (sf::IntRect (37, 10, _width, _height));
        }
        
        void draw (sf::RenderWindow* window)
        {
            window -> draw (_sprite);
        }

        void check (enum sf::Keyboard::Key, enum sf::Keyboard::Key,
                    enum sf::Keyboard::Key, enum sf::Keyboard::Key)
        {};
};

#endif //__BULLET_HPP__
