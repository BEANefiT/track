#ifndef __FLOWER_HPP__
#define __FLOWER_HPP__

#include "game.h"

class flower: public gameobj
{
protected:
    int     _damage;
    
public:
    flower (sf::Texture& t, float x, float y, int dmg):
        gameobj (2, t, x, y, 32, 32, 24, 24, 3, 4, 0, 0, 0, 0, 0, up),
    
        _damage (dmg)
    {};
    
    int             get_damage()                    override
    {
        return _damage;
    }
    
    void            draw (sf::RenderWindow& window) override
    {
        graphobj::draw (window);
    }
    
    void            respond (gameobj* obj)          override
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

#endif //__FLOWER_HPP__
