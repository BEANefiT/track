#ifndef __BVECTOR_HPP__
#define __BVECTOR_HPP__

#include <new>
#include "bvector.h"

template <typename data_T>
bvector <data_T> :: bvector (size_t capacity):
        _size (0),
        _capacity (capacity)
{
    _data = new (std::nothrow) data_T [_capacity]
}

template <typename data_T>
bvector <data_T> :: bvector (const bvector <data_T> &that):

        _size (that._size),
        _capacity (that._capacity)
{
    _data = new (std::nothrow) data_T [_capacity];

    for (int i = 0; i < _capacity; i++)
        _data[i] = that._data[i];
}

template <typename data_T>
bvector <data_T> :: bvector (size_t capacity, const data_T &value):
        _size (capacity),
        _capacity (capacity)
{
    _data = new (std::nothrow) data_T [_capacity];

    for (int i = 0; i < _capacity; i++)
        _data[i] = value;
}

template <typename data_T>
bvector <data_T> :: ~bvector ()
{
    if (_data != nullptr)
        delete _data;
}




#endif //__BVECTOR_HPP__
