#ifndef __HEART_HPP__
#define __HEART_HPP__

#include "game.h"

class heart: public gameobj
{
protected:
    int     _health;
    
public:
    heart (sf::Texture& t, float x, float y, int hp):
        gameobj (3, t, x, y, 32, 32, 24, 24, 4, 5, 0, 0, 0, 0, 0, up),
    
        _health (hp)
    {};
    
    int         get_damage()                        override
    {
        return _health;
    }
    
    void        draw (sf::RenderWindow& window)     override
    {
        graphobj::draw (window);
    }
    
    void        respond (gameobj* obj)              override
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
    
    void            check()                         override {};
    void            move (float time)               override {};
    sf::String*     get_scheme()                    override {};
};


#endif //__HEART_HPP__
