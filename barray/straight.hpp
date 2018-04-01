#ifndef __STRAIGHT_HPP__
#define __STRAIGHT_HPP__

#include "barray.h"

template <typename data_T>
data_T barray <data_T> :: operator [] (double index)
{
    if (index >= 0 && index < _capacity)
    {
        double frac = index - (int)index;
        double left = (index - frac);
        double right = left + 1;
        return _data[(int)left] * (1 - frac) + _data[(int)right] * frac;
    }
}

#endif //__STRAIGHT_HPP__
