#ifndef __CATMULL_ROM_HPP__
#define __CATMULL_ROM_HPP__

#include "barray.h"

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
    if (index >= 0 && index < _capacity)
    {
        int     P0 = (int)index - 1;
        int     P1 = P0 + 1;
        int     P2 = P0 + 2;
        int     P3 = P0 + 3;

        double  y0 = _data[P0];
        double  y1 = _data[P1];
        double  y2 = _data[P2];
        double  y3 = _data[P3];

        double  t0 = 0;
        double  t1 = tGet (t0, y1, y0);
        double  t2 = tGet (t1, y2, y1);
        double  t3 = tGet (t2, y3, y2);
        double  t  = index - P1;

        double A1 = pGet (t1, t0, t, y0, y1);
        double A2 = pGet (t2, t1, t, y1, y2);
        double A3 = pGet (t3, t2, t, y2, y3);
        double B1 = pGet (t2, t0, t, A1, A2);
        double B2 = pGet (t3, t1, t, A2, A3);

        return pGet (t2, t1, t, B1, B2);

    }
}

#endif //__CATMULL_ROM_HPP__
