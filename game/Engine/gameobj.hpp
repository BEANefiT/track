#ifndef __GAMEOBJ_HPP__
#define __GAMEOBJ_HPP__

#include "engine.h"
#include "graphobj.hpp"
#include "physobj.hpp"

class gameobj: public graphobj, public physobj
{
public:
    void            upd (sf::RenderWindow&, float time);
    
    gameobj (   sf::Texture&,           float x, float y,
                float width_graph,      float height_graph,
                float width_phys,       float height_phys);
    
    gameobj (   sf::Texture&,           float x, float y,
                float width_graph,      float height_graph,
                float width_phys,       float height_phys,
                float frame_cur,        float frame_count,
                float animation_speed);

    gameobj (   sf::Texture&,           float x, float y,
                float width_graph,      float height_graph,
                float width_phys,       float height_phys,
                float vx, float vy,     float ax, float ay,
                enum direction dir);

    gameobj (   sf::Texture&,           float x, float y,
                float width_graph,      float height_graph,
                float width_phys,       float height_phys,
                float frame_cur,        float frame_count,
                float animation_speed,
                float vx, float vy,     float ax, float ay,
                enum direction dir);
    
    void            set_speed (enum direction, float);
    virtual void    move (float);
    virtual void    collide (gameobj*);
    virtual void    respond (gameobj*);
    virtual void    draw (sf::RenderWindow&);
};

void gameobj::upd(sf::RenderWindow& window, float time)
{
    move (time);
    draw (window);
}

#endif //__GAMEOBJ_HPP__
