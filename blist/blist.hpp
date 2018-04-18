#ifndef __BLIST_HPP__
#define __BLIST_HPP__

#include "../bexcept/bexcept.hpp"

template <typename data_T>
class blist
{
public:
    class blist_elem
    {
    public:
        blist_elem (data_T elm, blist_elem* nxt, blist_elem* prv);

        void            fill (data_T val, blist_elem* nxt, blist_elem* prv);
        data_T          get_elem();
        blist_elem*     get_next();
        blist_elem*     get_prev();

    private:
        data_T          elem;
        blist_elem*     next;
        blist_elem*     prev;
    };

    blist();
    blist (data_T elm, blist_elem* nxt, blist_elem* prv);
    ~blist();

    bool        insert (blist_elem* pos, data_T value);
    bool        insert (size_t index, data_T value);
    bool        push_back (data_T value);
    bool        push_front (data_T value);

    data_T      back();
    data_T      front();
    data_T      get_elem (size_t index);

    blist_elem* get_head();
    blist_elem* get_tail();

    size_t      size();

    void        erase();
    bool        rm_elem(blist_elem*);

private:
    size_t      _size;
    blist_elem* _head;
    blist_elem* _tail;
};

template <typename data_T>
blist <data_T> :: blist ():
        _size (0),
        _head (nullptr),
        _tail (nullptr)
{}

template <typename data_T>
blist <data_T> :: ~blist ()
{
    erase();
}

template <typename data_T>
blist <data_T> :: blist_elem :: blist_elem (data_T elm, blist_elem* nxt, blist_elem* prv):
        elem (elm),
        next (nxt),
        prev (prv)
{}

template <typename data_T>
void blist <data_T> :: blist_elem :: fill (data_T val, blist_elem* nxt, blist_elem* prv)
{
    elem = val;
    next = nxt;
    prev = prv;
}

template <typename data_T>
data_T blist <data_T> :: blist_elem :: get_elem()
{
    return elem;
}

template <typename data_T>
typename blist <data_T> :: blist_elem* blist <data_T> :: blist_elem :: get_next()
{
    return next;
}

template <typename data_T>
typename blist <data_T> :: blist_elem* blist <data_T> :: blist_elem :: get_prev()
{
    return prev;
}

template <typename data_T>
bool blist <data_T> :: insert (blist_elem* pos, data_T value)
{
    if (_size != 0 && pos == nullptr)
    {
        bexcept_throw ("cannot insert before pos == nullptr", nullptr);
    }

    if (pos == _head)
    {
        try{ push_front (value); }

        catch (bexcept* e){ bexcept_throw_without_msg (e); }

        return 0;
    }

    auto tmp = new (std::nothrow) blist_elem (value, pos, pos -> get_prev());

    if (tmp == nullptr)
    {
        bexcept_throw ("cannot create an element", nullptr);
    }

    if (_size == 0)
    {
        _head = tmp;
        _tail = tmp;
        _size++;

        return 0;
    }

    if (_size == 1)
    {
        _head = tmp;
        _tail -> fill (_tail -> get_elem(), nullptr, tmp);
        _size++;

        return 0;
    }

    pos -> get_prev() -> fill (pos -> get_prev() -> get_elem(), tmp, pos -> get_prev() -> get_prev());

    pos -> fill (pos -> get_elem(), pos -> get_next(), tmp);

    _size++;

    return 0;
}

template <typename data_T>
bool blist <data_T> :: insert (size_t index, data_T value)
{
    if (_size == 0)
    {
        insert (nullptr, value);
    }

    if (index >= _size)
    {
        bexcept_throw ("cannot insert(), because index >= _size", nullptr);
    }

    auto tmp = _head;

    for (int i = 0; i < index; i++)
    {
        if (tmp == nullptr)
        {
            bexcept_throw ("element with this index does not exist", nullptr);
        }

        tmp = tmp -> get_next();
    }

    insert (tmp, value);
}

template <typename data_T>
bool blist <data_T> :: push_back(data_T value)
{
    auto tmp = new (std::nothrow) blist_elem (value, nullptr, _tail);

    if (tmp == nullptr)
    {
        bexcept_throw ("cannot create an element", nullptr);
    }

    if (_tail == nullptr)
    {
        _tail = tmp;
        _head = tmp;
        _size++;

        return 0;
    }

    _tail -> fill (_tail -> get_elem(), tmp, _tail -> get_prev());
    _tail = tmp;
    _size++;

    return 0;
}

template <typename data_T>
bool blist <data_T> :: push_front (data_T value)
{
    auto tmp = new (std::nothrow) blist_elem (value, _head, nullptr);

    if (tmp == nullptr)
    {
        bexcept_throw ("cannot create an element", nullptr);
    }

    if (_head == nullptr)
    {
        _head = tmp;
        _tail = tmp;
        _size++;

        return 0;
    }

    _head -> fill (_head -> get_elem(), _head -> get_next(), tmp);
    _head = tmp;
    _size++;

    return 0;
}

template <typename data_T>
data_T blist <data_T> :: back()
{
    if (_size > 0)
    {
        if (_tail == nullptr)
        {
            bexcept_throw ("_tail == nullptr", nullptr);
        }

        return _tail -> get_elem();
    }

    bexcept_throw ("blist is empty", nullptr);
}

template <typename data_T>
data_T blist <data_T> :: front()
{
    if (_size > 0)
    {
        if (_head == nullptr)
        {
            bexcept_throw ("_head == nullptr", nullptr);
        }

        return _head -> get_elem();
    }

    bexcept_throw ("blist is empty", nullptr);
}

template <typename data_T>
data_T blist <data_T> :: get_elem (size_t index)
{
    if (index < _size)
    {
        auto tmp = _head;

        if (tmp == nullptr)
        {
            bexcept_throw ("element with this index does not exist", nullptr);
        }

        for (int i = 0; i < index; i++)
        {
            tmp = tmp -> get_next();

            if (tmp == nullptr)
            {
                bexcept_throw ("element with this index does not exist", nullptr);
            }
        }

        return tmp -> get_elem();
    }

    bexcept_throw ("index >= size", nullptr);
}

template <typename data_T>
typename blist<data_T>::blist_elem* blist <data_T> :: get_head()
{
    return _head;
}

template <typename data_T>
typename blist<data_T>::blist_elem* blist <data_T> :: get_tail()
{
    return _tail;
}

template <typename data_T>
size_t blist <data_T> :: size()
{
    return _size;
}

template <typename data_T>
void blist <data_T> :: erase()
{
    auto tmp = _head;

    while (tmp != nullptr)
    {
        auto a = tmp -> get_next();

        delete tmp;
        _size--;

        tmp = a;
    }
}

template <typename data_T>
bool blist <data_T> :: rm_elem (blist_elem* pos)
{
    if (pos == nullptr)
    {
        bexcept_throw ("cannot remove not existing elem", nullptr);
    }

    if (_size == 0)
    {
        bexcept_throw ("blist is empty", nullptr);
    }

    auto tmp_l = pos -> get_prev();
    auto tmp_r = pos -> get_next();

    if (tmp_r == nullptr && tmp_l == nullptr)
    {
        delete pos;
        _head = nullptr;
        _tail = nullptr;
        pos = nullptr;
        _size--;

        return 0;
    }

    if (pos == _head)
    {
        tmp_r -> fill (tmp_r -> get_elem(), tmp_r -> get_next(), nullptr);

        delete _head;
        _head = tmp_r;
        _size--;

        return 0;
    }

    if (pos == _tail)
    {
        tmp_l -> fill (tmp_l -> get_elem(), nullptr, tmp_l -> get_prev());

        delete _tail;
        _tail = tmp_l;
        _size--;

        return 0;
    }

    if (tmp_l != nullptr && tmp_r != nullptr)
    {
        tmp_l -> fill (tmp_l -> get_elem(), tmp_r, tmp_l -> get_prev());
        tmp_r -> fill (tmp_r -> get_elem(), tmp_r -> get_next(), tmp_l);

        delete pos;
        _size--;

        return 0;
    }

    bexcept_throw_without_msg (nullptr);
}

#endif //__BLIST_HPP__
