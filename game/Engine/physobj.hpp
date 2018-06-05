#ifndef __PHYSOBJ_HPP__
#define __PHYSOBJ_HPP__

#include "engine.h"

class physobj
{
protected:
    float _x;
    float _y;
    float _vx;
    float _vy;
    float _ax;
    float _ay;
    float _width;
    float _height;
    
public:
    physobj (float x, float y, float width, float height);
    physobj (float x, float y, float width, float height, float vx, float vy);
    physobj (float x, float y, float width, float height, float vx, float vy, float ax, float ay);
    
    void    set_pos (float, float);
    void    set_pos (struct vector);
    void    move (float, float);
    void    move (struct vector);
    
    void    set_speed (float, float);
    void    set_speed (struct vector);
    void    change_speed (float, float);
    void    change_speed (struct vector);
    
    void    set_acceleration (float, float);
    void    set_acceleration (struct vector);
    void    change_acceleration (float, float);
    void    change_acceleration (struct vector);
};


#endif //__PHYSOBJ_HPP__
