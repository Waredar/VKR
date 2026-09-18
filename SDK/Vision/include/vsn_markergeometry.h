////////////////////////////////////////////////////////////////////////////////
/** 
  \file
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SPRITEGEOMETRY_H
#define __VSN_SPRITEGEOMETRY_H

#include <mb_placement3d.h>

#include <vsn_meshgeometry.h>
#include <vsn_planemarker.h>
#include <vsn_global.h>

namespace VSN {

class Canvas;
class RenderContext;
class MarkerGeometryPrivate;
class Image;
//------------------------------------------------------------------------------
/** 
*/
// ---
class VSN_CLASS MarkerGeometry final : public MeshGeometry
{
public:
    /// \ru Конструктор. \en Constructor. \~
    MarkerGeometry(const MbCartPoint3D & position, MarkerID markerId, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~MarkerGeometry();
public:
    //void SetMarker( int markerId );
public:
    /// \ru Получить габаритный куб объекта. \en Returns object bounding box. \~
    virtual const BoundingBox& GetBoundingBox() const override;
    virtual bool IsIgnorePixelCulling() const;
    virtual TranslucentValue GetTranslucentValue() const;
private:
    /// \ru Отрисовка тела. \en Renders a solid body. \~
    virtual void Render(RenderContext&) override;
private:
    VSN_DISABLE_COPY(MarkerGeometry);
    VSN_DECLARE_EX_PRIVATE(MarkerGeometry);
};

} // namespace VSN

#endif /* __VSN_SPRITEGEOMETRY_H */
