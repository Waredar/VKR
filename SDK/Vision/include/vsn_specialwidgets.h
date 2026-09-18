////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Набор специальных элементов управления.
         \en A set of special controls. \~
*/
#ifndef __VSN_SPECIALWIDGETS_H
#define __VSN_SPECIALWIDGETS_H

#include <vsn_object.h>
#include <vsn_widgets.h>
#include <vsn_global.h>
#include <vsn_flags.h>

namespace VSN {

class BasePointWidgetPrivate;
class HotPointWidgetPrivate;
class GravityPointWidgetPrivate;
class PlacementWidgetPrivate;
class RectangleWidgetPrivate;
////////////////////////////////////////////////////////////////////////////////
/**
  \brief \ru BasePointWidget является базовым классом для каждого стандартного представления,
             который использует похожую модель. BasePointWidget - это класс, который не может
             быть создан. Он обеспечивает стандартный интерфейс для взоимодействия с моделью
             с помощью слотов и механизма сигналов, позволяющий поддерживать подклассы в соотвествующем
             состоянии с помощью изменения в своих моделях. Этот класс обеспечивает поддержку навигации
             с помощью мыши. Сдвиг, визуальные эффекты,...
         \en BasePointWidget is the base class for every standard representation,
             which uses a similar model. BasePointWidget is a class that cannot
             be created. It provides a standard interface for interacting with the model
             using slots and a signal mechanism, allowing subclasses to be supported in the appropriate way
             through changes in their models. This class provides navigation support
             using the mouse. Shift, visual effects,... \~
*/
// ---
class VSN_CLASS BasePointWidget : public SceneWidget
{
    VSN_OBJECT(BasePointWidget)
public:
    /// \ru Деструктор. \en Destructor.
    virtual ~BasePointWidget();
public:
    /// \ru Вернуть текущий основной цвет элемента управления. \en Return the current main color of the control element. \~
    Color GetPrimaryColor() const;
    /// \ru Установить текущий основной цвет элемента управления. \en Set the current main color of the control element. \~
    void SetPrimaryColor(const Color& color);
    /// \ru Вернуть текущий размер элемента управления. \en Return the control's current size. \~
    float GetSize() const;
    /// \ru Установить текущий размер элемента управления. Возвращает true, если размер элемента был изменен. \en Set the current size of the control element. Returns true if the size of the element was changed. \~
    virtual bool SetSize(float fValue);
public:
     /// \ru Сигнал об изменении основного цвета элемента управления. \en The signal about the change in the main color of the control element. \~
     VSN_SIGNAL(Public, OnColorModified, void OnColorModified(Color color), color)
     /// \ru Сигнал об изменении размера элемента управления. \en Signal about changing the size of a control element. \~
     VSN_SIGNAL(Public, OnSizeModified, void OnSizeModified(float fSize), fSize)
protected:
    /// \ru Конструктор для наследников класса. \en Designer for inheriting classes. \~
    BasePointWidget(BasePointWidgetPrivate* pPntWidPriv, GraphicsScene* pScene);
private:
    VSN_DECLARE_EX_PRIVATE(BasePointWidget);
};

////////////////////////////////////////////////////////////////////////////////
/**
  \brief \ru GravityPointWidget является специальным элементом управления типа GravityPoint.
             Экземпляры этого объекта, находящиеся на сцене, предназначены для отрисовки гравитационной точки.
         \en Gravitypointwidget is a special GravityPoint control element.
             The copies of this object on the scene are designed to draw a gravitational point. \~
  \details \ru GravityPointWidget представляет собой интерактивный инструмент.
               GravityPointWidget имеет представление в виде трех закрытых торов, каждый из которых параллелен
               одной из оси Ox, Oy, Oz со сферой внутри либо без неё в зависимости от выбранного стиля виджета.
           \en GravityPointWidget is an interactive tool.
               GravityPointWidget has a view in the form of three closed tori, each of which is parallel to
               one of the axis of OX, Oy, OZ with the sphere inside or without it depending on the chosen widget style. \~
*/
// ---
class VSN_CLASS GravityPointWidget final : public BasePointWidget
{
    VSN_OBJECT(GravityPointWidget)
public:
    /// \ru Перечисление стиля отображения элемента управления. \en Enumeration of the control's display style. \~
   enum class Style
   {
       Torus,
       SphereInTorus,
   };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GravityPointWidget(GraphicsScene* pScene, Style eStyle = Style::Torus);
    /// \ru Деструктор. \en Destructor.
    virtual ~GravityPointWidget();
public:
    /// \ru Вернуть текущий стиль элемента управления. \en Return the control's current style. \~
    GravityPointWidget::Style  GetStyle() const;
    /// \ru Установить текущий стиль элемента управления. Возвращает true, если стиль элемента был изменен. \en Install the current style of the control element. Returns true if the style of the element has been changed. \~
    bool SetStyle(GravityPointWidget::Style eStyle);
    /// \ru Вернуть текущую толщину элемента управления. \en Return the current width of the control element. \~
    float GetWidth() const;
    /// \ru Установить текущую толщину элемента управления. Возвращает true, если толщина элемента была изменена. \en Install the current width of the control element. Returns true if the width of the element has been changed. \~
    bool SetWidth(float fValue);
    /// \ru Установить текущий размер элемента управления. Возвращает true, если размер элемента был изменен. \en Set the current size of the control element. Returns true if the size of the element was changed. \~
    bool SetSize(float fValue) override;
    /// \ru Вернуть текущий цвет сферы. \en Return the current sphere color. \~
    Color GetColorSphere() const;
    /// \ru Установить текущий цвет сферы. \en Set the current sphere color. \~
    void SetSphereColor(const Color& color);
public:
     /// \ru Сигнал об изменении стиля элемента управления. \en Signal about changing the style of a control element. \~
     VSN_SIGNAL(Public, OnStyleModified, void OnStyleModified(GravityPointWidget::Style eStyle), eStyle)
     /// \ru Сигнал об изменении ширины элемента управления. \en Signal about changing the width of the control element. \~
     VSN_SIGNAL(Public, OnWidthModified, void OnWidthModified(float fSize), fSize)
    /// \ru Сигнал об изменении цвета сферы. \en Signal of a change in the color of the sphere. \~
    VSN_SIGNAL(Public, OnSphereColor, void OnSphereColor(float fSize), fSize)
public:
    virtual void Render(RenderContext& context) const override;
private:
    VSN_DECLARE_EX_PRIVATE(GravityPointWidget);
};

////////////////////////////////////////////////////////////////////////////////
/**
  \brief \ru HotPointWidget является специальным элементом управления типа HotPoint.
             Экземпляры этого объекта, находящегося на сцене, предназначены для управления обектами сцены.
         \en HotPointWidget is a special HotPoint control.
             Instances of this object located in the scene are intended to manipulate scene objects. \~
  \details \ru HotPointWidget представляет собой интерактивный инструмент, который взаимодействует
               с процессом MoveWidgetProcess. HotPointWidget имеет два типа представления:
               "3D-сфера" и "2D-квадрат". Для HotPointWidget можно установить ограничения
               с помощью любого из локаторов, являющихся наследниками от AbsCoordLocator,
               задать локатор можно через функцию SetLocator. Также вы можете назначить
               свой собственный локатор, который должен быть унаследован от AbsCoordLocator.
               \n.
           \en HotPointWidget is an interactive tool that interacts with the MoveWidgetProcess.
               HotPointWidget has two types of representation: "3D sphere" and "2D square".
               For HotPointWidget, you can set restrictions using any of the locators, which are a descendant of AbsCoordLocator;
               you can set a locator using the SetLocator function. You can also assign your own locator, which should inherit from AbsCoordLocator. \~
*/
// ---
class VSN_CLASS HotPointWidget final : public BasePointWidget
{
    VSN_OBJECT(HotPointWidget)
public:
    /// \ru Перечисление стиля отображения элемента управления. \en Enumeration of the control's display style. \~
   enum class Style
   {
       Sphera,
       Rect,
   };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit HotPointWidget(GraphicsScene* pScene, Style eStyle = Style::Sphera);
    /// \ru Деструктор. \en Destructor.
    virtual ~HotPointWidget();
public:
    /// \ru Вернуть текущий стиль элемента управления. \en Return the control's current style. \~
    HotPointWidget::Style  GetStyle() const;
    /// \ru Установить текущий стиль элемента управления. \en Set the current control style. \~
    void SetStyle(HotPointWidget::Style eStyle);
    /// \ru Вернуть текущий цвет подсветки элемента управления. \en Return the control's current highlight color. \~
    Color GetHighlightColor() const;
    /// \ru Установить текущий цвет подсветки элемента управления. \en Set the control's current highlight color. \~
    void SetHighlightColor(const Color& color);
    /// \ru Вернуть текущий локатор элемента управления. \en Return the control's current locator. \~
    const AbsCoordLocator* GetLocator() const;
    /// \ru Установить текущий локатор элемента управления. \en Set the control's current locator. \~
    void SetLocator(AbsCoordLocator* pLocator, bool local);
 public:
     /// \ru Сигнал об изменении стиля элемента управления. \en Signal about changing the style of a control element. \~
     VSN_SIGNAL(Public, OnStyleModified, void OnStyleModified(HotPointWidget::Style eStyle), eStyle)
private:
    VSN_DECLARE_EX_PRIVATE(HotPointWidget);
};

////////////////////////////////////////////////////////////////////////////////
/**
  \brief \ru PlacementWidget является специальным элементом управления типа Placement.
             Экземпляры этого объекта, находящиеся на сцене, предназначены для управления объектами сцены.
         \en PlacementWidget is a special Placement control.
             Instances of this object located in the scene are intended to manipulate scene objects. \~
  \details \ru PlacementWidget представляет собой интерактивный инструмент, который взаимодействует
               с процессами MoveWidgetProcess. PlacementWidget имеет представление триады, которая состоит
               из компонентов: начало координат, ось X, ось Y, ось Z. Включая, выключая каждый компонент,
               вы можете комбинировать текущее представление элемента управления.
               Для каждого компонента PlacementWidget можно установить ограничения
               с помощью любого из локаторов, являющихся наследниками от AbsCoordLocator,
               задать локатор можно через функцию SetLocator, указав компонент. Также вы можете назначить
               свой собственный локатор, который должен быть унаследован от AbsCoordLocator.
               \n.
           \en PlacementWidget is an interactive tool that interacts
               with MoveWidgetProcess processes. PlacementWidget has an representation of ​​a triad that consists
               of the components: the origin, the axis X, the axis Y, the axis Z. By turning on, turning off each component,
               you can combine the current representation of the control element.
               For each component Placementwidget, you can set restrictions
               with the help of any of the locators inherited from AbsCoordLocator.
               You can set the locator through the SetLocator function by indicating the component. You can also set
               your own locator, which should be inherited from AbsCoordLocator. \~
*/
// ---
class VSN_CLASS PlacementWidget final : public SceneWidget
{
    VSN_OBJECT(PlacementWidget)
public:
    /// \ru Перечисление стиля отображения элемента управления. \en Enumeration of the control's display style. \~
   enum Companent
   {
       Original = 0x0001,
       AxisX = 0x0002,
       AxisY = 0x0004,
       AxisZ = 0x0008,
       TriadOXYZ = Original | AxisX | AxisY | AxisZ
   };
   VSN_DECLARE_FLAGS(Companents, Companent)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit PlacementWidget(GraphicsScene* pScene, Companents eStyle = Companent::TriadOXYZ);
    /// \ru Деструктор. \en Destructor.
    virtual ~PlacementWidget();
public:
    /// \ru Вернуть текущий стиль элемента управления. \en Return the control's current style. \~
    PlacementWidget::Companents  GetStyle() const;
    /// \ru Установить текущий стиль элемента управления. \en Set the current control style. \~
    void SetStyle(PlacementWidget::Companents eStyle);
    /// \ru Вернуть текущий цвет подсветки элемента управления. \en Return the control's current highlight color. \~
    Color GetHighlightColor() const;
    /// \ru Установить текущий цвет подсветки элемента управления. \en Set the control's current highlight color. \~
    void SetHighlightColor(const Color& color);
    /// \ru Вернуть текущий цвет компонента элемента управления. \en Return the current color of the component of the control element. \~
    Color GetColor(PlacementWidget::Companent eItem) const;
    /// \ru Установить текущий цвет компонента элемента управления. \en Set the current color of the component of the control element. \~
    void SetColor(PlacementWidget::Companent eItem, const Color& color);
    /// \ru Вернуть текущий локатор компонента элемента управления. \en Return the current locator of the component of the control element. \~
    const AbsCoordLocator* GetLocator(PlacementWidget::Companent eItem) const;
    /// \ru Установить текущий локатор компонента элемента управления. \en Set the current locator of the component of the control element. \~
    void SetLocator(PlacementWidget::Companent eItem, AbsCoordLocator* pLocator, bool local);
    /// \ru Вернуть текущий размер начала координат элемента управления. \en Return the current size of the control element origin. \~
    float GetSizeOriginal() const;
    /// \ru Установить текущий размер начала координат элемента управления. \en Set the current size of the control element origin. \~
    bool SetSizeOriginal(float fValue);
    /// \ru Вернуть текущий размер оси элемента управления. \en Return the current size of the axis of the control element. \~
    void GetSizeAxis(PlacementWidget::Companent eItem, float& fRadius, float& fLength) const;
    /// \ru Установить текущий размер оси элемента управления. \en Set the current size of the axis of the control element. \~
    bool SetSizeAxis(PlacementWidget::Companent eItem, float fRadius, float fLength);
public:
    /// \ru Сигнал об изменении цвета компонента элемента управления. \en Signal about changing the color of the component of the control element. \~
    VSN_SIGNAL(Public, OnColorModified, void OnColorModified(const Color& color), color)
    /// \ru Сигнал об изменении размера начала координат элемента управления. \en Signal about changing the origin of the component of the control element. \~
    VSN_SIGNAL(Public, OnSizeOriginalModified, void OnSizeOriginalModified(float fSize), fSize)
    /// \ru Сигнал об изменении размера оси элемента управления. \en Signal about changing the axis size of the component of the control element. \~
    VSN_SIGNAL(Public, OnSizeAxisModified, void OnSizeAxisModified(float fRadius, float fLength), fRadius,fLength)
    /// \ru Сигнал об изменении стиля элемента управления. \en Signal about changing the style of a control element. \~
    VSN_SIGNAL(Public, OnStyleModified, void OnStyleModified(PlacementWidget::Companents eStyle), eStyle)
private:
    VSN_DECLARE_EX_PRIVATE(PlacementWidget);
};

////////////////////////////////////////////////////////////////////////////////
/**
  \brief \ru RectangleWidget является специальным элементом управления типа Rectangle.
             Экземпляры этого объекта, находящиеся поверх сцены, предназначены для отрисовки
             прямоугольной рамки.
         \en RectangleWidget is a special Rectangle control element.
             Copies of this object located on top of the scene are designed to draw
             rectangular frames. \~
  \details \ru RectangleWidget представляет собой интерактивный инструмент.
               RectangleWidget может быть отрисован с перекрестием в середине рамки либо без него
               в зависимости от выставленного флага. Для RectangleWidget можно установить
               точки начала и конца отрисовки прямоугольника на сцене. Также можно менять цветовую
               композицию виджета с помощью соответствующих методов класса.
           \en RectangleWidget is an interactive tool.
               RectangleWidget can be drawn with a crossroads in the middle of the frame or without it
               Depending on the flag displayed.For RectangleWidget, you can install
               The points of the beginning and end of the rectangle drawing on the stage.You can also change color
               The composition of the widget using appropriate class methods. \~
*/
// ---
class VSN_CLASS RectangleWidget final : public ViewWidget
{
    VSN_OBJECT(RectangleWidget)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit RectangleWidget(GraphicsScene* pScene, bool bVisibleCross = true);
    /// \ru Деструктор. \en Destructor.
    virtual ~RectangleWidget();
public:
    // \ru Вернуть точку начала рамки. \en Return the point of start of the frame. \~
    PointF GetBeginPoint() const;
    // \ru Установить точку начала рамки. \en Set the point of start of the frame. \~
    void SetBeginPoint(const PointF& pnt);
    // \ru Вернуть точку конца рамки. \en Return the point of the end of the frame. \~
    PointF GetEndPoint() const;
    // \ru Установить точку конца рамки. \en Set the point of the end of the frame. \~
    void SetEndPoint(const PointF& pnt);
    // \ru Вернуть цвет заполнения рамки. \en Return the color of filling the frame. \~
    Color GetColorFill() const;
    // \ru Установить цвет заполнения рамки. \en Set the color of filling the frame. \~
    void SetColorFill(const Color& clr);
    // \ru Вернуть цвет бордера рамки. \en Return the color of the frame border. \~
    Color GetColorBorder() const;
    // \ru Установить цвет бордера рамки. \en Set the color of the frame border. \~
    void SetColorBorder(const Color& clr);
    // \ru Вернуть цвет перекрестия рамки. \en Return the color of the crossbar of the frame. \~
    Color GetColorCross() const;
    // \ru Установить цвет перекрестия рамки. \en Set the color of the crossbar of the frame. \~
    void SetColorCross(const Color& clr);
    // \ru Вернуть цвет заполнения рамки в обратном направлении. \en Return the color of filling the frame in the opposite direction. \~
    Color GetColorFillReverse() const;
    // \ru Вернуть цвет заполнения рамки в обратном направлении. \en Set the color of filling the frame in the opposite direction. \~
    void SetColorFillReverse(const Color& clr);
    // \ru Вернуть цвет бордера рамки в обратном направлении. \en Return the color of the frame border in the opposite direction. \~
    Color GetColorBorderReverse() const;
    // \ru Установить цвет бордера рамки в обратном направлении. \en Set the color of the frame border in the opposite direction. \~
    void SetColorBorderReverse(const Color& clr);
    // \ru Вернуть цвет перекрестия рамки в обратном направлении. \en Return the color of the crossbar of the frame in the opposite direction. \~
    Color GetColorCorssReverse() const;
    // \ru Установить цвет перекрестия рамки в обратном направлении. \en Set the color of the crossbar of the frame in the opposite direction. \~
    void SetColorCorssReverse(const Color& clr);
    // \ru Вернуть центральную точку рамки. \en Return the central point of the frame. \~
    PointF GetCenterPoint() const;
    // \ru Вернуть флаг отображения перекрестия в центре рамки. \en Return the flag of showing the crossbar in the center of the framework. \~
    bool GetEnabledCross();
    // \ru Установить флаг отображения перекрестия в центре рамки. \en Set the flag of showing the crossbar in the center of the framework. \~
    void SetEnabledCross(bool bEnabled);
    // \ru Получить ширину границы. \en Get the width of the border. \~
    float GetWidthBorder();
    // \ru Установить ширину границы. \en Set the width of the border. \~
    void SetWidthBorder(float value);
private:
    VSN_DECLARE_EX_PRIVATE(RectangleWidget);
};

} // namespace VSN

#endif /* __VSN_SPECIALWIDGETS_H */



