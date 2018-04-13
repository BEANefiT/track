#ifndef __BLIST_HPP__
#define __BLIST_HPP__

#include <cstddef>
#include "../log/b_log.hpp"

template <typename data_T>
class blist
{
public:
    explicit blist (b_log* log);
    ~blist();

    class blist_elem
    {
    public:
        void         fill (data_T val, blist_elem* nxt, blist_elem* prv);
        data_T       get_elem ();
        blist_elem*  get_next();
        blist_elem*  get_prev();

    private:
        data_T      elem;
        blist_elem* next;
        blist_elem* prev;
    };

    bool    insert (blist_elem* pos, data_T value);
    bool    push_back (data_T value);
    bool    push_front (data_T value);

    data_T  back ();
    data_T  front();
    data_T  get_elem();

    void    erase();

private:
    size_t      _size;
    b_log*      _log;
    blist_elem* _head;
    blist_elem* _tail;
};

template <typename data_T>
blist :: blist (b_log* log):
        _size (0),
        _log (log),
        _head (nullptr),
        _tail (nullptr)
{
    printlog ( "list construct\n" );
}

template <typename data_T>
blist :: ~blist ()
{
    printlog ("list destruct\n");

    erase();
}

template <typename data_T>
void blist :: blist_elem :: fill (data_T val, blist_elem* nxt, blist_elem* prv)
{
    elem = val;
    next = nxt;
    prev = prv;
}

template <typename data_T>
data_T blist :: blist_elem :: get_elem()
{
    return elem;
}

template <typename data_T>
blist_elem* blist :: blist_elem :: get_next()
{
    return next;
}

template <typename data_T>
blist_elem* blist :: blist_elem :: get_prev()
{
    return prev;
}

template <typename data_T>
bool blist :: insert (blist_elem* pos, data_T value)
{
    if (pos == nullptr)
    {
        printlog ("ERROR:\t\tpos == nullptr\n\n\n");

        return 1;
    }

    if (!_size)
    {
        printlog ("WARNING:\t\t_size = 0, inserting 1st elem\n\n");

        auto tmp = new (std::nothrow) blist_elem;

        if (tmp == nullptr)
        {
            printlog ("ERROR:\t\tcan't create an element\n\n\n");

            return 1;
        }

        tmp -> fill (value, nullptr, nullptr);

        _head = tmp;
        _tail = tmp;

        _size++;

        return 0;
    }

    if (_size == 1)
    {
        auto tmp = new (std::nothrow) blist_elem;

        if (tmp == nullptr)
        {
            printlog ("ERROR:\t\tcan't create an element\n\n\n");

            return 1;
        }

        tmp -> fill (value, _head, nullptr);

        _head = tmp;
        _tail -> fill (_tail -> get_elem(), nullptr, tmp);

        _size++;

        return 0;
    }

    if (pos == _head)
    {
        auto tmp = new (std::nothrow) blist_elem;

        if (tmp == nullptr)
        {
            printlog ("ERROR:\t\tcan't create an element\n\n\n");

            tmp -> fill (value, _head, nullptr);

            _head -> fill (_head -> get_elem(), _head -> get_next(), tmp);

            _head = tmp;

            _size++;

            return 0;
        }
    }

    auto tmp = new (std::nothrow) blist_elem;

    if (tmp == nullptr)
    {
        printlog ("ERROR:\t\tcan't create an element\n\n\n");

        return 1;
    }

    tmp -> fill (value, pos, pos -> get_prev());

    pos -> fill (pos -> get_elem(), pos -> get_next(), tmp);

    pos -> get_prev() -> fill (pos -> get_prev() -> get_elem(), tmp, pos -> get_prev() -> get_prev());

    _size++;

    return 0;
}

template <typename data_T>
bool blist :: push_back(data_T value)
{
    if (_tail == nullptr)
    {
        printlog ("WARNING:\t\tpushing 1st elem\n");

        auto tmp = new (std::nothrow) blist_elem;

        if (tmp == nullptr)
        {
            printlog ("ERROR:\t\tcan't create an element\n\n\n");

            return 1;
        }

        tmp -> fill (value, nullptr, nullptr);
        _tail = tmp;
        _head = tmp;
        _size++;

        return 0;
    }

    auto tmp = new (std::nothrow) blist_elem;

    if (tmp == nullptr)
    {
        printlog ("ERROR:\t\tcan't create an element\n\n\n");

        return 1;
    }

    tmp -> fill (value, nullptr, _tail);
    _tail -> fill (_tail -> get_elem(), tmp, _tail -> get_prev());
    _size++;

    return 0;
}






#endif //__BLIST_HPP__
