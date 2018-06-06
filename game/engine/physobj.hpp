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
    physobj (float x, float y, float width, float height, float vx, float vy, float ax, float ay);
    
    void            set_pos (float, float);
    void            set_pos (struct vector);
    void            move (float, float);
    void            move (struct vector);
    
    void            set_speed (float, float);
    void            set_speed (struct vector);
    void            change_speed (float, float);
    void            change_speed (struct vector);
    
    void            set_acceleration (float, float);
    void            set_acceleration (struct vector);
    void            change_acceleration (float, float);
    void            change_acceleration (struct vector);
    
    struct vector   get_pos();
    float           get_width();
    float           get_height();
};

physobj::physobj (float x, float y, float width, float height):
    _x      (x),
    _y      (y),
    _width  (width),
    _height (height)
{}

physobj::physobj (float x, float y, float width, float height, float vx, float vy, float ax, float ay):
    _x      (x),
    _y      (y),
    _width  (width),
    _height (height),
    _vx     (vx),
    _vy     (vy),
    _ax     (ax),
    _ay     (ay)
{}

#define SET( name, param1, param2, v, operand1, operand2)   \
    void    physobj:: name (float param1, float param2)     \
    {                                                       \
        operand1 = param1;                                  \
        operand2 = param2;                                  \
    }                                                       \
                                                            \
    void    physobj:: name (struct vector v)                \
    {                                                       \
        operand1 = v.x;                                   \
        operand2 = v.y;                                   \
    }

#define CHANGE( name, param1, param2, v, operand1, operand2)\
    void    physobj:: name (float param1, float param2)     \
    {                                                       \
        operand1 += param1;                                 \
        operand2 += param2;                                 \
    }                                                       \
                                                            \
    void    physobj:: name (struct vector v)                \
    {                                                       \
        operand1 += v.x;                                  \
        operand2 += v.y;                                  \
    }

SET     (set_pos, x,  y,  r,  _x, _y);
CHANGE  (move,    dx, dy, dr, _x, _y);

SET     (set_speed,    vx,  vy,  v,  _vx, _vy);
CHANGE  (change_speed, dvx, dvy, dv, _vx, _vy);

SET     (set_acceleration,    ax,  ay,  a,  _ax, _ay);
CHANGE  (change_acceleration, dax, day, da, _ax, _ay);

#undef SET
#undef CHANGE

struct vector   physobj::get_pos()
{
    struct vector v (_x, _y);
    
    return v;
}

float   physobj::get_width()
{
    return _width;
}

float   physobj::get_height()
{
    return _height;
}

#endif //__PHYSOBJ_HPP__
