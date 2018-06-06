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
    float           _frame_default;
    float           _frame_count;
    float           _frame_cur;
    float           _animation_speed;
    enum direction  _dir;
    
public:
    graphobj (sf::Texture&, float, float, float, float, float, float, float);
    graphobj (sf::Texture&, float, float, float, float, float, float, float, enum direction);
    
    void            set_pos (float, float);
    void            set_pos (struct vector);
    void            move (float, float);
    void            move (struct vector);
    void            stay();
    void            draw(sf::RenderWindow&);
};

graphobj::graphobj (sf::Texture& t, float x, float y, float width, float height,
                    float frame_default, float frame_count, float animation_speed):
    _x                  (x),
    _y                  (y),
    _width              (width),
    _height             (height),
    _frame_default      (frame_default),
    _frame_count        (frame_count),
    _frame_cur          (frame_default),
    _animation_speed    (animation_speed),
    _dir                (down)
{
    _sprite.setTexture  (t);
    _sprite.setPosition (x, y);
};

graphobj::graphobj (sf::Texture& t, float x, float y, float width, float height,
                    float frame_default, float frame_count, float animation_speed, enum direction dir):
    _x                  (x),
    _y                  (y),
    _width              (width),
    _height             (height),
    _frame_default      (frame_default),
    _frame_count        (frame_count),
    _frame_cur          (frame_default),
    _animation_speed    (animation_speed),
    _dir                (dir)
{
    _sprite.setTexture  (t);
    _sprite.setPosition (x, y);
}

void    graphobj::set_pos (float x, float y)
{
    _x = x;
    _y = y;
}

void    graphobj::set_pos (struct vector v)
{
    _x = v.x;
    _y = v.y;
}

void    graphobj::move (float dx, float dy)
{
    _x += dx;
    _y += dy;
    
    _frame_cur += _animation_speed;
    
    if (_frame_cur >= _frame_count)
        _frame_cur = 0;
    
    _sprite.setTextureRect  (sf::IntRect (_width * (int) _frame_cur, _height * _dir, _width, _height));
    _sprite.setPosition     (_x, _y);
}

void    graphobj::move (struct vector dv)
{
    _x += dv.x;
    _y += dv.y;
    
    _frame_cur += _animation_speed;
    
    if (_frame_cur >= _frame_count)
        _frame_cur = 0;
    
    _sprite.setTextureRect  (sf::IntRect (_width * (int) _frame_cur, _height * _dir, _width, _height));
    _sprite.setPosition     (_x, _y);
}

void    graphobj::stay()
{
    _sprite.setTextureRect (sf::IntRect (_width * _frame_default, _height * _dir, _width, _height));
}

void    graphobj::draw (sf::RenderWindow& window)
{
    window.draw (_sprite);
}

#endif //__GRAPHOBJ_HPP__
