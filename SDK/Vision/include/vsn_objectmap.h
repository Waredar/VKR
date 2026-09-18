#ifndef __VSN_OBJECTMAP_H
#define __VSN_OBJECTMAP_H

#include <initializer_list>
#include <map>

#include <vsn_objectset.h>
#include <vsn_objectlist.h>
#include <vsn_global.h>

namespace VSN {


template <typename Key> inline bool vsnMapLessThanKey(const Key& key1, const Key& key2)
{ return key1 < key2; }

template <typename Ptr> inline bool vsnMapLessThanKey(Ptr* key1, Ptr* key2)
{
    static_assert(sizeof(vuintptr) == sizeof(Ptr*), "vsnMapLessThanKey: vuintptr is not large enough to contain a ptr");
    return vuintptr(key1) < vuintptr(key2);
}

template <typename Ptr> inline bool vsnMapLessThanKey(const Ptr* key1, const Ptr* key2)
{
    static_assert(sizeof(vuintptr) == sizeof(const Ptr*), "vsnMapLessThanKey: vuintptr is not large enough to contain a ptr");
    return vuintptr(key1) < vuintptr(key2);
}

template <typename Key>
class vsnMapCompare
{
public:
    bool operator()(const Key& a, const Key& b)  const { return vsnMapLessThanKey(a, b); }
};

template <typename Key, typename Val, typename Compare = vsnMapCompare<Key>>
class ObjectMap;


template <typename Key, typename Val, typename C>
class ObjectMap
{
public:
    class iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;

        using pointer           = Val*;
        using reference         = Val&;

        using difference_type   = typename std::map<Key, Val, C>::difference_type;
        using size_type         = typename std::map<Key, Val, C>::difference_type;
        using value_type        = Val;

        iterator() = default;

        iterator(typename std::map<Key, Val, C>::iterator iter)
            : m_iter(std::move(iter)) {}

        const Key& key() const { return m_iter->first; }

        Val& value() const { return m_iter->second; }

        std::pair<const Key, Val>& pair() const { return *m_iter; }

        Val& operator*() const { return value(); }

        Val* operator->() const { return &value(); }

        bool operator==(iterator other) const { return m_iter == other.m_iter; }
        bool operator!=(iterator other) const { return m_iter != other.m_iter; }

        iterator& operator+=(size_type n) { std::advance(m_iter, n); return *this; }
        iterator& operator-=(size_type n) { std::advance(m_iter, -n); return *this; }
        iterator operator+(size_type n) const { auto tmp = m_iter; std::advance(tmp, n); return tmp; }
        iterator operator-(size_type n) const { auto tmp = m_iter; std::advance(tmp, -n); return tmp; }
        iterator& operator++() { ++m_iter; return *this; }
        iterator operator++(int) { return m_iter++; }
        iterator& operator--() { --m_iter; return *this; }
        iterator operator--(int) { return m_iter--; }

        friend class ObjectMap<Key, Val, C>;
    private:
        typename std::map<Key, Val, C>::iterator m_iter;
    };

    class const_iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;

        using pointer = const Val*;
        using reference = const Val&;

        using difference_type = typename std::map<Key, Val, C>::difference_type;
        using size_type = typename std::map<Key, Val, C>::difference_type;
        using value_type = Val;

        const_iterator() = default;

        const_iterator(typename std::map<Key, Val, C>::const_iterator iter)
            : m_iter(std::move(iter)) {}

        const_iterator(iterator iter)
            : m_iter(std::move(iter.m_iter)) {}

        const Key& key() const { return m_iter->first; }

        const Val& value() const { return m_iter->second; }

        const std::pair<const Key, Val>& pair() const { return *m_iter; }

        const Val& operator*() const { return value(); }
        const Val* operator->() const { return &value(); }

        bool operator==(const_iterator other) const { return m_iter == other.m_iter; }
        bool operator!=(const_iterator other) const { return m_iter != other.m_iter; }

        const_iterator& operator+=(size_type n) { std::advance(m_iter, n); return *this; }
        const_iterator& operator-=(size_type n) { std::advance(m_iter, -n); return *this; }

        const_iterator operator+(size_type n) const { auto tmp = m_iter; std::advance(tmp, n); return tmp; }
        const_iterator operator-(size_type n) const { auto tmp = m_iter; std::advance(tmp, -n); return tmp; }

        const_iterator& operator++() { ++m_iter; return *this; }
        const_iterator operator++(int) { return m_iter++; }
        const_iterator& operator--() { --m_iter; return *this; }
        const_iterator operator--(int) { return m_iter--; }

        friend class ObjectMap<Key, Val, C>;

        friend bool operator==(iterator iter1, const_iterator iter2) { return iter2.operator==(iter1); }
        friend bool operator!=(iterator iter1, const_iterator iter2) { return iter2.operator!=(iter1); }
    private:
        typename std::map<Key, Val, C>::const_iterator m_iter;
    };

    using difference_type = typename std::map<Key, Val, C>::difference_type;
    using pointer = Val*;
    using reference = Val&;
    using size_type = typename std::map<Key, Val, C>::difference_type;   // signed instead of unsigned
    using value_type = Val;

    using key_type = typename std::map<Key, Val, C>::key_type;
    using mapped_type = typename std::map<Key, Val, C>::mapped_type;
    using key_compare = typename std::map<Key, Val, C>::key_compare;

    using allocator_type = typename std::map<Key, Val, C>::allocator_type;

    using const_pointer = const Val*;
    using const_reference = const Val&;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
public:
    ObjectMap() = default;

    ObjectMap(const ObjectMap<Key, Val, C>& other) = default;
    ObjectMap(ObjectMap<Key, Val, C>&& other) = default;

    ObjectMap(std::initializer_list<std::pair<const Key, Val>> list, const C& compare = C())
        : m_data(list, compare) {}

    explicit ObjectMap(C compare)
        : m_data(compare) {}

    explicit ObjectMap(const std::map<Key, Val, C>& other)
        : m_data(other) {}

    template<typename Input_Iterator>
    ObjectMap(Input_Iterator first, Input_Iterator last, const C& compare = C())
        : m_data(first, last, compare) {}

    ~ObjectMap() = default;
public:
    // methods
    void clear() { m_data.clear(); }
    bool contains(const Key& key) const { return m_data.find(key) != m_data.end(); }

    size_type count(const Key& key) const { return m_data.count(key); }
    size_type count() const { return size(); }

    bool empty() const { return m_data.empty(); }

    bool isEmpty() const { return m_data.empty(); }

    ObjectPair<iterator, iterator> equal_range(const Key& key) { return m_data.equal_range(key); }
    ObjectPair<const_iterator, const_iterator> equal_range(const Key& key) const { return m_data.equal_range(key); }

    iterator erase(const_iterator iter) { return m_data.erase(iter.m_iter); }

    Val& first() { return begin().value(); }
    const Val& first() const { return begin().value(); }
    const Key& firstKey() const { return begin().key(); }
    iterator find(const Key& key) { return m_data.find(key); }
    const_iterator find(const Key& key) const { return m_data.find(key); }
    const_iterator constFind(const Key& key) const { return m_data.find(key); }
    iterator insert(const std::pair<const Key, Val>& data) 
    {
        m_data[data.first] = data.second;
        return m_data.lower_bound(data.first);
//        return m_data.insert_or_assign(data.first, data.second).first; // С++17
    }

    iterator insert(const Key& key, const Val& value) 
    {
        m_data[key] = value;
        return m_data.lower_bound(key);
//        return m_data.insert_or_assign(key, value).first; // С++17
    }
    iterator insert(const_iterator hint, const Key& key, const Val& value) 
    {
        auto oldSize = m_data.size();
        auto iter = m_data.emplace_hint(hint.m_iter, key, value);

        if (m_data.size() == oldSize)
            iter->second = value;
        return iter;
    }

    const Key key(const Val& value, const Key& defaultKey = Key()) const;

    ObjectList<Key> keys() const;
    ObjectList<Key> keys(const Val& value) const;

    Val& last() { return (end() - 1).value(); }
    const Val& last() const { return (end() - 1).value(); }
    const Key& lastKey() const { return (end() - 1).key(); }

    iterator lowerBound(const Key& key) { return m_data.lower_bound(key); }
    const_iterator lowerBound(const Key& key) const { return m_data.lower_bound(key); }

    size_type remove(const Key& key) { return m_data.erase(key); }

    size_type size() const { return static_cast<size_type>(m_data.size()); }

    void swap(ObjectMap<Key, Val, C>& other) { std::swap(m_data, other.m_data); }

    Val take(const Key& key) 
    {
        auto iter = m_data.find(key);
        if (iter == m_data.end())
            return Val();
        Val retval = std::move(iter->second);
        m_data.erase(iter);
        return retval;
    }

    iterator upperBound(const Key& key) { return m_data.upper_bound(key); }
    const_iterator upperBound(const Key& key) const { return m_data.upper_bound(key); }

    ObjectList<Key> uniqueKeys() const;

    ObjectMap<Key, Val, C>& unite(const ObjectMap<Key, Val, C>& other) 
    {
        m_data.insert(other.m_data.begin(), other.m_data.end());
        return *this;
    }

    const Val value(const Key& key) const;
    const Val value(const Key& key, const Val& defaultValue) const;

    ObjectList<Val> values() const;

    std::map<Key, Val, C> toStdMap() const;

    iterator begin() { return m_data.begin(); }
    const_iterator begin() const { return m_data.begin(); }

    const_iterator constBegin() const { return m_data.begin(); }
    const_iterator cbegin() const { return m_data.begin(); }

    iterator end() { return m_data.end(); }
    const_iterator end() const { return m_data.end(); }
    const_iterator constEnd() const { return m_data.end(); }
    const_iterator cend() const { return m_data.end(); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    ObjectMap<Key, Val, C>& operator=(const ObjectMap<Key, Val, C>& other) = default;
    ObjectMap<Key, Val, C>& operator=(ObjectMap<Key, Val, C>&& other) = default;

    bool operator==(const ObjectMap<Key, Val, C>& other) const { return m_data == other.m_data; }

    bool operator!=(const ObjectMap<Key, Val, C>& other) const { return m_data != other.m_data; }

    Val& operator[](const Key& key);
    const Val operator[](const Key& key) const;
private:
    std::map<Key, Val, C> m_data;
};

template <class Key, class Val, class C>
const Key ObjectMap<Key, Val, C>::key(const Val& value, const Key& defaultKey) const
{
    const_iterator iter = begin();
    while (iter != end()) 
    {
        if (iter.value() == value) 
            return iter.key();
        ++iter;
    }
    return defaultKey;
}

template <class Key, class Val, class C>
ObjectList<Key> ObjectMap<Key, Val, C>::keys() const
{
    ObjectList<Key> retval;
    const_iterator iter = begin();
    while (iter != end()) 
    {
        retval.add(iter.key());
        ++iter;
    }
    return retval;
}

template <class Key, class Val, class C>
ObjectList<Key> ObjectMap<Key, Val, C>::keys(const Val& value) const
{
    ObjectList<Key> retval;
    const_iterator iter = begin();
    while (iter != end()) 
    {
        if (iter.value() == value) 
            retval.add(iter.key());
        ++iter;
    }
    return retval;
}

template <class Key, class Val, class C>
ObjectList<Key> ObjectMap<Key, Val, C>::uniqueKeys() const
{
    ObjectList<Key> retval;
    retval.reserve(size());
    for (const auto& item : m_data) 
    {
        if (!retval.empty() && retval.last() == item.first) 
            continue;
        retval.add(item.first);
    }
    return retval;
}

template <class Key, class Val, class C>
const Val ObjectMap<Key, Val, C>::value(const Key& key) const
{
    auto iter = m_data.find(key);
    if (iter == m_data.end()) 
        return Val();
    return iter->second;
}

template <class Key, class Val, class C>
const Val ObjectMap<Key, Val, C>::value(const Key& key, const Val& defaultValue) const
{
    auto iter = m_data.find(key);
    if (iter == m_data.end()) 
        return defaultValue;
    return iter->second;
}

template <class Key, class Val, class C>
ObjectList<Val> ObjectMap<Key, Val, C>::values() const
{
    ObjectList<Val> retval;
    const_iterator iter = begin();
    while (iter != end()) 
    {
        retval.add(iter.value());
        ++iter;
    }
    return retval;
}

template <class Key, class Val, class C>
const Val ObjectMap<Key, Val, C>::operator[](const Key& key) const
{ return value(key); }

template <class Key, class Val, class C>
Val& ObjectMap<Key, Val, C>::operator[](const Key& key)
{
    auto range = m_data.equal_range(key);
    if (range.first == range.second) 
    {
        auto iter = m_data.emplace(key, Val()).first;
        return iter->second;
    }
    auto iter = --range.second;
    return iter->second;
}

template <class Key, class Val, class C>
std::map<Key, Val, C> ObjectMap<Key, Val, C>::toStdMap() const
{
    std::map<Key, Val, C> map;
    const_iterator iter = end();
    while (iter != begin()) 
    {
        --iter;
        map.insert(std::pair<Key, Val>(iter.key(), iter.value()));
    }
    return map;
}

} // namespace VSN

#endif // __VSN_OBJECTMAP
