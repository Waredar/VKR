////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс PrCameraRelativeOrbit обеспечивает интерактивные действия пользователя, 
               а именно управление камерой, ее вращением по орбите.
           \en PrCameraRelativeOrbit class provides interactive user actions, i.e. 
               camera control and its orbiting. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERARELATIVEORBIT_H
#define __VSN_PRCAMERARELATIVEORBIT_H

#include <vsn_prabscamera.h>
#include <vsn_objectpickselection.h>
#include <vsn_global.h>

namespace VSN {

class Viewport;
class PrCameraRelativeOrbitPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraRelativeOrbit обеспечивает вращение камеры по орбите вокруг сцены.
           \en PrCameraRelativeOrbit class provides camera orbiting around the target. \~
    \details \ru Особенность процесса PrCameraRelativeOrbit - это вращение камеры относительно выбранного объекта,
                 т.е. данный процесс непосредственно работает с механизмом поиска объектов сцены.
                 Назначение горячих кнопок мыши и клавиатуры в процесса PrCameraRelativeOrbit можно настроить
                 по своему усмотрению с помошью дополнительного функционала в базовом классе SetMouseButtonsActivate и
                 SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши
                 с одновременной нажатой клавишой клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана,
                 вы будете наблюдать перемещение камеры вокруг модели.
            \en NO TRANSLATION.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraRelativeOrbit : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraRelativeOrbit)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    PrCameraRelativeOrbit(GraphicsScene* pGraphicsScene, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~PrCameraRelativeOrbit();
protected:
    /// \ru Активировать процесс. \en Activates the process. \~
    virtual void Activate() final;
    /// \ru Деактивировать процесс. \en Deactivates the process. \~
    virtual void Deactivate() final;
    /// \ru Обработка события перемещения мыши. \en Processes the mouse move event. \~
    virtual void MouseMove(float dt) final;
public:
    /// \ru Сигнал будет отправлен перед началом вращения вокруг точки. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, signalPrepareRotate, void signalPrepareRotate(MbCartPoint3D& relativePnt), relativePnt)
public:
    /// \ru Слот для инициализации опорного объекта, относительно которого будет вращаться камера. \en NO TRANSLATION. \~
    VSN_SLOT(Public, slotObjectHoverMove, void slotObjectHoverMove(PickSelectionEventPtr event))
private:
    VSN_DECLARE_EX_PRIVATE(PrCameraRelativeOrbit);
    VSN_DISABLE_COPY(PrCameraRelativeOrbit);
};

} // namespace VSN

#endif /* __VSN_PRCAMERARELATIVEORBIT_H */
