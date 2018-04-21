#ifndef __STRAIGHT_HPP__
#define __STRAIGHT_HPP__

#include "barray.hpp"

template <typename data_T>
data_T barray <data_T> :: operator [] (double index)
{
    if (index == 0 || index == _size - 1)
        return _data[(int)index];

    if (index >= 0 && index < _capacity)
    {
        int     P0 = index;
        int     P1 = P0 + 1;
        double  t = index - P0;
        return    _data[P0] * (1 - t)
                + _data[P1] * t;
    }
}

#endif //__STRAIGHT_HPP__
