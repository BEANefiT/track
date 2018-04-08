#ifndef __STACK_BSTACK_H__
#define __STACK_BSTACK_H__

#include <cstddef>

template <typename data_T>

class bstack
{
public:
    bstack ();
    ~bstack ();

    data_T  pop ();
    data_T  top ();

    bool    push (data_T val);

    size_t  size ();

    bool    check ();

private:
    size_t  _size;
    size_t  _capacity;

    data_T*  _data;

    void    _resize (size_t new_sz);
};

#include "bstack.hpp"

#endif //__STACK_BSTACK_H__
