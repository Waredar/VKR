///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en . \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BOX_H
#define __VSN_BOX_H

#include <vsn_math.h>
#include <vsn_rect.h>
#include <vsn_global.h>

class MbCube;
namespace VSN {

struct Ray3DF;
//------------------------------------------------------------------------------
/** \brief \ru .
           \en . \~
  \details \ru . \n
           \en . \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS BoxF
{
public:
    /// \ru Пустой конструктор \en The empty constructor 
    BoxF();
    /// \ru Конструктор копирования. \en Copy constructor. 
    BoxF(const BoxF& init);
    /// \ru Конструктор копирования. \en Copy constructor. 
    BoxF(const MbCube& init);
    /// \ru Конструктор по координатам \en The constructor by coordinates 
    /**
      \param[in] xmin, ymin, zmin - \ru Координаты точки угла куба с минимальными  координатами.
                                    \en Coordinates of a box corner point with minimal coordinates. \~
      \param[in] xmax, ymax, zmax - \ru Координаты точки угла куба с максимальными  координатами.
                                    \en Coordinates of a box corner point with maximal coordinates. \~
      \param[in] normalize - \ru Нормализовать себя.
                             \en Normalize itself. \~
    */
    BoxF(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool normalize = false);
    /// \ru Конструктор по двум точкам. \en The constructor by two points. 
    /**
      \param[in] p0 - \ru Точка угла куба с минимальными  координатами.
                      \en A point of a box corner with minimal coordinates. \~
      \param[in] p1 - \ru Точка угла куба с максимальными  координатами.
                      \en A point of a box corner with maximal coordinates. \~
      \param[in] normalize - \ru Нормализовать себя.
                             \en Normalize itself. \~
    */
    BoxF(const Point3DF& p0, const Point3DF& p1, bool normalize = false);
    /// \ru Деструктор. \en Destructor. 
    ~BoxF();
public:
    /**
      \brief \ru Проверка на пустоту. \en The check for emptiness.
      \details \ru Габаритный параллелепипед считается пустым, если он не содержит ни одной точки 3D-пространства.
               \en A bounding box is empty if it doesn't contain any points of 3D-space \~
    */
    bool IsEmpty() const;
    /// \ru Установить пустым ("вывернутым"). \en Set empty ("reverted"). 
    void SetEmpty();
    /// \ru Инициализировать по координатам. \en Initialize by coordinates. 
    /**
      \param[in] xmin, ymin, zmin - \ru Координаты точки угла куба с минимальными  координатами.
                                    \en Coordinates of a box corner point with minimal coordinates. \~
      \param[in] xmax, ymax, zmax - \ru Координаты точки угла куба с максимальными  координатами.
                                    \en Coordinates of a box corner point with maximal coordinates. \~
      \param[in] normalize - \ru Нормализовать себя.
                             \en Normalize itself. \~
    */
    void Set(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool normalize = false);
    /// \ru Инициализировать по двум точкам. \en Initialize by two points. 
    /**
      \param[in] p0 - \ru Точка угла куба с минимальными  координатами.
                      \en A point of a box corner with minimal coordinates. \~
      \param[in] p1 - \ru Точка угла куба с максимальными  координатами.
                      \en A point of a box corner with maximal coordinates. \~
      \param[in] normalize - \ru Нормализовать себя.
                             \en Normalize itself. \~
    */
    void Set(const Point3DF& p0, const Point3DF& p1, bool normalize = false);

    /**
      \ru \name Функции доступа к полям
      \en \name Functions for access to fields.
      \{ */
      /// \ru Установить минимальную координату по X. \en Set the minimal coordinate by X. 
    void SetXMin(float s) { pmin.x = s; }
    /// \ru Установить минимальную координату по Y. \en Set the minimal coordinate by Y. 
    void SetYMin(float s) { pmin.y = s; }
    /// \ru Установить минимальную координату по Z. \en Set the minimal coordinate by Z. 
    void SetZMin(float s) { pmin.z = s; }
    /// \ru Установить максимальную координату по X. \en Set the maximal coordinate by X. 
    void SetXMax(float s) { pmax.x = s; }
    /// \ru Установить максимальную координату по Y. \en Set the maximal coordinate by Y. 
    void SetYMax(float s) { pmax.y = s; }
    /// \ru Установить максимальную координату по Z. \en Set the maximal coordinate by Z. 
    void SetZMax(float s) { pmax.z = s; }

    /// \ru Дать минимальную координату по X. \en Give the minimal coordinate by X. 
    float GetXMin() const { return pmin.x; }
    /// \ru Дать минимальную координату по Y. \en Give the minimal coordinate by Y. 
    float GetYMin() const { return pmin.y; }
    /// \ru Дать минимальную координату по Z. \en Give the minimal coordinate by Z. 
    float GetZMin() const { return pmin.z; }
    /// \ru Дать максимальную координату по X. \en Give the maximal coordinate by X. 
    float GetXMax() const { return pmax.x; }
    /// \ru Дать максимальную координату по Y. \en Give the maximal coordinate by Y. 
    float GetYMax() const { return pmax.y; }
    /// \ru Дать максимальную координату по Z. \en Give the maximal coordinate by Z. 
    float GetZMax() const { return pmax.z; }
    /** \} */

    /// \ru Дать минимальные координаты. \en Give the minimal coordinates. 
    Point3DF GetMin() const { return pmin; }
    /// \ru Дать максимальные координаты. \en Give the maximal coordinates. 
    Point3DF GetMax() const { return pmax; }

    /**
      \brief \ru Добавить габарит.
             \en Add bounding box. \~
      \details \ru Габарит добавляется в локальной системе координат исходного куба.
               \en A bounding box is added in the local coordinate system of the initial box. \~
      \param[in] r - \ru Габарит.
                     \en A bounding box. \~
      \param[in] place - \ru Локальная система координат.
                         \en A local coordinate system. \~
    */
    void AddRect(const RectF& r, const Matrix3DF& placeFrom);
    /**
      \brief \ru Проекция на плейсмент.
             \en A projection onto the placement. \~
      \details \ru Вычисляет прямоугольник, охватывающий проекцию куба на плейсмент.
               \en Calculates a rectangle covering a projection of box onto the placement. \~
      \param[in] place - \ru Локальная система координат.
                         \en A local coordinate system. \~
      \param[out] rect - \ru Прямоугольник, охватывающий искомую проекцию.
                         \en A rectangle covering a required projection. \~
    */
    void ProjectionRect(const Matrix3DF & matrixInto, RectF & rect) const;
    /**
      \brief \ru Определить положение куба относительно плоскости.
             \en Define the box position relative to the plane. \~
      \details \ru Определить положение куба относительно плоскости XY локальной системы координат, направление оси Z локальной системы координат при этом не учитывается.
               \en Define the box position relative to the plane XY of a local coordinate system, the Z axis of the local coordinate system is not taken into account here. \~
      \param[in] pl - \ru Локальная система координат, задающая плоскость.
                      \en A local coordinate system which defines a plane. \~
      \param[in] eps - \ru Метрическая точность.
                       \en A metric tolerance. \~
      \return \ru 0 - куб пересекает плоскость XY локальной системы координат,\n
                  1 - куб расположен над плоскостью XY локальной системы координат,\n
                 -1 - куб расположен под плоскостью XY локальной системы координат.
              \en 0 - box intersects the XY plane of a local coordinate system,\n
                  1 - box is located over the XY plane of a local coordinate system,\n
                 -1 - box is located under the XY plane of a local coordinate system. \~
    */
    int GetLocation(const Matrix3DF& placeFrom, double eps) const;
    /// \ru Нормализовать себя. \en Normalize itself. 
    void Normalize();
    /// \ru Включить в себя точку, заданную как XYZ. \en Enclose a point specified as XYZ. 
    /**
      \param[in] x, y, z - \ru Координаты точки, которую требуется включить в габарит.
                           \en Coordinates of a point which has to be included in the box. \~
    */
    void Include(float x, float y, float z);
    /// \ru Включить в себя точку. \en Enclose a point.
    void Include(const Point3DF &);
        /// \ru Включить в себя куб. \en Enclose a box.
    void Include(const BoxF &);
    /// \ru Куб объединения двух кубов. \en A box of union of two boxes. 
    /**
      \param[in] cube1, cube2 - \ru Исходные кубы.
                                \en Input boxes. \~
      \return \ru false, если итоговый куб пуст, \n true в противном случае.
              \en Returns false if the result box is empty, \n true otherwise. \~
    */
    bool Union(const BoxF& cube1, const BoxF& cube2);
    /// \ru Дать размер стороны X куба. \en Give the size of the X side of a box. 
    float GetLengthX() const;
    /// \ru Дать размер стороны Y куба. \en Give the size of the Y side of a box. 
    float GetLengthY() const;
    /// \ru Дать размер стороны Z куба. \en Give the size of the Z side of a box. 
    float GetLengthZ() const;
    /// \ru Дать размер диагонали куба. \en Give the size of box diagonal. 
    float GetDiagonal() const;
    /// \ru Выдать вершину куба по индексу. \en Get a box vertex by an index. 
    /**
      \param[in] index - \ru Исходный индекс. 0 <= index <= 7.
                         \en An initial index. 0 <= index <= 7. \~
      \param[out] p - \ru Искомая вершина.
                      \en Required vertex. \~
    */
    void GetVertex(size_t index, Point3DF& p) const;
    /// \ru Выдать центр куба. \en Give the box center.
    Point3DF GetCenter() const;
public:
    /// \ru Расширить куб во все стороны на величину delta. \en Expand the box in all directions on a "delta" amount. 
    void Enlarge(float delta);
    /// \ru Расширить куб во все стороны на соответствующую величину. \en Expand the box in all directions on a corresponding amount. 
    void Enlarge(float dx, float dy, float dz);
    /// \ru Сдвинуть вдоль вектора. \en Translate along a vector. 
    void Move(const Vector3DF & to);
    /// \ru Преобразовать согласно матрице. \en Transform according to the matrix. 
    void Transform(const Matrix3DF & matrix);
    /// \ru Масштабировать. \en Scale. 
    void Scale(float sx, float sy, float sz);
    /// \ru Являются ли объекты равными? \en Determine whether an object is equal? 
    bool IsSame(const BoxF& other) const;
public:
    /// \ru Определить пересечение с лучом. \en 
    bool Intersect(const Ray3DF& ray, float&) const;
    /// \ru Определить пересечение с плоскостью. возвращает 0 если пересекает, -1 если плоскость над кубом, 1 если под кубом \en 
    int Intersect(const Point3DF& o, const Vector3DF& x, const Vector3DF& y) const;

    /**
      \brief \ru Пересекается ли куб с линией.
             \en Whether the box intersects the line or not. \~
      \details \ru Линия задается точкой и вектором.
               \en A line is given by a point and vector. \~
      \param[in] eps - \ru Метрическая точность.
                       \en A metric tolerance. \~
      \return \ru true, если пересекается.
              \en Returns true if it intersects. \~
    */
//    bool Intersect(const MbCartPoint3D &, const MbVector3D &, float eps ) const;
public:
    /// \ru Присвоить значение. \en Assign a value. 
    void operator  = (const BoxF&);
    /// \ru Включить в себя точку. \en Enclose a point. 
    BoxF& operator |= (const Point3DF&);
    /// \ru Включить в себя габаритный куб. \en Enclose a bounding box. 
    BoxF& operator |= (const BoxF&);
    /// \ru Оператор равенства. \en The equality operator. 
    bool operator == (const BoxF&) const;
    /// \ru Оператор неравенства. \en The inequality operator. 
    bool operator != (const BoxF&) const;

    operator MbCube() const;
public:
    Point3DF pmin; ///< \ru Точка диагонали параллелепипеда с минимальными  координатами. \en A point of a box diagonal with minimal coordinates. 
    Point3DF pmax; ///< \ru Точка диагонали параллелепипеда с максимальными координатами. \en A point of a box diagonal with maximal coordinates. 
};

} // namespace VSN

#endif /*__VSN_POINT3D_H*/