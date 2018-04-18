#ifndef __BEXCEPT_HPP__
#define __BEXCEPT_HPP__

class bexcept: public std::exception
{
public:
    bexcept (const char* msg, const char* file, const char* func, const int line, bexcept* prev);
    bexcept (const char* file, const char* func, const int line, bexcept* prev);

    virtual const char*     what() const noexcept override;
    size_t                  count();
    void                    dump ();
    void                    set_count (size_t);

private:
    bexcept*        _prev;
    const char*     _what;
    const char*     _file;
    const char*     _func;
    const int       _line;
    size_t          _count;
};

bexcept :: bexcept (const char* msg, const char* file, const char* func, const int line, bexcept* prev):
        _prev (prev),
        _what (msg),
        _file (file),
        _func (func),
        _line (line)
{}

bexcept :: bexcept (const char* file, const char* func, const int line, bexcept* prev):
        _prev (prev),
        _what (nullptr),
        _file (file),
        _func (func),
        _line (line)
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

    std::cout << "in file \'" << _file << "\' in func \'" << _func << "\' in line \'" << _line << '\'';

    if (_what)
        std::cout << " \"" << _what <<'\"';

    std::cout << '\n';

    if (_prev)
    {
        _prev->set_count(_count + 1);

        _prev->dump();
    }

    delete this;
}

#define bexcept_throw( msg, prev )                                          \
    auto exception = new bexcept (msg, __FILE__, __func__, __LINE__, prev); \
    throw (exception);

#define bexcept_throw_without_msg( prev )                                   \
    auto exception = new bexcept (__FILE__, __func__, __LINE__, prev);      \
    throw (exception)

#endif //__BEXCEPT_HPP__
