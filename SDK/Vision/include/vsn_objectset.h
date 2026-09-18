#ifndef __VSN_OBJECTSET_H
#define __VSN_OBJECTSET_H

#include <initializer_list>
#include <unordered_set>
#include <vsn_objectvector.h>
#include <vsn_global.h>

namespace VSN {

template <class T>
class ObjectSetIterator;

template <class T>
class MutableObjectSetIterator;

template <class T>
class ObjectSet
{
public:
    using difference_type = typename std::unordered_set<T>::difference_type;
    using pointer         = typename std::unordered_set<T>::pointer;
    using reference       = typename std::unordered_set<T>::reference;
    using size_type       = typename std::unordered_set<T>::difference_type;
    using value_type      = typename std::unordered_set<T>::value_type;

    using key_type        = typename std::unordered_set<T>::key_type;
    using key_equal       = typename std::unordered_set<T>::key_equal;
    using hasher          = typename std::unordered_set<T>::hasher;

    using allocator_type  = typename std::unordered_set<T>::allocator_type;

    using iterator        = typename std::unordered_set<T>::iterator;
    using const_iterator  = typename std::unordered_set<T>::const_iterator;

    using const_pointer   = typename std::unordered_set<T>::const_pointer;
    using const_reference = typename std::unordered_set<T>::const_reference;
public:
    ObjectSet() = default;
    ObjectSet(const ObjectSet<T>& other) = default;
    ObjectSet(ObjectSet<T>&& other) = default;

    ObjectSet(std::initializer_list<T> args)
        : m_data(args) {}

    template<class Input_Iterator>
    ObjectSet(Input_Iterator first, Input_Iterator last);
public:
    // methods
    size_type capacity() const { return m_data.capacity(); }
    void clear() { m_data.clear(); }
    bool contains(const ObjectSet<T>& other) const;
    bool contains(const T& value) const { return m_data.count(value); }

    size_type count() const { return size(); }

    bool empty() const { return m_data.empty(); }
    bool isEmpty() const { return m_data.empty(); }

    size_type erase(const key_type& key) { return m_data.erase(key); }

    ObjectSet<T>& intersect(const ObjectSet<T>& other);
    bool intersects(const ObjectSet<T>& other) const;

    bool remove(const T& value) { return m_data.erase(value) != 0; }

    void reserve(size_type size) { m_data.reserve(size); }

    size_type size() const { return static_cast<size_type>(m_data.size()); }

    void squeeze() { m_data.reserve(size()); }

    ObjectSet<T>& subtract(const ObjectSet<T>& other);

    void swap(ObjectSet<T>& other) { m_data.swap(other.m_data); }

    ObjectSet<T>& unite(const ObjectSet<T>& other);

    ObjectList<T> values() const { return toList(); }

    // iterators
    iterator begin() { return m_data.begin(); }
    const_iterator begin() const { return m_data.begin(); }
    const_iterator cbegin() const { return m_data.begin(); }
    const_iterator constBegin() const { return m_data.begin(); }

    iterator end() { return m_data.end(); }
    const_iterator end() const { return m_data.end(); }
    const_iterator cend() const { return m_data.end(); }
    const_iterator constEnd() const { return m_data.end(); }

    iterator erase(const_iterator pos) { return m_data.erase(pos); }
    iterator erase(const_iterator first, const_iterator last) { return m_data.erase(first, last); }

    iterator find(const T& value) { return m_data.find(value); }
    const_iterator find(const T& value) const { return m_data.find(value); }
    const_iterator constFind(const T& value) const { return find(value); }

    iterator insert(const T& value) { return m_data.insert(value).first; }

    // operators
    ObjectSet<T>& operator=(const ObjectSet<T>& other) = default;
    ObjectSet<T>& operator=(ObjectSet<T>&& other) = default;

    bool operator==(const ObjectSet<T>& other) const { return m_data == other.m_data; }
    bool operator!=(const ObjectSet<T>& other) const { return m_data != other.m_data; }

    ObjectSet<T>& operator<<(const T& value) { insert(value); return *this; }
    ObjectSet<T>& operator|=(const ObjectSet<T>& other) { unite(other); return *this; }
    ObjectSet<T>& operator|=(const T& value) { insert(value); return *this; }
    ObjectSet<T>& operator&=(const ObjectSet<T>& other) { intersect(other); return *this; }
    ObjectSet<T>& operator&=(const T& value) 
    {
        ObjectSet<T> result;
        if (contains(value))
            result.insert(value);
        return (*this = result);
    }

    ObjectSet<T>& operator+=(const ObjectSet<T>& other) { unite(other); return *this; }
    ObjectSet<T>& operator+=(const T& value) { insert(value); return *this; }
    ObjectSet<T>& operator-=(const ObjectSet<T>& other) { subtract(other); return *this; }
    ObjectSet<T>& operator-=(const T& value) { remove(value); return *this; }
    ObjectSet<T> operator|(const ObjectSet<T>& other) const 
    {
        ObjectSet<T> result = *this;
        result |= other;
        return result;
    }

    ObjectSet<T> operator&(const ObjectSet<T>& other) const 
    {
        ObjectSet<T> result = *this;
        result &= other;
        return result;
    }

    ObjectSet<T> operator+(const ObjectSet<T>& other) const 
    {
        ObjectSet<T> result = *this;
        result += other;
        return result;
    }

    ObjectSet<T> operator-(const ObjectSet<T>& other) const 
    {
        ObjectSet<T> result = *this;
        result -= other;
        return result;
    }

    ObjectList<T> toList() const;
    static ObjectSet<T> fromList(const ObjectList<T>& list);
private:
    std::unordered_set<T> m_data;
};

template <class T>
inline ObjectSet<T>& ObjectSet<T>::unite(const ObjectSet<T>& other)
{
    m_data.insert(other.m_data.begin(), other.m_data.end());
    return *this;
}

template <class T>
inline ObjectSet<T>& ObjectSet<T>::intersect(const ObjectSet<T>& other)
{
    auto iter = m_data.cbegin();
    while (iter != m_data.cend()) 
    {

        if (!other.contains(*iter)) 
            iter = m_data.erase(iter);
        else
            ++iter;
    }
    return *this;
}

template <class T>
inline bool ObjectSet<T>::intersects(const ObjectSet<T>& other) const
{
    for (const auto& item : m_data) 
    {
        if (other.contains(item)) 
            return true;
    }
    return false;
}

template <class T>
inline ObjectSet<T>& ObjectSet<T>::subtract(const ObjectSet<T>& other)
{
    auto iter = m_data.cbegin();
    while (iter != m_data.cend()) 
    {
        if (other.contains(*iter)) 
            iter = m_data.erase(iter);
        else
            ++iter;
    }
    return *this;
}

template <class T>
inline bool ObjectSet<T>::contains(const ObjectSet<T>& other) const
{
    for (const auto& item : other.m_data) 
    {
        if (!contains(item))
            return false;
    }
    return true;
}

template <typename T>
ObjectList<T> ObjectSet<T>::toList() const
{
    ObjectList<T> result;
    for (const auto& item : m_data)
        result.append(item);
    return result;
}

template <typename T>
ObjectSet<T> ObjectList<T>::toSet() const
{
    ObjectSet<T> result;
    result.reserve(size());
    for (const auto& item : m_data)
        result.insert(item);
    return result;
}

template <typename T>
ObjectSet<T> ObjectSet<T>::fromList(const ObjectList<T>& list)
{ return list.toSet(); }

template <typename T>
ObjectList<T> ObjectList<T>::fromSet(const ObjectSet<T>& set)
{ return set.toList(); }

template <class T>
class ObjectSetIterator
{
    typedef typename ObjectSet<T>::const_iterator const_iterator;
    ObjectSet<T> c;
    const_iterator i;
public:
    inline ObjectSetIterator(const ObjectSet<T>& set)
        : c(set), i(c.constBegin()) {}

    inline ObjectSetIterator& operator=(const ObjectSet<T>& set)
    { c = set; i = c.constBegin(); return *this; }

    inline void toFront() { i = c.constBegin(); }
    inline void toBack() { i = c.constEnd(); }
    inline bool hasNext() const { return i != c.constEnd(); }
    inline const T& next() { return *i++; }
    inline const T& peekNext() const { return *i; }
    inline bool hasPrevious() const { return i != c.constBegin(); }
    inline const T& previous() { return *--i; }
    inline const T& peekPrevious() const { const_iterator p = i; return *--p; }

    inline bool findNext(const T& value) 
    {
        while (i != c.constEnd()) 
        {
            if (*i++ == value) 
                return true;
        }
        return false;
    }

    inline bool findPrevious(const T& value) 
    {
        while (i != c.constBegin()) 
        {
            if (*(--i) == value)
                return true;
        }
        return false;
    }
};

template <typename T>
class MutableObjectSetIterator
{
    typedef typename ObjectSet<T>::iterator iterator;
    ObjectSet<T>* c;
    iterator i, n;
    inline bool item_exists() const { return c->constEnd() != n; }
public:
    inline MutableObjectSetIterator(ObjectSet<T>& set)
        : c(&set)
    {
        i = c->begin();
        n = c->end();
    }

    inline ~MutableObjectSetIterator() 
    {
    }

    inline MutableObjectSetIterator& operator=(ObjectSet<T>& set)
    {
        c = &set;
        i = c->begin();
        n = c->end();
        return *this;
    }

    inline void toFront() 
    {
        i = c->begin();
        n = c->end();
    }

    inline void toBack() 
    {
        i = c->end();
        n = i;
    }

    inline bool hasNext() const 
    {
        return c->constEnd() != i;
    }
    inline const T& next() 
    {
        n = i++;
        return *n;
    }
    inline const T& peekNext() const 
    {
        return *i;
    }
    inline bool hasPrevious() const 
    {
        return c->constBegin() != i;
    }
    inline const T& previous() 
    {
        n = --i;
        return *n;
    }
    inline const T& peekPrevious() const 
    {
        iterator p = i;
        return *--p;
    }
    inline void remove() 
    {
        if (c->constEnd() != n) 
        {
            i = c->erase(n);
            n = c->end();
        }
    }
    inline const T& value() const 
    {
        VSN_ASSERT(item_exists());
        return *n;
    }
    inline bool findNext(const T& value) 
    {
        while (c->constEnd() != (n = i)) if (*i++ == value)
            return true;
        return false;
    }
    inline bool findPrevious(const T& value) 
    {
        while (c->constBegin() != i) if (*(n = --i) == value) 
            return true;
        n = c->end();
        return false;
    }
};

} // namespace VSN

#endif // __VSN_OBJECTSET_H
