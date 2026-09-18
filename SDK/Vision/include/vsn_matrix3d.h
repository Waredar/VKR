////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Расширенная матрица преобразования в трёхмерном пространстве.
           \en The extended matrix of transformation in a three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_MATRIX3D_H
#define __VSN_MATRIX3D_H

#include <vsn_point3d.h>
#include <vsn_vector3d.h>
#include <vsn_commonmatrix.h>
#include <vsn_global.h>

class MbMatrix3D;
namespace VSN {

//------------------------------------------------------------------------------
/** \brief \ru Матрица преобразования в трёхмерном пространстве.
           \en The matrix of transformation in a three-dimensional space. \~
  \details \ru Матрица преобразования в трёхмерном пространстве. \n
               Расширенная матрица имеет размерность (4, 4) и представляет собой обычную матрицу, 
               окаймлённую снизу вектором сдвига а справа нулевым столбцом. 
               Трансформация точки p по матрице M имеет вид: r = p * M (строка координат умножается на матрицу слева).\n
               Матрица преобразования из локальной системы координат может быть получена следующим образом:\n
               первая строка матрицы должна быть заполнена соответствующими компонентами первого вектора локальной системы,
               вторая строка матрицы должна быть заполнена соответствующими компонентами второго вектора локальной системы,
               третья строка матрицы должна быть заполнена соответствующими компонентами третьего вектора локальной системы,
               последняя строка матрицы должна быть заполнена соответствующими координатами положения начала локальной системы.
           \en The extended matrix of transformation in a three-dimensional space. \n
               The extended matrix has dimension (4, 4) and is a regular matrix 
               bordered below by a translation vector and by the null column to the right. 
               The transformation of point "p" by the matrix "M" has the form: r = p * M (the row of coordinates is multiplied by the matrix to the left).\n
               The transformation matrix from a local coordinate system can be obtained as follows:\n
               the first row must be filled with the corresponding components of the first vector of a locale system,
               the second row must be filled with the corresponding components of the second vector of a local system,
               the third row must be filled with the corresponding components of the third vector of a locale system,
               the last row of the matrix must be filled with the corresponding coordinates of a local system origin.
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS Matrix3DF
{
public:
    /// \ru Конструктор по умолчанию, определяет единичную матрицу. \en Default constructor. Defines the identity matrix. \~
    Matrix3DF();
    /// \ru Конструктор c возможностью указать элементы матрицы. \en The constructor with ability to set elements of the matrix. \~
    Matrix3DF(const float* pElements);
    /// \ru Конструктор c возможностью указать элементы матрицы. \en The constructor with ability to set elements of the matrix. \~
    Matrix3DF(float el00, float el01, float el02, float el03,
              float el10, float el11, float el12, float el13,
              float el20, float el21, float el22, float el23,
              float el30, float el31, float el32, float el33);
    /// \ru Конструктор по матрице 3x3, остальные элементы равны единицам.
    //  \en The constructor based on a 3x3 matrix, the remaining elements are equal to ones. \~
    explicit Matrix3DF(const Matrix3x3F& m);
    /// \ru Конструктор копирования. \en The copy constructor. \~
    Matrix3DF(const Matrix3DF&) = default;
    /// \ru Конструктор перемещения. \en The move constructor. \~
    Matrix3DF(Matrix3DF&&) = default;
    /// \ru Конструктор для совместимости с ядром. \en.  \~
    Matrix3DF(const MbMatrix3D& m);
    ~Matrix3DF() = default;
public:
    /// \ru Инициализировать элементами другой матрицы. \en Initialize by elements of another matrix. 
    Matrix3DF& Init(const Matrix3DF&);
    void Init(const Point3DF& origin, const Vector3DF& x, const Vector3DF& z);
    void Init(const Point3DF& origin, const Vector3DF& n);
public:
    /// \ru Присвоить значение элементу матрицы. \en Assign a value to the matrix element. \~
    inline void  SetElement(uint j, uint i, float value);
    /// \ru Получить элемент матрицы. \en Get an element of the matrix. \~
    inline float GetElement(uint j, uint i) const;

    /// \ru Получить первую строку (ось X). \en Get the first row (the X-axis). \~
    Vector3DF GetAxisX() const  { return {elements[0], elements[1],  elements[2]}; };
    /// \ru Получить вторую строку (ось Y). \en Get the second row (the Y-axis). 
    Vector3DF GetAxisY() const  { return {elements[4], elements[5],  elements[6]}; };
    /// \ru Получить третью строку (ось Z). \en Get the third row (the Z-axis). \~
    Vector3DF GetAxisZ() const  { return {elements[8], elements[9],  elements[10]}; };
    /// \ru Установить четвертую строку (начало системы координат). \en Set the fourth row (the origin of coordinates) \~
    void SetOrigin(const Point3DF& origin);
    /// \ru Получить четвертую строку (начало системы координат). \en Give the fourth row (the origin of coordinates) \~
    Point3DF GetOrigin() const { return {elements[12],elements[13], elements[14]}; };

    /// \ru Повернуть вокруг оси. \en Rotate around an axis.\~
    Matrix3DF& Rotate(const Vector3DF& v, double angle);
    /// \ru Повернуть вокруг заданной оси на заданный угол. \en Rotate around axis by angle. 
    Matrix3DF& Rotate(const Point3DF&p, const Vector3DF& dir, double angle);
    /// \ru Сдвинуть на заданный вектор. \en Translate by a given vector. \~
    Matrix3DF& Move(const Vector3DF&);
    /// \ru Масштабировать по X, Y, Z.. \en Scale by X, Y and Z. \~
    Matrix3DF& Scale(float);
    /**
      \brief \ru Масштабировать по X, Y, Z.
             \en Scale by X, Y and Z. \~
      \details \ru Масштабировать по X, Y, Z.
               \en Scale by X, Y and Z. \~
      \param[in] sx, sy, sz - \ru Коэффициенты масштабирования для каждой из осей.
                              \en Scaling coefficients for each axis. \~
    */
    void Scale(float sx, float sy, float sz);
    /// \ru Масштабировать по X. \en Scale by X. 
    void ScaleX(float s);
    /// \ru Масштабировать по Y. \en Scale by Y. 
    void ScaleY(float s);
    /// \ru Масштабировать по Z. \en Scale by Z. 
    void ScaleZ(float s);

    /// \ru Вернуть коэффициент масштабирования по X. \en Get scaling coefficient by X. 
    inline float GetScaleX() const { return Vector3DF(elements[0], elements[1], elements[2]).Length(); }
    /// \ru Вернуть коэффициент масштабирования по Y \en Get scaling coefficient by Y. 
    inline float GetScaleY() const { return Vector3DF(elements[4], elements[5], elements[6]).Length(); }
    /// \ru Вернуть коэффициент масштабирования по Z. \en Get scaling coefficient by Z. 
    inline float GetScaleZ() const { return Vector3DF(elements[8], elements[9], elements[10]).Length(); }

    Matrix3DF& Invert();
    /// \ru Умножить на матрицу. \en Multiply by a matrix.\~
    inline Matrix3DF& Multiply(const Matrix3DF& m);
    // \ru Вычислить обратную матрицу. \en Calculate inverse matrix.\~
    Matrix3DF& Div();
    /// \ru Транспонировать матрицу. \en Transpose a matrix. 
    Matrix3DF& Adj();

    /// \ru Преобразовать согласно заданной матрице. \en Transform according to the given matrix. \~
    Matrix3DF& Transform(const Matrix3DF& matr);
    /// \ru Являются ли объекты равными? \en Determine whether an object is equal?\~
    bool IsEqual(const Matrix3DF&) const;
    /// \ru Получить указатель на элементы. \en Get an elements pointer. \~
    const float* GetPointer() const;
    /// \ru Функция для создания матрицы вращения, которая вращает вектор "from" в другой вектор "to".
    /// \ru A function for creating a rotation matrix that rotates a vector called "from" into another vector called "to".
    static Matrix3DF& FromToMatrix(const Vector3DF& from, const Vector3DF& to, Matrix3DF& mtx);
public:
    /// \ru Присвоить значение. \en Assign a value. \~
    Matrix3DF& operator = (const Matrix3DF&) = default;
    /// \ru Переместить значение. \en Move a value. \~
    Matrix3DF& operator = (Matrix3DF&&) = default;
    /// \ru Умножить на матрицу: M = this * m. \en Multiply by a matrix: M = this * m. \~
    Matrix3DF  operator * (const Matrix3DF& m) const { return Matrix3DF(*this).Multiply(m); }
    /// \ru Умножить на матрицу: this = this * m. \en Multiply by a matrix: this = this * m. \~
    Matrix3DF& operator *= (const Matrix3DF& m) { Multiply(m); return *this; }
    bool operator == (const Matrix3DF& m) const { return IsEqual(m); }
    operator MbMatrix3D() const;
public:
    static Matrix3DF identity;
public:
    float elements[16];
};

//-----------------------------------------------------------------------------
// \ru Инициализировать элементами другой матрицы. \en Initialize by elements of another matrix. 
// ---
inline Matrix3DF& Matrix3DF::Init(const Matrix3DF& init)
{
    ::memcpy(elements, init.elements, sizeof(elements));
    return *this;
}

//-----------------------------------------------------------------------------
//
// ---
inline float Matrix3DF::GetElement(uint row, uint column) const
{ return elements[row * 4 + column]; }

//-----------------------------------------------------------------------------
//
// ---
inline void Matrix3DF::SetElement(uint row, uint column, float value)
{ elements[row * 4 + column] = value; }

//-----------------------------------------------------------------------------
//
// ---
inline Matrix3DF& Matrix3DF::Multiply(const Matrix3DF& B)
{
    Matrix3DF A(*this);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            SetElement(i, j,
                A.GetElement(i, 0) * B.GetElement(0, j) +
                A.GetElement(i, 1) * B.GetElement(1, j) +
                A.GetElement(i, 2) * B.GetElement(2, j) +
                A.GetElement(i, 3) * B.GetElement(3, j));
        }
    }
    return *this;
}

typedef std::shared_ptr<Matrix3DF> Matrix3DFPtr;

} // namespace VSN

#endif /*__VSN_MATRIX3D_H*/