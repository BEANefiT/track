#ifndef __GRAPHOBJ_HPP__
#define __GRAPHOBJ_HPP__

#include "engine.h"

class graphobj
{
protected:
    sf::Sprite      _sprite;
    float           _x;
    float           _y;
    float           _width;
    float           _height;
    float           _frame_cur;
    float           _frame_count;
    float           _animation_speed;
    enum direction  _dir;
    
public:
    graphobj (sf::Texture&, float, float, float, float, float, float, float);
    graphobj (sf::Texture&, float, float, float, float, float, float, float, enum direction);
    
    void    set_pos (float, float);
    void    set_pos (struct vector);
    void    move (float, float);
    void    move (struct vector);
};


#endif //__GRAPHOBJ_HPP__
