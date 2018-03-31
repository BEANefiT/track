#ifndef __BARRAY_H__
#define __BARRAY_H__

#include <cstddef>

template <typename data_T>

class barray
{
public:

    explicit barray (size_t);
    barray (const barray <data_T> &that);
    barray (barray <data_T> &&that) noexcept;
    ~barray ();

    data_T& operator [] (int index);
    data_T operator [] (double index);

private:

    size_t      _capacity;
    size_t      _size;
    data_T*     _data;
};

#endif //__BARRAY_H__
