////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Набор стандартных процессов модификации виджета.
         \en The set of standard models of the widget. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCHANGEWIDGETRT_H
#define __VSN_PRCHANGEWIDGETRT_H

#include <vsn_process.h>
#include <vsn_graphicsview.h>
#include <vsn_math.h>

namespace VSN {

class SceneWidget;
class WidgetBase;
class AbsCoordLocator;

/// \ru Процессное событие. \en Process event. \~
struct WidgetEvent
{
    PointI screenPoint; // точка на экране
    const Point3DF& touchPoint; // точка касания
    WidgetBase& widget; // манипулятор
    const Viewport& viewport; // окно
};

class WidgetProcessPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Базовый класс для процессоф модификации виджета. \n
           \en The Base class to modify widget. \~
           \details \ru  \n
                    \en  \~
*/
// ---
class VSN_CLASS WidgetProcess : public Process
{
    VSN_OBJECT(WidgetProcess);
public:
    /// \ru Конструктор для унаследования пользовательскими процессами. \en . \~
    WidgetProcess(Node* pParent = nullptr);
    virtual ~WidgetProcess();
public:
    /// \ru Событие запуска процесса. \en . \~
    virtual void EvStart(const WidgetEvent& ev) = 0;
    /// \ru Событие перемещения виджета при помощи курсора мыши. \en . \~
    virtual void EvMove(const WidgetEvent& ev) = 0;
    /// \ru Событие остановки процесса. \en . \~
    virtual void EvStop() = 0;
public:
    // дополнительные сообщения
    virtual void EvHoverEnter(const WidgetEvent& ev) = 0;
    virtual void EvHoverLeave() = 0;
    virtual void EvHoverMove(const WidgetEvent& ev) = 0;
    virtual void EvMouseDown(const WidgetEvent& ev, int flags) = 0;
    virtual void EvMouseUp(const WidgetEvent& ev, int flags) = 0;
    virtual void EvMouseDblClick(const WidgetEvent& ev, int flags) = 0;
protected:
    WidgetProcess(WidgetProcessPrivate*, Node* pParent = nullptr);
private:
    VSN_DECLARE_EX_PRIVATE(WidgetProcess);
};
typedef  std::shared_ptr<WidgetProcess> WidgetProcessPtr;


/// \ru Систтемы координат, используемые при перемещении по кривой. \en. \~
enum class WidgetConvertPlacements
{
    /** \ru Кривая находиться в системе координат сцены. Виджет перемещается по неподвижной кривой.
        \en . \~
    */
    Scene,
    /** \ru Кривая находиться в системе координат виджета, и перемещается вместе с виджетом. 
        \en . \~
    */
    Widget 
};

class MoveWidgetProcessPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Процесс перемещения виджета с использованием локаторов. \n
           \en. \~
           \details \ru Позволяет перемещать виджет по кривой, поверхности и свободно в пространстве \n
                    \en  \~
*/
// ---
class VSN_CLASS MoveWidgetProcess : public WidgetProcess
{
    VSN_OBJECT(MoveWidgetProcess);
public:
    /// \ru Конструктор. \en Constructor. \~
    MoveWidgetProcess(AbsCoordLocator* locator, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~MoveWidgetProcess();
public:
    /// \ru Событие запуска процесса. \en . \~
    virtual void EvStart(const WidgetEvent& ev) override; 
    /// \ru Событие перемещения виджета при помощи курсора мыши. \en . \~
    virtual void EvMove(const WidgetEvent& ev) override;
    /// \ru Событие остановки процесса. \en . \~
    virtual void EvStop() override;

    // дополнительные сообщения
    virtual void EvHoverEnter(const WidgetEvent&) override {};
    virtual void EvHoverLeave() override {};
    virtual void EvHoverMove(const WidgetEvent&) override {};
    virtual void EvMouseDown(const WidgetEvent&, int) override {};
    virtual void EvMouseUp(const WidgetEvent&, int) override {};
    virtual void EvMouseDblClick(const WidgetEvent&, int) override {};
public:
    /// \ru Поменять локатор процесса. \en . \~
    void SetLocator(AbsCoordLocator* locator);
    /// \ru Получить локатор процесса. \en . \~
    AbsCoordLocator* GetLocator() const;

    /// \ru Указать систему координат в которой находиться объект в локаторе (по умолчанию Widget). \en . \~
    void SetConvertPlacement(WidgetConvertPlacements);
    /// \ru В какой системе координат находиться объект в локаторе. \en . \~
    WidgetConvertPlacements GetConvertPlacement() const;
private:
    VSN_DECLARE_EX_PRIVATE(MoveWidgetProcess);
};

class RotateWidgetProcessPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Процесс вращения виджета вокруг оси. \n
           \en. \~
*/
// ---
class VSN_CLASS RotateWidgetProcess : public WidgetProcess
{
    VSN_OBJECT(RotateWidgetProcess);
public:
    /// \ru Конструктор. \en Constructor. \~
    RotateWidgetProcess(const MbAxis3D& axis, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~RotateWidgetProcess();
public:
    /// \ru Событие запуска процесса. \en . \~
    virtual void EvStart(const WidgetEvent& ev) override;
    /// \ru Событие перемещения виджета при помощи курсора мыши. \en . \~
    virtual void EvMove(const WidgetEvent& ev) override;
    /// \ru Событие остановки процесса. \en . \~
    virtual void EvStop() override;

    // дополнительные сообщения
    virtual void EvHoverEnter(const WidgetEvent&) override {};
    virtual void EvHoverLeave() override {};
    virtual void EvHoverMove(const WidgetEvent&)  override {};
    virtual void EvMouseDown(const WidgetEvent&, int) override {};
    virtual void EvMouseUp(const WidgetEvent&, int) override {};
    virtual void EvMouseDblClick(const WidgetEvent&, int) override {};

    /// \ru Задать шаг вращения, в радианах. \en . \~
    void SetStep(double);
    /// \ru Получить шаг вращения, в радианах. \en . \~
    double GetStep() const;
private:
    VSN_DECLARE_EX_PRIVATE(RotateWidgetProcess);
};

class CameraWidgetProcessPrivate;

class VSN_CLASS CameraWidgetProcess : public WidgetProcess
{
    VSN_OBJECT(CameraWidgetProcess);
public:
    /// \ru Конструктор. \en Constructor. \~
    CameraWidgetProcess(const MbAxis3D& axis, Node* pParent = nullptr);
    /// \ru Конструктор. \en Constructor. \~
    CameraWidgetProcess(const Vector3DF& vector, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~CameraWidgetProcess();
public:
    /// \ru Событие запуска процесса. \en . \~
    virtual void EvStart(const WidgetEvent& ev) override;
    /// \ru Событие перемещения виджета при помощи курсора мыши. \en . \~
    virtual void EvMove(const WidgetEvent& ev) override;
    /// \ru Событие остановки процесса. \en . \~
    virtual void EvStop() override;

    // дополнительные сообщения
    virtual void EvHoverEnter(const WidgetEvent&) override {};
    virtual void EvHoverLeave() override {};
    virtual void EvHoverMove(const WidgetEvent&)  override {};
    virtual void EvMouseDown(const WidgetEvent&, int) override {};
    virtual void EvMouseUp(const WidgetEvent&, int) override {};
    virtual void EvMouseDblClick(const WidgetEvent&, int) override {};
private:
    VSN_DECLARE_EX_PRIVATE(CameraWidgetProcess);
};

class TouchWidgetProcessPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Процесс событий клика мыши. \n
           \en. \~

           \details \ru Процесс генерирует события клика левой кнопки мыши по элементу. 
                        Если посли захвата мыши происходит перемещение, то будет выполняться рабочий процесс.
                        После работы рабочего процесса события клика мыши не приходят. \n
                    \en  \~
*/
// ---
class VSN_CLASS TouchWidgetProcess : public WidgetProcess
{
    VSN_OBJECT(TouchWidgetProcess);
public:
    /// \ru Конструктор. \en Constructor. \~
    TouchWidgetProcess(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~TouchWidgetProcess();
public:
    /// \ru Событие запуска процесса. \en . \~
    virtual void EvStart(const WidgetEvent& ev) override;
    /// \ru Событие перемещения виджета при помощи курсора мыши. \en . \~
    virtual void EvMove(const WidgetEvent& ev) override;
    /// \ru Событие остановки процесса. \en . \~
    virtual void EvStop() override;

    /// \ru дополнительные сообщения
    virtual void EvHoverEnter(const WidgetEvent& ev) override;
    virtual void EvHoverLeave() override;
    virtual void EvHoverMove(const WidgetEvent&) override {};
    virtual void EvMouseDown(const WidgetEvent&, int) override {};
    virtual void EvMouseUp(const WidgetEvent&, int) override {};
    virtual void EvMouseDblClick(const WidgetEvent&, int) override;

    /// \ru Задать рабочий процесс выполняюший работу. \en . \~
    void SetWorkProcess(WidgetProcess* process);
    /// \ru рабочий процесс выполняюший работу. \en . \~
    WidgetProcess* GetWorkProcess() const;
public:
    /// \ru Сигнал о наведении курсора на элемент. \en. \~
    VSN_SIGNAL(Public, OnHoverEnter, void OnHoverEnter(WidgetBase* widget), widget)
    /// \ru Сигнал о отведении курсора с элемента. \en. \~
    VSN_SIGNAL(Public, OnHoverLeave, void OnHoverLeave(WidgetBase* widget), widget)
    /// \ru Сигнал о наведении курсора на элемент. \en . \~
    VSN_SIGNAL(Public, OnHoverDelayEnter, void OnHoverDelayEnter(WidgetBase* widget), widget)
    /// \ru . \en. \~
    VSN_SIGNAL(Public, OnClick, void OnClick(WidgetBase* widget), widget)
    /// \ru. \en. \~
    VSN_SIGNAL(Public, OnDoubleClick, void OnDoubleClick(WidgetBase* widget), widget)
    /// \ru. \en. \~
    VSN_SIGNAL(Public, OnDelayClick, void OnDelayClick(WidgetBase* widget), widget)
    /// \ru Сигнал активации рабочего процесса. \en. \~
    VSN_SIGNAL(Public, OnStartWork, void OnStartWork(WidgetBase* widget), widget)
    /// \ru Сигнал активации рабочего процесса. \en. \~
    VSN_SIGNAL(Public, OnStopWork, void OnStopWork(WidgetBase* widget), widget)
private:
    VSN_DECLARE_EX_PRIVATE(TouchWidgetProcess);
};

} // namespace VSN

#endif /*__VSN_PRCHANGEWIDGETRT_H*/
