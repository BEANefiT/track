#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "gameobj.hpp"

class player: public gameobj
{
    protected:
        float       _default_speed;
        float       _diag_speed;

    public:
        player (sf::Texture* t, float x, float y):
            gameobj (t, 96, 96, x, y, 0, 0, 0, 0),
            _default_speed (0.1)
        {
            _diag_speed  = _default_speed / 1.41;
        };

        void move (float time) override
        {
            if (_vx == 0 && _vy == 0)
            {
                _sprite.setTextureRect (sf::IntRect (2 * _width, _dir * _height, _width, _height));
                return;
            }

            _x += _vx * time;
            _y += _vy * time;

            _sprite.move (_vx * time, _vy * time);
            _sprite.setTextureRect (sf::IntRect (   _width * (int)_frame_num,
                                                    _dir * _height,
                                                    _width,
                                                    _height                 ));
            _vx = 0;
            _vy = 0;

            _frame_num += 0.012;

            if (_frame_num >= 8)
                _frame_num = 1;
        }

        void draw (sf::RenderWindow* window)
        {
            window -> draw (_sprite);
        }

        virtual void check (enum sf::Keyboard::Key w, enum sf::Keyboard::Key a,
                            enum sf::Keyboard::Key s, enum sf::Keyboard::Key d) override
        {
            if (iskey (a))
            {
                if (iskey (w))  { speed (left_up,   _diag_speed); return; }
                    
                if (iskey (s))  { speed (left_down, _diag_speed); return; }

                speed (left, _default_speed);

                return;
            }

            if (iskey (d))
            {
                if (iskey (w))  { speed (right_up,   _diag_speed); return; }
                    
                if (iskey (s))  { speed (right_down, _diag_speed); return; }

                speed (right, _default_speed);

                return;
            }

            if (iskey (w))
            {
                speed (up, _default_speed);

                return;
            }

            if (iskey (s))
            {
                speed (down, _default_speed);

                return;
            }
        }
};

#endif //__PLAYER_HPP__
