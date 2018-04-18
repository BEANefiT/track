#ifndef __BEXCEPT_HPP__
#define __BEXCEPT_HPP__

class bexcept: public std::exception
{
public:
    bexcept (const char*, bexcept*);

    virtual const char*     what() const noexcept override;
    size_t                  count();
    void                    dump ();
    void                    set_count (size_t);

private:
    bexcept*        _prev;
    const char*     _what;
    size_t          _count;
};

bexcept :: bexcept (const char* str, bexcept* prev):
        _prev (prev),
        _count (0),
        _what (str)
{}

const char* bexcept :: what() const noexcept
{
    return _what;
}

size_t bexcept :: count()
{
    return _count;
}

void bexcept :: set_count (size_t count)
{
    _count = count;
}

void bexcept :: dump ()
{
    for (size_t i = 0; i < _count; i++)
        std::cout << '\t';

    std::cout << _what << '\n';

    _prev -> set_count (_count + 1);

    _prev -> dump();

    delete this;
}

#define bexcept_jump_next( msg )               \
    auto e2 = new bexcept (msg, e);            \
    throw (e2);



#endif //__BEXCEPT_HPP__
