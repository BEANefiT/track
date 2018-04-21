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
    for (int i = 0; i < _capacity; i++)
        _data [i].~data_T();

    if (_data != nullptr)
        delete [] _data;

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

    for (size_t i = 0; i < _capacity; i++)
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

    auto tmp = _data [--_size];
    _data [size].~data_T();

    return tmp;
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

template <>
class bvector <bool>
{
public:
    struct proxy_t
    {
        char*   arr;
        int     shift;

        proxy_t(char* ptr, int sh):
            arr (ptr),
            shift (sh)
        {}

        operator bool()
        {
            return (bool) ((*arr & 1) << shift)
        }
    };

    bvector();
    explicit bvector (size_t);
    bvector (const bvector &that);
    bvector (size_t, const bool &value);
    ~bvector ();

    void                swap (bvector &that);
    void                resize (size_t);
    void                push_back (const bool &value);
    bool                pop_back ();
    struct proxy_t      operator [] (size_t index);
    bvector             &operator = (const bvector &that);
    bvector             &operator = (bvector &&that) noexcept;
    size_t              size ();

private:

    size_t      _size;
    size_t      _capacity;
    char*       _data;
};

bvector <bool> :: bvector():
        _size (0),
        _capacity (0),
        _data (nullptr)
{}

bvector <bool> :: bvector (size_t capacity):
        _size (0),
        _capacity (8 * (capacity / 8 + (capacity % 8) / (capacity % 8)))
{
    _data = new (std::nothrow) char [_capacity / 8];

    if (_data == nullptr)
    {
        bexcept_throw ("can't allocate memory");
    }
}

bvector <bool> :: bvector (const bvector &that):
        _size (that._size),
        _capacity (that._capacity)
{
    _data = new (std::nothrow) char [_capacity / 8];

    if (_data == nullptr)
    {
        bexcept_throw ("can't allocate memory");
    }

    for (int i = 0; i < _capacity / 8; i++)
        _data [i] = that._data [i];
}

bvector <bool> :: bvector (size_t capacity, const bool &value):
        _capacity (8 * (capacity / 8 + (capacity % 8) / (capacity % 8))),
        _size (_capacity)
{
    _data = new (std::nothrow) char [_capacity / 8];

    if (_data == nullptr)
    {
        bexcept_throw ("can't allocate memory");
    }

    if (value == 0)
        for (int i = 0; i < _capacity / 8; i++)
            _data [i] = 0;

    if (value == 1)
        for (int i = 0; i < _capacity / 8; i++)
            _data [i] = 0xff;
}

bvector <bool> :: ~bvector ()
{
    if (_data != nullptr)
    {
        delete[] _data;
        _data = nullptr;
    }
}

void bvector <bool> :: swap (bvector &that)
{
    std::swap (_data, that._data);
    std::swap (_size, that._size);
    std::swap (_capacity, that._capacity);
}

void bvector <bool> :: resize (size_t new_capacity)
{
    if (new_capacity < _size)
    {
        bexcept_throw ("loss of data, because new_capacity < _size");
    }

    _capacity = 8 * (new_capacity / 8 + (new_capacity % 8) / (new_capacity % 8));

    auto new_data = new (std::nothrow) char [_capacity / 8];

    if (new_data == nullptr)
    {
        bexcept_throw ("can't allocate memory");
    }

    for (size_t i = 0; i < _capacity / 8; i++)
        new_data[i] = _data[i];

    delete _data;
    _data = new_data;
}

void bvector <bool> :: push_back (const bool &value)
{
    if (_size >= _capacity)
    {
        try{ resize(2 * _capacity + 1); }

        catch (bexcept* e){ bexcept_throw_without_msg (e); }
    }

    _data [_size / 8] |= (value << (7 - (_size % 8)));

    _size++;
}

data_T bvector <data_T> :: pop_back ()
{
    if (_size <= 0)
    {
        bexcept_throw ("bvector is empty");
    }

    return (bool) (_data [(_size - 1) / 8] & (1 >> ((8 - (_size-- % 8)) % 8)));
}

#endif //__BVECTOR_HPP__
