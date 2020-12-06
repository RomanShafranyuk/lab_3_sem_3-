#pragma once
template <typename T>
class Vector
{
    T *_data;
    size_t _size;
    size_t _capacity;

public:
    using iterator = T *;
    using const_iterator = const T *;
    Vector() : _data(nullptr), _size(0), _capacity(0) {std::cout << "Default constructor\n";}
    Vector(const Vector<T> &rhs) : _data(new T[rhs._size]), _size(rhs._size), _capacity(rhs._capacity)
    {
        std::cout << "Copy constructor\n";
        for (size_t i = 0; i < _size; ++i)
        {
            _data[i] = rhs._data[i];
        }
    }
    Vector(size_t new_size) : _data(new T[new_size + 1]), _size(new_size), _capacity(new_size + 1) {}
    Vector(Vector<T> &&rhs) noexcept : _data(rhs._data), _size(rhs._size)
    {
        std::cout << "Move constructor\n";
        rhs._data = nullptr;
        rhs._size = 0;
    }
    void swap(Vector<T> &rhs) noexcept
    {
        std::swap(_data, rhs._data);
        std::swap(_size, rhs._size);
        std::swap(_capacity, rhs._capacity);
    }
    Vector<T> &operator=(const Vector<T> &rhs)
    {
        auto temp(rhs);
        swap(temp);
        return *this;
    }
    Vector<T> &operator=(Vector<T> &&rhs) noexcept
    {
        swap(rhs);
        return *this;
    }
    size_t size() const noexcept
    {
        return _size;
    }
    const T &operator[](const size_t index) const
    {
        if (index >= _size)
            throw "Incorrect index";
        return _data[index];
    }

    T &operator[](size_t index)
    {
        if (index >= _size)
            throw "Incorrect index";
        return _data[index];
    }
    const_iterator begin() const
    {
        return _data;
    }
    iterator begin()
    {
        return _data;
    }
    const_iterator end() const
    {
        return _data + _size;
    }
    iterator end()
    {
        return _data + _size;
    }
    void clear() noexcept
    {
        delete[] _data;
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }
    void resize(size_t new_size)
    {
        std::cout << "Resize from " << _size << " to " << new_size << std::endl;
        if (_data == nullptr)
        {
            // std::cout << "#1" << std::endl;
            _data = new T[new_size + 100];
            _size = new_size;
            _capacity = new_size + 100;
            // std::cout << "Done!" << std::endl;
            return;
        }
        if (new_size <= _capacity - 1)
            _size = new_size;
        else
        {
            // std::cout << "#2" << std::endl;
            T *tmp = new T[new_size + 100];
            for (size_t i = 0; i < _size; i++)
            {
                tmp[i] = _data[i];
            }
            clear();
            _data = tmp;
            _size = new_size;
            _capacity = new_size + 100;
        }
        // std::cout << "Done!" << std::endl;
    }

    iterator insert(const_iterator pos, const T &value)
    {
        if (pos < begin() || pos > end())
            throw "Iterator out of range";
        std::cout << "Insert!" << std::endl;
        iterator ret = _data;
        if (pos == end())
        {
            std::cout << "End!" << std::endl;
            resize(_size + 1);
            _data[_size - 1] = value;
            ret = _data + _size - 1;
        }
        else if (pos == begin())
        {
            std::cout << "Begin!" << std::endl;
            resize(_size + 1);
            for (int i = (int)_size - 2; i >= 0; i--)
                _data[i + 1] = std::move_if_noexcept(_data[i]);
            _data[0] = value;
            ret = _data;
        }
        else
        {
            resize(_size + 1);
            const_iterator tmp = _data;
            int index = 0;
            while (tmp != pos)
            {
                tmp++;
                index++;
            }
            for (int i = (int)_size - 2; i >= index; i--)
                _data[i + 1] = std::move_if_noexcept(_data[i]);
            _data[index] = value;
            ret = _data + index;
        }
        return ret;
    }

    iterator erase(iterator pos)
    {
        if (pos < begin() || pos > end())
            throw "Iterator out of range";
        auto ret = _data;
        if (pos == end())
        {
            _data[_size - 1] = 0;
            resize(_size - 1);
            ret = _data + _size - 1;
        }
        else
        {
            iterator tmp = pos;
            for (; tmp <= end() - 2; tmp++)
            {
                *tmp = std::move_if_noexcept(*(tmp + 1));
            }
            resize(_size - 1);
            ret = (iterator)pos;
        }
        return ret;
    }
    ~Vector()
    {
        std::cout << "Destructor!" << std::endl;
        clear();
    }
};
