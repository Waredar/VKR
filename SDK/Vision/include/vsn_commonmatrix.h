////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс CommonMatrix — это класс-шаблон, представляющий матрицу 
             преобразования CxR с C столбцами и R строками.
         \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COMMONMATRIX_H
#define __VSN_COMMONMATRIX_H

#include <vsn_mathdefs.h>
#include <vsn_global.h>

namespace VSN {

//------------------------------------------------------------------------------
/** \brief  \ru NO TRANSLATION.
            \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION.
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Interaction
*/
// ---
template <int C, int R, typename T>
class CommonMatrix
{
public:
    CommonMatrix();
    explicit CommonMatrix(const T* values);
public:
    void Init(T value);
    bool IsIdentity() const;
    void SetToIdentity();
    CommonMatrix<R, C, T> Transposed() const;
    void CopyDataTo(T* values) const;
    T* GetData() { return *m; }
    const T* GetData() const { return *m; }
    const T* GetConstData() const { return *m; }
public:
    const T& operator()(int row, int column) const;
    T& operator()(int row, int column);

    CommonMatrix<C, R, T>& operator+=(const CommonMatrix<C, R, T>& other);
    CommonMatrix<C, R, T>& operator-=(const CommonMatrix<C, R, T>& other);
    CommonMatrix<C, R, T>& operator*=(T factor);
    CommonMatrix<C, R, T>& operator/=(T divisor);
    bool operator==(const CommonMatrix<C, R, T>& other) const;
    bool operator!=(const CommonMatrix<C, R, T>& other) const;

    template<int CC, int RR, typename TT>
    friend CommonMatrix<CC, RR, TT> operator+(const CommonMatrix<CC, RR, TT>& m1, const CommonMatrix<CC, RR, TT>& m2);
    template<int CC, int RR, typename TT>
    friend CommonMatrix<CC, RR, TT> operator-(const CommonMatrix<CC, RR, TT>& m1, const CommonMatrix<CC, RR, TT>& m2);
    template<int CC, int M1, int M2, typename TT>
    friend CommonMatrix<M1, M2, TT> operator*(const CommonMatrix<CC, M2, TT>& m1, const CommonMatrix<M1, CC, TT>& m2);
    template<int CC, int RR, typename TT>
    friend CommonMatrix<CC, RR, TT> operator-(const CommonMatrix<CC, RR, TT>& matrix);
    template<int CC, int RR, typename TT>
    friend CommonMatrix<CC, RR, TT> operator*(TT factor, const CommonMatrix<CC, RR, TT>& matrix);
    template<int CC, int RR, typename TT>
    friend CommonMatrix<CC, RR, TT> operator*(const CommonMatrix<CC, RR, TT>& matrix, TT factor);
    template<int CC, int RR, typename TT>
    friend CommonMatrix<CC, RR, TT> operator/(const CommonMatrix<CC, RR, TT>& matrix, TT divisor);
private:
    T m[C][R];  ///< \ru Порядок столбцов в соответствии с OpenGL. \en NO TRANSLATION.
};

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T>::CommonMatrix()
{
    SetToIdentity();
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T>::CommonMatrix(const T* values)
{
    for (int col = 0; col < C; ++col)
        for (int row = 0; row < R; ++row)
            m[col][row] = values[row * C + col];
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline void CommonMatrix<C, R, T>::Init(T value)
{
    for (int col = 0; col < C; ++col)
        for (int row = 0; row < R; ++row)
            m[col][row] = value;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline bool CommonMatrix<C, R, T>::IsIdentity() const
{
    for (int col = 0; col < C; ++col) 
    {
        for (int row = 0; row < R; ++row) 
        {
            if (row == col) 
            {
                if (m[col][row] != 1.0f)
                    return false;
            }
            else 
            {
                if (m[col][row] != 0.0f)
                    return false;
            }
        }
    }
    return true;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline void CommonMatrix<C, R, T>::SetToIdentity()
{
    for (int col = 0; col < C; ++col) 
    {
        for (int row = 0; row < R; ++row) 
        {
            if (row == col)
                m[col][row] = 1.0f;
            else
                m[col][row] = 0.0f;
        }
    }
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<R, C, T> CommonMatrix<C, R, T>::Transposed() const
{
    CommonMatrix<R, C, T> result;
    for (int row = 0; row < R; ++row)
    {
        for (int col = 0; col < C; ++col)
            result.m[row][col] = m[col][row];
    }
    return result;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline void CommonMatrix<C, R, T>::CopyDataTo(T* values) const
{
    for (int col = 0; col < C; ++col)
    {
        for (int row = 0; row < R; ++row)
            values[row * C + col] = T(m[col][row]);
    }
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline const T& CommonMatrix<C, R, T>::operator()(int row, int column) const
{
    VSN_ASSERT(row >= 0 && row < R && column >= 0 && column < C);
    return m[column][row];
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline T& CommonMatrix<C, R, T>::operator()(int row, int column)
{
    VSN_ASSERT(row >= 0 && row < R && column >= 0 && column < C);
    return m[column][row];
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T>& CommonMatrix<C, R, T>::operator+=(const CommonMatrix<C, R, T>& other)
{
    for (int row = 0; row < R; ++row)
    {
        for (int col = 0; col < C; ++col)
            m[col][row] += other.m[col][row];
    }
    return *this;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T>& CommonMatrix<C, R, T>::operator-=(const CommonMatrix<C, R, T>& other)
{
    for (int row = 0; row < R; ++row)
    {
        for (int col = 0; col < C; ++col)
            m[col][row] -= other.m[col][row];
    }
    return *this;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T>& CommonMatrix<C, R, T>::operator*=(T factor)
{
    for (int row = 0; row < R; ++row)
    {
        for (int col = 0; col < C; ++col)
            m[col][row] *= factor;
    }
    return *this;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline bool CommonMatrix<C, R, T>::operator==(const CommonMatrix<C, R, T>& other) const
{
    for (int row = 0; row < R; ++row)
    {
        for (int col = 0; col < C; ++col) 
        {
            if (m[col][row] != other.m[col][row])
                return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline bool CommonMatrix<C, R, T>::operator!=(const CommonMatrix<C, R, T>& other) const
{
    return !(*this == other);
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T>& CommonMatrix<C, R, T>::operator/=(T divisor)
{
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col)
            m[col][row] /= divisor;
    return *this;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T> operator+(const CommonMatrix<C, R, T>& m1, const CommonMatrix<C, R, T>& m2)
{
    CommonMatrix<C, R, T> result;
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col)
            result.m[col][row] = m1.m[col][row] + m2.m[col][row];
    return result;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T> operator-(const CommonMatrix<C, R, T>& m1, const CommonMatrix<C, R, T>& m2)
{
    CommonMatrix<C, R, T> result;
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col)
            result.m[col][row] = m1.m[col][row] - m2.m[col][row];
    return result;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int M1, int M2, typename T>
inline CommonMatrix<M1, M2, T> operator*(const CommonMatrix<C, M2, T>& m1, 
    const CommonMatrix<M1, C, T>& m2)
{
    CommonMatrix<M1, M2, T> result;
    for (int row = 0; row < M2; ++row) 
    {
        for (int col = 0; col < M1; ++col) 
        {
            T sum(0.0f);
            for (int j = 0; j < C; ++j)
                sum += m1.m[j][row] * m2.m[col][j];
            result.m[col][row] = sum;
        }
    }
    return result;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T> operator-(const CommonMatrix<C, R, T>& matrix)
{
    CommonMatrix<C, R, T> result;
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col)
            result.m[col][row] = -matrix.m[col][row];
    return result;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T> operator*(T factor, const CommonMatrix<C, R, T>& matrix)
{
    CommonMatrix<C, R, T> result;
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col)
            result.m[col][row] = matrix.m[col][row] * factor;
    return result;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T> operator*(const CommonMatrix<C, R, T>& matrix, T factor)
{
    CommonMatrix<C, R, T> result;
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col)
            result.m[col][row] = matrix.m[col][row] * factor;
    return result;
}

//-----------------------------------------------------------------------------
//
// ---
template <int C, int R, typename T>
inline CommonMatrix<C, R, T> operator/(const CommonMatrix<C, R, T>& matrix, T divisor)
{
    CommonMatrix<C, R, T> result;
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col)
            result.m[col][row] = matrix.m[col][row] / divisor;
    return result;
}

// Определение псевдонимов для полезных вариантов CommonMatrix.
typedef CommonMatrix<2, 2, float> Matrix2x2F;
typedef CommonMatrix<2, 3, float> Matrix2x3F;
typedef CommonMatrix<2, 4, float> Matrix2x4F;
typedef CommonMatrix<3, 2, float> Matrix3x2F;
typedef CommonMatrix<3, 3, float> Matrix3x3F;
typedef CommonMatrix<3, 4, float> Matrix3x4F;
typedef CommonMatrix<4, 2, float> Matrix4x2F;
typedef CommonMatrix<4, 3, float> Matrix4x3F;

// ---
inline Matrix3x3F& FromToMatrixF(const Vector3DF& from, const Vector3DF& to, Matrix3x3F& mtx)
{
    VSN_UNUSED(from);
    VSN_UNUSED(to);
/*
    const float e = from * to;
    const float f = (e < 0) ? -e : e;
    if (f > static_cast<float>(1.0) - static_cast<float>(0.00001))
    {
        Vector3DF u, v;
        Vector3DF x;
        x.x = (from.x > 0.0) ? from.x : -from.x;
        x.y = (from.y > 0.0) ? from.y : -from.y;
        x.z = (from.z > 0.0) ? from.z : -from.z;
        if (x.x < x.y)
        {
            if (x.x < x.z)
            {
                x.x = static_cast<float>(1.0);
                x.y = x.z = static_cast<float>(0.0);
            }
            else
            {
                x.z = static_cast<float>(1.0);
                x.x = x.y = static_cast<float>(0.0);
            }
        }
        else
        {
            if (x.y < x.z)
            {
                x.y = static_cast<float>(1.0);
                x.x = x.z = static_cast<float>(0.0);
            }
            else
            {
                x.z = static_cast<float>(1.0);
                x.x = x.y = static_cast<float>(0.0);
            }
        }
        u.x = x.x - from.x; u.y = x.y - from.y; u.z = x.z - from.z;
        v.x = x.x - to.x;   v.y = x.y - to.y;   v.z = x.z - to.z;
        const float c1_ = static_cast<float>(2.0) / (u * u);
        const float c2_ = static_cast<float>(2.0) / (v * v);
        const float c3_ = c1_ * c2_ * (u * v);

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
                mtx[i][j] = -c1_ * u[i] * u[j] - c2_ * v[i] * v[j] + c3_ * v[i] * u[j];
            mtx[i][i] += static_cast<float>(1.0);
        }
    }
    else
    {
        const Vector3DF v = from | to;
        const float h = static_cast<float>(1.0) / (static_cast<float>(1.0) + e);
        const float hvx = h * v.x;
        const float hvz = h * v.z;
        const float hvxy = hvx * v.y;
        const float hvxz = hvx * v.z;
        const float hvyz = hvz * v.y;
        mtx[0][0] = e + hvx * v.x;
        mtx[0][1] = hvxy - v.z;
        mtx[0][2] = hvxz + v.y;

        mtx[1][0] = hvxy + v.z;
        mtx[1][1] = e + h * v.y * v.y;
        mtx[1][2] = hvyz - v.x;

        mtx[2][0] = hvxz - v.y;
        mtx[2][1] = hvyz + v.x;
        mtx[2][2] = e + hvz * v.z;
    }
*/
    return mtx;
}

} // namespace VSN

#endif /*__VSN_COMMONMATRIX_H */