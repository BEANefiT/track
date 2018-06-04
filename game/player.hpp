#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "gameobj.hpp"

class player: public gameobj
{
    protected:
        float default_speed;
        float diag_speed;

    public:
        player (sf::Texture* t, float x, float y):
            gameobj (t, 96, 96, x, y, 0, 0, 0, 0),
            default_speed (0.1)
        {
            diag_speed = default_speed / 1.41;
            sprite.setTexture (*t);
            sprite.setPosition (_x, _y);
        };

        void move(float time) override
        {
            if (_vx == 0 && _vy == 0)
            {
                sprite.setTextureRect (sf::IntRect (2 * _width, _dir * _height, _width, _height));
                return;
            }

            sprite.move (_vx * time, _vy * time);
            sprite.setTextureRect (sf::IntRect (_width * (int)_frame_num, _dir * _height, _width, _height));
            _vx = 0;
            _vy = 0;

            _frame_num += 0.01;

            if (_frame_num > 8)
                _frame_num = 1;
        }

        virtual void check (enum sf::Keyboard::Key w, enum sf::Keyboard::Key a, enum sf::Keyboard::Key s, enum sf::Keyboard::Key d) override
        {
            if (iskey (a))
            {
                if (iskey (w))  { speed (left_up, diag_speed); return; }
                    
                if (iskey (s))  { speed (left_down, diag_speed); return; }

                speed (left, default_speed);

                return;
            }

            if (iskey (d))
            {
                if (iskey (w))  { speed (right_up, diag_speed); return; }
                    
                if (iskey (s))  { speed (right_down, diag_speed); return; }

                speed (right, default_speed);

                return;
            }

            if (iskey (w))
            {
                speed (up, default_speed);

                return;
            }

            if (iskey (s))
            {
                speed (down, default_speed);

                return;
            }
        }
};

#endif //__PLAYER_HPP__
