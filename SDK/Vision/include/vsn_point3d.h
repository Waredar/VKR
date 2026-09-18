///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс Point3DF определяет трехмерная точка.
         \en The three-dimensional point. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_POINT3D_H
#define __VSN_POINT3D_H

#include <vsn_global.h>

class MbCartPoint3D;

namespace VSN {

class PointF;
class Matrix3DF;
class Vector3DF;
//------------------------------------------------------------------------------
/** \brief \ru Трехмерная точка.
           \en The three-dimensional point. \~
  \details \ru Трехмерная точка (картезианская точка) описывается тремя координатами в декартовой 
               системе координат. Точку можно описать радиусом-вектором. Радиус-вектор описывает преобразование, 
               переводящее начальную точку декартовой системы координат в точку пространства с заданными 
               координатами в этой декартовой системе координат. \n
           \en The three-dimensional point (cartesian point) is defined by three coordinates in 
               a cartesian coordinate system. A point can be defined by radius-vector. A radius-vector 
               describes transform which translates a start point of a cartesian coordinate system to 
               a space point with the given coordinates in this system. \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS Point3DF
{
public:
    Point3DF() = default;
    Point3DF(float x, float y, float z);
    Point3DF(const Point3DF& pnt) = default;
    Point3DF(Point3DF&& pnt) = default;
    Point3DF(const MbCartPoint3D& pnt);
    ~Point3DF() = default;
public:
    /// \ru Инициализация по двумерной точке. \en The initialization by two-dimensional point. \~
    Point3DF& Init(const PointF& p);
    /// \ru Инициализировать по координатам. \en Initialize by coordinates. \~
    Point3DF& Init(const Point3DF& pnt) { x = pnt.x; y = pnt.y; z = pnt.z; return *this; }
    /// \ru Инициализировать по координатам. \en Initialize by coordinates. \~
    Point3DF& Init(float xx, float yy, float zz) { x = xx; y = yy; z = zz; return *this; }
    /// \ru Преобразовать согласно матрице. \en Transform according to the matrix. \~
    Point3DF& Transform(const Matrix3DF& m);
    /// \ru Сдвинуть вдоль вектора. \en Translate along a vector. \~
    Point3DF& Move(float dx, float dy, float dz) { x += dx; y += dy; z += dz; return *this; }
    /// \ru Повернуть вокруг оси. \en Rotate around an axis. \~
    Point3DF& Rotate(const Point3DF& axisP1, const Point3DF& axisP2, float angle);
    /// \ru Обнулить координаты. \en Set coordinates to zero. \~
    Point3DF& SetZero() { x = y = z = 0; return *this; }
public:
    /// \ru Расстояние до точки. \en The distance to a point. 
    float DistanceToPoint(const Point3DF &) const;
    /// \ru Квадрат расстояния от точки до точки. \en The squared distance between two points. 
    float DistanceToPoint2(const Point3DF & to) const;
    /// \ru Являются ли объекты равными? \en Are the objects equal?
    bool IsEqual(const Point3DF & other) const;
public:
    /// \ru Добавить вектор. \en Add a vector. \~
    void operator += ( const Vector3DF& );
    /// \ru Вычесть вектор. \en Subtract a vector. \~
    void operator -= ( const Vector3DF& );
    /// \ru Добавить координаты точки. \en Add point coordinates. \~
    void operator += ( const Point3DF& );
    /// \ru Вычесть координаты точки. \en Subtract point coordinates. \~
    void operator -= ( const Point3DF& );
    /// \ru Сложить точку и вектор. \en Add a point and vector. 
    Point3DF operator + (const Vector3DF&) const;
    /// \ru Вычесть из точки вектор. \en Subtract a vector from the point. \~
    Point3DF operator - (const Vector3DF&) const;
    /// \ru Сложить две точки. \en Add two points. 
    Point3DF operator + (const Point3DF&) const;
    /// \ru Вычесть из точки точку. \en Subtract a point from the point. \~
    Point3DF operator - (const Point3DF&) const;
    /// \ru Унарный минус. \en The unary minus. \~
    Point3DF operator - () const;

    Point3DF& operator = (const Vector3DF&);
    Point3DF& operator = (const Point3DF&) = default;
    Point3DF& operator = (Point3DF&&) = default;

    inline bool operator == (const Point3DF& p) const {return IsEqual(p);}

    operator MbCartPoint3D() const;
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

//------------------------------------------------------------------------------
/// \ru Умножить точку на матрицу. \en Multiply vector by matrix. 
// ---
inline Point3DF operator * (const Point3DF& p, const Matrix3DF& m)
{ return Point3DF(p).Transform(m); }


} // namespace VSN


#endif /*__VSN_POINT3D_H*/
