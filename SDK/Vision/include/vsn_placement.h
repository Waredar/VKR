#ifndef _VSN_PLACEMENT_H
#define _VSN_PLACEMENT_H

#include <vsn_ray.h>
#include <vsn_point3d.h>
#include <vsn_vector3d.h>
#include <vsn_matrix3d.h>

namespace VSN {

class Placement3DF final
{
public:
    Placement3DF() = default;
    Placement3DF(const Point3DF& origin, const Vector3DF& normal);
    Placement3DF(const Vector3DF& x, const Vector3DF& y, const Point3DF& origin);
public:
    // спроецировать точку на плоскость, оставив в исходной ск
    Point3DF ProjectPoint(const Point3DF& p) const;
    // спроецировать точку на плоскость
    void ProjectPoint(const Point3DF& p, float& u, float& v) const;
    // поиск пересечения луча и плоскости
    bool IntersectRay(const Ray3DF& ray, Point3DF& p, float& d) const;

    Matrix3DF From() const;
    Matrix3DF Into() const;
public:
    Vector3DF x = {1,0,0};
    Vector3DF y = {0,1,0};
    Point3DF origin;
};

//------------------------------------------------------------------------------
/**
*/
// ---
inline Placement3DF::Placement3DF(const Point3DF& origin, const Vector3DF& n)
    :origin(origin)
{
    Matrix3DF m; m.Init(origin, n);
    x.Transform(m); x.Normalize();
    y.Transform(m); y.Normalize();
}

//------------------------------------------------------------------------------
/**
*/
// ---
inline Placement3DF::Placement3DF(const Vector3DF& x, const Vector3DF& y, const Point3DF& origin)
    : x(x)
    , y(y)
    , origin(origin)
{

}

//------------------------------------------------------------------------------
/**
*/
// ---
inline bool Placement3DF::IntersectRay(const Ray3DF& ray, Point3DF& p, float& d) const
{
    Vector3DF vect(origin, ray.origin);
    Vector3DF z = x | y; z.Normalize();

    float h = z * ray.dir;
    float a = z * vect;

    if (fabs(h) > std::numeric_limits<float>::epsilon()) {
        d = -a / h;
        p = origin + (vect - z * a + (ray.dir - z * h) * d);
        return true;
    }

    return false;
}

//------------------------------------------------------------------------------
/**
*/
// ---
inline Point3DF Placement3DF::ProjectPoint(const Point3DF& p) const
{
    float u, v;
    ProjectPoint(p, u, v);

    return { // point on
          origin.x + x.x * u + y.x * v,
          origin.y + x.y * u + y.y * v,
          origin.z + x.z * u + y.z * v,
    };
}

//------------------------------------------------------------------------------
/**
*/
// ---
inline void Placement3DF::ProjectPoint(const Point3DF& p, float& u, float& v) const
{
    const Vector3DF vect(origin, p);

    u = (x * vect);
    v = (y * vect);
    const float lx = (x * x);
    const float ly = (y * y);
    //C3D_ASSERT((lx > NULL_EPSILON) && (ly > NULL_EPSILON));

    u /= lx;
    v /= ly;
}

//------------------------------------------------------------------------------
/**
*/
// ---
inline Matrix3DF Placement3DF::From() const
{
    Vector3DF z = x | y;

    return Matrix3DF{
        x.x, x.y, x.z, 0,
        y.x, y.y, y.z, 0,
        z.x, z.y, z.z, 0,
        origin.x, origin.y, origin.z, 1
    };
}

//------------------------------------------------------------------------------
/**
*/
// ---
inline Matrix3DF Placement3DF::Into() const
{
    Vector3DF z = x | y;

    Matrix3DF m{
        x.x, x.y, x.z, 0,
        y.x, y.y, y.z, 0,
        z.x, z.y, z.z, 0,
        origin.x, origin.y, origin.z, 1
    };
    m.Div();

    return m;
}

} // namespace VSN

#endif /*_VSN_PLACEMENT_H*/