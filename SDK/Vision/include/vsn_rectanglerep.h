#ifndef __VSN_RECTANGLEREP_H
#define __VSN_RECTANGLEREP_H

#include <vsn_geometryrep.h>

namespace VSN {

/* RectangleRep */
class VSN_CLASS RectangleRep : public GeometryRep
{
    VSN_OBJECT(RectangleRep);
    VSN_PROP_READ_WRITE_NOTIFY(width, GetWidth, SetWidth, WidthModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, HeightModified);
public:
    explicit RectangleRep(Node* pParent = nullptr);
    virtual ~RectangleRep();
public:
    /// \ru Выдать ширину прямоугольника. \en Get width.
    float GetWidth() const;
    /// \ru Выдать высоту прямоугольника. \en Get height.
    float GetHeight() const;
public:
    /// \ru Задать ширину прямоугольника. \en Set width.
    VSN_SLOT(Public, SetWidth, void SetWidth(float width))
    /// \ru Задать высоту прямоугольника. \en Set width.
    VSN_SLOT(Public, SetHeight, void SetHeight(float height))
public:
    VSN_SIGNAL(Public, WidthModified, void WidthModified(float width), width)
    VSN_SIGNAL(Public, HeightModified, void HeightModified(float height), height)
private:
    VSN_DISABLE_COPY(RectangleRep);
};

} // namespace VSN

#endif /* __VSN_RECTANGLEREP_H */

