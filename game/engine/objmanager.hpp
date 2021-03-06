#ifndef __OBJMANAGER_HPP__
#define __OBJMANAGER_HPP__

#include "engine.h"
#include "gameobj.hpp"
#include "../../blist/blist.hpp"

class objmanager
{
    private:
        blist <gameobj*>*   _objs;
    public:
        objmanager ();
        ~objmanager();
    
        void    create (gameobj*);
    
        void    run (sf::RenderWindow&, float time);
};

objmanager::objmanager ()
{
    _objs = new blist <gameobj*> ();
};

objmanager::~objmanager()
{
    _objs -> erase();
}

void    objmanager::create (gameobj* object)
{
    _objs -> push_back (object);
}

void    objmanager::run (sf::RenderWindow& window, float time)
{
    blist <gameobj*> :: blist_elem* obj_ptr1 = _objs -> get_head();
    blist <gameobj*> :: blist_elem* obj_ptr  = obj_ptr1;
    
    for (int i = 0; i < _objs -> size(); i++)
    {
        obj_ptr -> get_elem() -> check();
        obj_ptr = obj_ptr -> get_next();
    }
    
    for (int i = 0; i < _objs -> size(); i++)
    {
        blist <gameobj*> :: blist_elem* obj_ptr2 = obj_ptr1 -> get_next();
        
        gameobj* obj1 = obj_ptr1 -> get_elem();
        
        for (int j = i + 1; j < _objs -> size(); j++)
        {
            gameobj* obj2 = obj_ptr2 -> get_elem();
            
            obj1 -> respond (obj2);
            obj2 -> respond (obj1);
            
            obj_ptr2 = obj_ptr2 -> get_next();
        }
        
        obj1 -> upd (window, time);
            
        blist <gameobj*> :: blist_elem* tmp = obj_ptr1 -> get_next();
        
        if (!(obj1 -> isAlive()))
            _objs -> rm_elem(obj_ptr1);
        
        obj_ptr1 = tmp;
    }
}

#endif //__OBJMANAGER_HPP__
