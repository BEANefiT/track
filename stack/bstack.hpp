//#ifdef __STACK_BSTACK_H__

#ifndef __STACK_BSTACK_HPP__
#define __STACK_BSTACK_HPP__

#include <iostream>
#include <cstddef>

template <typename data_T>

class bstack
{
public:
    bstack ();
    explicit bstack (size_t capacity);
    ~bstack ();

    data_T  pop ();
    data_T  top ();

    void    push (data_T val);
    void    resize (size_t new_sz);

    size_t  size ();

    bool    check ();

private:
    size_t  _size;
    size_t  _capacity;

    data_T*  _data;
};

template <typename data_T>
bstack <data_T> :: bstack () :
    _size (0),
    _capacity (0),
    _data (nullptr)
{};

template <typename data_T>
bstack <data_T> :: bstack (size_t capacity):
        _capacity (capacity),
        _size (0)
{
<<<<<<< HEAD
    _data = new data_T [_capacity];
}
=======
    b_log _log;
    _size = 0;
    _capacity = 0;
    _data = new (std::nothrow) data_T [_capacity];
};
>>>>>>> log constructor into stack

template <typename data_T>
bstack <data_T> :: ~bstack ()
{
    if (_data != nullptr)
        delete [] _data;
};

template <typename data_T>
data_T bstack <data_T> :: pop ()
{
    if (_size > 0)
    {
        return _data[--_size];
    }
};

template <typename data_T>
data_T bstack <data_T> :: top ()
{
    if (_size > 0)

        return _data [_size - 1];
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
    auto newdata = new data_T [new_sz];

    for (int i = 0; i < _size; i++)
        newdata [i] = _data [i];

    _capacity = new_sz;
    delete [] _data;
    _data = newdata;
}


#endif //__STACK_BSTACK_HPP__