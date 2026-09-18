#ifndef __VSN_OBJECTVECTOR_H
#define __VSN_OBJECTVECTOR_H

#include <vector>
#include <vsn_objectlist.h>
#include <vsn_objectvector.h>
#include <vsn_global.h>

namespace VSN {

template <class T>
class MutableObjectVectorIterator;

template <typename T>
class ObjectVector
{
public:
    using difference_type = typename std::vector<T>::difference_type;
    using pointer         = typename std::vector<T>::pointer;
    using reference       = typename std::vector<T>::reference;
    using size_type       = typename std::vector<T>::difference_type;
    using value_type      = typename std::vector<T>::value_type;

    using allocator_type  = typename std::vector<T>::allocator_type;

    using iterator        = typename std::vector<T>::iterator;
    using const_iterator  = typename std::vector<T>::const_iterator;

    using const_pointer   = typename std::vector<T>::const_pointer;
    using const_reference = typename std::vector<T>::const_reference;

    using reverse_iterator       = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;
public:
    ObjectVector() = default;
    explicit ObjectVector(size_type size) : m_data(size) {}
    ObjectVector(size_type size, const T& value) : m_data(size, value) {}
    ObjectVector(const ObjectVector<T>& other) = default;
    ObjectVector(ObjectVector<T>&& other) = default;
    ObjectVector(std::initializer_list<T> args) : m_data(args) {}

    template<class Input_Iterator>
    ObjectVector(Input_Iterator first, Input_Iterator last) : m_data(first, last) {}

    ~ObjectVector() = default;
public:
    void add(const T& value) { m_data.push_back(value); }
    void add(T&& value) { m_data.push_back(std::move(value)); }
    void add(const ObjectVector<T> &other) { m_data.insert(m_data.end(), other.m_data.begin(), other.m_data.end()); }
    template <typename Iter>
    void add(Iter begin, Iter end) { m_data.insert(m_data.end(), begin, end); }

    const_reference at(size_type i) const;

    reference back() { return m_data.back(); }
    const_reference back() const { return m_data.back(); }
    size_type capacity() const { return m_data.capacity(); }
    void clear() { m_data.clear(); }
    bool isExist(const T& value) const;
    size_type count(const T& value) const;

    size_type count() const { return size(); }
    T* data() { return m_data.data(); }
    const T* data() const { return m_data.data(); }
    const T* constData() const { return m_data.data(); }
    bool empty() const { return m_data.empty(); }
    bool isEmpty() const { return m_data.empty(); }
    bool endsWith(const T& value) const { return ! isEmpty() && m_data.back()== value; }
    ObjectVector<T>& fill(const T &value, size_type newSize = -1);

    const_reference constFirst() const { VSN_ASSERT(! isEmpty()); return m_data.front(); }
    reference first() { VSN_ASSERT(! isEmpty()); return m_data.front(); }

    const_reference first() const { VSN_ASSERT(! isEmpty()); return m_data.front(); }

    reference front() { return m_data.front(); }
    const_reference front() const { return m_data.front(); }

    size_type indexOf(const T& value, size_type from = 0) const 
    {
        size_type retval = -1;
        auto iter = std::find(m_data.begin() + from, m_data.end(), value);
        if (iter != m_data.end())
            retval = iter - m_data.begin();
        return retval;
    }

    void insert(size_type pos, const T& value);
    void insert(size_type pos, size_type count, const T& value);

    const_reference constLast() const { VSN_ASSERT(! isEmpty()); return m_data.back(); }
    reference last() { VSN_ASSERT(! isEmpty()); return m_data.back(); }

    const_reference last() const { VSN_ASSERT(!isEmpty()); return m_data.back(); }
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

    ObjectVector<T> mid(size_type pos, size_type length = -1) const;
    void move(size_type from, size_type to);
    void pop_back() { VSN_ASSERT(! isEmpty()); m_data.pop_back(); }
    void pop_front() { VSN_ASSERT(! isEmpty()); m_data.erase(m_data.begin()); }

    void prepend(const T& value) { insert(m_data.begin(), 1, value); }
    void push_back(const T& value) { m_data.push_back(value); }
    void push_back(T&& value) { m_data.push_back(std::move(value)); }
    void push_front(const T& value) { m_data.insert(m_data.begin(), value); }
    void push_front(T&& value) { m_data.insert(m_data.begin(), std::move(value)); }

    void remove(size_type pos) 
    {
        VSN_ASSERT_X(pos >= 0 && pos < size(), "ObjectVector<T>::remove", "index out of range");
        m_data.erase(begin() + pos, begin() + pos + 1);
    }
    void remove(size_type pos, size_type count)  
    {
        VSN_ASSERT_X(pos >= 0 && count >= 0 && pos + count <= size(), "ObjectVector<T>::remove", "index out of range");
        m_data.erase(m_data.begin() + pos, m_data.begin() + pos + count);
    }

    size_type removeAll(const T& value);

    void removeAt(size_type pos) 
    {
        VSN_ASSERT_X(pos >= 0 && pos < size(), "ObjectVector<T>::removeAt", "index out of range");
        m_data.erase(m_data.begin() + pos);
    }

    void removeFirst() 
    {
        VSN_ASSERT(!isEmpty());
        m_data.erase(m_data.begin());
    }

    void removeLast() 
    {
        VSN_ASSERT(! isEmpty());
        m_data.pop_back();
    }

    bool removeOne(const T& value) 
    {
        auto iter = std::find(m_data.begin(), m_data.end(), value);
        if (iter != m_data.end()) 
        {
            m_data.erase(iter);
            return true;
        }
        return false;
    }

    void replace(size_type i, const T &value);
    void reserve(size_type size) { m_data.reserve(size); }
    void resize(size_type size) { m_data.resize(size); }
    size_type size() const { return static_cast<size_type>(m_data.size()); }
    void squeeze() { m_data.shrink_to_fit(); }
    bool startsWith(const T& value) const { return ! isEmpty() && m_data.front() == value; }
    void swap(ObjectVector<T>& other) { std::swap(m_data, other.m_data); }

    T takeAt(size_type i);
    T takeFirst();
    T takeLast();

    T value(size_type i) const;
    T value(size_type i, const T& defaultValue) const;

    static ObjectVector<T> fromList(const ObjectList<T> &list) { return list.toVector(); }
    static ObjectVector<T> fromStdVector(const std::vector<T> &vector) 
    {
        ObjectVector<T> tmp;
        tmp.m_data = vector;
        return tmp;
    }

    ObjectList<T> toList() const;

    std::vector<T> toStdVector() const { return m_data; }
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

    iterator insert(iterator before, size_type count, const T &value) { return m_data.insert(before, count, value); }
    iterator insert(iterator before, const T& value) { return m_data.insert(before, value); }

    template <typename Iter>
    iterator insert(iterator pos, Iter begin, Iter end) { return m_data.insert(pos, begin, end); }

    // operators
    ObjectVector<T>& operator=(const ObjectVector<T>& other) = default;
    ObjectVector<T>& operator=(ObjectVector<T>&& other)      = default;

    bool operator==(const ObjectVector<T> &other) const { return (m_data == other.m_data); }
    bool operator!=(const ObjectVector<T> &other) const { return (m_data != other.m_data); }

    reference operator[](size_type i);
    const_reference operator[](size_type i) const;

    ObjectVector<T>& operator+=(const ObjectVector<T>& other);

    ObjectVector<T> operator+(const ObjectVector<T>& other) const 
    {
        ObjectVector n = *this;
        n += other;
        return n;
    }

   ObjectVector<T> &operator+=(const T& value) { add(value); return *this; }
   ObjectVector<T> &operator<< (const T& value) { add(value); return *this; }
   ObjectVector<T> &operator<<(const ObjectVector<T>& other) { *this += other; return *this; }
private:
    std::vector<T> m_data;
};

// constructors
template <typename T>
inline typename ObjectVector<T>::const_reference ObjectVector<T>::at(size_type i) const
{
   VSN_ASSERT_X(i < size(), "ObjectVector<T>::at", "index out of range");
   return m_data[i];
}

template <typename T>
bool ObjectVector<T>::isExist(const T& value) const
{
    for (const auto& item : m_data) 
    {
        if (item == value)
            return true;
    }
    return false;
}

template <typename T>
typename ObjectVector<T>::size_type ObjectVector<T>::count(const T& value) const
{
    size_type retval = 0;
    for (const auto &item : m_data) 
    {
        if (item == value) 
            ++retval;
    }
    return retval;
}

template <typename T>
ObjectVector<T>& ObjectVector<T>::fill(const T &value, size_type newSize)
{
    if (newSize != -1)
        m_data.resize(newSize);
    for (auto &item : m_data)
        item = value;
    return *this;
}

template <typename T>
inline void ObjectVector<T>::insert(size_type pos, const T& value)
{
    VSN_ASSERT_X(pos >= 0 && pos <= size(), "ObjectVector<T>::insert", "index out of range");
    m_data.insert(m_data.begin() + pos, value);
}

template <typename T>
inline void ObjectVector<T>::insert(size_type pos, size_type count, const T& value)
{
    VSN_ASSERT_X(pos >= 0 && pos <= size(), "ObjectVector<T>::insert", "index out of range");
    m_data.insert(m_data.begin() + pos, count, value);
}

template <typename T>
ObjectVector<T> ObjectVector<T>::mid(size_type pos, size_type length) const
{
    if (length < 0 || pos + length > size())
        length = size() - pos;

    if (pos == 0 && length == size())
        return *this;

    ObjectVector<T> retval(m_data.begin() + pos, m_data.begin() + pos + length);
    return retval;
}

template <typename T>
inline void ObjectVector<T>::move(size_type from, size_type to)
{
    VSN_ASSERT_X(from >= 0 && from < size(), "ObjectVector<T>::move", "from index out of range");
    VSN_ASSERT_X(to   >= 0 && to   < size(), "ObjectVector<T>::move", "to index out of range");

    if (to == from) 
    {
    } 
    else if (to > from) 
        std::rotate(m_data.begin() + from, m_data.begin() + from + 1, m_data.begin() + to + 1);
    else 
        std::rotate(m_data.rend() - from - 1, m_data.rend() - from, m_data.rend() - to);
}

template <typename T>
typename ObjectVector<T>::size_type ObjectVector<T>::removeAll(const T& value)
{
    auto iter = std::remove(m_data.begin(), m_data.end(), value);
    auto retval = m_data.end() - iter;
    m_data.erase(iter, m_data.end());
    return retval;
}

template <typename T>
inline void ObjectVector<T>::replace(size_type i, const T& value)
{
    VSN_ASSERT_X(i >= 0 && i < size(), "ObjectVector<T>::replace", "index out of range");
    m_data[i] = value;
}

template <typename T>
inline T ObjectVector<T>::takeAt(size_type i)
{
    if (i < 0 || i >= size()) 
    {
        std::string msg = "ObjectVector<T>::takeAt() Index is out of Range. (Index is " + std::to_string(i) +
                        ", Size is " + std::to_string(size()) + ")";
        throw std::logic_error(msg);
    }
    T value = std::move(m_data[i]);
    removeAt(i);
    return value;
}

template <typename T>
inline T ObjectVector<T>::takeFirst()
{
    T value = first();
    removeFirst();
    return value;
}

template <typename T>
inline T ObjectVector<T>::takeLast()
{
    T value = last();
    removeLast();
    return value;
}


template<typename T>
T ObjectVector<T>::value(size_type i) const
{
    if (i < 0 || i >= size())
        return T();
    return m_data.begin()[i];
}

template<typename T>
T ObjectVector<T>::value(size_type i, const T &defaultValue) const
{
    return ((i < 0 || i >= size()) ? defaultValue : m_data[i]);
}

// operators
template <typename T>
inline typename ObjectVector<T>::const_reference ObjectVector<T>::operator[](size_type i) const
{
    VSN_ASSERT_X(i >= 0 && i < size(), "ObjectVector<T>::operator[]", "index out of range");
    return m_data[i];
}

template <typename T>
inline typename ObjectVector<T>::reference ObjectVector<T>::operator[](size_type i)
{
    VSN_ASSERT_X(i < size(), "ObjectVector<T>::operator[]", "index out of range");
    return m_data[i];
}

template <typename T>
ObjectVector<T>& ObjectVector<T>::operator+=(const ObjectVector &other)
{
    m_data.insert(m_data.end(), other.m_data.begin(), other.m_data.end());
    return *this;
}

template <typename T>
ObjectList<T> ObjectVector<T>::toList() const
{
    ObjectList<T> result;
    for (const auto& pos : m_data)
        result.add(pos);
    return result;
}

template <typename T>
ObjectVector<T> ObjectList<T>::toVector() const
{
    ObjectVector<T> result( m_data.begin(), m_data.end() );
    return result;
}

template <typename T>
ObjectList<T> ObjectList<T>::fromVector(const ObjectVector<T>& vector)
{
    return vector.toList();
}

template <class T>
class MutableObjectVectorIterator
{
    typedef typename ObjectVector<T>::iterator iterator;
    typedef typename ObjectVector<T>::const_iterator const_iterator;

    ObjectVector<T>* c;
    iterator i, n;

    bool item_exists() const { return const_iterator(n) != c->constEnd(); }
public:
    inline MutableObjectVectorIterator(ObjectVector<T>& vector)
        : c(&vector)
    {
        i = c->begin();
        n = c->end();
    }

    inline MutableObjectVectorIterator& operator=(ObjectVector<T>& vector)
    {
        c = &vector;
        i = c->begin();
        n = c->end();
        return *this;
    }

    inline void toFront() { i = c->begin(); n = c->end(); }
    inline void toBack() { i = c->end(); n = i; }
    inline bool hasNext() const { return c->constEnd() != const_iterator(i); }
    inline T& next() { n = i++; return *n; }
    inline T& peekNext() const { return *i; }
    inline bool hasPrevious() const { return c->constBegin() != const_iterator(i); }
    inline T& previous() { n = --i; return *n; }
    inline T& peekPrevious() const { iterator p = i; return *--p; }

    inline void remove() 
    {
        if (c->constEnd() != const_iterator(n)) 
        {
            i = c->erase(n);
            n = c->end();
        }
    }

    inline void setValue(const T& value) const { if (c->constEnd() != const_iterator(n)) * n = value; }
    inline T& value() { VSN_ASSERT(item_exists()); return *n; }
    inline const T& value() const { VSN_ASSERT(item_exists()); return *n; }
    inline void insert(const T& value) { n = i = c->insert(i, value); ++i; }

    inline bool findNext(const T& value) 
    {
        while (c->constEnd() != const_iterator(n = i)) 
        {
            if (*i++ == value)
                return true;
        }
        return false;
    }

    inline bool findPrevious(const T& value)
    {
        while (c->constBegin() != const_iterator(i))
        {
            if (*(n = --i) == value)
                return true;
        }
        n = c->end();
        return false;
    }
};

} // namespace VSN

#endif // __VSN_OBJECTVECTOR_H
