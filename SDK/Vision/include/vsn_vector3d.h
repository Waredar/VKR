////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Вектор в трехмерном пространстве.
         \en Vector in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_VECTOR3D_H
#define __VSN_VECTOR3D_H

#include <vsn_mathdefs.h>
#include <vsn_global.h>

class MbVector3D;

namespace VSN {

class Matrix3DF;
class Point3DF;

//------------------------------------------------------------------------------
/** \brief \ru Вектор в трехмерном пространстве.
           \en Vector in three-dimensional space. \~
  \details \ru Вектор описывает перемещение или направление в трёхмерном пространстве
               и определяется тремя компонентами x, y, z в декартовой системе координат.  \n
               Вектор не привязан к точкам пространства и поэтому не имеет метода,
               перемещающего его в пространстве. \n
           \en Vector describes translation or direction in three-dimensional space
               and is defined by three coordinates x, y, z in the Cartesian coordinate system.  \n
               Vector is not binded to space points and therefore has not method
               for translating it in space. \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS Vector3DF
{
public:
    /// \ru Конструктор без параметров, вектор нулевой. \en Constructor without parameters, vector is zero. \~
    Vector3DF() {};
    /// \ru Конструктор по координатам. \en The constructor by coordinates. \~
    Vector3DF(float x, float y, float z);
    /// \ru Конструктор по углам. \en The constructor by angles. \~
    Vector3DF(float a, float b);
    /// \ru Конструктор по точке. \en The constructor by point. \~
    Vector3DF(const Point3DF& p);
    /// \ru Конструктор по двум точкам. \en Constructor by two points. \~
    Vector3DF(const Point3DF& p1, const Point3DF& p2, bool normalize = false);
    /// \ru Конструктор копирования. \en Copy constructor. \~
    Vector3DF(const Vector3DF&) = default;
    /// \ru Конструктор перемещения. \en Move constructor. \~
    Vector3DF(Vector3DF&&) = default;
    /// \ru . \en . 
    Vector3DF(const MbVector3D& mathVec);
    /// \ru деструктор. \en D. \~
    ~Vector3DF() = default;
public:
    void Init(float x, float y, float z);
    void Init(const Point3DF& p1, const Point3DF& p2, bool normalize);
    /// \ru Нормализовать. \en Normalize. \~
    Vector3DF& Normalize();
    /// \ru Нормализовать и вернуть новый вектор. \en NO TRANSLATION. \~
    Vector3DF Normalized() const;
    /// \ru Преобразовать согласно матрице. Матрица действует на вектор справа. \en Transform according to the matrix. A matrix acts on a vector from the right. \~
    Vector3DF& Transform(const Matrix3DF& m);
    /// \ru Прибавить к вектору вектор v1, умноженный на t1. \en Add vector v1 multiplied by t1 to a vector \~
    Vector3DF& Add(const Vector3DF& v1, float t1);
    /// \ru Прибавить к вектору сумму векторов v1 и v2, умноженных на t1 и t2 соответственно. \en Add sum of vectors v1 and v2 multiplied with t1 and t2 correspondingly to a vector. \~
    Vector3DF& Add(const Vector3DF& v1, float t1, const Vector3DF& v2, float t2);
    /// \ru Сдвинуть вдоль вектора. \en Translate along a vector. \~ 
    Vector3DF& Move(float dx, float dy, float dz) { x += dx; y += dy; z += dz; return *this; }
    /// \ru Повернуть вокруг оси на заданный угол. \en Rotate at given angle around axis. \~ 
    Vector3DF& Rotate(const Vector3DF& axis, float angle);
    /// \ru Повернуть вокруг оси. \en Rotate around an axis. \~
    Vector3DF& Rotate(const Point3DF& axisP1, const Point3DF& axisP2, float angle);
    /// \ru Является ли вектор нулевым? \en Check if  vector is zero. 
    bool IsZero(float eps = FLT_EPSILON) const;
    /// \ru Обнулить координаты. \en Set coordinates to zero. \~
    Vector3DF& SetZero() { x = y = z = 0; return *this; }
    /// \ru Сменить направление вектора на противоположное. \en Change vector direction to opposite. 
    Vector3DF& Invert();

    /// \ru Проверить вектор на вырожденность. \en Check vector for degeneracy. \~
    bool IsDegenerate() const;
    /// \ru Проверить коллинеарность векторов с заданной точностью (по синусу угла между векторами). \en Check if vectors are colinear with given tolerance (by sine of angle between vectors). 
    bool IsColinear(const Vector3DF& with) const;
    /// \ru Проверить ортогональность векторов с заданной точностью. \en Check if vectors are orthogonal with given tolerance. 
    bool IsOrthogonal(const Vector3DF& with) const;
    /// \ru Рассчитать длину вектора. \en Calculate vector length. \~ 
    float Length() const;
    /// \ru Рассчитать квадрат длины вектора. \en Calculate vector length square. \~
    float Length2() const;
    /// \ru Рассчитать угол между векторами. \en Calculate angle between vectors. \~
    float Angle(const Vector3DF& with) const;

    /// \ru Являются ли объекты равными? \en Are the objects equal? \~
    bool IsSame(const Vector3DF& other) const;
    bool IsSame(const Vector3DF& other, float eps) const;

    /// \ru Смешать значение вектора со значением другого вектора. \en NO_TRANSLATE \~
    Vector3DF Mix(const Vector3DF& v, float t) const;
public:
    /// \ru Сложить векторы. \en Sum up two vectors. \~
    Vector3DF& operator += (const Vector3DF&);
    /// \ru Вычесть из вектора точку. \en Subtract point from vector. \~
    Vector3DF& operator -= (const Vector3DF&);
    /// \ru Умножить вектор на число. \en Multiply vector by number. \~
    Vector3DF& operator *= (float);
    /// \ru Разделить вектор на число. \en Divide vector by number. \~
    Vector3DF& operator /= (float);
    /// \ru Унарный минус. \en Unary minus. 
    Vector3DF operator - () const;
    /// \ru Сложить векторы. \en Sum up two vectors.
    Vector3DF operator + (const Vector3DF&) const;
    /// \ru Найти разность векторов. \en Find the difference of vectors. 
    Vector3DF operator - (const Vector3DF&) const;
    /// \ru Проверить на равенство. \en Check for equality. 
    bool operator == (const Vector3DF&) const;
    /// \ru Доступ к одному элементу. \en access a single element, non-const. 
    float& operator[](unsigned int i);
    /// \ru Вычислить скалярное произведение двух векторов. \en Calculate dot product of two vectors. \~
    float operator * (const Vector3DF&) const;
    /// \ru Вычислить векторное произведение двух векторов. \en Calculate vector product of two vectors. \~
    Vector3DF operator | (const Vector3DF&) const;
    /// \ru Вычислить вектор как копию данного вектора, преобразованную матрицей. \en Calculate the vector as this copy transformed by the matrix. \~
    Vector3DF operator * (const Matrix3DF&) const;
    /// \ru Сравнение. \en Comparison. \~
    bool operator < (const Vector3DF& other) const;
    // ---
    Vector3DF& operator = (const Vector3DF&) = default;
    operator MbVector3D()const;
public:
    static const Vector3DF xAxis;  ///< \ru Вектор "X" стандартного базиса. \en "X" vector of standard basis. 
    static const Vector3DF yAxis;  ///< \ru Вектор "Y" стандартного базиса. \en "Y" vector of standard basis. 
    static const Vector3DF zAxis;  ///< \ru Вектор "Z" стандартного базиса. \en "Z" vector of standard basis.
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

//------------------------------------------------------------------------------
// \ru Проверить, является ли вектор нулевым. \en Check if  vector is zero. 
// ---
inline bool Vector3DF::IsZero(float eps) const 
{
    return (::fabs(x) < eps && ::fabs(y) < eps && ::fabs(z) < eps);
}

//------------------------------------------------------------------------------
/// \ru Умножить вектор на число. \en Multiply vector by number. 
// ---
inline Vector3DF operator * (const Vector3DF& vector, float factor)
{ return Vector3DF(vector.x * factor, vector.y * factor, vector.z * factor); }

inline Vector3DF operator * (float factor, const Vector3DF& vector)
{ return Vector3DF(vector.x * factor, vector.y * factor, vector.z * factor); }

//------------------------------------------------------------------------------
/// \ru Умножить вектор на матрицу. \en Multiply vector by matrix. 
// ---
inline Vector3DF operator * (const Vector3DF& vector, const Matrix3DF& m)
{ return Vector3DF(vector).Transform(m); }

} // namespace VSN

#endif /*__VSN_VECTOR3D_H*/
