#ifndef __CATMULL_ROM_HPP__
#define __CATMULL_ROM_HPP__

#include "barray.hpp"

double tGet (double ti, double yj, double yi)
{
    return ti + pow (1 + pow (yj - yi, 2), 0.25);
}

double pGet (double ti, double tj, double t, double M, double N)
{
    return    (ti - t) / (ti - tj) * M
              + (t - tj) / (ti - tj) * N;
}

template <typename data_T>
data_T barray <data_T> :: operator [] (double index)
{
    if (index >= 1 && index < _capacity)
    {
        int     P0 = (int)index - 1;
        int     P1 = P0 + 1;
        int     P2 = P0 + 2;
        int     P3 = P0 + 3;
        double  t = index - P1;

        return 0.5 * (    (-1) * t * pow (1-t, 2) * _data[P0]
                        + (2 - 5 * pow (t, 2) + 3 * pow (t, 3)) * _data[P1]
                        + t * (1 + 4 * t - 3 * pow (t, 2)) * _data[P2]
                        + pow (t, 2) * (t - 1) * _data[P3]
                     );
    }
}

#endif //__CATMULL_ROM_HPP__
