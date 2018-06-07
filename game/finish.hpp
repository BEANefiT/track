#ifndef __FINISH_HPP__
#define __FINISH_HPP__

#include "game.h"

class finish: public gameobj
{
public:
    finish (sf::Texture& t, float x, float y):
        gameobj (4, t, x, y, 32, 32, 24, 24, 5, 6, 0, 0, 0, 0, 0, up)
    {};
    
    void            draw (sf::RenderWindow& window)     override
    {
        graphobj::draw (window);
    }
    
    void            respond (gameobj* obj)              override
    {
        switch (obj -> get_type())
        {
            case player_:
            {
                if (collide (obj))
                    _life = false;
                
                break;
            }
        }
    }
    
    int             get_damage()                        override {};
    void            check()                             override {};
    void            move (float time)                   override {};
    sf::String*     get_scheme()                        override {};
};

#endif //__FINISH_HPP__
