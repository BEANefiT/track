#ifndef __BOOLARRAY_H__
#define __BOOLARRAY_H__

#include <cstddef>

class boolarray
{
public:

    explicit boolarray (size_t);
    boolarray (const boolarray &that);
    boolarray (boolarray &&that) noexcept;
    ~boolarray ();

    bool operator [] (int index);



private:
    size_t      _arr_sz;
    size_t      _capacity;
    size_t      _size;
    int*        _data;
};

#endif //__BOOLARRAY_H__
