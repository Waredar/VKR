////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Node является базовым классом для всех классов C3D Vision, которые используются для построения сцены.
         \en Node class is the base class for all C3D Vision classes that are used to construct a scene. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_NODE_H
#define __VSN_NODE_H

#include <memory>
#include <vsn_object.h>
#include <vsn_nodekey.h>
#include <vsn_scenemodification.h>
#include <vsn_nodemodification.h>
#include <vsn_global.h>

namespace VSN {

class NodePrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Node является базовым классом для всех классов Vision, которые используются для построения сцены.
            \en Node class is the base class for all Vision classes that are used to construct a scene. \~
  \details  \ru Класс Node наследован от класса Object и определяет связь между узлами графа. Сам по себе Node не имеет
                визуального представления и у него нет особого назначения. Класс Node необходим для построения графа
                сцены. Родителем экземпляра Node может быть только другой экземпляр Node. Каждый экземпляр Node
                имеет уникальный ключ, который позволяет ему быть узнаваемым в других экземплярах. \n.
            \en Node class inherits from Object class and defines the link between graph nodes. Node class has no
                visual presentation in itself and no special purpose. Node class is needed to consruct a scene graph.
                The parent of Node instance can be only another Node instance. Each Node instance has a unique key
                for recognition of other instances. \n \~
    \ingroup Vision_Node
*/
// ---
class VSN_CLASS Node : public Object
{
    VSN_OBJECT(Node)
    VSN_PROP_READ_WRITE_NOTIFY(enabled, IsEnabled, SetEnabled, EnabledModified);
public:
    /// \ru Конструктор по умолчанию. \en Constructor with parent. \~
    explicit Node(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~Node() override;
public:
    /// \ru Вернуть ключ, идентифицирующий экземпляр Node. \en Returns key identifing Node instance. \~
    NodeKey GetUniqueKey() const;
    /// \ru Установить уникальный ключ для этого экземпляра. \en Sets the unique key for the instance. \~
    void SetUniqueKey(const NodeKey& key);

    /// \ru Вернуть пользовательский ключ, идентифицирующий экземпляр Node. \en Returns custom key identifing Node instance. \~
    NodeKey GetCustomKey() const;
    /// \ru Установить пользовательский уникальный ключ для этого экземпляра. \en Sets the custom unique key for the instance. \~
    void SetCustomKey(const NodeKey& key);

    /// \ru Вернуть указатель на родительский объект или nullptr, если родителя нет. \en Returns pointer to the parent object or nullptr if no parent. \~
    Node* GetParentNode() const;
    /// \ru Вернуть флаг включение узла. По умолчанию флаг всегда включен. \en Returns the Node enabled flag. By default, the flag is always on.\~
    bool IsEnabled() const;

    /// \ru Вернуть массив дочерних узлов для этого узла. \en Return an array of child nodes for this node. \~
    ObjectList<Node*> GetChildNodes() const;

    /// \ru Установить родительский объект для этого объекта. \en Sets parent object to the object. \~
    void SetParent(Node* pParent);
    /// \ru Вернуть True, если уведомления заблокированы, в противном случае False. \en True if notifications are blocked, otherwise, False. \~
    bool IsNotificationsBlocked() const;
    /// \ru Установить блокировку уведомлений и вернуть предыдущее значение блокировки. \en Sets blocking of notifications and returns the previous blocking value. \~
    bool SetBlockNotifications(bool block);
public:
    /// \ru Установить флаг включения узла. \en Sets the node enable flag. \~
    VSN_SLOT(Public, SetEnabled, void SetEnabled(bool bEnabled))
public:
    VSN_SIGNAL(Public, NodeDestroyed, void NodeDestroyed())
    VSN_SIGNAL(Public, EnabledModified, void EnabledModified(bool bEnabled), bEnabled)
    VSN_SIGNAL(Public, OnParentModified, void OnParentModified(Node* pParent), pParent)
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for internal use. \~
    Node(NodePrivate& dd, Node* pParent);
protected:
    /// \ru Эта функция вызывается, если произошли какие-либо изменения в сцене. \en The function is called in case of scene being modified. \~
    virtual void SceneModificationEvent(const std::shared_ptr<SceneModification>& modification);
private:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const;
private:
    VSN_DECLARE_EX_PRIVATE(Node);
    friend class Messenger;
    friend class NodeCreatedModificationGenerator;
};

inline NodeKey vKeyForNode(Node* node) { return node ? node->GetUniqueKey() : NodeKey(); }

template<typename T>
inline NodeKeyVector vKeysForNodes(const T& nodes)
{
    NodeKeyVector indexs;
    indexs.reserve(nodes.size());
    for (const auto n : nodes)
        indexs.push_back(n->GetUniqueKey());
    return indexs;
}

/* NodeKeyTypePair*/
struct NodeKeyTypePair
{
    NodeKeyTypePair()
        : key()
        , type(nullptr)
    {}

    explicit NodeKeyTypePair(const NodeKey& _key, const MetaObject* _type)
        : key(_key)
        , type(_type)
    {}
    NodeKey key;
    const MetaObject* type;
};

} // namespace VSN

#endif /* __VSN_NODE_H */
