#ifndef __VSN_REGION_H
#define __VSN_REGION_H

#include <vsn_atomic.h>
#include <vsn_rect.h>
#include <vsn_point.h>
#include <vsn_global.h>

namespace VSN {

struct RegionPrivate;
struct RegionData;
/* Region */
class VSN_CLASS Region
{
public:
    enum RegionType { Rectangle, Ellipse };
public:
    Region();
    Region(int x, int y, int w, int h, RegionType t = Rectangle);
    Region(const RectI& r, RegionType t = Rectangle);
    Region(const Region& region);
    Region(Region&& other);
    ~Region();
public:
    Region& operator=(const Region& other);
    inline void Swap(Region &other) { std::swap(d, other.d); }
    bool IsEmpty() const;
    bool IsNull() const;

    bool PntInRegion(const PointI& pnt) const;
    bool RectInRegion(const RectI& rc) const;

    void Offset(int dx, int dy);
    inline void Offset(const PointI &p) { Offset(p.GetX(), p.GetY()); }
    Region Offseted(int dx, int dy) const;
    inline Region Offseted(const PointI &p) const { return Offseted(p.GetX(), p.GetY()); }

    Region United(const Region& reg) const;
    Region United(const RectI& rc) const;
    Region Intersected(const Region& reg) const;
    Region Intersected(const RectI& rc) const;
    Region Subtracted(const Region& reg) const;
    Region Xored(const Region& reg) const;

    bool Intersects(const Region& reg) const;
    bool Intersects(const RectI& rc) const;

    RectI GetBoundingRect() const;
    std::vector<RectI> GetRects() const;
    void SetRects(const RectI* rect, int num);
    int GetRectCount() const;

    Region operator|(const Region& reg) const;
    Region operator+(const Region& reg) const;
    Region operator+(const RectI& rc) const;
    Region operator&(const Region& reg) const;
    Region operator&(const RectI& rc) const;
    Region operator-(const Region& reg) const;
    Region operator^(const Region& reg) const;

    Region& operator|=(const Region& reg);
    Region& operator+=(const Region& reg);
    Region& operator+=(const RectI& rc);
    Region& operator&=(const Region& reg);
    Region& operator&=(const RectI& rc);
    Region& operator-=(const Region& reg);
    Region& operator^=(const Region& reg);

    bool operator==(const Region& reg) const;
    inline bool operator!=(const Region& reg) const { return !(operator==(reg)); }
private:
    Region Duplicate() const;
    void Detach();
    struct RegionData* d;
};

} // namespace VSN

#endif // __VSN_REGION_H
