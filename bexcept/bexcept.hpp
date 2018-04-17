#ifndef __BEXCEPT_HPP__
#define __BEXCEPT_HPP__

class bexcept
{
public:
    bexcept (const char*, size_t, bexcept*);

    void     what();
    size_t   count();

private:
    bexcept*        _prev;
    const char*     _msg;
    size_t          _count;
};

bexcept :: bexcept (const char* str, size_t count, bexcept* prev):
        _prev (prev),
        _count (count),
        _msg (str)
{}

void bexcept :: what()
{
    for (size_t i = 0; i < _count; i++)
        std::cout << "\t\t";

    std::cout << "In:\t" << _what << '\n';

    if (_prev)
        _prev -> what();
}

size_t bexcept :: count()
{
    return _count;
}

#endif //__BEXCEPT_HPP__
