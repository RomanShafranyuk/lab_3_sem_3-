#pragma once
template <typename T>
class List
{
    struct Node
    {
        T data;
        Node *prev;
        Node *next;

        Node(const T &data, Node *prev, Node *next) : data(data), prev(prev), next(next) {}
    };

    Node *_dummy;
    Node *_head;
    Node *_tail;
    size_t _size;

public:
    class ConstIterator
    {
        Node *node;

    public:
        ConstIterator(Node *new_node) : node(new_node) {}
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = const T *;
        using reference = const T &;
        using iterator_category = std::bidirectional_iterator_tag;

        friend class List<T>;

        ConstIterator &operator++()
        {
            node = node->next;
            return *this;
        }

        ConstIterator operator++(int)
        {
            auto result(*this);
            node = node->next;
            return result;
        }

        ConstIterator &operator--()
        {
            node = node->prev;
            return (*this);
        }

        ConstIterator operator--(int)
        {
            auto result(*this);
            node = node->next;
            return result;
        }
        const T &operator*() const
        {
            return node->data;
        }
        T& operator*()
        {
            return node->data;
        }
        ConstIterator *operator->()
        {
            return node;
        }

        bool operator==(ConstIterator rhs)
        {
            return node == rhs.node;
        }

        bool operator!=(ConstIterator rhs)
        {
            return node != rhs.node;
        }
    };

    List() : _dummy(new Node(T(), nullptr, nullptr)), _head(nullptr), _tail(nullptr), _size(0)
    {
        std::cout << "Default constructor!" << std::endl;
        _dummy->prev = _dummy;
        _dummy->next = _dummy;
    }
    List(size_t size) : _dummy(new Node(T(), nullptr, nullptr)), _head(nullptr), _tail(nullptr), _size(0)
    {
        std::cout << "Size constructor!" << std::endl;
        _dummy->prev = _dummy;
        _dummy->next = _dummy;
        while (_size != size)
            insert(end(), T());
    }
    T &operator[](size_t ind)
    {
        if (ind >= _size)
            throw "Index is very big";
        auto tmp = _head;

        for (size_t i = 0; i < ind; i++)
            tmp = tmp->next;

        return tmp->data;
    }
    T operator[](size_t ind) const
    {
        if (ind >= _size)
            throw "Index is very big";
        auto tmp = _head;
        for (size_t i = 0; i < ind; i++)
            tmp = tmp->next;
        return tmp->data;
    }

    List(const List<T> &rhs) : _dummy(new Node(T(), nullptr, nullptr)), _head(nullptr), _tail(nullptr), _size(0)
    {
        std::cout << "Copy constructor!" << std::endl;
        _dummy->prev = _dummy;
        _dummy->next = _dummy;
        for (size_t i = 0; i < rhs._size; i++)
        {
            insert(end(), rhs[i]);
        }
    }

    List(List<T> &&rhs) noexcept : _dummy(new Node(T(), nullptr, nullptr)),_head(nullptr),_tail(nullptr),_size(0)
    {
        std::cout << "Move constructor!" << std::endl;
        _dummy->prev = _dummy;
        _dummy->next = _dummy;
        swap(rhs);
    }

    List<T> &operator=(const List<T> &rhs)
    {
        auto temp(rhs);
        swap(temp);
        return *this;
    }

    List<T> &operator=(List<T> &&rhs) noexcept
    {
        swap(rhs);
        return *this;
    }

    void swap(List<T> &rhs) noexcept
    {
        std::swap(_head, rhs._head);
        std::swap(_tail, rhs._tail);
        std::swap(_size, rhs._size);
    }

    size_t size() const noexcept
    {
        return _size;
    }
    ConstIterator begin() const
    {
        return ConstIterator(_head);
    }
    ConstIterator end() const
    {
        return ConstIterator(_dummy);
    }

    ConstIterator insert(ConstIterator pos, const T &value)
    {
        auto ret = _head;
        if (_size == 0)
        {
            _head = new Node(value, nullptr, nullptr);
            _tail = _head;
            _tail->next = _dummy;
            _head->prev = _dummy;
            _dummy->prev = _tail;
            ret = _head;
        }
        else if (pos == begin())
        {
            auto tmp1 = new Node(value, nullptr, nullptr);
            tmp1->next = _head;
            tmp1->prev = _dummy;
            _head->prev = tmp1;
            _head = tmp1;
            _tail = _dummy->prev;
            ret = tmp1;
        }
        else if (pos == end())
        {
            auto tmp1 = new Node(value, nullptr, nullptr);
            tmp1->next = _dummy;
            tmp1->prev = _tail;
            _tail->next = tmp1;
            _tail = tmp1;
            ret = tmp1;
        }
        else
        {
            auto tmp=pos.node;
            auto tmp1 = new Node(value, nullptr, nullptr);
            tmp1->next=tmp;
            tmp1->prev=tmp->prev;
            tmp->prev=tmp1;
            tmp1->prev->next=tmp1;
            ret = tmp1;
        }
        ++_size;
        return ConstIterator(ret);
    }

    ConstIterator erase(ConstIterator pos)
    {
        auto ret = _head;
        if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            ret = nullptr;
        }
        else if (pos == begin())
        {
            _head = _head->next;
            delete _head->prev;
            _head->prev = _dummy;
            ret = _head;
        }
        else if (pos == end())
        {
            _tail = _tail->prev;
            delete _tail->next;
            _tail->next = _dummy;
            --_size;
            ret = _tail;
        }
        else
        {
            auto tmp=pos.node;
            ret = tmp->next;
            tmp->prev->next=tmp->next;
            tmp->next->prev=tmp->prev;
            delete tmp;

        }
        --_size;
        return ConstIterator(ret);
    }

    void clear()
    {
        std::cout << "Clear method!" << std::endl;
        if (_size==0)
        {
            std::cout <<"Object is empty\n";
            return;
        } 
        // Node *tmp = _head;
        // while (_head!= _dummy)
        // {
        //     tmp = _head;
        //     _head = _head->next;
        //     delete tmp;
        // }
        while ( _size != 0 )
            erase(begin());
        delete _dummy;
    }

    ~List()
    {
        std::cout <<"Destructor\n";
        clear();
        std::cout << "Done\n";
    }
};
