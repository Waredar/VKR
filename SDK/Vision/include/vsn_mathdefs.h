#ifndef __VSN_MATHDEFS_H
#define __VSN_MATHDEFS_H

#include <cstdlib>
#include <cmath>
#include <climits>
#include <utility>

#include <vsn_global.h>

namespace VSN {

} // namespace VSN

template <typename T>
inline T vAbs(const T &t) { return t >= 0 ? t : -t; }
template <typename T>
inline const T& vMin(const T& a, const T& b) { return (a < b) ? a : b; }
template <typename T>
inline const T& vMax(const T& a, const T& b) { return (a < b) ? b : a; }

inline int vRound(double d)   { return d >= 0.0 ? int(d + 0.5)     : int(d - double(int(d - 1)) + 0.5) + int(d - 1); }
inline int vRound(float d)    { return d >= 0.0f ? int(d + 0.5f)   : int(d - float(int(d - 1)) + 0.5f) + int(d - 1); }
inline int64 vRound64(double d) { return d >= 0.0 ? int64(d + 0.5)   : int64(d - double(int64(d - 1)) + 0.5) + int64(d - 1); }
inline int64 vRound64(float d)  { return d >= 0.0f ? int64(d + 0.5f) : int64(d - float(int64(d - 1)) + 0.5f) + int64(d - 1); }

template<class T>
static inline bool IsEqual(T a, T b) { return std::fabs(a - b) <= std::numeric_limits<T>::epsilon() * std::fabs(a + b); }
template<class T>
static inline bool IsLess(T a, T b) { return IsEqual(a, b) ? false : a < b; }
template<class T>
static inline bool IsMore(T a, T b) { return IsEqual(a, b) ? false : a > b; }


/**
    \brief \ru Сравнивает значения с плавающей запятой p1 и p2 и возвращает true, 
               если они считаются равными, иначе false.
           \en NO TRANSLATION. \~
*/
inline bool IsSame(double p1, double p2)
{ return (vAbs(p1 - p2) * 1000000000000. <= vMin(vAbs(p1), vAbs(p2))); }

/**
    \brief \ru Сравнивает значения с плавающей запятой p1 и p2 и возвращает true, 
               если они считаются равными, иначе false.
           \en NO TRANSLATION. \~
*/
inline bool IsSame(float p1, float p2)
{ return (vAbs(p1 - p2) * 100000.f <= vMin(vAbs(p1), vAbs(p2))); }

/**
    \brief \ru Возвращает true, если абсолютное значение d находится в пределах 
               от std::numeric_limits<double>::epsilon() до 0,0.
           \en NO TRANSLATION. \~
*/
inline bool IsEqualNull(double d)
{ return vAbs(d) <= std::numeric_limits<double>::epsilon(); }

/**
    \brief \ru Возвращает true, если абсолютное значение d находится в пределах
               от std::numeric_limits<float>::epsilon() до 0,0.
           \en NO TRANSLATION. \~
*/
inline bool IsEqualNull(float d)
{ return vAbs(d) <= std::numeric_limits<float>::epsilon(); }

/**
    \brief \ru Эта функция преобразует градусы из числа с плавающей запятой в радианы.
           \en NO TRANSLATION. \~
*/
inline float ConvertDegToRad(float degrees)
{ return degrees * float(M_PI / 180.f); }

/**
    \brief \ru Эта функция преобразует градусы из числа двойной точности в радианы.
           \en NO TRANSLATION. \~
*/
inline double ConvertDegToRad(double degrees)
{ return degrees * (M_PI / 180.0); }


/**
    \brief \ru Эта функция преобразует радианы в градусы.
           \en NO TRANSLATION. \~
*/
inline float ConvertRadToDeg(float radians)
{ return radians * float(180.f / M_PI); }

/**
    \brief \ru Эта функция преобразует радианы в градусы.
           \en NO TRANSLATION. \~
*/
inline double ConvertRadToDeg(double radians)
{ return radians * (180.0 / M_PI); }

#endif /* __VSN_MATHDEFS_H */
