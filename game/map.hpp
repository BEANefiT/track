#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "game.h"

class map: public gameobj
{
    protected:
        sf::String*     _scheme;
        int             _map_width;
        int             _map_height;

    public:
        map (int width, int height, float block_sz,
             sf::Texture& t, sf::String* scheme):

            gameobj (0, t, 0, 0, block_sz, block_sz, block_sz, block_sz),
    
            _scheme         (scheme),
            _map_width      (width),
            _map_height     (height)
        {};

        void draw (sf::RenderWindow& window) override
        {
            _sprite.setPosition (0, 0);
            
            for (int i = 0; i < _map_height; i++)
            {
                for (int j = 0; j < _map_width; j++)
                {
                    #define DEF_TILE( c, x, y )                                                 \
                        case c:                                                                 \
                        {                                                                       \
                            _sprite.setTextureRect (sf::IntRect (   x, y,                       \
                                                                    graphobj::_width,           \
                                                                    graphobj::_height));        \
                                                                                                \
                            graphobj::draw (window);                                            \
                                                                                                \
                            _sprite.move (graphobj::_width, 0);                                 \
                                                                                                \
                            break;                                                              \
                        }

                    switch (_scheme [i][j])
                    {
                        #include "level"
                    }

                    #undef DEF_TILE
                }

                _sprite.move (-_map_width * graphobj::_width, graphobj::_height);
            }
        }
    
        void move (float)           override {};

        void respond (gameobj*)     override {};
    
        void check()                override {};
    
        sf::String* get_scheme()    override { return _scheme; }
};

#endif //__MAP_HPP__
