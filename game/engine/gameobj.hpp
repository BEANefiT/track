#ifndef __GAMEOBJ_HPP__
#define __GAMEOBJ_HPP__

#include "engine.h"
#include "graphobj.hpp"
#include "physobj.hpp"

class gameobj: public graphobj, public physobj
{
    private:
        bool    _life;
        int     _type;
    
    public:
        gameobj (   int, sf::Texture&,      float x, float y,
                    float width_graph,      float height_graph,
                    float width_phys,       float height_phys);
    
        gameobj (   int, sf::Texture&,      float x, float y,
                    float width_graph,      float height_graph,
                    float width_phys,       float height_phys,
                    float frame_default,    float frame_count,
                    float animation_speed);

        gameobj (   int, sf::Texture&,      float x, float y,
                    float width_graph,      float height_graph,
                    float width_phys,       float height_phys,
                    float vx, float vy,     float ax, float ay,
                    enum direction dir);

        gameobj (   int, sf::Texture&,      float x, float y,
                    float width_graph,      float height_graph,
                    float width_phys,       float height_phys,
                    float frame_default,    float frame_count,
                    float animation_speed,
                    float vx, float vy,     float ax, float ay,
                    enum direction dir);
    
        void            upd (sf::RenderWindow&, float time);
        void            set_speed (enum direction, float);
        bool            isAlive();
        virtual void    move (float time);
        virtual void    collide (gameobj*);
        virtual void    draw (sf::RenderWindow&);
};

gameobj::gameobj (  int type, sf::Texture& t,   float x, float y,
                    float width_graph,          float height_graph,
                    float width_phys,           float height_phys):

    graphobj    (t, x, y, width_graph, height_graph, 0, 0, 0),

    physobj     (x + width_graph / 2, y + height_graph / 2,
                 width_phys, height_phys),

    _life       (true),
    _type       (type)
{}

gameobj::gameobj (  int type, sf::Texture& t,   float x, float y,
                    float width_graph,          float height_graph,
                    float width_phys,           float height_phys,
                    float frame_default,        float frame_count,
                    float animation_speed):

    graphobj    (t, x, y, width_graph, height_graph,
                 frame_default, frame_count, animation_speed),

    physobj     (x + width_graph / 2, y + height_graph / 2,
                 width_phys, height_phys),

    _life       (true),
    _type       (type)
{}

gameobj::gameobj (  int type, sf::Texture& t,   float x, float y,
                    float width_graph,          float height_graph,
                    float width_phys,           float height_phys,
                    float vx, float vy,         float ax, float ay,
                    enum direction dir):

    graphobj    (t, x, y, width_graph, height_graph, 0, 0, 0, dir),

    physobj     (x + width_graph / 2, y + height_graph / 2,
                 width_phys, height_phys, vx, vy, ax, ay),

    _life       (true),
    _type       (type),
{}

gameobj::gameobj (  int type, sf::Texture& t,   float x, float y,
                    float width_graph,          float height_graph,
                    float width_phys,           float height_phys,
                    float frame_default,        float frame_count,
                    float animation_speed,      float vx, float vy,
                    float ax, float ay          enum direction dir):

    graphobj    (t, x, y, width_graph, height_graph,
                 frame_default, frame_count, animation_speed, dir),

    physobj     (x + width_graph / 2, y + height_graph / 2,
                 width_phys, height_phys, vx, vy, ax, ay),

    _life       (true),
    _type       (type)
{}

void    gameobj::upd(sf::RenderWindow& window, float time)
{
    move (time);
    draw (window);
}

bool    gameobj::isAlive()
{
    return _life;
}

void    gameobj::set_speed (enum direction dir, float v)
{
    _dir = dir;
    _vx = v;
    _vy = v;
}

#endif //__GAMEOBJ_HPP__
