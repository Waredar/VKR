////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru CommandContainer позволяет пользователю определить набор действий, 
               которые пользователь хочет использовать в своем приложении.
           \en CommandContainer class gives the user an opportunity to define an action set,
               that the user needs to use in his application. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COMMANDCONTAINER_H
#define __VSN_COMMANDCONTAINER_H

#include <vsn_feature.h>
#include <vsn_global.h>

namespace VSN {

class Command;
class Coordinate;
class CommandContainerPrivate;
//------------------------------------------------------------------------------
/** \brief \ru CommandContainer позволяет пользователю определить набор действий, 
               которые пользователь хочет использовать в своем приложении.
           \en CommandContainer class gives the user an opportunity to define an action set,
               that the user needs to use in his application. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS CommandContainer : public Feature
{
    VSN_OBJECT(CommandContainer)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit CommandContainer(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~CommandContainer();
public:
    /// \ru Вернуть список действий. \en Returs action list.
    ObjectVector<Command*> GetCommands() const;
    /// \ru Добавить действие в список действий. \en Adds action to action list.
    void AddCommand(Command* pCommand);
    /// \ru Удалить действие из списка действий. \en Removes action from action list.
    void RemoveCommand(Command* pCommand);

    /// \ru Вернуть список координат. \en Returns coordinate list.
    ObjectVector<Coordinate*> GetCoordinates() const;
    /// \ru Добавить координату в список координат. \en Adds coordinate to coordinate list.
    void AddCoordinate(Coordinate* pCoordinate);
    /// \ru Удалить координату из списка координат. \en Removes coordinate from coordinate list.
    void RemoveCoordinate(Coordinate* pCoordinate);
protected:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const;
private:
    VSN_DECLARE_EX_PRIVATE(CommandContainer);
    VSN_DISABLE_COPY(CommandContainer);
};

} // namespace VSN

#endif // __VSN_COMMANDCONTAINER_H
