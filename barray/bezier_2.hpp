#ifndef __BEZIER_2_HPP__
#define __BEZIER_2_HPP__

#include "barray.hpp"

template <typename data_T>
data_T barray <data_T> :: operator [] (double index)
{
    if (index >= 0 && index < _capacity)
    {
        int     P0 = (int)index - ((int)index % 2);
        int     P1 = P0 + 1;
        int     P2 = P0 + 2;
        double  t = (index - P0) / 2;
        return    _data[P0] * pow ((1-t), 2)
                + _data[P1] * (2 * t * (1 - t))
                + _data[P2] * pow (t, 2);
    }
}

#endif //__BEZIER_2_HPP__
