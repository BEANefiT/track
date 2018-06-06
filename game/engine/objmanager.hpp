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
    
        void    run();
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

void    objmanager::run()
{
    blist <gameobj*> :: blist_elem* obj_ptr1 = _objs -> get_head();
    blist <gameobj*> :: blist_elem* obj_ptr2 = obj_ptr1 -> get_next();
    
    for (int i = 0; i < _objs -> size(); i++)
    {
        gameobj* obj1 = obj_ptr1 -> get_elem();
        
        for (int j = i + 1; j < _objs -> size(); j++)
        {
            gameobj* obj2 = obj_ptr2 -> get_elem();
            
            obj1 -> collide (obj2);
            obj2 -> collide (obj1);
            
            obj_ptr2 = obj_ptr2 -> get_next();
        }
        
        obj1 -> upd();
            
        blist <gameobj*>* tmp = obj_ptr1 -> get_next();
        
        if (!(obj1 -> isAlive()))
            rm (obj_ptr1);
        
        obj_ptr1 = tmp;
    }
}

#endif //__OBJMANAGER_HPP__
