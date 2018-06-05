#ifndef __GAMEOBJ_HPP__

#define __GAMEOBJ_HPP__

#include <SFML/Graphics.hpp>

#define iskey sf::Keyboard::isKeyPressed

enum direction
{
    left_down   = 5,
    down        = 4,
    right_down  = 3,
    left        = 6,
    left_up     = 7,
    right       = 2,
    right_up    = 1,
    up          = 0
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
 
class gameobj
{
    protected:
        sf::Sprite      _sprite;
        float           _frame_num;
        float           _width;
        float           _height;
        float           _x;
        float           _y;
        float           _vx;
        float           _vy;
        float           _ax;
        float           _ay;
        enum direction  _dir;
       
    public:      
        void            upd (sf::RenderWindow*, float time);
        void            speed (enum direction, float v);
        struct vector   getPosition ();
        struct vector   getSpeed ();
        struct vector   getAcceleration ();

        virtual void move (float time)          = 0;
        virtual void draw (sf::RenderWindow*)   = 0;

        gameobj (   sf::Texture* texture, float width, float height, float x, float y,
                    float vx, float vy, float ax, float ay):
            _frame_num      (0),
            _width          (width),
            _height         (height),
            _x              (x),
            _y              (y),
            _vx             (vx),
            _vy             (vy),
            _ax             (ax),
            _ay             (ay),
            _dir            (down)

        {
            _sprite.setTexture (*texture);
            _sprite.setPosition (_x, _y);
        }

        virtual void check (enum sf::Keyboard::Key, enum sf::Keyboard::Key,
                            enum sf::Keyboard::Key, enum sf::Keyboard::Key) = 0;
};

void gameobj::upd(sf::RenderWindow* window, float time)
{
    move (time);
    draw (window);
}

void gameobj::speed (enum direction dir, float v)
{
    _dir = dir;

    switch (dir)
    {
        case down:       { _vy =  v;           break; }

        case left:       { _vx = -v;           break; }

        case right:      { _vx =  v;           break; }

        case up:         { _vy = -v;           break; }

        case right_up:   { _vy = -v; _vx =  v; break; }
    
        case right_down: { _vy =  v; _vx =  v; break; }

        case left_up:    { _vy = -v; _vx = -v; break; }

        case left_down:  { _vy =  v; _vx = -v; break; }
    }
}

struct vector gameobj::getPosition ()
{
    return vector (_x, _y);
}

struct vector gameobj::getSpeed ()
{
    return vector (_vx, _vy);
}

struct vector gameobj::getAcceleration ()
{
    return vector (_ax, _ay);
}

#endif //__GAMEOBJ_HPP__
