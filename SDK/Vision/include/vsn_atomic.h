#ifndef __VSN_ATOMIC_H
#define __VSN_ATOMIC_H

#include <atomic>
#include <vsn_global.h>

namespace VSN {

#ifndef ATOMIC_INT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE 0
#endif

#ifndef ATOMIC_POINTER_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE 0
#endif

/* AtomicInt */
class AtomicInt
{
public:
    inline AtomicInt() : m_data(0) {}
    inline AtomicInt(int value) : m_data(value) {}
    inline AtomicInt(const AtomicInt &other) 
    {
        int data = other.Load();
        Store(data);
    }
public:
    inline AtomicInt &operator=(const AtomicInt &other)
    {
        int data = other.Load();
        Store(data);
        return *this;
    }
    inline AtomicInt& operator=(int data) 
    {
        Store(data);
        return *this;
    }
public:
    inline int Load() const { return m_data.load(); }
    inline int LoadRelaxed() const { return m_data.load(std::memory_order_relaxed); }
    inline int LoadAcquire() { return m_data.load(std::memory_order_acquire); }

    inline void Store(int newValue) { m_data.store(newValue); }
    inline void StoreRelaxed(int newValue) { m_data.store(newValue, std::memory_order_relaxed); }
    inline void StoreRelease(int newValue) { m_data.store(newValue, std::memory_order_release); }

    static bool IsReferenceCountingNative() { return ATOMIC_INT_LOCK_FREE == 2; }
    static bool IsReferenceCountingWaitFree() { return ATOMIC_INT_LOCK_FREE == 2; }

    inline bool AddRef() { int newValue = ++m_data; return newValue != 0; }
    inline bool Release() { int newValue = --m_data; return newValue != 0;}

    static bool IsTestAndSetNative() { return ATOMIC_INT_LOCK_FREE == 2; }
    static bool IsTestAndSetWaitFree() { return ATOMIC_INT_LOCK_FREE == 2; }

    inline bool CheckAndSetRelaxed(int expectedValue, int newValue) { return m_data.compare_exchange_strong(expectedValue, newValue, std::memory_order_relaxed); }
    inline bool CheckAndSetAcquire(int expectedValue, int newValue) { return m_data.compare_exchange_strong(expectedValue, newValue, std::memory_order_acquire); }
    inline bool CheckAndSetRelease(int expectedValue, int newValue) { return m_data.compare_exchange_strong(expectedValue, newValue, std::memory_order_release); }
    inline bool CheckAndSetOrdered(int expectedValue, int newValue) { return m_data.compare_exchange_strong(expectedValue, newValue, std::memory_order_seq_cst); }

    static bool IsFetchAndStoreNative() { return ATOMIC_INT_LOCK_FREE == 2; }
    static bool IsFetchAndStoreWaitFree() { return ATOMIC_INT_LOCK_FREE == 2; }

    inline int FetchAndStoreRelaxed(int newValue) { return m_data.exchange(newValue, std::memory_order_relaxed); }
    inline int FetchAndStoreAcquire(int newValue) { return m_data.exchange(newValue, std::memory_order_acquire); }
    inline int FetchAndStoreRelease(int newValue) { return m_data.exchange(newValue, std::memory_order_release);}
    inline int FetchAndStoreOrdered(int newValue) { return m_data.exchange(newValue, std::memory_order_seq_cst);}

    static bool IsFetchAndAddNative() { return ATOMIC_INT_LOCK_FREE == 2; }
    static bool IsFetchAndAddWaitFree() { return ATOMIC_INT_LOCK_FREE == 2; }

    inline int FetchAndAddRelaxed(int valueToAdd) { return m_data.fetch_add(valueToAdd, std::memory_order_relaxed); }
    inline int FetchAndAddAcquire(int valueToAdd) { return m_data.fetch_add(valueToAdd, std::memory_order_acquire); }
    inline int FetchAndAddRelease(int valueToAdd) { return m_data.fetch_add(valueToAdd, std::memory_order_release); }
    inline int FetchAndAddOrdered(int valueToAdd) { return m_data.fetch_add(valueToAdd, std::memory_order_seq_cst); }
public:
    std::atomic<int> m_data;
};


template <typename T>
class AtomicPointer
{
public:
    AtomicPointer(T *value = 0) : m_data(value) {
    }

    AtomicPointer(const AtomicPointer<T> &other) {
        T *data = other.load();
        store(data);
    }

    AtomicPointer<T> &operator=(const AtomicPointer<T> &other) {
        T *data = other.load();
        store(data);

        return *this;
    }

    AtomicPointer<T> &operator=(T *data) {
        store(data);
        return *this;
    }

    T *load() const {
        return m_data.load();
    }

    T *loadAcquire() {
        return m_data.load(std::memory_order_acquire);
    }

    void store(T *newValue) {
        m_data.store(newValue);
    }

    void storeRelease(T *newValue) {
        m_data.store(newValue, std::memory_order_release);
    }

    //   
    static bool isTestAndSetNative() {
        return ATOMIC_POINTER_LOCK_FREE == 2;
    }

    static bool isTestAndSetWaitFree() {
        return ATOMIC_POINTER_LOCK_FREE == 2;
    }

    bool testAndSetRelaxed(T *expectedValue, T *newValue) {
        return m_data.compare_exchange_strong(expectedValue, newValue, std::memory_order_relaxed);
    }

    bool testAndSetAcquire(T *expectedValue, T *newValue) {
        return m_data.compare_exchange_strong(expectedValue, newValue, std::memory_order_acquire);
    }

    bool testAndSetRelease(T *expectedValue, T *newValue) {
        return m_data.compare_exchange_strong(expectedValue, newValue, std::memory_order_release);
    }

    bool testAndSetOrdered(T *expectedValue, T *newValue) {
        return m_data.compare_exchange_strong(expectedValue, newValue, std::memory_order_seq_cst);
    }

    //
    static bool isFetchAndStoreNative() {
        return ATOMIC_POINTER_LOCK_FREE == 2;
    }

    static bool isFetchAndStoreWaitFree() {
        return ATOMIC_POINTER_LOCK_FREE == 2;
    }

    T *fetchAndStoreRelaxed(T *newValue)  {
        return m_data.exchange(newValue, std::memory_order_relaxed);
    }

    T *fetchAndStoreAcquire(T *newValue) {
        return m_data.exchange(newValue, std::memory_order_acquire);
    }

    T *fetchAndStoreRelease(T *newValue) {
        return m_data.exchange(newValue, std::memory_order_release);
    }

    T *fetchAndStoreOrdered(T *newValue) {
        return m_data.exchange(newValue, std::memory_order_seq_cst);
    }

    //
    static bool isFetchAndAddNative() {
        return ATOMIC_POINTER_LOCK_FREE == 2;
    }

    static bool isFetchAndAddWaitFree() {
        return ATOMIC_POINTER_LOCK_FREE == 2;
    }

    T *fetchAndAddRelaxed(std::ptrdiff_t valueToAdd) {
        return m_data.fetch_add(valueToAdd, std::memory_order_relaxed);
    }

    T *fetchAndAddAcquire(std::ptrdiff_t valueToAdd) {
        return m_data.fetch_add(valueToAdd, std::memory_order_acquire);
    }

    T *fetchAndAddRelease(std::ptrdiff_t valueToAdd){
        return m_data.fetch_add(valueToAdd, std::memory_order_release);
    }

    T *fetchAndAddOrdered(std::ptrdiff_t valueToAdd){
        return m_data.fetch_add(valueToAdd, std::memory_order_seq_cst);
    }

private:
    std::atomic<T*> m_data;
};

template <typename T>
inline void vAtomicAssign(T *&d, T *x)
{
    if (d == x)
        return;
    x->ref.ref();
    if (!d->ref.deref())
        delete d;
    d = x;
}

template <typename T>
inline void vAtomicDetach(T *&d)
{
    if (d->ref.load() == 1)
        return;
    T *x = d;
    d = new T(*d);
    if (!x->ref.deref())
        delete x;
}

} // namespace VSN

#endif // __VSN_ATOMIC_H
