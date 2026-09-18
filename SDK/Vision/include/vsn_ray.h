#ifndef __VSN_RAY_H
#define __VSN_RAY_H

#include <cmath>
#include <vsn_matrix3d.h>
#include <vsn_point3d.h>
#include <vsn_vector3d.h>

namespace VSN {

//------------------------------------------------------------------------------
/// \ru Разделить вектор на число. \en Divide vector by number. 
// ---
inline Vector3DF operator / (const Vector3DF& vector, float factor)
{
    float invFactor = (1.0f / factor);
    return Vector3DF(vector.x * invFactor, vector.y * invFactor, vector.z * invFactor);
}


//------------------------------------------------------------------------------
/** 

*/
// ---
struct Ray3DF final
{
    Point3DF origin;
    Vector3DF dir;

    Ray3DF() = default;
    inline Ray3DF(const Point3DF& origin, const Vector3DF& dir);
    inline void Transform(const Matrix3DF& m);
    inline Point3DF PointOn(float distance) const;
    inline float DistanceToPoint(const Point3DF& to) const;

    inline bool Cross(const Ray3DF& other, Point3DF& p1, Point3DF& p2) const;
    // returns point on other ray
    inline bool Cross(const Ray3DF& other, Point3DF& p) const;

    inline float PointProjection(const Point3DF& p) const;
};

inline Ray3DF::Ray3DF(const Point3DF& origin, const Vector3DF& dir)
: origin(origin), dir(dir)
{
}


inline void Ray3DF::Transform(const Matrix3DF& m)
{
    origin.Transform(m);
    dir.Transform(m);
}


inline Point3DF Ray3DF::PointOn(float distance) const
{
    return {
        origin.x + dir.x * distance,
        origin.y + dir.y * distance,
        origin.z + dir.z * distance,
    };
}

// Растояние от линии луча до точки
inline float Ray3DF::DistanceToPoint(const Point3DF& to) const
{
    Vector3DF r(to, origin);
    return ::fabs((dir | r).Length());
}

inline bool Ray3DF::Cross(const Ray3DF& other, Point3DF& p1, Point3DF& p2) const
{
    Vector3DF cax = dir | other.dir;
    if (cax.Length() > 0.0f)
    {
        Vector3DF diff = origin - other.origin;
        cax.Normalize();
        Vector3DF axd(cax | other.dir);
        axd.Normalize();
        p1 = origin - dir * (axd * diff) / (axd * dir);
        Vector3DF axb(cax | dir);
        axb.Normalize();
        p2 = other.origin + other.dir * (axb * diff) / (axb * other.dir);
        return true;
    }
    return false;
}


// returns pint on crossed ray
inline bool Ray3DF::Cross(const Ray3DF& other, Point3DF& p) const
{
    Vector3DF cax = dir | other.dir;
    if (cax.Length() > 0.0f)
    {
        Vector3DF diff = origin - other.origin;
        cax.Normalize();
        //Vector3DF axd(cax | other.dir);
        //axd.Normalize();
        //p = origin - dir * (axd * diff) / (axd * dir); // point on this
        Vector3DF axb(cax | dir);
        axb.Normalize();
        p = other.origin + other.dir * (axb * diff) / (axb * other.dir);// point on other
        return true;
    }

    return false;
}


inline float Ray3DF::PointProjection(const Point3DF& p) const
{
    Vector3DF d2(origin, p);
    return dir*d2 / (dir.Length()* dir.Length());
}


} // namespace VSN

#endif /*__VSN_RAY_H*/
