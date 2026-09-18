///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс PointI и PointF определяет точку на плоскости и использует целочисленную точность.
         \en PointI and PointF class defines point on the plane using integer precision. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_POINT_H
#define __VSN_POINT_H

#include <mb_cart_point.h>
#include <vsn_mathdefs.h>
#include <vsn_global.h>

namespace VSN {

static inline bool IsEqual(float a, float b) { return std::abs(a - b) < std::numeric_limits<float>::epsilon(); }

//----------------------------------------------------------------------------
//
/** \brief \ru Класс PointI определяет точку на плоскости и использует целочисленную точность.
           \en PointI class defines point on the plane using integer precision. \~
    \details \ru Точка задается координатами х и у, которые можно получить с помощью функций GetX() и GetY(). 
                 Функция IsNull() возвращает истину, если обе координаты х и у равны 0. Координаты могут быть установлены или изменены 
                 с помощью функций SetX() и SetY() или в качестве альтернативы функциями InitX() и InitY(), которые возвращают ссылки на координаты. \n
             \en PointI is defined with X- and Y-coordinates that can be returned with GetX() and GetY() functions.
                 IsNull() function returns True, if both X- and Y-coordinates are 0. The coordinates can be set or changed
                 with SetX() and SetY() functions, or alternatively InitX() and InitY() functions that return coordinate references. \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS PointI
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    PointI();
    /// \ru Специальный конструктор для инициализации координат x и y. \en Special constructor for initialization X- and Y-coordinates. \~
    PointI(int x, int y);
public:
    /// \ru Вернуть true, если обе координаты х и у равны 0, в противном случае возвращает false. \en True if both X- and Y-coordinates are 0. \~
    inline bool IsNull() const;

    /// \ru Вернуть координату х. \en Returns X-coordinate. \~
    inline int GetX() const;
    /// \ru Установить координату х. \en Sets X-coordinate. \~
    inline void SetX(int x);

    /// \ru Вернуть координату y. \en Returns Y-coordinate. \~
    inline int GetY() const;
    /// \ru Установить координату y. \en Sets Y-coordinate. \~
    inline void SetY(int y);

    /// \ru Инициализация координаты х. \en Initializes X-coordinate. \~
    inline int& InitX();
    /// \ru Инициализация координаты y. \en Initializes Y-coordinate. \~
    inline int& InitY();
    /// \ru Вернуть сумму абсолютных значений x и y. Это вектора от начала координат до точки. \en NO TRANSLATION. \~
    inline int GetVectorLength() const;
    /// \ru Вернуть сумму абсолютных значений x() и y() - "Манхэттен длина". \en Returns the sum of the absolute values of x() and y() - "Manhattan length".
    inline int GetManhattanDistance() const;

    /// \ru Добавить указанную точку в эту точку и вернуть ссылку на эту точку. \en Adds the specified point to the given point and returns point reference. \~
    PointI& operator += (const PointI& p);
    /// \ru Вычесть указанную точку из этой точки и вернуть ссылку на эту точку. \en Subtracts the specified point from the given point and returns point reference. \~
    PointI& operator -= (const PointI& p);

    inline PointI& operator*=(float factor);
    inline PointI& operator*=(double factor);
    inline PointI& operator*=(int factor);

    /// \ru Вернуть true, если указанная точка и эта точка равны, в противном случае возвращает false. \en True if the specified point and the given point are equal. \~
    bool operator == (const PointI& p);
    /// \ru Вернуть true если указанная точка и эта точка не равны, в противном случае возвращает false. \en True if the specified point and the given point are not equal. \~
    bool operator != (const PointI& p);
    const PointI operator + (const PointI& p);
    const PointI operator - (const PointI& p);
private:
    int m_xPnt; ///< \ru Координата x точки. \en PointI X-coordinate. \~ 
    int m_yPnt; ///< \ru Координата y точки. \en PointI Y-coordinate. \~ 
};

inline PointI::PointI() : m_xPnt(0), m_yPnt(0) {}
inline PointI::PointI(int x, int y) : m_xPnt(x), m_yPnt(y) {}

inline bool PointI::IsNull() const { return m_xPnt == 0 && m_yPnt == 0; }

inline int PointI::GetX() const { return m_xPnt; }
inline void PointI::SetX(int x) { m_xPnt = x; }

inline int PointI::GetY() const { return m_yPnt; }
inline void PointI::SetY(int y) { m_yPnt = y; }

inline int& PointI::InitX() { return m_xPnt; }
inline int& PointI::InitY() { return m_yPnt; }

inline int PointI::GetVectorLength() const
{ return std::abs(m_xPnt) + std::abs(m_yPnt); }

inline int PointI::GetManhattanDistance() const
{ return std::abs(GetX()) + std::abs(GetY()); }

inline PointI& PointI::operator += (const PointI& p) { m_xPnt += p.m_xPnt; m_yPnt += p.m_yPnt; return *this; }
inline PointI &PointI::operator -= (const PointI& p) { m_xPnt -= p.m_xPnt; m_yPnt -= p.m_yPnt; return *this; }

inline PointI& PointI::operator*=(float factor)
{
    m_xPnt = static_cast<int>(round(m_xPnt * factor));
    m_yPnt = static_cast<int>(round(m_yPnt * factor));
    return *this;
}

inline PointI& PointI::operator*=(double factor)
{
    m_xPnt = static_cast<int>(round(m_xPnt * factor));
    m_yPnt = static_cast<int>(round(m_yPnt * factor));
    return *this;
}

inline PointI& PointI::operator*=(int factor)
{
    m_xPnt = m_xPnt * factor;
    m_yPnt = m_yPnt * factor;
    return *this;
}

inline bool PointI::operator == ( const PointI& p ) { return m_xPnt == p.m_xPnt && m_yPnt == p.m_yPnt; }
inline bool PointI::operator != (const PointI& p) { return m_xPnt != p.m_xPnt || m_yPnt != p.m_yPnt; }
inline const PointI PointI::operator + (const PointI& p) { return PointI(m_xPnt + p.m_xPnt, m_yPnt + p.m_yPnt); }
inline const PointI PointI::operator - (const PointI& p) { return PointI(m_xPnt - p.m_xPnt, m_yPnt - p.m_yPnt); }


//----------------------------------------------------------------------------
//
/** \brief \ru Класс PointF определяет точку на плоскости и использует двойноую точность.
           \en PointI class defines point on the plane using float-precision. \~
    \details \ru Точка задается координатами х и у, которые можно получить с помощью функций GetX() и GetY().
                 Функция IsNull() возвращает истину, если обе координаты х и у равны 0. Координаты могут быть установлены или изменены
                 с помощью функций SetX() и SetY() или в качестве альтернативы функциями InitX() и InitY(), которые возвращают ссылки на координаты. \n
             \en PointF is defined with X- and Y-coordinates that can be returned with GetX() and GetY() functions.
                 IsNull() function returns True, if both X- and Y-coordinates are 0. The coordinates can be set or changed
                 with SetX() and SetY() functions, or alternatively InitX() and InitY() functions that return coordinate references. \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS PointF
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    PointF();
    /// \ru Специальный конструктор для инициализации координат x и y. \en Special constructor for initialization X- and Y-coordinates.
    PointF(const PointI& other);
    /// \ru Специальный конструктор для инициализации координат x и y. \en Special constructor for initialization X- and Y-coordinates.
    PointF(float x, float y);
    /// \ru Специальный конструктор для инициализации координат x и y. \en Special constructor for initialization X- and Y-coordinates.
    PointF(const MbCartPoint& pnt);
public:
    /// \ru Вернуть true, если обе координаты х и у равны 0, в противном случае возвращает false. \en True if both X- and Y-coordinates are 0.
    inline bool IsNull() const;
    /// \ru Вернуть координату х. \en Returns X-coordinate.
    inline float GetX() const;
    /// \ru Установить координату х. \en Sets X-coordinate.
    inline void SetX(float x);
    /// \ru Вернуть координату y. \en Returns Y-coordinate.
    inline float GetY() const;
    /// \ru Установить координату y. \en Sets Y-coordinate.
    inline void SetY(float y);
    /// \ru Инициализация координаты х, y. \en Initializes X-coordinate, Y-coordinate.
    inline void Init(float x, float y);
    /// \ru Инициализация координаты х. \en Initializes X-coordinate.
    inline float& InitX();
    /// \ru Инициализация координаты y. \en Initializes Y-coordinate.
    inline float& InitY();
    inline PointI ToPoint() const;
    /// \ru Вернуть сумму абсолютных значений x() и y() - "Манхэттен длина". \en Returns the sum of the absolute values of x() and y() - "Manhattan length".
    inline float GetManhattanDistance() const;

    inline PointF& operator+=(const PointF&);
    inline PointF& operator-=(const PointF&);
    inline PointF& operator*=(float c);
    inline PointF& operator/=(float c);

    friend inline bool operator==(const PointF&, const PointF&);
    friend inline bool operator!=(const PointF&, const PointF&);

    friend inline const PointF operator+(const PointF&, const PointF&);
    friend inline const PointF operator-(const PointF&, const PointF&);
    friend inline const PointF operator+(const PointF&);
    friend inline const PointF operator-(const PointF&);
    friend inline const PointF operator/(const PointF&, float);
    friend inline const PointF operator*(float, const PointF&);
    friend inline const PointF operator*(const PointF&, float);

    operator MbCartPoint() const { return MbCartPoint(static_cast<double>(m_xPnt), static_cast<double>(m_yPnt)); }
private:
    float m_xPnt; ///< \ru Координата x точки. \en PointF X-coordinate.
    float m_yPnt; ///< \ru Координата y точки. \en PointF Y-coordinate.
};

inline PointF::PointF() : m_xPnt(0), m_yPnt(0) { }
inline PointF::PointF(float x, float y) : m_xPnt(x), m_yPnt(y) { }
inline PointF::PointF(const PointI& other) : m_xPnt(static_cast<float>(other.GetX())), m_yPnt(static_cast<float>(other.GetY())) {}
inline PointF::PointF(const MbCartPoint& pnt) : m_xPnt(static_cast<float>(pnt.x)), m_yPnt(static_cast<float>(pnt.y)) {}

inline bool PointF::IsNull() const { return IsEqual(m_xPnt, 0.0) && IsEqual(m_yPnt, 0.0); }

inline float PointF::GetX() const { return m_xPnt;}
inline void PointF::SetX(float xpos) { m_xPnt = xpos; }

inline float PointF::GetY() const { return m_yPnt;}
inline void PointF::SetY(float ypos) { m_yPnt = ypos; }

inline void PointF::Init(float x, float y) { m_xPnt = x; m_yPnt = y;  }
inline float& PointF::InitX() { return m_xPnt; }
inline float& PointF::InitY() { return m_yPnt; }

inline PointI PointF::ToPoint() const { return PointI(vRound(m_xPnt), vRound(m_yPnt)); }

inline float PointF::GetManhattanDistance() const { return std::fabs(m_xPnt) + std::fabs(m_yPnt); }

inline PointF& PointF::operator+=(const PointF& other) { m_xPnt += other.m_xPnt; m_yPnt += other.m_yPnt; return *this; }
inline PointF& PointF::operator-=(const PointF& other) { m_xPnt -= other.m_xPnt; m_yPnt -= other.m_yPnt; return *this; }
inline PointF& PointF::operator*=(float cof) { m_xPnt *= cof; m_yPnt *= cof; return *this; }

inline bool operator==(const PointF& pnt1, const PointF& pnt2) { return IsEqual(pnt1.m_xPnt - pnt2.m_xPnt, 0.0) && IsEqual(pnt1.m_yPnt - pnt2.m_yPnt, 0.0); }
inline bool operator!=(const PointF& pnt1, const PointF& pnt2) { return !IsEqual(pnt1.m_xPnt - pnt2.m_xPnt, 0.0) || !IsEqual(pnt1.m_yPnt - pnt2.m_yPnt, 0.0);}

inline const PointF operator+(const PointF& pnt1, const PointF& pnt2) { return PointF(pnt1.m_xPnt + pnt2.m_xPnt, pnt1.m_yPnt + pnt2.m_yPnt);}
inline const PointF operator-(const PointF& pnt1, const PointF& pnt2) { return PointF(pnt1.m_xPnt - pnt2.m_xPnt, pnt1.m_yPnt - pnt2.m_yPnt); }
inline const PointF operator*(const PointF& other, float cof) { return PointF(other.m_xPnt*cof, other.m_yPnt*cof); }
inline const PointF operator*(float cof, const PointF& other) { return PointF(other.m_xPnt*cof, other.m_yPnt*cof); }
inline const PointF operator+(const PointF& other) { return other; }
inline const PointF operator-(const PointF& other) { return PointF(-other.m_xPnt, -other.m_yPnt); }
inline PointF &PointF::operator/=(float divisor) { m_xPnt /= divisor; m_yPnt /= divisor; return *this; }
inline const PointF operator/(const PointF& other, float divisor) { return PointF(other.m_xPnt / divisor, other.m_yPnt / divisor); }

} // namespace VSN

#endif /*__VSN_POINT_H*/
