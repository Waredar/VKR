////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru OrientationMarker является классом управления ориентацией камерой сцены.
         \en OrientationMarker is a class for controlling the camera orientation. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_ORIENTATIONMARKER_H
#define __VSN_ORIENTATIONMARKER_H

#include <vsn_object.h>
#include <vsn_widgets.h>
#include <vsn_global.h>

namespace VSN {

class GraphicsView;
class OrientationMarkerPrivate;
//------------------------------------------------------------------------------
/** \brief \ru OrientationMarker является классом управления ориентацией камерой сцены.
           \en OrientationMarker is a class for controlling the camera orientation. \~
  \details \ru OrientationMarker обеспечивает управление камерой основной сцены. OrientationMarker позиционирует камеру 
               согласно стандартным ориентациям, например: сверху, снизу, справа, слева, спереди, сзади и изометрической проекцией.
               OrientationMarker имеет зоны реакции при наведении манипулятора мыши на примитивы этого манипулятора, можно 
               переключаться между стандартными проекциями. Кроме того, OrientationMarker обеспечивает возможность динамической работы 
               с помощью манипулятора мыши при захвате определенных примитивов и использует событие mousemove.
               OrientationMarker имеет два состояния, который определяются с помощью функции SetEnabled, если enabled равен false,
               то OrientationMarker не будет реагировать на действия мыши и наоборот. OrientationMarker также работает с функцией
               SetVisible, т.е., если visible равен значению false, то OrientationMarker не будет отображаться в сцене. 
               OrientationMarker можно расположить в разных определенных позициях, например: справа снизу(по умолчанию), справа сверху, 
               слева сверху, слева снизу. OrientationMarker имеет в данной реализации два представления: TriadMarker и BoxMarker.
               TriadMarker- представляет собой оси XYZ, позволяет позиционировать камеру по осям X,Y,Z изометрию XYZ, а также 
               вращать камеру относительно каждой из осей.
               BoxMarker - представляет собой видовой куб, позволяющий позиционировать камеру по граням, углам и ребрам куба, 
               а также вращать камеру относительно вектора камеры. \n.
           \en OrientationMarker provides control of main scene's camera. OrientationMarker positions the camera according to
               standard projections such as: top, bottom, right, left, front, back and isometric projection. OrientationMarker has
               reaction zones when pointing the mouse cursor to the control's primitives, that can be use to switch between the 
               standard projections. In addition, OrientationMarker provides the ability to work dynamically with the mouse when catching certain primitives and
               uses mousemove event. OrientationMarker has two states that are controlled with SetEnabled. If enabled is false then
               OrientationMarker will not react to mouse events and vice versa. OrientationMarker also has SetVisible method, so if
               visible is false than OrientationMarker will not be shown in the scene. OrientationMarker can be placed in different
               predefined locations: bottom right(the default), bottom left, top right, top left. OrientationMarker has two representations:
               TriadMarker and BoxMarker.
               TriadMarker consists of axes XYZ and allows positioning and rotation of the camera along each axis and
               setting isometric view.
               BoxMarker is a view cube that allows you to position the camera along the edges, corners and edges of the cube,
               as well as rotate the camera relative to the camera vector \n \~
  \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS OrientationMarker final : public Object //Node
{
    VSN_OBJECT(OrientationMarker)
public:
    /// \ru Перечисление расположения маркера ориентации. \en Enumeration of orientation marker positions.
    enum class Corner
    {
        TopLeft,     ///< \ru верхний левый угол.  \en top left corner. \~
        TopRight,    ///< \ru верхний правый угол. \en top right corner. \~
        BottomLeft,  ///< \ru нижний левый угол.   \en bottom left corner. \~
        BottomRight  ///< \ru нижний правый угол.  \en bottom right corner. \~
    };
    /// \ru Перечисление стиля отображения маркера ориентации. \en Enumeration of orientation marker styles.
    enum class Style
    {
        TriadMarker,
        BoxMarker,
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit OrientationMarker(Node* pParent = nullptr);
    /// \ru Конструктор с параметрами. \en Default constructor. \~
    explicit OrientationMarker(GraphicsView* pGraphics,  Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~OrientationMarker();
public:
    /// \ru Ширина контрола в пикселях на экране. \en Control width in pixels. \~
    int GetWidth() const;
    /// \ru Высота контрола в пикселях на экране. \en Control height in pixels. \~
    int GetHeight() const;
    /// \ru Вернуть текущий стиль маркера. \en Returns marker style. \~
    OrientationMarker::Style  GetStyle() const;
    /// \ru Вернуть текущее расположение маркера. \en Returns current marker position.
    OrientationMarker::Corner  GetCorner() const;
    /// \ru Проверить, является ли маркер видимым. \en Check if marker is visible. \~
    bool IsVisible() const;
    /// \ru Проверить, является ли маркер активным. \en Check if marker is active. \~
    bool IsEnabled() const;
    /// \ru Проверить, включен флаг обновления сцены при изменении маркера ориентации. \en Check if marker is active. \~
    bool IsRefreshScreen() const;
    /// \ru Установить, флаг обновления сцены при изменении маркера ориентации. \en Check if marker is active. \~
    void SetRefreshScreen(bool bEnable);
    /// \ru Получить значение границ. \en Get margin values. \~
    void GetMargins(int* left, int* top, int* right, int* bottom) const;
    /// \ru Перестроить маркер. \en Rebuild market. \~
    void RebuildMarket();
    /// \ru Получить опции представления триада в пикселях на экране. \en Get options for representing the triad in pixels. \~
    void GetRepOptionTriad(uint& nHeightAxis, uint& nHeightArrow, uint& nRadiusAxis, uint& nRadiusArrow, uint& nRadiusOrigin, uint& nRadiusTour, uint& nLetter);
public:
    /// \ru Ширина контрола в пикселях на экране. \en Control width in pixels. \~
    VSN_SLOT(Public, SetWidth, void SetWidth(int width))
    /// \ru Высота контрола в пикселях на экране. \en Control height in pixels. \~
    VSN_SLOT(Public, SetHeight, void SetHeight(int width))
    /// \ru Установить текущий стиль маркера. \en Set marker's style. \~
    VSN_SLOT(Public, SetStyle, void SetStyle(OrientationMarker::Style eStyle))
    /// \ru Установить текущее расположение маркера. \en Set marker position. \~
    VSN_SLOT(Public, SetCorner, void SetCorner(Corner corner))
    /// \ru Установить активность маркера. \en Enable or disable marker. \~
    VSN_SLOT(Public, SetEnabled, void SetEnabled(bool bEnabled))
    /// \ru Установить видимость  маркера. \en Set marker visibility. \~
    VSN_SLOT(Public, SetVisible, void SetVisible(bool bVisible))
    /// \ru Установить опции представления триада в пикселях на экране. \en Set options for representing the triad in pixels. \~
    VSN_SLOT(Public, SetRepOptionTriad, void SetRepOptionTriad(uint nHeightAxis, uint nHeightArrow, uint nRadiusAxis, uint nRadiusArrow, uint nRadiusOrigin, uint nRadiusTour, uint nLetter))
public:
    VSN_SIGNAL(Public, CornerModified, void CornerModified(Corner corner), corner  )
    VSN_SIGNAL(Public, StyleModified,  void StyleModified(Style eStyle),   eStyle  )
    VSN_SIGNAL(Public, WidthModified,  void WidthModified(int nWidth),     nWidth  )
    VSN_SIGNAL(Public, HeightModified, void HeightModified(int nHeight),   nHeight )
    VSN_SIGNAL(Public, EnableModified, void EnableModified(bool bEnabled), bEnabled)
    VSN_SIGNAL(Public, VisibleModified,void VisibleModified(bool bVisible),bVisible)
    VSN_SIGNAL(Public, OptionTriadModified,
        void OptionTriadModified(int nHeightAxis, int nHeightArrow, int nRadiusAxis, int nRadiusArrow, int nRadiusOrigin, int nRadiusTour, int nLetter),
        nHeightAxis, nHeightArrow, nRadiusAxis, nRadiusArrow, nRadiusOrigin, nRadiusTour, nLetter)
private:
    VSN_SLOT(Private, OnCntSphere, void OnCntSphere(WidgetBase*));
    VSN_SLOT(Private, OnXAxsis, void OnXAxsis(WidgetBase*));
    VSN_SLOT(Private, OnYAxsis, void OnYAxsis(WidgetBase*));
    VSN_SLOT(Private, OnZAxsis, void OnZAxsis(WidgetBase*));
    VSN_SLOT(Private, OnPlaneXZ, void OnPlaneXZ(WidgetBase*));
    VSN_SLOT(Private, OnPlaneYZ, void OnPlaneYZ(WidgetBase*));
    VSN_SLOT(Private, OnPlaneXY, void OnPlaneXY(WidgetBase*));
    VSN_SLOT(Private, OnHoverEnterTrousX, void OnHoverEnterTrousX(WidgetBase*));
    VSN_SLOT(Private, OnHoverLeaveTrousX, void OnHoverLeaveTrousX(WidgetBase*));
    VSN_SLOT(Private, OnHoverEnterTrousY, void OnHoverEnterTrousY(WidgetBase*));
    VSN_SLOT(Private, OnHoverLeaveTrousY, void OnHoverLeaveTrousY(WidgetBase*));
    VSN_SLOT(Private, OnHoverEnterTrousZ, void OnHoverEnterTrousZ(WidgetBase*));
    VSN_SLOT(Private, OnHoverLeaveTrousZ, void OnHoverLeaveTrousZ(WidgetBase*));
    VSN_SLOT(Private, OnHoverEnterPlaneYZ, void OnHoverEnterPlaneYZ(WidgetBase*));
    VSN_SLOT(Private, OnHoverLeavePlaneYZ, void OnHoverLeavePlaneYZ(WidgetBase*));
    VSN_SLOT(Private, OnHoverEnterPlaneXZ, void OnHoverEnterPlaneXZ(WidgetBase*));
    VSN_SLOT(Private, OnHoverLeavePlaneXZ, void OnHoverLeavePlaneXZ(WidgetBase*));
    VSN_SLOT(Private, OnHoverEnterPlaneXY, void OnHoverEnterPlaneXY(WidgetBase*));
    VSN_SLOT(Private, OnHoverLeavePlaneXY, void OnHoverLeavePlaneXY(WidgetBase*));
 private:
    VSN_SLOT(Private, OnRight, void OnRight(WidgetBase* ws));
    VSN_SLOT(Private, OnTop, void OnTop(WidgetBase*));
    VSN_SLOT(Private, OnFront, void OnFront(WidgetBase*));
    VSN_SLOT(Private, OnLeft, void OnLeft(WidgetBase* ws));
    VSN_SLOT(Private, OnDown, void OnDown(WidgetBase*));
    VSN_SLOT(Private, OnRear, void OnRear(WidgetBase*));
    VSN_SLOT(Private, IsoTL_OnClick, void IsoTL_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoTF_OnClick, void IsoTF_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoTR_OnClick, void IsoTR_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoTB_OnClick, void IsoTB_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoBL_OnClick, void IsoBL_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoBF_OnClick, void IsoBF_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoBR_OnClick, void IsoBR_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoBB_OnClick, void IsoBB_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoLF_OnClick, void IsoLF_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoRF_OnClick, void IsoRF_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoLB_OnClick, void IsoLB_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoRB_OnClick, void IsoRB_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoTLF_OnClick, void IsoTLF_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoTRF_OnClick, void IsoTRF_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoTLB_OnClick, void IsoTLB_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoTRB_OnClick, void IsoTRB_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoBLF_OnClick, void IsoBLF_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoBRF_OnClick, void IsoBRF_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoBLB_OnClick, void IsoBLB_OnClick(WidgetBase*));
    VSN_SLOT(Private, IsoBRB_OnClick, void IsoBRB_OnClick(WidgetBase*));
    VSN_SLOT(Private, OnArrowNext, void OnArrowNext(WidgetBase*));
    VSN_SLOT(Private, OnArrowPrev, void OnArrowPrev(WidgetBase*));
private:
    VSN_SLOT(Private, OnHoverLeave, void OnHoverLeave(WidgetBase*));
    VSN_SLOT(Private, OnHoverEnter, void OnHoverEnter(WidgetBase*));
private:
    VSN_DECLARE_EX_PRIVATE(OrientationMarker);
};

typedef std::shared_ptr<OrientationMarker> OrientationMarkerPtr;
} // namespace VSN

#endif /* __VSN_ORIENTATIONMARKER_H */

