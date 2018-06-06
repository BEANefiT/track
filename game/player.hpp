#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "game.h"

#define ISKEY sf::Keyboard::isKeyPressed
#define KEY sf::Keyboard::Key

#define PLAYER_LEFT( c )                                                                                                                            \
    scheme [(int) ((get_pos().y + get_height() / 2) / obj -> get_height())] [(int) ((get_pos().x - get_width() / 2) / obj -> get_width())] == c ||  \
    scheme [(int) ((get_pos().y + get_height() / 2) / obj -> get_height())] [(int) ((get_pos().x - get_width() / 2) / obj -> get_width())] == c

#define PLAYER_RIGHT( c )                                                                                                                           \
    scheme [(int) ((get_pos().y + get_height() / 2) / obj -> get_height())] [(int) ((get_pos().x + get_width() / 2) / obj -> get_width())] == c ||  \
    scheme [(int) ((get_pos().y + get_height() / 2) / obj -> get_height())] [(int) ((get_pos().x + get_width() / 2) / obj -> get_width())] == c

#define PLAYER_UP( c )                                                                                                                              \
    scheme [(int) ((get_pos().y + get_height() / 3) / obj -> get_height())] [(int) ((get_pos().x + get_width() / 3) / obj -> get_width())] == c ||  \
    scheme [(int) ((get_pos().y + get_height() / 3) / obj -> get_height())] [(int) ((get_pos().x - get_width() / 3) / obj -> get_width())] == c

#define PLAYER_DOWN( c )                                                                                                                            \
    scheme [(int) ((get_pos().y + get_height()) / obj -> get_height())] [(int) ((get_pos().x + get_width() / 3) / obj -> get_width())] == c ||  \
    scheme [(int) ((get_pos().y + get_height()) / obj -> get_height())] [(int) ((get_pos().x - get_width() / 3) / obj -> get_width())] == c

class player: public gameobj
{
    protected:
        float       _default_speed;
        float       _diag_speed;
        int         _hitpoints;

    public:
        player (sf::Texture& t, float x, float y):
    
            gameobj (1, t, x, y, 96, 96, 32, 32, 2, 8, 0.03),
    
            _default_speed  (0.3),
            _hitpoints      (100)
        {
            _diag_speed  = _default_speed / 1.41;
        };
    
        void move (float time) override
        {
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
    
        void respond (gameobj* obj) override
        {
            switch (obj -> get_type())
            {
                case map_:
                {
                    sf::String* scheme = obj -> get_scheme();
                    
                    if (_vx < 0)
                        if (PLAYER_LEFT( '0' ) || PLAYER_LEFT( 's' ))
                            _vx = 0;
                        
                    if (_vx > 0)
                        if (PLAYER_RIGHT( '0' ) || PLAYER_RIGHT( 's' ))
                            _vx = 0;
                    
                    if (_vy < 0)
                        if (PLAYER_UP( '0' ) || PLAYER_UP( 's' ))
                            _vy = 0;
                    
                    if (_vy > 0)
                        if (PLAYER_DOWN( '0' ) || PLAYER_DOWN( 's' ))
                            _vy = 0;
                    
                    break;
                }
                    
                case flower_:
                {
                    if (collide (obj))
                    {
                        _hitpoints -= 50;
                        
                        if (_hitpoints <= 0)
                            _life = false;
                    }
                    
                    break;
                }
            }
        }
    
        void check() override
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
    
        sf::String* get_scheme() override {}
};

#endif //__PLAYER_HPP__
