#ifndef __BVECTOR_HPP__
#define __BVECTOR_HPP__

#include <new>
#include "bvector.h"

template <typename data_T>
bvector <data_T> :: bvector (size_t capacity):
        _size (0),
        _capacity (capacity)
{
    _data = new (std::nothrow) data_T [_capacity];
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

template <typename data_T>
void bvector <data_T> :: swap (bvector <data_T> &that)
{
    std::swap (_data, that._data);
    std::swap (_size, that._size);
    std::swap (_capacity, that._capacity);
}

template <typename data_T>
void bvector <data_T> :: resize (size_t new_capacity)
{
    data_T* new_data = new (std::nothrow) data_T [new_capacity];

    for (size_t i = 0; i < _size; i++)
        new_data[i] = _data[i];

    delete _data;
    _capacity = new_capacity;
    _data = new_data;
}

template <typename data_T>
void bvector <data_T> :: push_back (const data_T &value)
{
    if (_size >= _capacity)
        resize (2 * _capacity);

    _data[_size++] = value;
}

template <typename data_T>
data_T bvector <data_T> :: pop_back ()
{
    if (_size > 0)
        return _data[--_size];
}

template <typename data_T>
data_T &bvector <data_T> :: operator [] (size_t index)
{
    if (index < _size)
        return _data[index];
}

template <typename data_T>
bvector <data_T> &bvector <data_T> :: operator = (const bvector <data_T> &that)
{
    bvector <data_T> tmp (that);
    swap (tmp);
}

template <typename data_T>
bvector <data_T> &bvector <data_T> :: operator = (bvector &&that) noexcept
{
    std::swap (_size, that._size);
    std::swap (_capacity, that._capacity);
    std::swap (_data, that._data);

}

template <typename data_T>
size_t bvector <data_T> :: size ()
{
    return _size;
}

#endif //__BVECTOR_HPP__
