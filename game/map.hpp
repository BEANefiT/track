#ifndef __MAP_H__
#define __MAP_H__

#include "gameobj.hpp"
#include <iostream>

class map: public gameobj
{
    protected:
        sf::Sprite  _sprite;
        sf::String  _legend;
        sf::String  _scheme;
        float       _block_sz;
        int         _block_count;
        int         _texture_width;
        int         _map_width;
        int         _map_height;

    public:
        map (   int width, int height, int count, float block_sz, sf::Texture* t,
                int texture_width, sf::String legend, sf::String scheme):

            gameobj (t, block_sz, block_sz, 0, 0, 0, 0, 0, 0),
            _scheme         (scheme),
            _legend         (legend),
            _block_sz       (block_sz),
            _block_count    (count),
            _texture_width  (texture_width),
            _map_width      (width),
            _map_height     (height)
        {};

        void draw (sf::RenderWindow* window)
        {
            for (int i = 0; i < _map_height; i++)
            {
                for (int j = 0; j < _map_width; j++)
                {
                    char tmp = _scheme [_map_height * i + j];

                    for (int k = 0; k < _block_count; k++)
                    {
                        if (_legend [k] == tmp)
                        {
                            _sprite.setTextureRect (sf::IntRect ( _block_sz * (k % _texture_width),
                                                                  _block_sz * (k / _texture_width),
                                                                  _block_sz,
                                                                  _block_sz                      ));

                            _sprite.setPosition (_block_sz * i, _block_sz * j);

                            window -> draw (_sprite);

                            break;
                        }
                    }
                }
            }
        }
        
        void check (enum sf::Keyboard::Key, enum sf::Keyboard::Key,
                            enum sf::Keyboard::Key, enum sf::Keyboard::Key) override {};

        void move (float) override {};
};        

#endif //__MAP_H__
