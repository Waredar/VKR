////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Класс PrCameraComplexRotation обеспечивает интерактивные действия пользователя, а именно управление 
           камерой, ее вращением несколькими способами.
       \en PRCAMERACOMPLEXROTATION class provides the user's interactive actions, namely controlling 
           a camera, its rotation in several ways. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAROTATEABOUT_H
#define __VSN_PRCAMERAROTATEABOUT_H

#include <vsn_graphicsview.h>
#include <vsn_prabscamera.h>
#include <vsn_objectpickselection.h>
#include <vsn_global.h>

namespace VSN {

class GravityPointWidget;
class PrCameraComplexRotationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraComplexRotation обеспечивает интерактивные действия пользователя, а именно управление 
               камерой, ее вращением несколькими способами относительно точки фокуса, тогда как вид остается фиксированным. 
           \en PRCAMERACOMPLEXROTATION class provides the user's interactive actions, namely controlling
               a camera, its rotation in several ways relative to the focus point, while the view remains fixed. \~
    \details \ru PrCameraComplexRotation позволяет с помощью функции SetRotationType выбрать тип вращения, вращение камеры 
                 вокруг точки фокуса модели, вращение модели вокруг точки фокуса в любом направлении или вращение модели вокруг
                 вертикального вектора, как если бы модель была расположена на поворотной платформе. При использовании 
                 тип вращения ConstrainedRotation есть возможность назначить вектор вращения с помощью функции SetRotationVector, 
                 используя предопределенные варианты или произвольный вектор с помощью функции SetArbitraryRotationVector. 
                 Для задания произвольного вектора необходимо предварительно вызвать функцию SetRotationVector с параметром RotationNone.
                 Также для всех типов вращения необходимо назначить точку вращения через функцию SetGravityPoint, по умолчанию 
                 ее значения равны (0,0,0).
                 Назначение горячих кнопок мыши и клавиатуры в процессах PrCameraComplexRotation можно настроить 
                 по своему усмотрению с помощью дополнительного функционала в базовом классе SetMouseButtonsActivate и
                 SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши 
                 с одновременным нажатием клавиши клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана, 
                 вы будете наблюдать перемещение камеры вокруг модели.
             \en PRCAMERACOMPLEXROTATION allows you to select the type of rotation, rotation of the camera using the SetRotationType function 
                 around the point of the model’s focus, rotation of the model around the focus point in any direction or rotation of the model around
                 the vertical vector, as if the model were located on a rotary platform. Using 
                 the type ConstrainedRotation it is possible to assign a rotation vector using the SetRotationVector function, 
                 using predetermined options or an arbitrary vector using the SetArbitraryRotationVector function. 
                 To assign an arbitrary vector, it is necessary to first call the SetRotationVector function with the RotationNone parameter.
                 Also, for all types of rotation, it is necessary to assign a rotation point through the SetGravityPoint function, by default 
                 its value is (0,0,0).
                 The purpose of the hot keys of the mouse and keyboard in the Prcameracomplexrotation processes can be configured, 
                 using additional functionality in the base class, SetMouseButtonsActivate and
                 SetKeyboardButtonsActivate.For example, to activate the process, you can assign the left mouse button 
                 With the simultaneous pressing of the keyboard Ctrl.When the mouse moves in the plane of the screen, 
                 You will observe the movement of the camera around the model.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraComplexRotation : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraComplexRotation)
public:
    /// \ru Доступны следующие инструменты орбиты. \en The following orbit tools are available. \~
    enum RotationType
    {
        Rotation,            /// \ru Вращение камеры вокруг точки фокуса модели. \en The rotation of the camera around the focus point of the model. \~ 
        FreeRotation,        /// \ru Вращение модели вокруг точки фокуса в любом направлении. \en The rotation of the model around the focus point in any direction. \~ 
        ConstrainedRotation  /// \ru Вращение модели вокруг вертикального вектора, как если бы модель была расположена на поворотной платформе. \en The rotation of the model around the vertical vector, as if the model was located on a rotary platform. \~ 
    };
    /// \ru Доступны следующие инструменты орбиты. \en The following orbit tools are available. \~
    enum RotationVector
    {
        RotationNone,
        RotateAboutX,
        RotateAboutY,
        RotateAboutZ,
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit PrCameraComplexRotation(GraphicsScene* pGraphicsScene, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraComplexRotation();
public:
    /// \ru Вернуть указатель на центр вращения. \en Return the pointer to the center of rotation. \~
    GravityPointWidget* GetGravityPoint() const;

    /// \ru Вернуть тип вращения. \en Return the type of rotation. \~
    RotationType GetRotationType() const;
    /// \ru Установить тип вращения. \en Set the type of rotation. \~
    void SetRotationType(RotationType type);

    /// \ru Вернуть вертикальный вектор для вращения ConstrainedRotation. Значение по умолчанию равно RotateAboutZ. \en Return the vertical vector for ConstrainedRotation. The default value is RotateAboutZ. \~
    RotationVector GetRotationVector() const;
    /// \ru Установить вертикальный вектор для вращения ConstrainedRotation. \en Set the vertical vector for ConstrainedRotation. \~
    void SetRotationVector(const RotationVector& vector);

    /// \ru Вернуть произвольный вектор для вращения ConstrainedRotation. \en Return the arbitrary vector for ConstrainedRotation. \~
    Vector3DF GetArbitraryRotationVector() const;
    /// \ru Установить произвольный вектор для вращения ConstrainedRotation. \en Set the arbitrary vector for ConstrainedRotation. \~
    void SetArbitraryRotationVector(const Vector3DF& vertical);

    /// \ru Вернуть признак видимости точки вращения. \en Return the visibility of the rotation point. \~
    bool IsVisibleRotationCenter() const;
    /// \ru Установить видимость точки вращения. \en Set the visibility of the rotation point. \~
    void SetVisibleRotationCenter(bool visible);

    /// \ru Вернуть точку центра вращения. \en Return the center of rotation. \~
    Point3DF GetRotationCenter() const;
    /// \ru Установить точку центра вращения. \en Set the center of rotation. \~
    void SetRotationCenter(const Point3DF& pnt);
    /// \ru Сбросить назначенный пользователем центра вращения. \en Clear current center of rotation. \~
    void ClearRotationCenter();

    /// \ru Вернуть значение признака точки гравитации по центру экрана. \en Return if the gravity point in the center of the screen. \~
    bool IsAlignedToScreenCenter() const;
    /// \ru Установить точку гравитации по центру экрана. \en Set the gravity point in the center of the screen. \~
    void SetAlignedToScreenCenter(bool bCenter);
protected:
    /// \ru Активировать процесс. \en Activates the process. \~
    virtual void Activate() final;
    /// \ru Деактивировать процесс. \en Deactivates the process. \~
    virtual void Deactivate() final;
    /// \ru Обработка события перемещения мыши. \en Processes the mouse move event. \~
    virtual void MouseMove(float dt) final;
protected:
    /// \ru Слот для инициализации опорного объекта, относительно которого будет вращаться камера. \en The slot for initializing the support object, relative to which the camera will rotate. \~
    VSN_SLOT(Protected, slotObjectHoverMove, void slotObjectHoverMove(PickSelectionEventPtr event))
private:
    VSN_DECLARE_EX_PRIVATE(PrCameraComplexRotation);
    VSN_DISABLE_COPY(PrCameraComplexRotation);
};

} // namespace VSN

#endif /* __VSN_PRCAMERAROTATEABOUT_H */
