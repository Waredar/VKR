////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Набор стандартных виджетов.
         \en he set of standard widgets. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_WIDGETS_H
#define __VSN_WIDGETS_H

#include <memory>
#include <vsn_widgetmodels.h>
#include <vsn_math.h>
#include <vsn_global.h>
#include <vsn_ray.h>
namespace VSN {

class RenderContext;
class WidgetProcess;
class GuiModulePrivate;
////////////////////////////////////////////////////////////////////////////////
/**
  \brief \ru WidgetBase является базовым классом элемента управления, позволяющим 
             создать манипулятор с различной логикой поведения и отрисовочным 
             представлением на одной и той же основе.
         \en WidgetBase is the base control class that allows
             create a manipulator with different behavior logic and rendering
             presentation on the same basis. \~
  \details \ru WidgetBase обеспечивает элемент управления, позволяющий создать 
               манипулятор с различной логикой поведения и отрисовочным представлением 
               на одной и той же основе.
               Элемент управления представляет собой интерактивный инструмент, с помощью 
               которого можно осуществить взаимодействие с объектами сцены. Такие инструменты 
               основаны на концепции Model-View-Controller, позволяющей создать манипулятор с
               различной логикой поведения и отрисовочным представлением на одной и той же 
               основе. Как и в подобных элементах управления, модель (Model) предоставляет 
               данные и реагирует на команды контроллера, изменяя своё состояние; 
               представление (View) отвечает за отображение данных модели пользователю, 
               реагируя на изменения модели; контроллер (Controller) интерпретирует действия 
               пользователя, оповещая модель о необходимости изменений.
               \n.
           \en WidgetBase provides a control that allows you to create
               manipulator with different behavior logic and rendering representation
               on the same basis.
               The control is an interactive tool that allows you to
               which you can interact with scene objects. Such tools
               are based on the Model-View-Controller concept, which allows you to create a manipulator with
               different behavior logic and rendering representation on the same
               basis. As with similar controls, the Model provides
               data and responds to controller commands, changing its state;
               View is responsible for displaying model data to the user,
               responding to model changes; controller (Controller) interprets actions
               user, notifying the model about the need for changes. \~
*/
// ---
class VSN_CLASS WidgetBase
{
public:
    virtual ~WidgetBase() {};
public:
    /// \ru Отобразить элемент управления. \en Render the control. \~
    virtual void Render(RenderContext& context) const = 0;
    /// \ru Поиск геометрии по лучу. \en Search the geometry by a ray \~
    virtual std::pair<int, float> Intersect(const Ray3DF& ray) const = 0;
    /// \ru Рисовать элемент управления только в экраннных координатах. \en Draw control only in screen coordinates. \~
    virtual bool IsScreenOnly() const = 0;
    /// \ru Проверить, включена ли подстветка элемента управления. \en Check the highlight of the control. \~
    virtual bool IsHighlightEnable() const = 0;
    /// \ru Подключить процесс к компоненту элемента управления. \en Connect process to a component of the control. \~
    virtual void AssignProcess(int id, WidgetProcess* process) = 0;
    /// \ru Получить подключенный процесс к компоненту элемента управления. \en Get a process connected to a component of the control. \~
    virtual WidgetProcess* GetAssignedProcess(int id) const = 0;
};

class GraphicsScene;
class SceneWidgetPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс элемента управления, находящегося на сцене.\n
           \en The class of the control element located on the scene. \~
           \details \ru Экземпляры этого объекта предназначены для управления объектам сцены.
                        Позволяет перемещать точку в глобальной системе координат. \n
                    \en Instances of this class are designed to manage elements (properties) of the scene.
+                       Allows you to move a point in the global coordinate system. \~
*/
// ---
class VSN_CLASS SceneWidget : public Node, public WidgetBase
{
    VSN_OBJECT(SceneWidget);
public:
    /// \ru Конструктор. \en Constructor. \~
    explicit SceneWidget(GraphicsScene* pScene, WidgetModelPtr ptrModel, const Point3DF& origin = {});
    /// \ru Конструктор. \en Constructor. \~
    explicit SceneWidget(GraphicsScene* pScene, WidgetModelPtr ptrModel, const Matrix3DF& transform);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~SceneWidget();
public:
    /// \ru Отобразить элемент управления. \en Render the control. \~
    void Render(RenderContext& context) const override;
    /// \ru Поиск геометрии по лучу. \en Search the geometry by the ray. \~
    std::pair<int, float> Intersect(const Ray3DF& ray) const override;
    /// \ru Рисовать элемент управления только в экраннных координатах. \en Draw control only in screen coordinates. \~
    bool IsScreenOnly() const override;
    /// \ru Проверить, включена ли подстветка элемента управления. \en Check the highlight of the control. \~
    bool IsHighlightEnable() const override;
    /// \ru Установить подстветку элемента управления. \en Set the highlight of the control. \~
    void SetHighlightEnable(bool value);
public:
    /// \ru Изменить размещение элемента управления без сигнала об изменении. \en Change the position of the control without initiation the modify signal. \~
    void Init(const Point3DF& origin);
    /// \ru Изменить размещение элемента управления без сигнала об изменении. \en Change the position of the control without initiation the modify signal. \~
    void Init(const Matrix3DF& transform);
    /// \ru Получить положение элемента управления. \en Get position of the control. \~
    const Matrix3DF& GetTransform() const;
    /// \ru Указать сцену, в которой отобразиться элемент управления. \en Set the Scene where the control will be displayed. \~
    void SetScene(GraphicsScene* pScene);
    /// \ru Проверить, является ли элемент управления видимым. \en Check the visibility of the contro. \~
    bool IsVisible() const;
    /// \ru Установить видимость элемента управления. \en Set the visibility of the contro. \~
    void SetVisible(bool bVisible);
    /// \ru Установить состояние отображения. \en Set the display state. \~
    void SetState(int state);
    /// \ru Получить состояние отображения. \en Get the display state. \~
    int GetState() const;
    /// \ru Установить модель. \en Set model. \~
    void SetModel(WidgetModelPtr ptrModel);
    /// \ru Сделать виджет масштабируемым. \en NO TRANSLATION.\~
    void SetScalable(bool value);
    /// \ru Узнать являеться ли виджет масштабируемым \en NO TRANSLATION.\~
    bool IsScalable() const;
public:
    /// \ru Получить точку позиции элемента управления. \en Get constrol position. \~
    Point3DF GetOrigin() const;
    /// \ru Изменить точку позиции элемента управления. \en Set constrol position. \~
    void SetOrigin(const Point3DF& origin);
    /// \ru Повернуть элемент управления. \en Rotate the control. \~
    void Rotate(const Point3DF& origin, const Vector3DF vAxis, float angle);
    /// \ru Получить размер. \en Get the bounding box. \~
    MbCube GetSize() const;
public:
    /// \ru Сигнал об изменении размещения элемента управления. \en Signal about the change of control placement. \~
    VSN_SIGNAL(Public, OnModified, void OnModified(SceneWidget* item), item)
    /// \ru Событие запуска процесса. \en Process start event. \~
    VSN_SIGNAL(Public, OnStartProcess, void OnStartProcess(SceneWidget* item), item)
    /// \ru Событие остановки процесса. \en Process stop event. \~
    VSN_SIGNAL(Public, OnStopProcess, void OnStopProcess(SceneWidget* item), item)
    /// \ru Событие изменения позиции.\en Signal about the change of position. \~
    VSN_SIGNAL(Public, OnPositionModified, void OnPositionModified(const Matrix3DF transform), transform)
public:
    /// \ru Подключить процесс к компоненту элемента управления. \en Connect process to a component of the control. \~
    void AssignProcess(int id, WidgetProcess* process) override;
    /// \ru Получить подключенный процесс к компоненту элемента управления. \en Get a process connected to a component of the control. \~
    WidgetProcess* GetAssignedProcess(int id) const override;
private:
    using Node::SetParent;
protected:
    SceneWidget(SceneWidgetPrivate* priv,  GraphicsScene* pScene);
private:
    VSN_DECLARE_EX_PRIVATE(SceneWidget);
};

class Viewport;
class ViewWidgetPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс элемента управления, находящегося поверх сцены.\n
           \en The class of the element located on the window above the scene. \~
           \details \ru  \n
                    \en  \~
*/
// ---
class VSN_CLASS ViewWidget : public Object, public WidgetBase
{
    VSN_OBJECT(ViewWidget);
public:
    /// \ru Конструктор. \en Constructor. \~
    explicit ViewWidget(WidgetModelPtr ptrModel, Viewport& viewPort);
    /// \ru Конструктор. \en Constructor. \~
    virtual ~ViewWidget();
public:
    /// \ru Отобразить элемент управления. \en Render the control. \~
    void Render(RenderContext& context) const override;
    /// \ru Поиск геометрии по лучу. \en Search the geometry by the ray. \~
    std::pair<int, float> Intersect(const Ray3DF& ray) const override;
    /// \ru Рисовать элемент управления только в экранных координатах. \en Draw control only in screen coordinates. \~
    bool IsScreenOnly() const override;
    /// \ru Проверить, включена ли подсветка элемента управления. \en Check the highlight of the control. \~
    bool IsHighlightEnable() const override;
    /// \ru Установить подсветку элемента управления. \en Set the highlight of the control. \~
    void SetHighlightEnable(bool value);
    /// \ru Разместить элемент управления с отступами от границ родительской области. \en. Place the control indented from the boundaries of the parent area. \~
    void SetMargin(int left, int top, int right = -1, int bottom = -1);
    /// \ru Получить значение левой границы. \en Get the left margin value. \~
    int GetLeftMargin() const;
    /// \ru Получить значение правой границы. \en Get the right margin value. \~
    int GetRightMargin() const;
    /// \ru Получить значение верхней границы. \en Get the top margin value. \~
    int GetTopMargin() const;
    /// \ru Получить значение нижней границы. \en Get the bottom margin value. \~
    int GetBottomMargin() const;
    /// \ru Установить состояние отображения. \en Set the display state. \~
    void SetState(int state);
    /// \ru Получить состояние отображения. \en Get the display state. \~
    int GetState() const;
    /// \ru Ширина элемента управления в пикселях на экране. \en Return width of control in pixels on screen. \~
    int GetWidth() const;
    /// \ru Высота элемента управления в пикселях на экране. \en Return height of control in pixels on screen. \~
    int GetHeight() const;
    /// \ru Ширина элемента управления в пикселях на экране. \en Set width of control in pixels on screen. \~
    void SetWidth(int width);
    /// \ru Высота элемента управления в пикселях на экране. \en Set height of control in pixels on screen. \~
    void SetHeight(int height);
    /// \ru Позиция центра модели. \en Model center position. \~
    PointI GetModelOrigin() const;
    /// \ru Визуальная модель. \en Visual model. \~
    const WidgetModel* GetModel() const;
    /// \ru Установить модель. \en Set model. \~
    void SetModel(WidgetModelPtr ptrModel);
    /// \ru Проверить, является ли элемента управления видимым. \en Check the visibility of the control. \~
    bool IsVisible() const;
    /// \ru Установить видимость элемента управления. \en Set the visibility of the control. \~
    void SetVisible(bool bVisible);
    /// \ru Подключить процесс к компоненту элемента управления. \en Connect process to a component of the control. \~
    void AssignProcess(int id, WidgetProcess* process) override;
    /// \ru Получить подключенный процесс к компоненту элемента управления. \en Get a process connected to a component of the control. \~
    WidgetProcess* GetAssignedProcess(int id) const override;
public:
    /// \ru Сигнал о наведении курсора на элемент управления. \en Signal when the cursor hovers over an element. \~
    VSN_SIGNAL(Public, OnHoverEnter, void OnHoverEnter(WidgetBase* widget), widget)
    /// \ru Сигнал об отведении курсора с элемента управления. \en Signal when the cursor moves away from an element. \~
    VSN_SIGNAL(Public, OnHoverLeave, void OnHoverLeave(WidgetBase* widget), widget)
protected:
    ViewWidget(ViewWidgetPrivate* priv, Viewport& viewport);
private:
    VSN_DECLARE_EX_PRIVATE(ViewWidget);
};
typedef std::shared_ptr<ViewWidget> ViewWidgetPtr;

} // namespace VSN

#endif //__VSN_WIDGETS_H
