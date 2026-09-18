////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru AbsCoordinateListener абстрактный базовый класс, который принимает 
               события от любого виртуального устройства взаимодействия, например,
               мыши, клавиатуры и.т.д.
           \en AbsCoordinateListener class is the base abstract class taking events
               from any virtual interaction device, for example, mouse, keyboard, etc. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ABSCOORDINATELISTENER_H
#define __VSN_ABSCOORDINATELISTENER_H

#include <vsn_node.h>
#include <vsn_global.h>

namespace VSN {

class AbsInputDevice;
class AbsCoordinateListenerPrivate;
//------------------------------------------------------------------------------
/** \brief \ru AbsCoordinateListener абстрактный базовый класс, который принимает 
               события от любого виртуального устройства взаимодействия, например,
               мыши, клавиатуры и.т.д.
           \en AbsCoordinateListener class is the base abstract class taking events
               from any virtual interaction device, for example, mouse, keyboard, etc. \~
  \details \ru AbsCoordinateListener имеет сигнал, который генерируется в случае
               взаимодействия пользователя с устройством, когда происходят изменения. \n.
           \en AbsCoordinateListener class has a signal that is generated in case of 
               interaction between the user and a device, when changes happen. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS AbsCoordinateListener : public Node
{
    VSN_OBJECT(AbsCoordinateListener)
    VSN_PROP_READ_WRITE_NOTIFY(pInteractionDevice, GetInteractionDevice, SetInteractionDevice, OnInteractionDeviceModified)
public:
    /// \ru Деструктор. \en Destructor. \~
    ~AbsCoordinateListener();
public:
    /// \ru Вернуть указатель на источник взаимодействия. \en Returns pointer to interaction source. \~
    AbsInputDevice* GetInteractionDevice() const;
public: // slots group
    /// \ru Установить источник взаимодействия. \en Sets interaction source. \~
    VSN_SLOT(Public, SetInteractionDevice, void SetInteractionDevice(AbsInputDevice* pInteractionDevice))
public: // signals group
    /// \ru Сигнал об изменении источника взаимодействия. \en Signal of changing interaction source. \~
    VSN_SIGNAL(Public, OnInteractionDeviceModified, void OnInteractionDeviceModified(AbsInputDevice* pInteractionDevice), pInteractionDevice)
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for inner use. \~
    AbsCoordinateListener(AbsCoordinateListenerPrivate& dd, Node* pParent = nullptr);
private:
    VSN_DECLARE_EX_PRIVATE(AbsCoordinateListener);
    VSN_DISABLE_COPY(AbsCoordinateListener);
};

} // namespace VSN

#endif // __VSN_ABSCOORDINATELISTENER_H
