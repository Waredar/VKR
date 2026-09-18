////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru InputCommand хранит устройства ввода, а также код кнопок, которые в 
             дальнейшем будут использоваться как события.
         \en InputCommand class stores input devices, and also button codes,
             that will be used as events further. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_INPUTCOMMAND_H
#define __VSN_INPUTCOMMAND_H

#include <vsn_absinputcommand.h>
#include <vsn_global.h>

namespace VSN {

class AbsInputDevice;
class InputCommandPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru InputCommand хранит устройства ввода, а также код кнопок, которые в дальнейшем 
                будут использоваться как события.
            \en InputCommand class stores input devices, and also button codes,
                that will be used as events further. \~
    \details \ru InputCommand взаимодействует с настоящим устройством и обрабатывает заказанные 
                 пользователем кнопки с последующей генерацией действия. Кроме того, действия могут быть вызваны
                 не одной кнопкой устройства, а несколькими. Например, кнопки от устройства мыши 
                 или клавиатуры.
             \en InputCommand class interacts with a real device and processes buttons specified by the user
                 with the following action generation. Moreover, actions can be called by not only a button, but several.
                 For example, the buttons of a mouse device or a keyboard. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS InputCommand : public AbsInputCommand
{
    VSN_OBJECT(InputCommand)
    VSN_PROPERTY_READ_WRITE_NOTIFY(pDevice, GetInteractionDevice, SetInteractionDevice, OnInteractionDeviceModified)
    VSN_PROPERTY_READ_WRITE_NOTIFY(buttons, GetButtons, SetButtons, OnButtonsModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit InputCommand(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~InputCommand();
public:
    /// \ru Вернуть указатель на текущее устройство взаимодействия. \en Returns a pointer to the current interaction device. \~
    AbsInputDevice* GetInteractionDevice() const;
    /// \ru Содержит кнопки, которые могут вызвать эту команду. \en Contains the buttons capable of calling the command. \~
    std::vector<int> GetButtons() const;
public: // slots group
    /// \ru Установить текущее устройство взаимодействия. \en Sets the current interaction device. \~
    VSN_SLOT(Public, SetInteractionDevice, void SetInteractionDevice(AbsInputDevice* pDevice))
    /// \ru Установить массив кодов горячих клавиш для активизации команды. \en Sets the array of hotkey codes to activate the command. \~
    VSN_SLOT(Public, SetButtons, void SetButtons(const std::vector<int>& buttons))
public: // signals group
    /// \ru Этот сигнал будет сгенерирован при модификации устройства взаимодействия. \en The signal is generated when modifying the interaction device. \~
    VSN_SIGNAL(Public, OnInteractionDeviceModified, void OnInteractionDeviceModified(AbsInputDevice* pDevice), pDevice)
    /// \ru Этот сигнал будет сгенерирован при модификации состояния кнопок, связанных с этой командой. \en The signal is generated when modifying button states related to the command. \~
    VSN_SIGNAL(Public, OnButtonsModified, void OnButtonsModified(const std::vector<int>& buttons), buttons)
private:
    VSN_DECLARE_EX_PRIVATE(InputCommand)
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
};

} // namespace VSN

#endif // __VSN_INPUTCOMMAND_H
