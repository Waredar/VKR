////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Класс PrCameraRotate обеспечивает интерактивные действия пользователя, а именно управление 
           камерой, ее вращением по орбите.
       \en PrCameraRotate class provides interactive user actions, i.e. camera control and its orbiting. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAROTATE_H
#define __VSN_PRCAMERAROTATE_H

#include <vsn_graphicsview.h>
#include <vsn_prabscamera.h>
#include <vsn_global.h>

namespace VSN {

class PrCameraRotatePrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraRotate обеспечивает интерактивное вращение камеры вокруг сцены.
           \en NO TRANSLATION. \~
    \details \ru Назначение горячих кнопок мыши и клавиатуры в процессах PrCameraRotate можно настроить 
                 по своему усмотрению с помощью дополнительного функционала в базовом классе SetMouseButtonsActivate и
                 SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши 
                 с одновременной нажатой клавишой клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана, 
                 вы будете наблюдать перемещение камеры вокруг модели.
             \en NO TRANSLATION.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraRotate : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraRotate)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit PrCameraRotate(GraphicsScene* pGraphicsScene, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraRotate();
protected:
    /// \ru Активировать процесс. \en Activates the process. \~
    virtual void Activate() final;
    /// \ru Деактивировать процесс. \en Deactivates the process. \~
    virtual void Deactivate() final;
    /// \ru Обработка события перемещения мыши. \en Processes the mouse move event. \~
    virtual void MouseMove(float dt) final;
private:
    VSN_DECLARE_EX_PRIVATE(PrCameraRotate);
    VSN_DISABLE_COPY(PrCameraRotate);
};

} // namespace VSN

#endif /* __VSN_PRCAMERAROTATE_H */
