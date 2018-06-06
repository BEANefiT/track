#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SFML/Graphics.hpp>

enum direction
{
    up          = 0,
    right_up    = 1,
    right       = 2,
    right_down  = 3,
    down        = 4,
    left_down   = 5,
    left        = 6,
    left_up     = 7
};

struct vector
{
    float x;
    float y;
    
    vector (float a, float b):
    x (a),
    y (b)
    {};
};

#endif //__ENGINE_H__
