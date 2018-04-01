#ifndef __STRAIGHT_HPP__
#define __STRAIGHT_HPP__

#include "barray.h"

template <typename data_T>
data_T barray <data_T> :: operator [] (double index)
{
    if (index >= 0 && index < _capacity)
    {
        int     P0 = (int)index;
        int     P1 = P0 + 1;
        double  t = index - P0;
        return  _data[P0] * (1 - t)
                + _data[P1] * t;
    }
}

#endif //__STRAIGHT_HPP__
