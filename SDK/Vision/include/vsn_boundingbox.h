///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en . \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BOUNDINGBOX_H
#define __VSN_BOUNDINGBOX_H

#include <vsn_box.h>
#include <vsn_math.h>
#include <vsn_rect.h>
#include <vsn_global.h>

class MbCube;

namespace VSN {

constexpr float  FLT_MIN_RADIUS = 1.0E-4F;  ///< \ru Минимальный  радиус объекта. \en Minimal object radius.

//------------------------------------------------------------------------------
/** \brief \ru .
           \en . \~
  \details \ru . \n
           \en . \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS BoundingBox
{
public:
    /// \ru Пустой конструктор \en The empty constructor \~
    BoundingBox();
    /// \ru Конструктор копирования. \en Copy constructor. \~
    BoundingBox(const BoundingBox& init);
    /// \ru Конструктор копирования. \en Copy constructor. \~
    BoundingBox(const MbCube& init);
    /// \ru Конструктор по координатам \en The constructor by coordinates \~
    /**
      \param[in] xmin, ymin, zmin - \ru Координаты точки угла куба с минимальными  координатами.
                                    \en Coordinates of a box corner point with minimal coordinates. \~
      \param[in] xmax, ymax, zmax - \ru Координаты точки угла куба с максимальными  координатами.
                                    \en Coordinates of a box corner point with maximal coordinates. \~
      \param[in] normalize - \ru Нормализовать себя.
                             \en Normalize itself. \~
    */
    BoundingBox(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, bool normalize = false);
    /// \ru Конструктор по двум точкам. \en The constructor by two points. 
    /**
      \param[in] p0 - \ru Точка угла куба с минимальными  координатами.
                      \en A point of a box corner with minimal coordinates. \~
      \param[in] p1 - \ru Точка угла куба с максимальными  координатами.
                      \en A point of a box corner with maximal coordinates. \~
      \param[in] normalize - \ru Нормализовать себя.
                             \en Normalize itself. \~
    */
    BoundingBox(const Point3DF& p0, const Point3DF& p1, bool normalize = false);
    /// \ru Конструктор копирования (BoxF). \en Copy constructor (BoxF). \~
    BoundingBox(const BoxF& box);
    /// \ru Деструктор. \en Destructor. \~
    ~BoundingBox();
public:
    /**
      \brief \ru Проверка на пустоту. \en The check for emptiness.\~
      \details \ru Габаритный параллелепипед считается пустым, если он не содержит ни одной точки 3D-пространства.
               \en A bounding box is empty if it doesn't contain any points of 3D-space \~
    */
    bool IsEmpty() const;
    /// \ru Установить пустым ("вывернутым"). \en Set empty ("reverted"). 
    void SetEmpty();
    /// \ru Инициализировать по координатам. \en Initialize by coordinates. \~
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
    /// \ru Дать минимальные координаты. \en Give the minimal coordinates. \~
    inline Point3DF GetMin() const { return m_box.GetMin(); }
    /// \ru Дать максимальные координаты. \en Give the maximal coordinates. \~
    inline Point3DF GetMax() const { return m_box.GetMax(); }
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
    /// \ru Нормализовать себя. \en Normalize itself. \~
    void Normalize();
    /// \ru Включить в себя точку, заданную как XYZ. \en Enclose a point specified as XYZ. \~
    /**
      \param[in] x, y, z - \ru Координаты точки, которую требуется включить в габарит.
                           \en Coordinates of a point which has to be included in the box. \~
    */
    void Include(float x, float y, float z);
    /// \ru Включить в себя точку. \en Enclose a point.\~
    void Include(const Point3DF&);
        /// \ru Включить в себя куб. \en Enclose a box.\~
    void Include(const BoundingBox&);
    /// \ru Куб объединения двух кубов. \en A box of union of two boxes. \~
    /**
      \param[in] cube1, cube2 - \ru Исходные кубы.
                                \en Input boxes. \~
      \return \ru false, если итоговый куб пуст, \n true в противном случае.
              \en Returns false if the result box is empty, \n true otherwise. \~
    */
    bool Union(const BoundingBox& cube1, const BoundingBox& cube2);
    /// \ru Дать размер стороны X куба. \en Give the size of the X side of a box. \~
    float GetLengthX() const;
    /// \ru Дать размер стороны Y куба. \en Give the size of the Y side of a box. \~
    float GetLengthY() const;
    /// \ru Дать размер стороны Z куба. \en Give the size of the Z side of a box. \~
    float GetLengthZ() const;
    /// \ru Дать размер диагонали куба. \en Give the size of box diagonal. \~
    float GetDiagonal() const;
    /// \ru Выдать вершину куба по индексу. \en Get a box vertex by an index. \~
    /**
      \param[in] index - \ru Исходный индекс. 0 <= index <= 7.
                         \en An initial index. 0 <= index <= 7. \~
      \param[out] p - \ru Искомая вершина.
                      \en Required vertex. \~
    */
    void GetVertex(size_t index, Point3DF& p) const;
    /// \ru Выдать центр куба. \en Give the box center.\~
    Point3DF GetCenter() const;
public:
    /// \ru Расширить куб во все стороны на величину delta. \en Expand the box in all directions on a "delta" amount. \~
    void Enlarge(float delta);
    /// \ru Расширить куб во все стороны на соответствующую величину. \en Expand the box in all directions on a corresponding amount. \~
    void Enlarge(float dx, float dy, float dz);
    /// \ru Сдвинуть вдоль вектора. \en Translate along a vector. \~
    void Move(const Vector3DF& to);
    /// \ru Преобразовать согласно матрице. \en Transform according to the matrix. \~
    void Transform(const Matrix3DF& matrix);
    /// \ru Масштабировать. \en Scale. \~
    void Scale(float sx, float sy, float sz);
    /// \ru Являются ли объекты равными? \en Determine whether an object is equal? \~
    bool IsSame(const BoundingBox& other) const;
public:
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
    bool Intersect(const MbCartPoint3D&, const MbVector3D&, float eps) const;

    /// \ru Пересекается ли габаритный параллелепипед с другим параллелепипедом. \en Whether the box intersects another box or not. 
    /**
      \param[in] other - \ru Другой параллелепипед.
                         \en Another box. \~
      \param[in] eps - \ru Метрическая точность.
                       \en A metric tolerance. \~
      \return \ru true, если пересекается.
              \en Returns true if it intersects. \~
    */
    bool Intersect(const BoundingBox& other, float eps = (FLT_MIN_RADIUS + FLT_MIN_RADIUS)) const;
    //
    const BoxF& GetModelBox() const; 
public:
    /// \ru Присвоить значение. \en Assign a value. \~
    void operator  = (const BoundingBox&);
    /// \ru Включить в себя точку. \en Enclose a point. \~
    BoundingBox& operator |= (const Point3DF&);
    /// \ru Включить в себя габаритный куб. \en Enclose a bounding box. \~
    BoundingBox& operator |= (const BoundingBox&);
    /// \ru Оператор равенства. \en The equality operator. \~
    bool operator == (const BoundingBox&) const;
    /// \ru Оператор неравенства. \en The inequality operator. \~
    bool operator != (const BoundingBox&) const;

    operator MbCube() const;
public:
    BoxF m_box;
};

} // namespace VSN

#endif /* __VSN_BOUNDINGBOX_H */
