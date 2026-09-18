////////////////////////////////////////////////////////////////////////////////
/** 
  \file  
  \brief \ru Класс PrCameraPan панорамирует камеру относительно текущего вида.
         \en PrCameraPan class pans the camera relative to a current view. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAPAN_H
#define __VSN_PRCAMERAPAN_H

#include <vsn_prabscamera.h>
#include <vsn_global.h>

namespace VSN {

class Viewport;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraPan панорамирует камеру относительно текущего вида.
           \en PrCameraPan class pans the camera relative to a current view. \~
    \details \ru Назначение горячих кнопок мыши и клавиатуры в процессах PrCameraPan можно настроить
                 по своему усмотрению с помощью дополнительного функционала в базовом классе SetMouseButtonsActivate и
                 SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши
                 с одновременно нажатой клавишой клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана,
                 вы будете наблюдать перемещение камеры вокруг модели.
             \en PrCameraPan class provides the ability to set keys of a mouse and a keyboard in processes
                 at your own discretion using the additional functional in the base SetMouseButtonsActivate
                 and SetKeyboardButtonsActivate classes. For example, to activate a process, you can set the left mouse button
                 with Ctrl key pressed simultaneously. So, when moving a mouse in the screen plane,
                 you can see the camera moving around a model. \n \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraPan : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraPan)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    PrCameraPan(GraphicsScene* pGraphicsScene, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~PrCameraPan();
protected:
    /// \ru Активировать процесс. \en Activates the process. \~
    virtual void Activate() final;
    /// \ru Деактивировать процесс. \en Deactivates the process. \~
    virtual void Deactivate() final;
    /// \ru Обработка события перемещения мыши. \en Processes the mouse move event. \~
    virtual void MouseMove(float dt) final;
private:
    VSN_DECLARE_EX_PRIVATE(PrAbstractCamera);
    VSN_DISABLE_COPY(PrCameraPan);
};

} // namespace VSN

#endif /* __VSN_PRCAMERAPAN_H */
