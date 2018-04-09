#ifndef __STACK_BSTACK_HPP__
#define __STACK_BSTACK_HPP__

#include <iostream>
#include <cstddef>
#include <cassert>
#include "../log/b_log.hpp"


template <typename data_T>
class bstack
{
public:
    explicit bstack (b_log *log);
    bstack (size_t capacity, b_log* log);
    ~bstack ();

    data_T  top ();

    void    pop ();
    void    push (data_T val);
    bool    resize (size_t new_sz);

    size_t  size ();

private:
    size_t      _size;
    size_t      _capacity;

    data_T*     _data;
    b_log*      _log;
};

template <typename data_T>
bstack <data_T> :: bstack (b_log* log):
    _size (0),
    _capacity (0),
    _data (nullptr),
    _log (log)
{
    printlog ( "stack construct, _capacity = 0\n" );
};

template <typename data_T>
bstack <data_T>:: bstack (size_t capacity, b_log* log):
        _capacity (capacity),
        _size (0),
        _log (log)
{
    printlog ("stack constructor, _capacity = %zd\n", capacity);
    _data = new (std::nothrow) data_T [_capacity];

    if (_data == nullptr)
    {
        printlog ("%%s: ERROR:\t\tcan\'t alloc mem, stack constr\n\n\n");//, __LINE__);


    }
}

template <typename data_T>
bstack <data_T> :: ~bstack ()
{
    printlog ("stack destr\n");

    if (_data != nullptr)
        delete [] _data;
};

template <typename data_T>
void bstack <data_T> :: pop ()
{
    if (_size > 0)
        _size--;

    else
        printlog ("%%s: ERROR:\t\tcannot pop for _sz = 0\n\n\n");//, __LINE__);
};

template <typename data_T>
data_T bstack <data_T> :: top ()
{
    if (_size > 0)
        return _data [_size - 1];

    printlog ("ERROR: cant top() for _sz = 0, return poison val\n\n\n");
};

template <typename data_T>
void bstack <data_T> :: push (data_T val)
{
    if (_size >= _capacity)
        if (resize ((_capacity + 1) * 2))
        {
            printlog ("ERROR: cant push()\n\n\n");

            return;
        }
    _data[_size++] = val;
}

template <typename data_T>
size_t bstack <data_T> :: size ()
{
    return _size;
}

template <typename data_T>
bool bstack <data_T> :: resize (size_t new_sz)
{
    printlog ("\'%zd\' -> \'%zd\')\n", _capacity, new_sz);

    auto newdata = new (std::nothrow) data_T [new_sz];

    if (newdata == nullptr)
    {
        printlog ("ERROR: cant alloc mem for stack\n\n\n");

        return 1;
    }

    if (new_sz < _size)
    {
        _size = new_sz;
        printlog ("loss of data, _new_sz < _size\n\n");
    }

    for (int i = 0; i < std::min (_size, new_sz); i++)
        newdata [i] = _data [i];

    _capacity = new_sz;
    delete [] _data;
    _data = newdata;
    return 0;
}


#endif //__STACK_BSTACK_HPP__