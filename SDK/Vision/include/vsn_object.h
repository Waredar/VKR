////////////////////////////////////////////////////////////////////////////////
/**
  \file 
  \brief \ru Класс Object является базовым классом для всех объектов сцены.
         \en Object class is the base class for all scene objects. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_OBJECT_H
#define __VSN_OBJECT_H

#include <vsn_objectlist.h>
#include <vsn_basicobject.h>
#include <vsn_objectdefs.h>
#include <vsn_metaobject.h>
#include <vsn_namespace.h>
#include <vsn_processevent.h>
#include <vsn_mutex.h>

namespace VSN {

#ifndef VSN_NO_EMIT
#define emit
#endif

class Mutex;
class Thread;
class ObjectPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс Object является базовым классом для всех объектов сцены.
           \en Object class is the base class for all scene objects. \~
    \ingroup Vision_Base
*/
// ---
class VSN_CLASS Object : public BasicObject
{
protected:
    typedef Object vsn_class;
private:
    VSN_OBJECT_BASE(Object);
public:
    /// \ru Конструктор c родителем. \en Constructor with parent. \~
    explicit Object(Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~Object();
public:
    /// \ru Установить родителя для объекта. \en NO TRANSLATION. \~
    void SetParent(Object* pParent);
    /// \ru Мьютекс объекта. \en Object mutex. \~
    Mutex* GetMutex();
    /// \ru Получить имя объекта. \en Returns name. \~
    String GetObjectName() const;
    /// \ru Установить имя объекту. \en Sets name. \~
    void SetObjectName(const String& name);
    /// \ru Вернуть тип объекта. \en TRANSLATION. \~
    bool IsControlType() const;
    /// \ru Вернуть указатель на родителя. \en NO TRANSLATION. \~
    Object* GetParent() const;
    /// \ru Вернуть вариант свойства по имени. \en NO TRANSLATION. \~
    Variant GetProperty(const String& name) const;
    // \ru Создать и установить свойств по имени и значению. \en NO TRANSLATION. \~
    bool SetProperty(const String& name, const Variant& value);

    bool Connect(const Object* pSender, const char* signalMethod, const char* location, const char* slotMethod, ConnectionType type = AutoConnection);
    static bool Connect(const Object* sender, const char* signalMethod, const char* location, const Object* receiver, const char* slotMethod, ConnectionType type = AutoConnection);
    static bool Connect(const Object* sender, const char* signalMethod, const Object* receiver, const char* slotMethod, ConnectionType type = AutoConnection, const char* location = nullptr);
    static bool Connect(const Object* sender, const MetaMethod& signalMethod, const Object* receiver, const MetaMethod& slotMethod, ConnectionType type = AutoConnection);
    bool Connect(const Object* sender, const char* signalMethod, const char* slotMethod, ConnectionType type = AutoConnection);

    static bool Disconnect(const Object* sender, const char* signalMethod, const Object *receiver, const char* slotMethod);
    static bool Disconnect(const Object* sender, const MetaMethod& signalMethod, const Object* receiver, const MetaMethod& slotMethod);
    static bool Disconnect(const Object* sender, const char* signalMethod, const char* location, const Object* receiver, const char* slotMethod);
    static bool Disconnect(const Object* sender, int signal_index, const Object* receiver, int method_index);
    bool Disconnect(const char* signalMethod = nullptr, const Object* receiver = nullptr, const char* slotMethod = nullptr) const;
    bool Disconnect(const char* signalMethod, const char* lineNumber, const Object* receiver = nullptr, const char* slotMethod = nullptr) const;
    bool Disconnect(const Object* receiver, const char* slotMethod = nullptr) const;

    // signal/slot method ptr
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
    static bool Connect(const Sender* sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver* receiver, SlotReturn(SlotClass::*slotMethod)(SlotArgs...), ConnectionType type = AutoConnection);
    // функция ptr или лямбда
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
    static bool Connect(const Sender *sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver* receiver, T slot, ConnectionType type = AutoConnection);
    // signal/slot method ptr
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
    static bool Disconnect(const Sender* sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver *receiver, SlotReturn(SlotClass::*slotMethod)(SlotArgs...));
    // signal method ptr, nullptr slot
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver>
    static bool Disconnect(const Sender* sender, void (SignalClass::* signalMethod)(SignalArgs...),
        const Receiver* receiver, std::nullptr_t slotMethod = nullptr);
    // функция ptr или лямбда
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
    static bool Disconnect(const Sender* sender, void (SignalClass::*signalMethod)(SignalArgs...), 
        const Receiver *receiver, T slot);

    /// \ru Вернуть признак блокировки сигналов этого объекта. \en NO TRANSLATION. \~
    bool IsSignalsBlocked() const;
    /// \ru Установить признак блокировки сигналов этого объекта. \en NO TRANSLATION. \~
    bool SetBlockSignals(bool bBlock);

    /// \ru Добавить слушателя событий. \en NO TRANSLATION. \~
    void AddEventListener(Object* pObject);
    /// \ru Удалить слушателя событий. \en NO TRANSLATION. \~
    void RemoveEventListener(Object* pObject);
    /// \ru Вернуть указатель на объект, который с генерировал сигнал. \en NO TRANSLATION. \~
    Object* GetSender() const;
public:
    VSN_SIGNAL(Public, ObjectNameModified, void ObjectNameModified(const String& objectName), objectName)
    VSN_SIGNAL(Public, Destroyed, void Destroyed(Object* object = nullptr), object)
    VSN_SLOT  (Public, DeferredDelete, void DeferredDelete())
public:
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    Thread* GetThread() const;
    /// \ru Связывание c потоком. \en NO TRANSLATION. \~
    void BindWithThread(Thread* thread);
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    int StartTimer(int interval, TimerType timerType = tt_CoarseTimer);
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    void KillTimer(int id);
    /// \ru Вернуть список указателей детей. \en NO TRANSLATION.
    const ObjectList<Object*>& GetChildren() const;
    /// \ru Вернуть указателей на ребенка. \en NO TRANSLATION.
    template<typename T>
    inline T FindChild(const String& objName = String()) const;
    /// \ru Вернуть список указателей детей. \en NO TRANSLATION.
    template<typename T>
    inline ObjectList<T> FindChildren(const String& objName = String(), VSN::ChildFindingPolicies policies = VSN::FindAllNestedChildren) const;
public:
    virtual bool OnEvent(ProcessEvent* event);
    virtual bool OnEventFilter(Object* object, ProcessEvent* event);
protected:
    virtual void OnChildEvent(ChildEvent* event);
    virtual void OnCustomEvent(ProcessEvent* event);
protected:
    static std::unordered_map<std::type_index, MetaObject *>& GetMetaObjectsMap();
    static Mutex& GetMetaObjectMutex();
protected:
    virtual void OnConnectNotify(const char* pSignal) const;
    virtual void OnDisconnectNotify(const char* pSignal) const;
    virtual void OnConnectNotify(const MetaMethod& signalMethod) const;
    virtual void OnDisconnectNotify(const MetaMethod& signal) const;
protected:
    Object(ObjectPrivate& d, Object* pParent = nullptr);
private:
    template<class T>
    void vsn_FindChildren(const String& objName, VSN::ChildFindingPolicies policies, ObjectList<T>& list) const;
protected:
    friend class MetaObject;
    friend class ThreadData;
    friend class BaseApplication;
    friend class BaseApplicationPrivate;
    friend class ApplicationPrivate;
    friend class Application;
    VSN_DECLARE_PRIVATE(Object);
};

// ---
template<typename T>
inline T Object::FindChild(const String& objName) const
{
    T pFindObject = nullptr;
    const ObjectList<Object*>& children = GetChildren();
    for (Object* pCurChild : children)
    {
        if (T pChild = dynamic_cast<T>(pCurChild))
        {
            if (objName.IsEmpty() || pChild->GetObjectName() == objName)
            {
                pFindObject = pChild;
                break;
            }
        }
        if (pFindObject = pCurChild->FindChild<T>(objName))
            break;
    }
    return pFindObject;
}
// ---
template<typename T>
inline ObjectList<T> Object::FindChildren(const String& objName, VSN::ChildFindingPolicies policies) const
{
    ObjectList<T> list;
    vsn_FindChildren<T>(objName, policies, list);
    return list;
}

template<class T>
void Object::vsn_FindChildren(const String& objName, VSN::ChildFindingPolicies policies, ObjectList<T>& list) const
{
    const ObjectList<Object*>& children = GetChildren();
    for (Object* pCurChild : children)
    {
        if (T pChild = dynamic_cast<T>(pCurChild))
        {
            if (objName.IsEmpty() || pChild->GetObjectName() == objName)
                list.add(pChild);
        }
        if (policies & VSN::FindAllNestedChildren)
            pCurChild->vsn_FindChildren<T>(objName, policies, list);
    }
}

// ---
template <class T>
inline T vobject_cast(Object* pObject) { return dynamic_cast<T>(pObject); }
// ---
template <class T>
inline T vobject_cast(const Object* pObject) { return dynamic_cast<T>(pObject); }
// ---
template <class T>
inline const char* vobject_interface_iid() { return 0; }

#include <vsn_objectinternal.h>

} // namespace VSN

#endif // __VSN_OBJECT_H
