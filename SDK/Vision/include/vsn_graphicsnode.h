#ifndef __VSN_GRAPHICSNODE_H
#define __VSN_GRAPHICSNODE_H

#include <vsn_node.h>
#include <vsn_global.h>

namespace VSN {

class GraphicsNodePrivate;
/* GraphicsNode */
class VSN_CLASS GraphicsNode : public Node
{
    VSN_OBJECT(GraphicsNode)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GraphicsNode(Node* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~GraphicsNode();
public:
    // \ru Вернуть указатель на родителя. \en Returns a pointer to the parent. \~
    GraphicsNode* GetParentGraphicsNode() const;
protected:
    explicit GraphicsNode(GraphicsNodePrivate& dd, Node* parent = nullptr);
private:
    VSN_DECLARE_EX_PRIVATE(GraphicsNode);
};

} // namespace VSN

#endif // __VSN_GRAPHICSNODE_H
