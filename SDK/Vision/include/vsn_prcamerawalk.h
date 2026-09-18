////////////////////////////////////////////////////////////////////////////////
/** 
  \file  
  \brief \ru Класс PrCameraWalk обеспечивает масштабирование сцены относительно ее центра.
         \en PrCameraWalk class provides scene zooming about its center. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAZOOM_H
#define __VSN_PRCAMERAZOOM_H

#include <vsn_prabscamera.h>
#include <vsn_global.h>

namespace VSN {

class Viewport;
namespace Experiment {

class PrCameraWalkPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraWalk масштабирования сцены относительно ее центра.
           \en PrCameraWalk class provides scene zooming about its center. \~
  \details \ru Особенность процесса PrCameraWalk - увеличение размера по направлению к цели. PrCameraWalk
               осуществляет два режима работы: с помощью колеса мыши, если IsZoomWheel взведена, как true,
               иначе PrCameraWalk реализует действия "наезд/отъезд" камеры на цель. PrCameraWalk также имеет возможность,
               как и остальные процессы управления, назначить горячие кнопки мыши и клавиатуры для активизации действий
               по своему усмотрению с помощью дополнительного функционала в базовом классе SetMouseButtonsActivate и
               SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши
               с одновременной нажатой клавишой клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана,
               вы будете наблюдать перемещение камеры вокруг модели.
           \en NO TRANSLATION.\n \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraWalk : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraWalk)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~ 
    PrCameraWalk(GraphicsScene* pGraphicsScene, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraWalk();
public:
protected:
    /// \ru Активировать процесс. \en Activates the process. \~
    virtual void Activate() final;
    /// \ru Деактивировать процесс. \en Deactivates the process. \~
    virtual void Deactivate() final;
    /// \ru Обработка события перемещения мыши. \en Processes the mouse move event. \~
    virtual void MouseMove(float dt) final;
    /// \ru Обработка события движения колеса мыши. \en Handling the mouse wheel motion event. \~
    virtual void MouseWheel(const PointI& pnt, int delta) final;
private:
    VSN_DECLARE_EX_PRIVATE(PrCameraWalk);
    VSN_DISABLE_COPY(PrCameraWalk);
};

} //namespace Experiment

} // namespace VSN

#endif /* __VSN_PRCAMERAZOOM_H */
