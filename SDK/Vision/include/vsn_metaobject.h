////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Набор макросов и шаблонов, реализующих простую и портативную систему RTTI.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#include <vsn_object.h>

#ifndef __VSN_METAOBJECT_H
#define __VSN_METAOBJECT_H

#include <map>
#include <typeindex>
#include <string>

#include <vsn_string.h>
#include <vsn_meta.h>
#include <vsn_global.h>

namespace VSN {

class Object;
/* MetaClassInfo */
class VSN_CLASS MetaClassInfo
{
public:
    MetaClassInfo() = default;
    MetaClassInfo(const String& name, const String& value)
        : m_name(name)
        , m_value(value)
    {
    }
public:
    const String& GetName() const { return m_name; }
    const String& GetValue() const { return m_value; }
private:
    String m_name;
    String m_value;
};

class MetaObjectPrivate;
/* MetaObject */
class VSN_CLASS MetaObject
{
public:
    virtual ~MetaObject();
public:
    virtual MetaClassInfo GetMetaClassInfo(int index) const = 0;
    virtual int GetClassInfoCount() const = 0;
    virtual const char* GetMetaClassName() const = 0;
    virtual const MetaObject* GetSuperClass() const = 0;
    size_t GetClassInfoOffset() const;
    bool IsInherits(const MetaObject* pMetaObject) const;
    Object* Cast(Object* pObj) const;
    const Object* Cast(const Object* pObj) const;

    virtual int GetMethodCount() const = 0;
    virtual const MetaMethod& GetMethodByIndex(int index) const = 0;
    MetaMethod GetMethodByStorage(const AbsStorage& temp) const;
    int GetMethodOffset() const;
    virtual const MetaMethod& GetMethod(const Internal::AbsStorageFunction& method) const = 0;

    virtual MetaEnum GetEnumByIndex(int index) const = 0;
    virtual int GetEnumCount() const = 0;
    int GetEnumOffset() const;

    int GetIndexMethod(const String& method) const;
    int GetIndexEnumerator(const String& pName) const;
    int GetIndexSignal(const String& signal) const;
    int GetIndexSlot(const String& slot) const;

    int GetIndexProp(const String& name) const;
    virtual MetaProperty GetPropByIndex(int index) const = 0;
    virtual int GetPropCount() const = 0;
    int GetPropOffset() const;

    template<class MethodClass, class... MethodArgs>
    const MetaMethod& Method(void (MethodClass::*methodPtr)(MethodArgs...)) const;
};

template<class MethodClass, class... MethodArgs>
const MetaMethod& MetaObject::Method(void (MethodClass::*methodPtr)(MethodArgs...)) const
{
    StorageImpl<void (MethodClass::*)(MethodArgs...)> storage = methodPtr;
    const MetaMethod& result = GetMethod(storage);
    return result;
}

class MetaObjectRealizationPrivate;
/* MetaObjectRealization */
class VSN_CLASS MetaObjectRealization : public MetaObject
{
public:
    void SetClassInfo(const String& name, const String& value);
    MetaClassInfo GetMetaClassInfo(int index) const override;
    int GetClassInfoCount() const override;

    MetaEnum GetEnumByIndex(int index) const override;
    int GetEnumCount() const override;

    const MetaMethod& GetMethodByIndex(int index) const override;
    int GetMethodCount() const override;

    MetaProperty GetPropByIndex(int index) const override;
    int GetPropCount() const override;

    int SetEnum(const String& name, std::type_index id, const String& scope);

    const MetaMethod& GetMethod(const Internal::AbsStorageFunction& method) const override;
public:
    void BindMethodBegin(const String& name, MetaMethod method);
    void BindMethodBegin(const String& name, MetaMethod::AccessType access, MetaMethod::MethodType type);
    // properties
    void BindPropRead(const String& name, const char* dataType, std::shared_ptr<AbsReadBase> ptrMethod);
    void BindPropWrite(const String& name, std::shared_ptr<AbsWriteBase> ptrMethod);
    void BindPropBool(const String& name, AbsReadBase* method, MetaProperty::PropType type);
    void BindPropInt(const String& name, int value, MetaProperty::PropType type);
protected:
    static int CalcCountStorage(const char* va_args);
    bool InstallMetaMethod(const String& name, MetaMethod::MethodType type, const String& args, 
        std::shared_ptr<const AbsStorage> methodStorage, MetaMethod::AccessType access);
    bool InsertMetaMethodByName(const String& className, const String& name, 
        std::shared_ptr<const AbsStorage> methodStorage, MetaMethod::MethodType type);
    void InsertMetaMethodByType(MetaMethod::MethodType type, const String& tokenKey, const MetaMethod& data);
    void InsertUpdateProp(const String& name, std::shared_ptr<AbsStorage> ptrStorageMethod);
    ObjectMap<String, MetaMethod>& GetMapMethodByType(MetaMethod::MethodType type) const;
    ObjectMap<String, MetaProperty>& GetMapProperties();
protected:
    MetaObjectRealization();
protected:
    std::shared_ptr<MetaObjectRealizationPrivate> m_ptrObjectImpl;
};

/* TMetaObjectRealization */
template<class T>
class TMetaObjectRealization : public MetaObjectRealization
{
public:
    TMetaObjectRealization();// = default;
public:
    void PostBuild();
    const char* GetMetaClassName() const override;
    const char* GetInterface_iid() const;
    const MetaObject* GetSuperClass() const override;
public:
    // signals
    template<class M>
    void BindMethodEnd(const String& name, M method, MetaMethod::MethodType type);
    // slots, invokables
    template<class M>
    void BindMethod(const String& name, M method, MetaMethod::MethodType type, const String& args, MetaMethod::AccessType access);
    // properties
    template<class M>
    void BindPropNotify(const String& name, M method);
};

template<class T>
TMetaObjectRealization<T>::TMetaObjectRealization()
{
}

template<class T>
void TMetaObjectRealization<T>::PostBuild()
{
    // вызывает перегруженную версию, чтобы обеспечить обработку других перегрузок
    T::vsn_Overload(VSN_VALUE_NUMBER<VSN_DEF_VALUE_ZERO>());
}

template<class T>
const char* TMetaObjectRealization<T>::GetMetaClassName() const
{ return T::vsn_className(); }

template<class T>
inline const char* vobject_interface_iid();

template<class T>
const char* TMetaObjectRealization<T>::GetInterface_iid() const
{ return vobject_interface_iid<T *>(); }

template<class T>
const MetaObject* TMetaObjectRealization<T>::GetSuperClass() const
{ return &T::vsn_parent::GetStaticMetaObject(); }

template<>
inline const MetaObject* TMetaObjectRealization<Object>::GetSuperClass() const
{ return nullptr; }

template<class T> template<class M>
void TMetaObjectRealization<T>::BindMethodEnd(const String& name, M method, MetaMethod::MethodType type)
{
    if (name.IsEmpty())
        return;
    // обновить основную карту
    auto methodStorage = std::make_shared<StorageImpl<M>>(method);
    if (!InsertMetaMethodByName(T::GetStaticMetaObject().GetMetaClassName(), name, methodStorage, type))
        methodStorage.reset();
}

template<class T> template<class M>
void TMetaObjectRealization<T>::BindMethod(const String& name, M method, MetaMethod::MethodType type, const String& args, MetaMethod::AccessType access)
{
    // обновить основную карту
    if (name.IsEmpty() || args.IsEmpty())
        return;
    auto methodStorage = std::make_shared<StorageImpl<M>>(method);
    if (!InstallMetaMethod(name, type, args, methodStorage, access))
        methodStorage.reset();
}

template<class T> template<class M>
void TMetaObjectRealization<T>::BindPropNotify(const String& name, M method)
{
    if (name.IsEmpty())
        return;
    InsertUpdateProp(name, std::make_shared<StorageImpl<M>>(method));
}

template<class T>
void vsn_namespace_register_enum(const char* name, std::type_index id, const char* scope)
{
    const_cast<TMetaObjectRealization<T>&>(T::GetStaticMetaObject()).SetEnum(name, id, scope);
}

} // namespace VSN

#endif /* __VSN_METAOBJECT_H */
