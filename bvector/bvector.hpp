#ifndef __BVECTOR_HPP__
#define __BVECTOR_HPP__

#include "../bexcept/bexcept.hpp"

template <typename data_T>
class bvector
{
public:

    bvector();
    explicit bvector (size_t);
    bvector (const bvector <data_T> &that);
    bvector (size_t, const data_T &value);
    ~bvector ();

    void                swap (bvector <data_T> &that);
    void                resize (size_t);
    void                push_back (const data_T &value);
    data_T              pop_back ();
    data_T              &operator [] (size_t index);
    bvector <data_T>    &operator = (const bvector <data_T> &that);
    bvector <data_T>    &operator = (bvector &&that) noexcept;
    size_t              size ();

private:

    size_t      _size;
    size_t      _capacity;
    data_T*     _data;
};

template <typename data_T>
bvector <data_T> :: bvector():
        _size (0),
        _capacity (0),
        _data (nullptr)
{}

template <typename data_T>
bvector <data_T> :: bvector (size_t capacity):
        _size (0),
        _capacity (capacity)
{
    _data = new (std::nothrow) data_T [_capacity];

    if (_data == nullptr)
    {
        bexcept_throw ("can't allocate memory");
    }
}

template <typename data_T>
bvector <data_T> :: bvector (const bvector <data_T> &that):
        _size (that._size),
        _capacity (that._capacity)
{
    _data = new (std::nothrow) data_T [_capacity];

    if (_data == nullptr)
    {
        bexcept_throw ("can't allocate memory");
    }

    for (int i = 0; i < _capacity; i++)
        _data[i] = that._data[i];
}

template <typename data_T>
bvector <data_T> :: bvector (size_t capacity, const data_T &value):
        _size (capacity),
        _capacity (capacity)
{
    _data = new (std::nothrow) data_T [_capacity];

    if(_data == nullptr)
    {
        bexcept_throw ("can't allocate memory");
    }

    for (int i = 0; i < _capacity; i++)
        _data[i] = value;
}

template <typename data_T>
bvector <data_T> :: ~bvector ()
{
    if (_data != nullptr)
        delete _data;

    _data = nullptr;
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
    if (new_capacity < _size)
    {
        bexcept_throw ("loss of data, because new_capacity < _size");
    }

    data_T* new_data = new (std::nothrow) data_T [new_capacity];

    if (new_data == nullptr)
    {
        bexcept_throw ("can't allocate memory");
    }

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
    {
        try{ resize(2 * _capacity + 1); }

        catch (bexcept* e){ bexcept_throw_without_msg (e); }
    }

    _data[_size++] = value;
}

template <typename data_T>
data_T bvector <data_T> :: pop_back ()
{
    if (_size <= 0)
    {
        bexcept_throw ("bvector is empty");
    }

    return _data[--_size];
}

template <typename data_T>
data_T &bvector <data_T> :: operator[] (size_t index)
{
    if (index >= _capacity)
    {
        bexcept_throw ("index >= _capacity");
    }

    return _data[index];
}

template <typename data_T>
bvector <data_T> &bvector <data_T> :: operator= (const bvector <data_T> &that)
{
    try
    {
        bvector<data_T> tmp(that);
        swap(tmp);
    }

    catch (bexcept *e)
    {
        bexcept_throw_without_msg (e);
    }
}

template <typename data_T>
bvector <data_T> &bvector <data_T> :: operator= (bvector &&that) noexcept
{
    try{ swap (that); }

    catch (bexcept* e){ bexcept_throw_without_msg (e); }
}

template <typename data_T>
size_t bvector <data_T> :: size ()
{
    return _size;
}

#endif //__BVECTOR_HPP__
