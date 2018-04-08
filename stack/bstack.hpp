//#ifdef __STACK_BSTACK_H__

#ifndef __STACK_BSTACK_HPP__
#define __STACK_BSTACK_HPP__

#include <iostream>
#include <cstddef>

template <typename data_T>

class bstack
{
public:
    bstack (b_log *log);
    explicit bstack (size_t capacity, b_log* log);
    ~bstack ();

    data_T  top ();

    void    pop ();
    void    push (data_T val);
    void    resize (size_t new_sz);

    size_t  size ();

    bool    check ();

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
    _log -> print ("stack construct w/ _capacity = 0\n");
};

template <typename data_T>
bstack <data_T> :: bstack (size_t capacity, b_log* log):
        _capacity (capacity),
        _size (0),
        _log (log)
{
    _log -> print ("stack constructor w/ _capacity = %zd\n", capacity);
    _data = new (std::nothrow) data_T [_capacity];

    if (_data == nullptr)
    {
        _log -> print ("cannot allocate mem for stack constr\n");
        throw ("cannot allocate mem for stack");
    }
}

template <typename data_T>
bstack <data_T> :: ~bstack ()
{
    _log -> print ("stack destr\n");

    if (_data != nullptr)
        delete [] _data;
};

template <typename data_T>
void bstack <data_T> :: pop ()
{
    if (_size > 0)
        _size--;

    _log -> print ("cannot stack.pop for _sz = 0\n");
};

template <typename data_T>
data_T bstack <data_T> :: top ()
{
    if (_size > 0)
        return _data [_size - 1];

    _log -> print ("cannot stack.top() for _sz = 0, return poison val\n");
};

template <typename data_T>
void bstack <data_T> :: push (data_T val)
{
    if (_size >= _capacity)
        resize ((_capacity + 1) * 1.4);

    _data[_size++] = val;
}

template <typename data_T>
size_t bstack <data_T> :: size ()
{
    return _size;
}

template <typename data_T>
void bstack <data_T> :: resize (size_t new_sz)
{
    _log -> print ("stack.resize (%zd)\n", new_sz);

    auto newdata = new (std::nothrow) data_T [new_sz];

    if (newdata == nullptr)
    {
        _log -> print ("cannot allocate mem for stack\n");

        return;
    }

    if (new_sz < _size)
        _log -> print ("loss of data, _new_sz < _size\n");

    for (int i = 0; i < std::min (_size, new_sz); i++)
        newdata [i] = _data [i];

    _capacity = new_sz;
    delete [] _data;
    _data = newdata;
}


#endif //__STACK_BSTACK_HPP__