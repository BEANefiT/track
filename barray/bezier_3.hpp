#ifndef __BEZIER_3_HPP__
#define __BEZIER_3_HPP__

#include "barray.h"

template <typename data_T>
data_T barray <data_T> :: operator [] (double index)
{
    if (index >= 0 && index < _capacity)
    {
        int     P0 = (int)index - (int)index % 3;
        int     P1 = P0 + 1;
        int     P2 = P0 + 2;
        int     P3 = P0 + 3;
        double  t = (index - P0) / 3;
        return    _data[P0] * pow (1 - t, 3)
                + _data[P1] * 3 * t * pow (1 - t, 2)
                + _data[P2] * 3 * pow (t, 2) * (1 - t)
                + _data[P3] * pow (t, 3);

    }
}

#endif //__BEZIER_3_HPP__
