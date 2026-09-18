#ifndef __VSN_CONSTRUCTRECTANGLEGEOMETRY_H
#define __VSN_CONSTRUCTRECTANGLEGEOMETRY_H

#include <vsn_meshgeometry.h>

namespace VSN {

class ConstructRectangleGeometryPrivate;
/* ConstructRectangleGeometry */
class VSN_CLASS ConstructRectangleGeometry : public MeshGeometry
{
    VSN_OBJECT(ConstructRectangleGeometry);
public:
    ConstructRectangleGeometry(Node* pParent = nullptr);
    virtual ~ConstructRectangleGeometry();
public:
    // Вернуть точку начала рамки.
    MbCartPoint GetBeginPoint() const;
    // Установить точку начала рамки.
    void SetBeginPoint(const MbCartPoint& pnt);
    // Вернуть точку конца рамки.
    MbCartPoint GetEndPoint() const;
    // Установить точку конца рамки.
    void SetEndPoint(const MbCartPoint& pnt);
    // Вернуть цвет заполнения рамки.
    Color GetColorFillRect() const;
    // Установить цвет заполнения рамки.
    void SetColorFillRect(const Color& clr);
    // Вернуть цвет бордера рамки.
    Color GetColorRectBorder() const;
    // Установить цвет бордера рамки.
    void SetColorRectBorder(const Color& clr);
private:
    /// \ru Отрисовать сферу с помощью OpenGL. \en Draw a sphere with OpenGL.
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(ConstructRectangleGeometry);
    VSN_DECLARE_EX_PRIVATE(ConstructRectangleGeometry);
};

}
#endif /*__VSN_CONSTRUCTRECTANGLEGEOMETRY_H */