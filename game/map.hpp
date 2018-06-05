#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "gameobj.hpp"

struct legend_t
{
    char*           chars;
    struct vector*  pos;

    legend_t (char* a, struct vector* b):
        chars   (a),
        pos     (b)
    {};
};

class map: public gameobj
{
    protected:
        sf::String*     _scheme;
        float           _block_sz;
        int             _map_width;
        int             _map_height;

    public:
        map (int width, int height, float block_sz, sf::Texture* t, const char* level, sf::String* scheme):

            gameobj (t, block_sz, block_sz, 0, 0, 0, 0, 0, 0),
            _scheme         (scheme),
            _block_sz       (block_sz),
            _map_width      (width),
            _map_height     (height)
        {};

        void draw (sf::RenderWindow* window)
        {
            for (int i = 0; i < _map_height; i++)
            {
                for (int j = 0; j < _map_width; j++)
                {
                    #define DEF_TILE( c, x, y )                                                 \
                        case c:                                                                 \
                        {                                                                       \
                            _sprite.setTextureRect (sf::IntRect (x, y, _block_sz, _block_sz));  \
                                                                                                \
                            _sprite.setPosition (_block_sz * j, _block_sz * i);                 \
                                                                                                \
                            window -> draw (_sprite);                                           \
                                                                                                \
                            break;                                                              \
                        }

                    switch (_scheme [i][j])
                    {
                        #include "level"
                    }

                    #undef DEF_TILE
                }
            }
        }
        
        void check (enum sf::Keyboard::Key, enum sf::Keyboard::Key,
                            enum sf::Keyboard::Key, enum sf::Keyboard::Key) override {};

        void move (float) override {};
};        

#endif //__MAP_HPP__
