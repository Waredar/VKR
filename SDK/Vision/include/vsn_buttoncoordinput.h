////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru ButtonCoordInput класс, который принимает события от назначенного устройства (мышь и пр.) по 
               взаимодействию его кнопок, если они имеются.
           \en ButtonCoordInput class takes events from the assigned device, for example, mouse, etc.
               Events are taken when interacting with device buttons if any. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BUTTONCOORDINPUT_H
#define __VSN_BUTTONCOORDINPUT_H

#include <vsn_abscoordinatelistener.h>
#include <vsn_global.h>

namespace VSN {

class ButtonCoordInputPrivate;
//------------------------------------------------------------------------------
/** \brief \ru ButtonCoordInput класс, который принимает события от назначенного устройства (мышь и пр.)
               по взаимодействию его кнопок, если они имеются. 
           \en ButtonCoordInput class takes events from assigned device, for example, mouse, etc.
               Events are taken when interacting with device buttons if any. \~
  \details \ru ButtonCoordInput имеет вспомогательные функции, а также слоты и сигнал для 
               удобства использования этого объекта, которые позволяют настроить объект 
               для нужд пользователя. \n.
           \en ButtonCoordInput class has secondary functions, and also slots, and the signal for convenient
               use of the object. They help configure the object as the user needs. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS ButtonCoordInput : public AbsCoordinateListener
{
    VSN_OBJECT(ButtonCoordInput)
    VSN_PROP_READ_WRITE_NOTIFY(scale, GetScale, SetScale, OnScaleModified)
    VSN_PROP_READ_WRITE_NOTIFY(buttons, GetButtons, SetButtons, OnButtonsModified)
    VSN_PROP_READ_WRITE_NOTIFY(acceleration, GetAcceleration, SetAcceleration, OnAccelerationModified)
    VSN_PROP_READ_WRITE_NOTIFY(deceleration, GetDeceleration, SetDeceleration, OnDecelerationModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit ButtonCoordInput(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~ButtonCoordInput();
public:
    /// \ru Вернуть масштаб значений координат. \en Returns scale of coordinate values. \~
    float GetScale() const;
    /// \ru Вернуть коды кнопок, которые необходимы для управления координатой. \en Returns button codes that are needed to control coordinate. \~
    std::vector<int> GetButtons() const;
    /// \ru Вернуть величину значения скорости по координате при удержании клавиши. \en Returns speed value by coordinate when pressing key. \~
    float GetAcceleration() const;
    /// \ru Вернуть величину скорости, при которой значение оси возвращается в нормальное состояние при отпускании кнопки. \en Returns speed value, with which axis value takes normal state, when releasing button. \~
    float GetDeceleration() const;
public: // slots group
    /// \ru Вернуть масштаб значений координат. \en Returns scale of coordinate values. \~
    VSN_SLOT(Public, SetScale, void SetScale(float scale))
    /// \ru Установить коды клавиш для управления координатой. \en Sets key codes to control coordinate. \~
    VSN_SLOT(Public, SetButtons, void SetButtons(const std::vector<int>& buttons))
    /// \ru Установить величину значения скорости по координате при удержании клавиши. \en Sets speed value by coordinate when pressing key. \~
    VSN_SLOT(Public, SetAcceleration, void SetAcceleration(float acceleration))
    /// \ru Установить скорость, с которой значение оси возвращается в нормальное состояние при отпускании кнопки. \en Returns speed value, with which axis value takes normal state, when releasing button. \~
    VSN_SLOT(Public, SetDeceleration, void SetDeceleration(float deceleration))
public: // signals group
    /// \ru Сигнал об изменении масштаба. \en Scale change signal. \~
    VSN_SIGNAL(Public, OnScaleModified, void OnScaleModified(float scale), scale)
    /// \ru Сигнал об изменении вектора ключей. \en Signal of changing key vector. \~
    VSN_SIGNAL(Public, OnButtonsModified, void OnButtonsModified(const std::vector<int>& buttons), buttons)
    /// \ru Сигнал об изменении скорости изменения при удержании клавиши. \en Signal of changing change speed when pressing key. \~
    VSN_SIGNAL(Public, OnAccelerationModified, void OnAccelerationModified(float acceleration), acceleration)
    /// \ru Сигнал об изменении скорости изменения при отпускании клавиши. \en Signal of changing change speed when releasing key. \~
    VSN_SIGNAL(Public, OnDecelerationModified, void OnDecelerationModified(float deceleration), deceleration)
private:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(ButtonCoordInput)
    VSN_DISABLE_COPY(ButtonCoordInput)
};

} // namespace VSN

#endif // __VSN_BUTTONCOORDINPUT_H
