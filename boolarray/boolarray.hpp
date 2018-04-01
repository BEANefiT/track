#ifndef __BOOLARRAY_HPP__
#define __BOOLARRAY_HPP__

#include <new>
#include "boolarray.h"

boolarray :: boolarray (size_t capacity):
        _size (0),
        _capacity (capacity)
{
    _arr_sz = capacity / 8 + 1;
    _data = new (std::nothrow) int [_arr_sz];
}

boolarray :: boolarray (const boolarray &that):
        _capacity (that._capacity),
        _size (that._size),
        _arr_sz (that._arr_sz)
{
    _data = new (std::nothrow) int [_arr_sz];

    for (size_t i = 0; i < _size / 8 + 1; i++)
    {
        _data[i] = that._data[i];
    }
}

boolarray :: boolarray (boolarray &&that) noexcept
{
    std::swap (_data, that._data);
    std::swap (_size, that._size);
    std::swap (_capacity, that._capacity);
    std::swap (_arr_sz, that._arr_sz);
}

boolarray :: ~boolarray ()
{
    delete [] _data;
}



#endif //__BOOLARRAY_HPP__
