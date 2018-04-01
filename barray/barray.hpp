#ifndef __BARRAY_HPP__
#define __BARRAY_HPP__

#include <new>
#include "barray.h"
#include "bezier_2.hpp"

template <typename data_T>
barray <data_T> :: barray (size_t capacity):
        _capacity (capacity),
        _size (0)
{
    _data = new (std::nothrow) data_T [_capacity];
}

template <typename data_T>
barray <data_T> :: barray (const barray <data_T> &that):
        _size (that._size),
        _capacity (that._capacity)
{
    _data = new (std::nothrow) data_T [_capacity];

    for (size_t i = 0; i < _capacity; i++)
        _data[i] = that._data[i];
}

template <typename data_T>
barray <data_T> :: barray (barray <data_T> &&that) noexcept
{
    std::swap (_size, that._size);
    std::swap (_capacity, that._capacity);
    std::swap (_data, that._data);
}

template <typename data_T>
barray <data_T> :: ~barray ()
{
    delete [] _data;
}

template <typename data_T>
data_T& barray <data_T> :: operator [] (int index)
{
    if (index >= 0 && index < _capacity)
        return _data[index];
}

#endif //__BARRAY_HPP__
