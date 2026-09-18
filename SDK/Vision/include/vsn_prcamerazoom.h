////////////////////////////////////////////////////////////////////////////////
/** 
  \file  
  \brief \ru Класс PrCameraZoom обеспечивает масштабирование сцены относительно ее центра.
         \en PrCameraZoom class provides scene zooming about its center. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAZOOM_H
#define __VSN_PRCAMERAZOOM_H

#include <vsn_prabscamera.h>
#include <vsn_global.h>

namespace VSN {

class Viewport;
class PrCameraZoomPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraZoom масштабирования сцены относительно ее центра.
           \en PrCameraZoom class provides scene zooming about its center. \~
  \details \ru Особенность процесса PrCameraZoom - увеличение размера по направлению к цели. PrCameraZoom
               осуществляет два режима работы: с помощью колеса мыши, если IsZoomWheel взведена, как true,
               иначе PrCameraZoom реализует действия "наезд/отъезд" камеры на цель. PrCameraZoom также имеет возможность,
               как и остальные процессы управления, назначить горячие кнопки мыши и клавиатуры для активизации действий
               по своему усмотрению с помощью дополнительного функционала в базовом классе SetMouseButtonsActivate и
               SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши
               с одновременной нажатой клавишой клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана,
               вы будете наблюдать перемещение камеры вокруг модели.
           \en NO TRANSLATION.\n \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraZoom : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraZoom)
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~ 
    explicit PrCameraZoom(GraphicsScene* pGraphicsScene, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraZoom();
protected:
    /// \ru Вернуть признак масштабирования с помощью колеса мыши. \en NO TRANSLATION. \~
    bool IsZoomWheel() const;
    /// \ru Установить признак масштабирования с помощью колеса мыши. \en NO TRANSLATION. \~
    void SetZoomWheel(bool bWheel);
public:
    /// \ru Вернуть направление колеса мыши. \en Return revert mouse wheel direction. \~
    bool IsZoomWheelReversed() const;
    /// \ru Установить направление колеса мыши. \en Set mouse wheel direction. \~
    void SetZoomWheelReverse(bool bReverse);

    /** \brief \ru Вернуть максимальное значение масштабирования для камеры. Значение в единицах пространства объекта.
               \en Return the maximum zoom value for the camera. Value in units of object space. \~
    */
    float GetZoomLimit() const;

    /** \brief \ru Установите максимальное значение масштабирования для камеры. Это гарантирует, что окно всегда просматривает больше чем это значение.
               \en Set the maximum zoom value for a camera. It guarantees that the window always views more than this number of units. \~
        \param[in] zoomlimit - \ru Ззначение в единицах пространства объекта.
                               \en Pass a value in object space units. \~
    */
    void SetZoomLimit(float zoomlimit);

    /** \brief \ru Выполнить автоматический расчет предела масштабирования на основе ограничивающего прямоугольника сцены.
               \en Performs an automatic calculation of the zoom limit based off of the bounding box of the scene. \~
    */
    void SetZoomLimit();
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
    VSN_DECLARE_EX_PRIVATE(PrCameraZoom);
    VSN_DISABLE_COPY(PrCameraZoom);
};

/* PrCameraZoomWheel */
class VSN_CLASS PrCameraZoomWheel : public PrCameraZoom
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~ 
    explicit PrCameraZoomWheel(GraphicsScene* pGraphicsScene, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraZoomWheel();
private:
    VSN_DISABLE_COPY(PrCameraZoomWheel);
};

/* PrCameraZoomMove */
class VSN_CLASS PrCameraZoomMove : public PrCameraZoom
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~ 
    explicit PrCameraZoomMove(GraphicsScene* pGraphicsScene, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraZoomMove();
private:
    VSN_DISABLE_COPY(PrCameraZoomMove);
};

} // namespace VSN

#endif /* __VSN_PRCAMERAZOOM_H */
