#ifndef __BEXCEPT_HPP__
#define __BEXCEPT_HPP__

class bexcept: public std::exception
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

    std::cout << "In:\t" << _msg << '\n';

    if (_prev)
        _prev -> what();

    delete this;
}

size_t bexcept :: count()
{
    return _count;
}

#define bexcept_jump_next( msg )               \
    auto e2 = new bexcept (msg, e -> count() + 1, e);    \
    throw (e2);



#endif //__BEXCEPT_HPP__
