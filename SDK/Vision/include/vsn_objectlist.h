#ifndef __VSN_OBJECTLIST_H
#define __VSN_OBJECTLIST_H

#include <deque>
#include <list>
#include <string>
#include <vsn_global.h>

namespace VSN {

template <class T>
class ObjectVector;

template <class T>
class ObjectSet;

template <typename T>
class ObjectList
{
public:
    ObjectList() = default;
    ObjectList(const ObjectList<T>& other) = default;
    ObjectList(ObjectList<T>&& other) = default;
    ObjectList(std::initializer_list<T> args) :  m_data(args) {}

    template<class Input_Iterator>
    ObjectList(Input_Iterator first, Input_Iterator last) : m_data(first, last) {}
    ~ObjectList() = default;
public:
    using difference_type           = typename std::deque<T>::difference_type;
    using pointer                   = typename std::deque<T>::pointer;
    using reference                 = typename std::deque<T>::reference;
    using size_type                 = typename std::deque<T>::difference_type;
    using value_type                = typename std::deque<T>::value_type;

    using allocator_type            = typename std::deque<T>::allocator_type;

    using iterator                  = typename std::deque<T>::iterator;
    using const_iterator            = typename std::deque<T>::const_iterator;

    using const_pointer             = typename std::deque<T>::const_pointer;
    using const_reference           = typename std::deque<T>::const_reference;

    using reverse_iterator          = typename std::deque<T>::reverse_iterator;
    using const_reverse_iterator    = typename std::deque<T>::const_reverse_iterator;
public:
    void add(const T& value) { m_data.push_back(value); }
    void add(T&& value) { m_data.push_back(std::move(value)); }

    void add(const ObjectList<T>& other) 
    {
        if (this != &other) 
        {
            m_data.insert(m_data.end(), other.m_data.begin(), other.m_data.end());
            return;
        }
        auto numElements = this->size();
        for (ObjectList<T>::size_type i = 0; i < numElements; ++i)
            m_data.push_back(m_data[i]);
    }

    void add(ObjectList<T>&& other) 
    {
        if (this != &other) 
        {
            for (auto& item : other)
                m_data.push_back(std::move(item));
            return;
        }
        auto numElements = this->size();
        for (ObjectList<T>::size_type i = 0; i < numElements; ++i)
            m_data.push_back(std::move(m_data[i]));
    }

    const T& at(size_type i) const;
    T& back() { return m_data.back(); }
    const T& back() const { return m_data.back(); }
    void clear() { return m_data.clear(); }
    bool contains(const T& value) const;

    size_type count(const T& value) const;
    size_type count() const { return size(); }
    bool empty() const { return m_data.empty(); }
    bool isEmpty() const { return m_data.empty(); }
    bool endsWith(const T& value) const { return ! isEmpty() && m_data.back() == value; }

    T& first() {  VSN_ASSERT(!isEmpty()); return m_data.front(); }
    const T& first() const { VSN_ASSERT(! isEmpty()); return m_data.front(); }
    const_reference constFirst() const { VSN_ASSERT(! isEmpty());return m_data.front(); }

    T& front() { return m_data.front(); }
    const T& front() const { return m_data.front(); }
    size_type indexOf(const T& value, size_type from = 0) const 
    {
        size_type retval = -1;
        auto iter = std::find(m_data.begin() + from, m_data.end(), value);
        if (iter != m_data.end())
            retval = iter - m_data.begin();
        return retval;
    }

    T& last() { VSN_ASSERT(! isEmpty()); return m_data.back(); }
    const T& last() const { VSN_ASSERT(! isEmpty()); return m_data.back(); }
    const_reference constLast() const { VSN_ASSERT(! isEmpty()); return m_data.back(); }
    void insert(size_type i, const T& value);
    size_type length() const { return size(); }

    size_type lastIndexOf(const T& value, size_type from = -1) const 
    {
        size_type retval = -1;
        size_type from_reverse = 0;
        if (from >= 0)
            from_reverse = size() - from;
        auto iter = std::find(m_data.rbegin() + from_reverse, m_data.rend(), value);
        if (iter != m_data.rend())
            retval = m_data.rend() - iter - 1;
        return retval;
    }

    ObjectList<T> mid(size_type pos, size_type length = -1) const;
    void move(size_type from, size_type to);

    void pop_back() { removeLast(); }
    void pop_front() { removeFirst(); }
    void prepend(const T& value) { m_data.push_front(value); }
    void push_back(const T& value) { m_data.push_back(value); }
    void push_front(const T& value) { m_data.push_front(value); }

    void remove(size_type i)
    {
        VSN_ASSERT_X(i >= 0 && i < size(), "ObjectList<T>::remove", "index out of range");
        erase(begin() + i, begin() + i + 1);
    }

    void remove(size_type i, size_type n)
    {
        VSN_ASSERT_X(i >= 0 && n >= 0 && i + n <= size(), "ObjectList<T>::remove", "index out of range");
        m_data.erase(m_data.begin() + i, m_data.begin() + i + n);
    }

    size_type removeAll(const T& value);
    void removeAt(size_type i) 
    {
        VSN_ASSERT_X(i >= 0 && i < size(), "ObjectList<T>::removeAt", "index out of range");
        m_data.erase(m_data.begin() + i);
    }

    void removeFirst() 
    {
        VSN_ASSERT(!isEmpty());
        m_data.pop_front();
    }

    void removeLast() 
    {
        VSN_ASSERT(!isEmpty());
        m_data.pop_back();
    }

    bool removeOne(const T& value);
    void replace(size_type i, const T& value);

    [[deprecated]] void reserve(size_type size) {}
    void resize(size_type size) { m_data.resize(size); }
    size_type size() const { return static_cast<size_type>(m_data.size()); }

    bool startsWith(const T& value) const { return ! isEmpty() && m_data.front() == value; }

    T takeAt(size_type i);
    T takeFirst();
    T takeLast();

    T value(size_type i) const;
    T value(size_type i, const T& defaultValue) const;

    static ObjectList<T> fromSet(const ObjectSet<T>& set);
    static ObjectList<T> fromVector(const ObjectVector<T>& vector);
    static ObjectList<T> fromStdList(const std::list<T>& other) 
    {
        ObjectList<T> tmp;
        std::copy(other.begin(), other.end(), std::back_inserter(tmp));
        return tmp;
    }

    ObjectSet<T> toSet() const;
    ObjectVector<T> toVector() const;

    std::list<T> toStdList() const 
    {
        std::list<T> tmp(m_data.begin(), m_data.end());
        return tmp;
    }

    iterator begin() { return m_data.begin(); }
    const_iterator begin() const { return m_data.begin(); }
    const_iterator constBegin() const { return m_data.begin(); }
    const_iterator cbegin() const { return m_data.begin(); }
    iterator end() { return m_data.end(); }
    const_iterator end() const { return m_data.end(); }
    const_iterator constEnd() const { return m_data.end(); }
    const_iterator cend() const { return m_data.end(); }

    reverse_iterator rbegin() { return m_data.rbegin(); }
    const_reverse_iterator rbegin() const { return m_data.rbegin(); }
    const_reverse_iterator crbegin() const { return m_data.rbegin(); }

    reverse_iterator rend() { return m_data.rend(); }
    const_reverse_iterator rend() const { return m_data.rend(); }
    const_reverse_iterator crend() const { return m_data.rend(); }

    iterator erase(const_iterator begin, const_iterator end) { return m_data.erase(begin, end); }
    iterator erase(const_iterator pos) { return m_data.erase(pos); }

    iterator insert(iterator before, const T& value) { return m_data.insert(before, value); }
public:
    ObjectList<T>& operator=(const ObjectList<T>& other) = default;
    ObjectList<T>& operator=(ObjectList<T>&& other) = default;

    bool operator==(const ObjectList<T>& other) const { return (m_data == other.m_data); }
    bool operator!=(const ObjectList<T>& other) const { return (m_data != other.m_data); }
    ObjectList<T> operator+(const ObjectList<T>& other) const
    {
        ObjectList n = *this;
        n += other;
        return n;
    }
    ObjectList<T>& operator+=(const ObjectList<T>& other) { add(other); return *this; }
    ObjectList<T>& operator+=(const T& value) { add(value); return *this; }
    ObjectList<T>& operator<< (const T& value) { add(value); return *this; }
    ObjectList<T>& operator<<(const ObjectList<T>& other) { *this += other; return *this; }
    const T& operator[](size_type i) const;
    T& operator[](size_type i);
private:
    std::deque<T> m_data;
};

template <typename T>
inline const T& ObjectList<T>::at(size_type i) const
{
    if (i < 0 || i >= size())
    {
        std::string msg = "ObjectList<T>::at() Index is out of Range. (Index is " + std::to_string(i) +
                    ", Size is " + std::to_string(size()) + ")";
        throw std::logic_error(msg);
    }
    return m_data[i];
}

template <typename T>
bool ObjectList<T>::contains(const T& value) const
{
    for (const auto& item : m_data)
    {
        if (item == value)
            return true;
    }
    return false;
}

template <typename T>
typename ObjectList<T>::size_type ObjectList<T>::count(const T& value) const
{
    size_type retval = 0;
    for (const auto& item : m_data)
    {
        if (item == value)
            ++retval;
    }
    return retval;
}

template <typename T>
inline void ObjectList<T>::insert(size_type i, const T& value)
{
    VSN_ASSERT_X(i >= 0 && i <= size(), "ObjectList<T>::insert", "index out of range");
    m_data.insert(m_data.begin() + i, value);
}

template<typename T>
ObjectList<T> ObjectList<T>::mid(size_type pos, size_type length) const
{
    VSN_ASSERT_X(pos < size(), "ObjectList<T>::mid", "pos out of range");

    if (length < 0 || pos + length > size())
        length = size() - pos;

    if (pos == 0 && length == size())
        return *this;
    ObjectList<T> retval(m_data.begin() + pos, m_data.begin() + pos + length);
    return retval;
}

template <typename T>
inline void ObjectList<T>::move(size_type from, size_type to)
{
    VSN_ASSERT_X(from >= 0 && from < size(), "ObjectList<T>::move", "from index out of range");
    VSN_ASSERT_X(to   >= 0 && to   < size(), "ObjectList<T>::move", "to index out of range");
    if (to == from)
    {
    }
    else if (to > from) 
        std::rotate(m_data.begin() + from, m_data.begin() + from + 1, m_data.begin() + to + 1);
    else 
        std::rotate(m_data.rend() - from - 1, m_data.rend() - from, m_data.rend() - to);
}

template <typename T>
typename ObjectList<T>::size_type ObjectList<T>::removeAll(const T& value)
{
    auto iter  = std::remove(m_data.begin(), m_data.end(), value);
    auto retval = m_data.end() - iter;
    m_data.erase(iter, m_data.end());
    return retval;
}

template <typename T>
inline void ObjectList<T>::replace(size_type i, const T &value)
{
    VSN_ASSERT_X(i >= 0 && i < size(), "ObjectList<T>::replace", "index out of range");
    m_data[i] = value;
}

template <typename T>
bool ObjectList<T>::removeOne(const T& value)
{
    size_type index = indexOf(value);
    if (index != -1) 
    {
        removeAt(index);
        return true;
    }
    return false;
}

template <typename T>
inline T ObjectList<T>::takeAt(size_type i)
{
    if (i < 0 || i >= size()) 
    {
        std::string msg = "ObjectList<T>::takeAt() Index is out of Range. (Index is " + std::to_string(i) +
                        ", Size is " + std::to_string(size()) + ")";
        throw std::logic_error(msg);
    }
    T value = std::move(m_data[i]);
    removeAt(i);
    return value;
}

template <typename T>
inline T ObjectList<T>::takeFirst()
{
    T value = first();
    removeFirst();
    return value;
}

template <typename T>
inline T ObjectList<T>::takeLast()
{
    T value = last();
    removeLast();
    return value;
}

template<typename T>
T ObjectList<T>::value(size_type i) const
{
    if (i < 0 || i >= size())
        return T();
    return m_data[i];
}

template<typename T>
T ObjectList<T>::value(size_type i, const T& defaultValue) const
{
    return ((i < 0 || i >= size()) ? defaultValue : m_data[i]);
}

// operators
template <typename T>
inline const T &ObjectList<T>::operator[](size_type i) const
{
    if (i < 0 || i >= size())
    {
        std::string msg = "ObjectList<T>::operator[] Index is out of Range. (Index is " + std::to_string(i) +
                        ", Size is " + std::to_string(size()) + ")";
        throw std::logic_error(msg);
    }
    return m_data[i];
}

template <typename T>
inline T& ObjectList<T>::operator[](size_type i)
{
    if (i < 0 || i >= size())
    {
        std::string msg = "ObjectList<T>::operator[] Index is out of Range. (Index is " + std::to_string(i) +
                        ", Size is " + std::to_string(size()) + ")";
        throw std::logic_error(msg);
    }
    return m_data[i];
}

} // namespace VSN

#endif // __VSN_OBJECTLIST_H
