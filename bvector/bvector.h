#ifndef __BVECTOR_H__
#define __BVECTOR_H__

#include <cstddef>

template <typename data_T>

class bvector
{
public:

    explicit bvector (size_t capacity = 1);
    bvector (const bvector <data_T> &that);
    bvector (size_t, const data_T &value);
    ~bvector ();

    void                swap (bvector <data_T> &that);
    void                resize (size_t);
    void                push_back (const data_T &value);
    data_T              pop_back ();
    data_T              &operator[] (size_t index);
    bvector <data_T>    &operator= (const bvector &that);
    bvector <data_T>    &operator= (bvector &&that);
    size_t              size ();

private:

    size_t      _size;
    size_t      _capacity;
    data_T*     _data;
};

#endif //__BVECTOR_H__
