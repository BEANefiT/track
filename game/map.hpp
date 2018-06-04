#ifndef __MAP_H__
#define __MAP_H__

#include "gameobj.hpp"

class map: public gameobj
{
    protected:
        sf::String _scheme;

    public:
        map (sf::Texture* t, sf::String scheme):
            gameobj (t, res, res, 0, 0, 0, 0, 0, 0),
            _scheme (scheme)
        {};

        void draw (sf::RenderWindow* window)
        {
            
        }

}        
