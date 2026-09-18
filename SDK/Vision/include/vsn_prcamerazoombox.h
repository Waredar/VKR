////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс PrCameraZoomBox увеличивает камеру в выбранной области.
           \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAZOOMBOX_H
#define __VSN_PRCAMERAZOOMBOX_H

#include <vsn_process.h>
#include <vsn_graphicsview.h>
#include <vsn_mouseevent.h>
#include <vsn_global.h>

namespace VSN {

class PrCameraZoomBoxPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraZoomBox увеличивает камеру в выбранной области.
           \en NO TRANSLATION. \~
    \details \ru PrCameraZoomBox использует функциональность рисования Rectangle для определения прямоугольника 
                 выбора по событию MouseDown, а затем расширяет событию MouseUp для вычисления коэффициента 
                 масштабирования и направления.
             \en NO TRANSLATION.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraZoomBox : public Process
{
    VSN_OBJECT(PrCameraZoomBox);
public:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION. \~ 
    explicit PrCameraZoomBox(GraphicsView* pGraphicsView, GraphicsScene* pGraphicsScene, Node* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraZoomBox();
public:
    // \ru Вернуть кнопки мыши для активации процесса. \en NO TRANSLATION. \~
    std::vector<int> GetMouseButtonsActivate() const;
    // \ru Установить кнопки мыши для активации процесса. \en NO TRANSLATION. \~
    void SetMouseButtonsActivate(const std::vector<int>& vecKey);

    /// \ru Вернуть цвет заполнения рамки. \en NO TRANSLATION. \~
    Color GetColorFillRect() const;
    /// \ru Установить цвет заполнения рамки. \en NO TRANSLATION. \~
    void SetColorFillRect(const Color& clr);

    /// \ru Вернуть цвет бордера рамки. \en NO TRANSLATION. \~
    Color GetColorRectBorder() const;
    /// \ru Установить цвет бордера рамки. \en NO TRANSLATION. \~
    void SetColorRectBorder(const Color& clr);

    /// \ru Вернуть расстояние для старта рисования рамки. \en NO TRANSLATION. \~
    int GetStartDragDistance() const;
    /// \ru Установить расстояние для старта рисования рамки. \en NO TRANSLATION. \~
    void SetStartDragDistance(int dis);
public:
    VSN_SIGNAL(Public, signalActivated, void signalActivated())
    VSN_SIGNAL(Public, signalDeactivated, void signalDeactivated())
protected:
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseDown, void slotMouseDown(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseMove, void slotMouseMove(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseUp, void slotMouseUp(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseLeave, void slotMouseLeave(MouseEventObject* pMouse))
private:
    VSN_DECLARE_EX_PRIVATE(PrCameraZoomBox);
};

} // namespace VSN

#endif /* __VSN_PRCAMERAZOOMBOX_H */
