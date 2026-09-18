////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс PrAbstractCamera является базовым классом, который обрабатывает 
               пользовательский ввод и работает над управлением сценой.
           \en PrAbstractCamera class is the base class that performs processing
               of the user's input and operates with the scene. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRABSCAMERA_H
#define __VSN_PRABSCAMERA_H

#include <vsn_process.h>
#include <vsn_mouseevent.h>
#include <vsn_mouseeventhandler.h>
#include <vsn_graphicsview.h>
#include <vsn_global.h>

namespace VSN {

class KeyboardDevice;
class CommandContainer;
class PrAbstractCameraPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrAbstractCamera является базовым классом, который обрабатывает 
               пользовательский ввод и работает над управлением сценой.
           \en PrAbstractCamera class is the base class that performs processing
               of the user's input and operates with the scene. \~
    \details \ru PrAbstractCamera обеспечивает поддержку пользовательского ввода и логику взаимодействия.
                 Класс PrAbstractCamera реализует функции для настройки активности данного процесса для основных устройств,
                 таких, например, как мышь и клавиатура. Пользователь может настроить взаимодействие этих устройств 
                 по своему усмотрению с помощью функций SetMouseButtonsActivate и SetKeyboardButtonsActivate.
             \en PrAbstractCamera class provides support of the user's input and logic of interaction.
                 PrAbstractCamera class implements functions for setting the activity of the given process
                 for such main devices as a mouse or a keyboard. The user can set interaction of these devices
                 at his own discretion using the SetMouseButtonsActivate and SetKeyboardButtonsActivate functions.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrAbstractCamera : public Process
{
    VSN_OBJECT(PrAbstractCamera);
    VSN_PROP_READ_WRITE_NOTIFY(linearSpeed, GetLinearSpeed, SetLinearSpeed, OnLinearSpeedModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~ 
    explicit PrAbstractCamera(GraphicsScene* pGraphicsScene, Node* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrAbstractCamera();
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for inner use. \~ 
    explicit PrAbstractCamera(PrAbstractCameraPrivate& dd, Node* parent = nullptr);
public:
    /// \ru Вернуть true, если процесс активный. \en Returns true if the process is active. \~
    bool IsActive() const;
    /// \ru Вернуть true, если назначенные клавиши клавиатуры активны. \en Returns true if the specified keys are active. \~
    bool IsActiveKeyboard() const;

    /// \ru Вернуть текущую линейную скорость процесса камеры. Линейная скорость определяет скорость движения камеры. \en Returns the current linear speed of the camera process. The linear speed defines a speed of camera move. \~
    float GetLinearSpeed() const;
    /// \ru Установить линейную скорость процесса камеры. Линейная скорость определяет скорость движения камеры. \en Sets the linear speed of the camera process. The linear speed defines a speed of camera move. \~
    void SetLinearSpeed(float linearSpeed);

    // \ru Вернуть кнопки мыши для активации процесса. \en Returns mouse buttons for activating the process. \~
    std::vector<int> GetMouseButtonsActivate() const;
    // \ru Установить кнопки мыши для активации процесса. \en Sets mouse buttons for activating the process. \~
    void SetMouseButtonsActivate(const std::vector<int>& vecKey);

    // \ru Вернуть кнопки клавиатуры для активации процесса. \en Returns keys for activating the process. \~
    std::vector<int> GetKeyboardButtonsActivate() const;
    // \ru Установить кнопки клавиатуры для активации процесса. \en Sets keys for activating the process. \~
    void SetKeyboardButtonsActivate(const std::vector<int>& vecKey);

    // \ru Вернуть значение флага активации, если клавиша на клавиатуре определена и нажата.
    // \en Returns the process activation flag only if a key preset is pressed. \~
    bool HasActivationIfKeyPressed() const;
    // \ru Установить флаг активации процесса, если клавиша на клавиатуре определена и нажата. 
    // \en Sets the process activation flag only if a key preset is pressed. \~
    void SetActivationIfKeyPressed(bool set);
public:
    // \ru Вернуть начальную точку процесса после активации. \en Returns the initial selection point. \~
    PointI GetFirstPoint() const;
    // \ru Вернуть текущую точку процесса после активации. \en Returns the current selection point. \~
    PointI GetCurrentPoint() const;
    // \ru Вернуть старую точку после выполнения функции Motion. \en Returns the old point after executing the Motion function. \~
    PointI GetRealOldPoint() const;
protected:
    /// \ru Вернуть true, если можно активировать процесс. \en Returns true if the process can be activated. \~
    virtual bool CanActivate() const;
    /// \ru Активировать процесс. \en Activates the process. \~
    virtual void Activate();
    /// \ru Деактивировать процесс. \en Deactivates the process. \~
    virtual void Deactivate();
    /// \ru Обработка события перемещения мыши. \en Processes the mouse move event. \~
    virtual void MouseMove(float dt);
    /// \ru Обработка события движения колеса мыши. \en Processes the mouse wheel event. \~
    virtual void MouseWheel(const PointI& pnt, int delta);
protected:
    // \ru Вернуть указатель на обработчик мыши. \en Returns a pointer to the mouse handler. \~
    MouseEventHandler* GetMouseEventHandler() const;
    // \ru Вернуть указатель на контейнер команд. \en Returns a pointer to the command container. \~
    CommandContainer* GetCommandContainer() const;
    // \ru Вернуть указатель на устройства клавиатуры. \en Returns a pointer to keyboard devices. \~
    KeyboardDevice* GetKeyboardDevice() const;
public:
    /// \ru Сигнал генерируется, если в сцене произошли изменения относительно камеры. \en The signal is generated if the camera in the scene changes. \~
    VSN_SIGNAL(Public, OnCameraModified, void OnCameraModified())
    /// \ru Сигнал будет сгенерирован при изменении линейной скорости движения камеры. \en The signal is generated if the linear speed of camera move changes. \~
    VSN_SIGNAL(Public, OnLinearSpeedModified, void OnLinearSpeedModified())
public:
    VSN_SIGNAL(Public, signalActivated, void signalActivated())
    VSN_SIGNAL(Public, signalDeactivated, void signalDeactivated())
public:
    /// \ru Слот для активизации и инициализации данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Public, slotActiveModified, void slotActiveModified(bool bIsActive))
protected:
    /// \ru Слот для непосредственной работы данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotProcessed, void slotProcessed(float dt))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseDown, void slotMouseDown(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseMove, void slotMouseMove(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseUp, void slotMouseUp(MouseEventObject* pMouse))
    /// \ru Слот для считывания данных мыши при использовании колеса. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotMouseWheel, void slotMouseWheel(WheelEventObject* pWheel))
private:
    VSN_DECLARE_EX_PRIVATE(PrAbstractCamera);
};

} // namespace VSN

#endif /* __VSN_PRABSCAMERA_H */
