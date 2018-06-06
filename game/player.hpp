#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "game.h"

#define ISKEY sf::Keyboard::isKeyPressed
#define KEY sf::Keyboard::Key

class player: public gameobj
{
    protected:
        float       _default_speed;
        float       _diag_speed;

    public:
        player (sf::Texture& t, float x, float y):
    
            gameobj (1, t, x, y, 96, 96, 32, 32, 2, 8, 0.03),
    
            _default_speed (0.3)
        {
            _diag_speed  = _default_speed / 1.41;
        };

        void check();
    
        void move (float time) override
        {
            check();
            
            if (_vx == 0 && _vy == 0)
            {
                stay();
                
                return;
            }
            
            struct vector df (_vx * time, _vy * time);
            
            graphobj::  move (df);
            physobj::   move (df);

            _vx = 0;
            _vy = 0;
        }

        void draw (sf::RenderWindow& window) override
        {
            graphobj::draw (window);
        }
    
        void collide (gameobj* obj) override
        {
            switch (obj -> get_type())
            {
                case 0:
                {
                    
                }
            }
        }
};

void player::check()
{
    if (ISKEY (KEY::A))
    {
        if (ISKEY (KEY::W))  { set_speed (left_up,   -_diag_speed, -_diag_speed); return; }
        
        if (ISKEY (KEY::S))  { set_speed (left_down, -_diag_speed,  _diag_speed); return; }
        
        set_speed (left, -_default_speed, 0);
        
        return;
    }
    
    if (ISKEY (KEY::D))
    {
        if (ISKEY (KEY::W))  { set_speed (right_up,   _diag_speed, -_diag_speed); return; }
        
        if (ISKEY (KEY::S))  { set_speed (right_down, _diag_speed,  _diag_speed); return; }
        
        set_speed (right, _default_speed, 0);
        
        return;
    }
    
    if (ISKEY (KEY::W))
    {
        set_speed (up, 0, -_default_speed);
        
        return;
    }
    
    if (ISKEY (KEY::S))
    {
        set_speed (down, 0, _default_speed);
        
        return;
    }
}

#endif //__PLAYER_HPP__
