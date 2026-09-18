////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru AbsVisionComponent - это базовый класс для любых компонентов Vision.
               AbsVisionComponent служит для обеспечения однородности классов и связи 
               между ними.
           \en AbsVisionComponent class is a base class for any Vision component.
               AbsVisionComponent class provides homogeneity of classes and their interaction. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ABSVISIONCOMPONENT_H
#define __VSN_ABSVISIONCOMPONENT_H

#include <vsn_object.h>
#include <vsn_visionwork.h>
#include <vsn_nodekey.h>
#include <vsn_global.h>

namespace VSN {

class InternalNodeMaps;
typedef std::shared_ptr<InternalNodeMaps> InternalNodeMapsPtr;

class AbsVisionComponentPrivate;
//------------------------------------------------------------------------------
/** \brief   \ru AbsVisionComponent - это базовый класс для любых компонентов Vision.
                 AbsVisionComponent служит для обеспечения однородности классов и связи   
                 между ними.
             \en AbsVisionComponent class is a base class for any Vision component.
                 AbsVisionComponent class provides homogeneity of classes and their interaction. \~
    \ingroup NO GROUP
*/
class VSN_CLASS AbsVisionComponent : public Object
{
    VSN_OBJECT(AbsVisionComponent);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit AbsVisionComponent(Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~AbsVisionComponent();
protected:
    /// \ru Вернуть уникальный ключ Essence. \en Returns unique Essence key. \~
    NodeKey GetTopEssenceKey() const;
    virtual ObjectVector<VisionWorkPtr> WorksToExecute(int64 time);

    virtual void OnInstalled();
    virtual void OnUninstalled();

    /// \ru Вызывается в контексте Engine. \en Called in Engine context. \~
    virtual void OnEngineStarting() {}
    /// \ru Вызывается в контексте Engine. \en Called in Engine context. \~
    virtual void OnEngineClosing() {}
protected:
    template<class Frontend>
    void InstallInternalKind(const InternalNodeMapsPtr& functor);
    void InstallInternalKind(const MetaObject& pObject, const InternalNodeMapsPtr& functor);
protected:
    AbsVisionComponent(AbsVisionComponentPrivate& d, Object* parent);
private:
    friend class VisionEngine;
    friend class VisionManager;
    friend class GraphicsSceneEngine;
    VSN_DECLARE_EX_PRIVATE(AbsVisionComponent);
};

template<class Frontend>
void AbsVisionComponent::InstallInternalKind(const InternalNodeMapsPtr& functor)
{
    InstallInternalKind(Frontend::GetStaticMetaObject(), functor);
}

} // namespace VSN

#endif /* __VSN_ABSVISIONCOMPONENT_H */
