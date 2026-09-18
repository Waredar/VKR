////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Файл содержит классы для поиска объектов, которые находятся под курсором мыши, 
               либо объекты, которые попали в ограниченный прямоугольник.
           \en The file contains classes searching objects under the mouse cursor or objects
               getting in a bounding rectangle. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRFINDSELECTOBJECT_H
#define __VSN_PRFINDSELECTOBJECT_H

#include <vsn_process.h>
#include <vsn_mouseevent.h>
#include <vsn_graphicsview.h>
#include <vsn_global.h>

namespace VSN {

class MouseEventHandler;
class ObjectPickSelection;
class PrBasicFindSelectPrivate;
//------------------------------------------------------------------------------
/** \brief \ru PrBasicFindSelect базовый класс для поиска объектов разными способами.
           \en PrBasicFindSelect class is the base class to search objects with different methods. \~
    \details \ru PrBasicFindSelect содержит функцию, которая инициализирует механизм поиска объектов.
             \en PrBasicFindSelect class contains a function initializing the mechanism of searching objects.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrBasicFindSelect : public Process
{
    VSN_OBJECT(PrBasicFindSelect);
public:
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrBasicFindSelect();
public:
    /// \ru Вернуть указатель на MouseEventHandler для Object::Connect. \en Returns a pointer to MouseEventHandler for Object::Connect. \~
    MouseEventHandler* GetMouseEventHandler() const;
    /// \ru Вернуть указатель на ObjectPickSelection. \en Returns a pointer to ObjectPickSelection. \~
    ObjectPickSelection* GetObjectPickSelection() const;
    /// \ru Установить указатель на поиск объектов. \en Sets a pointer to the object search. \~
    virtual void SetPickSelection(ObjectPickSelection* pPickSelection);
    // \ru Вернуть кнопки мыши для активации процесса. \en Returns the mouse buttons to activate a process. \~
    std::vector<int> GetMouseButtonsActivate() const;
    // \ru Установить кнопки мыши для активации процесса. \en Sets the mouse buttons to activate a process. \~
    void SetMouseButtonsActivate(const std::vector<int>& vecKey);
protected:
    explicit PrBasicFindSelect(PrBasicFindSelectPrivate& dd, Node* parent);
private:
    VSN_DECLARE_EX_PRIVATE(PrBasicFindSelect);
};

class PrFindSelectObjectPrivate;
//------------------------------------------------------------------------------
/** \brief \ru PrFindSelectObject класс для поиска объектов под курсором.
           \en PrFindSelectObject class performs searching objects under the mouse cursor. \~
    \details \ru PrFindSelectObject инициализируется по умолчанию в механизме поиска класса ObjectPickSelection.
             \en PrFindSelectObject is initialized by default in the ObjectPickSelection class search mechanism.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrFindSelectObject : public PrBasicFindSelect
{
    VSN_OBJECT(PrFindSelectObject);
public:
    PrFindSelectObject(GraphicsScene* pGraphicsScene, Node* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrFindSelectObject();
public:
    /// \ru Вернуть величену задержки для подсветки. \en Returns highlight delay value. \~
    int GetHighlightDelay();
    /// \ru Установить задержку для подсветки. \en Set highlight delay. \~
    void SetHighlightDelay(int delay);
protected:
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseDown, void slotMouseDown(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseMove, void slotMouseMove(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseUp, void slotMouseUp(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en The slot takes events from the manipulator mouse. \~
    VSN_SLOT(Protected, slotMouseLeave, void slotMouseLeave(MouseEventObject* pMouse))
    /// <summary>
    VSN_SLOT(Protected, slotEnabledModified, void slotEnabledModified(bool bEnabled))
private:
    VSN_DECLARE_EX_PRIVATE(PrFindSelectObject);
};


class PrFindSelectAreaPrivate;
//------------------------------------------------------------------------------
/** \brief \ru PrFindSelectArea класс для поиска объектов ограниченной рамкой.
           \en PrFindSelectObject class performs searching objects with the bounding frame. \~
    \details \ru PrFindSelectArea как и PrFindSelectObject может быть добавлен пользователем самостоятельно в 
                 механизме поиска класса ObjectPickSelection. PrFindSelectArea имеет вспомогательный функционал, 
                 который может обеспечивать поведение выбора объектов рамкой. Также присутствует функционал, с помощью
                 которого пользователь может назначить горячие клавиши для активизациии процесса. PrFindSelectArea позволяет
                 настроить цвет рамки в зависимости от своего стиля пользовательского интерфейса.
             \en PrFindSelectArea class, like PrFindSelectObject class, can be added on the user's own
                 in the ObjectPickSelection class search mechanism. PrFindSelectArea class has a secondary functional
                 that can provide a behavior of the object selection with the frame. The class also has a functional that the user can use 
                 to set hotkeys to activate a process. PrFindSelectArea class provides setting a frame color depending on 
                 the user interface style. \n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrFindSelectArea : public PrBasicFindSelect
{
    VSN_OBJECT(PrFindSelectArea);
public:
    /// \ru Возможные типы поведения объектов во время выбора. \en All possible types of object selection behavior. \~
    enum RectType
    {
        at_UnifyingCutting, /// \ru Объединяющая и секущая рамка определяет вектор направления рамки. \en The frame becomes unifying and cutting, and defines a vector of its direction. \~ 
        at_CuttingUnifying, /// \ru Секущая и объединяющая рамка определяет вектор направления рамки. \en The frame becomes cutting and unifying, and defines a vector of its direction. \~ 
        at_OnlyUnifying,    /// \ru Объединяющая рамка, выбор объектов происходит, когда они полностю попадают в область рамки. \en The frame becomes only unifying, and makes objects selected when they get in the frame area entirely. \~ 
        at_OnlyCutting,     /// \ru Секущая рамка, выбор объектов происходит, когда они попадают частично в область рамки. \en The frame becomes only cutting, and makes objects selected when they get in the frame area partially. \~ 
    };
public:
    /// \ru Конструктор для внутреннего использования. \en Constructor for inner use. \~ 
    explicit PrFindSelectArea(GraphicsScene* pGraphicsScene, Node* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrFindSelectArea();
public:
    // \ru Вернуть тип рамки для выбора объекта. \en Returns the frame type for selecting an object. \~
    RectType GetRectType() const;
    // \ru Установить тип рамки для выбора объекта. \en Sets the frame type for selecting an object. \~
    void SetRectType(RectType type);

    // \ru Вернуть кнопки клавиатуры для активации процесса. \en Returns keys for activating the process. \~
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    std::vector<int> GetKeyboardButtonsActivate() const;
    // \ru Установить кнопки клавиатуры для активации процесса. \en Sets keys for activating the process. \~
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    void SetKeyboardButtonsActivate(const std::vector<int>& vecKey);

    // \ru Вернуть значение флага активации, если клавиша на клавиатуре определена и нажата.
    // \en Returns the process activation flag only if a key preset is pressed. \~
    VSN_DEPRECATED_X("Do not use this feature, it will be removed.")
    bool HasActivationIfKeyPressed() const;
    // \ru Установить флаг активации процесса, если клавиша на клавиатуре определена и нажата. 
    // \en Sets the process activation flag only if a key preset is pressed. \~
    VSN_DEPRECATED_X("Do not use this feature, it will be removed.")
    void SetActivationIfKeyPressed(bool set);

    /// \ru Вернуть цвет заполнения для объединяющей рамки. \en Returns the filling color of the unifying frame. \~
    Color GetUnifyingRectFillColor() const;
    /// \ru Вернуть цвет границ для объединяющей рамки. \en Returns the border color of the unifying frame. \~
    Color GetUnifyingRectBorderColor() const;
    /// \ru Установить цвет заполнения и границ для объединяющей рамки. \en Sets the border and filling color of the unifying frame. \~
    void SetUnifyingColorRect(const Color& clrFill, const Color& clrBorder);

    /// \ru Вернуть цвет заполнения для секущей рамки. \en Returns the filling color of the cutting frame. \~
    Color GetCuttingRectFillColor() const;
    /// \ru Вернуть цвет границ для секущей рамки. \en Returns the border color of the cutting frame. \~
    Color GetCuttingColorRectBorderColor() const;
    /// \ru Установить цвет заполнения и границ для секущей рамки. \en Sets the border and filling color of the cutting frame. \~
    void SetCuttingColorRect(const Color& clrFill, const Color& clrBorder);

    /// \ru Есть ли объект под курсором мыши. \en Checks if there is an object under the mouse cursor. \~
    bool IsObjectUnderCursor() const;

    /// \ru Вернуть расстояние для начала рисования рамки. \en Returns the drag distance to start drawing the frame. \~
    VSN_DEPRECATED_X("Don't use this function, use Application::GetBeginDragDistance().")
    int GetStartDragDistance() const;
    /// \ru Установить расстояние для старта рисования рамки. \en Sets the drag distance to start drawing the frame. \~
    VSN_DEPRECATED_X("Don't use this function, use Application::GetBeginDragDistance().")
    void SetStartDragDistance(int dis);
public:
    VSN_SIGNAL(Public, signalStartArea,  void signalStartArea(bool& bAllow), bAllow)
    VSN_SIGNAL(Public, signalFinishArea, void signalFinishArea())
public:
    VSN_SIGNAL(Public, signalActivated,   void signalActivated())
    VSN_SIGNAL(Public, signalDeactivated, void signalDeactivated())
    VSN_SIGNAL(Public, signalToResetPreselectedObjects, void signalToResetPreselectedObjects())
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
    VSN_DECLARE_EX_PRIVATE(PrFindSelectArea);
};

} // namespace VSN

#endif /* __VSN_PRFINDSELECTOBJECT_H */
