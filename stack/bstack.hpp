//#ifdef __STACK_BSTACK_H__

#ifndef __STACK_BSTACK_HPP__
#define __STACK_BSTACK_HPP__

#include <iostream>
#include "bstack.h"

template <typename data_T>
bstack <data_T> :: bstack () :
    _size (0),
    _capacity (1),
    _data (nullptr)
{
    _size = 0;
    _capacity = 1;
    _data = new (_capacity) data_T;
};

template <typename data_T>
bstack <data_T> :: ~bstack ()
{
    if (_data != nullptr)
        delete _data;
};

template <typename data_T>
data_T bstack <data_T> :: pop ()
{
    if (_size > 0)
    {
        _size--;
        return _data [_size];
    }
};

template <typename data_T>
data_T bstack <data_T> :: top ()
{
    if (_size > 0)
        return _data [_size - 1];
};

template <typename data_T>
bool bstack <data_T> :: push (data_T val)
{
    if (_size >= _capacity)
        _resize (_capacity * 2);

    _data[_size++] = val;

}

template <typename data_T>
size_t bstack <data_T> :: size ()
{
    return _size;
}

template <typename data_T>
bool bstack <data_T> :: _resize (size_t new_sz)
{
    data_T* newdata = new (new_sz) data_T;

    for (int i = 0; i < _size; i++)
        newdata [i] = _data [i];

    delete _data;
    _data = newdata;
}


#endif //__STACK_BSTACK_HPP__
