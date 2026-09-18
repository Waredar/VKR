////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Камера для отрисовки 3D сцены.
       \en Camera for 3D scene rendering. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_CAMERA_H
#define __VSN_CAMERA_H

#include <vsn_essence.h>
#include <vsn_namespace.h>
#include <vsn_math.h>
#include <vsn_global.h>

namespace VSN {

class CameraPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс виртуальной камеры для отрисовки 3D сцены.
           \en A class for 3D scene rendering, using virtual camera. \~
    \details \ru Класс виртуальной камеры для отрисовки 3D сцены. Он представляет много разных методов для позиционирования, ориентации камеры,
                 а также точку взгляда на сцену и.т.д. При отрисовке сцены камера расчитывает как матрицу проецирования, так и матрицу вида.
                 Камера может позиционироваться перед любым сегментом сцены для правильного его отображения. Положение и ориентация камеры
                 по умолчанию равны (0,0,1) по направлению взгляда вдоль отрицательной оси.\n.
             \en A virtual camera class for 3D scene rendering. It represents a lot of different methods for positioning, camera orientation,
                and also gives a point of scene view. When rendering a scene the camera initializes matrix of projection and view matrix.
                Camera can be positioned in front of any scene segment for its right rendering.
                The default position and orientation of the camera are (0,0,1) with a view direction along negative axis.\n \~
    \ingroup Vision_Viewport
*/
// ---
class VSN_CLASS Camera : public Essence
{
    VSN_OBJECT(Camera)
public:
    /** \brief \ru Конструктор по умолчанию.
               \en Default constructor. \~
        \details \ru Конструктор по умолчанию. Позиция взгляда (0, 0, 1), up-вектор инициализирован по оси y (0, 1, 0).
                     Угол обзора составляет 30 градусов и диапазон отсечения составляет (0.1, 1000.0).\n
                 \en Default constructor. The position of view is (0, 0, 1), up vector is initialized by y-axis (0, 1, 0). View angle is 30 degrees, clipping range is (0.1, 1000.0). \n \~
    */
    Camera();
    /// \ru Конструктор по параметрам. \en Constructor by parameters. \~ 
    Camera(const Point3DF&, const Point3DF&, const Vector3DF&);
    /// \ru Конструктор копирования. \en Copy constructor. \~
    Camera(const Camera& other);
    /// \ru Деструктор. \en Destructor. \~ 
    ~Camera() override;
public:
    /// \ru Инициализация камеры по параметрам. \en Initializes the camera by parameters. \~ 
    void Init(const Point3DF& position, const Point3DF& targetPosition, const Vector3DF& up);
    /// \ru Инициализация камеры по параметрам. \en Initializes the camera by parameters. \~
    void Init(const Point3DF& position, const Vector3DF& up);
    /// \ru Инициализация камеры по параметру. \en Initializes the camera by parameter. \~ 
    void Init(const Point3DF& position);
    /// \ru Инициализация камеры по параметру. \en Initializes the camera by parameter. \~ 
    void InitTarget(const Point3DF& targetPosition);
    /// \ru Инициализация камеры по другой камере. \en Initializes the camera by other camera. \~ 
    void Init(const Camera& other);
public:
    /// \ru Вернуть реальное расстояние между объектом и камерой. \en Returns a real distance between target and camera. \~ 
    float DistanceCameraToTarget() const;
    /// \ru Установить новое расстояние между камерой и объектом, т.е. переместить камеру. Эта величина должна быть положительная. \en Sets new distance between target and camera, i.e. replace the camera. This value must be positive. \~
    void SetDistanceCameraToTarget(float dis);
    /// \ru Установить новое расстояние между объектом и камерой, т.е. переместить объект. Эта величина должна быть положительная. \en Sets new distance between target and camera, i.e. replace the camera. This value must be positive. \~ 
    void SetDistanceTargetToCamera(float dis);

    /// \ru Вернуть позицию камеры. \en Returns camera position. \~ 
    const Point3DF& GetPosition() const;
    /// \ru Установить новую позицию камеры. По умолчанию позиция (0, 0, 1). \en Sets new position for the camera. The default position is (0, 0, 1). \~   
    void SetPosition(const Point3DF& position);

    /// \ru Вернуть позицию объекта сцены. По умолчанию в качестве позиции объекта берется его центр. \en Returns position of scene target. The default position of target is the origin. \~  
    const Point3DF& GetTargetPosition() const;
    /// \ru Установить позицию объекта. По умолчанию в качестве позиции объекта берется его центр. \en Sets position of target. The default position of target is the origin. \~
    void SetPositionTarget(const Point3DF& targetPosition);

    /// \ru Вернуть up-вектор камеры. По умолчанию значение (0, 1, 0). \en Returns up vector of the camera. The default value is (0, 1, 0). \~ 
    const Vector3DF& GetUpVector() const;
    /// \ru Установить up-вектор камеры. По умолчанию значение (0, 1, 0). \en Sets up vector of the camera. The default value is (0, 1, 0). \~ 
    void SetUpVector(const Vector3DF& up);

    /// \ru Вернуть вектор взгляда от камеры до цели. \en Returns view vector from camera to target. \~ 
    Vector3DF GetForward() const;
    /// \ru Вернуть вектор со стороны камеры. \en Returns vector from the camera. \~ 
    Vector3DF GetSideVector() const;
    /// \ru Получить видовую матрицу (матрицу камеры). \en Returns view matrix (camera matrix). \~ 
    const Matrix3DF& GetViewMatrix() const;

    /// \ru Вернуть up вектор камеры по умолчанию. \en Returns the default up vector of the camera. \~ 
    const Vector3DF& GetDefaultUpVector() const;
    /// \ru Установить up вектор камеры по умолчанию. \en Sets the default up vector of the camera. \~ 
    void SetDefaultUpVector(const Vector3DF& vecUp);

    /// \ru Установить стандартный вид ориентации. \en Sets standard view of orientation. \~ 
    void SetViewOrientation(Orientation orientation);
    /// \ru Вернуть матрицу вида камеры. \en Returns view matrix of the camera. \~ 
    Matrix3DF GetModelViewMatrix() const;
    Matrix3DF GetWorldTransform() const;
public:
    /// \ru Вращение вокруг начала координат мира(по орбите). \en Rotates around the world origin (by orbit). \~ 
    void RotateSpherical(const Vector3DF& vectOld, const Vector3DF& vectCur);
    /// \ru Панорамирование вида. \en View panning. \~ 
    void Pan(const Vector3DF& vectShift);
    /// \ru Сдвиг вектора камеры вдоль вектора взгляда (фактор должен быть больше 0). \en Moves vector of the camera along view vector(factor must be more 0). \~ 
    void SetZoom(float factor);

    /// \ru Поменять положение камеры согласно заданной матрице. \en Changes the camera position by the defined matrix. \~ 
    void Transform(const Matrix3DF& matMove);
    /// \ru Повернуть вокруг оси. \en Rotates about the axis. \~ 
    void RotateAbout(const Vector3DF& axis, float angle, const Point3DF& pnt);
    /// \ru Повернуть вокруг объекта (его позиции). \en Rotates about the target( its origin). \~ 
    void RotateAboutTarget(const Vector3DF& vec, float angle);
    /// \ru Перемещение камеры по вектору. \en Moves the camera by vector. \~
    void Translate(const Vector3DF& vecTrans);

    /** \brief \ru Перемещение камеры вокруг объекта сцены.
               \en Moves the camera about scene target. \~
        \param[in] angle1 - \ru Расстояние в радианах, которое камера обойдет вокруг объекта(Target) слева на право. Может быть отрицательным.
                            \en The distance, in radians, that camera passes around the target from left to right. Can be negative. \~

        \param[in] angle2 - \ru Расстояние в радианах, которое камера обойдет вокруг объекта(Target) снизу вверх. Может быть отрицательным.
                            \en The distance, in radians, that camera passes around the target from bottom to top. Can be negative. \~
    */
    void Orbit(float angle1, float angle2);

    /** \brief \ru Вращение камеры вокруг оси взгляда.
               \en Rotates camera about view axis. \~
        \param[in] angle - \ru Угол поворота камеры вокруг оси взгляда в радианах.
                           \en Rotation angle of the camera, in radians, about view axis. \~
    */
    void Roll(float angle);
public:
    /// \ru Настроить камеру перед отрисовкой всей сцены. \en Sets camera before the whole scene rendering. \~ 
    void MultMatrix();
public:
    /// \ru Оператор равенства. \en Equality operator. \~ 
    bool operator == (const Camera& other) const;
public:
    VSN_SIGNAL(Public, OnCameraModified, void OnCameraModified())
    VSN_SIGNAL(Public, OnOrientationModified, void OnOrientationModified(Orientation orientation), orientation)
private:
    VSN_DECLARE_EX_PRIVATE(Camera);
};

} // namespace VSN

#endif /* __VSN_CAMERA_H */
