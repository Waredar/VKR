////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Класс PolygonGeometry является геометрическим объектом примитивов кривых.
           \en The PolygonGeometry class is a geometry object of curve primitives. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_POLYGONGEOMETRY_H
#define __VSN_POLYGONGEOMETRY_H

#include <vector>
#include <vsn_geometry.h>
#include <vsn_point3d.h>
#include <vsn_vector3d.h>
#include <vsn_pen.h>
#include <vsn_nodekey.h>
#include <vsn_namespace.h>
#include <vsn_global.h>

namespace VSN {

///< \ru Координаты 1D текстуры. \en 1D texture coordinates. \~
struct Point3DFTexture1D
{
    Point3DF point;
    float    tCoord;
};

///< \ru Координаты 2D текстуры. \en 2D texture coordinates. \~
struct Point3DFTexture2D
{
    Point3DF point;
    PointF   tCoord;
};

///< \ru Координаты 3D текстуры. \en 3D texture coordinates. \~
struct Point3DFTexture3D
{
    Point3DF point;
    Point3DF tCoord;
};

///< \ru Координаты для задания цвета. \en Coordinates for setting a color. \~
struct Point3DFColor
{
    Point3DF point;
    uint32_t color;
};

///< \ru Координаты для задания позиции вместе с нормалью. \en Coordinates for setting a position with normal. \~
struct Point3DNormal3D
{
    Point3DF point;
    Vector3DF normal;
};

class PolygonDescriptorPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PolygonDescriptor определяет дополнительные параметры для создания геометрических кривых.
           \en The PolygonDescriptor class defines additional options for creating geometric curves. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS PolygonDescriptor
{
public:
    PolygonDescriptor(const Point3DF* positions, size_t count, const Pen& pen, uint8_t priority = 0);
    PolygonDescriptor(const Point3DF* positions, size_t count, const Pen& pen, const Vector3DF& normal, uint8_t priority = 0);
    PolygonDescriptor(const Point3DFTexture1D* positions, size_t count, const Pen& pen, uint8_t priority = 0);
    PolygonDescriptor(const Point3DFTexture1D* positions, size_t count, const Pen& pen, const Vector3DF& normal, uint8_t priority = 0);
    PolygonDescriptor(const Point3DFColor* positions, size_t count, const Pen& pen, uint8_t priority = 0);
    PolygonDescriptor(const Point3DFColor* positions, size_t count, const Pen& pen, const Vector3DF& normal, uint8_t priority = 0);
    PolygonDescriptor(const PolygonDescriptor&);
    PolygonDescriptor(PolygonDescriptor&&);
    ~PolygonDescriptor();
public:
    PolygonDescriptor& operator = (const PolygonDescriptor&);
    PolygonDescriptor& operator = (PolygonDescriptor&&);
protected:
    PolygonDescriptor(size_t count, const Pen& pen, const Vector3DF& normal, uint8_t priority);
private:
    VSN_DECLARE_PRIVATE(PolygonDescriptor);
};

class RenderContext;
class PolygonGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PolygonGeometry является геометрическим объектом примитивов кривых.
           \en The PolygonGeometry class is a geometry object of curve primitives. \n \~
    \details \ru Класс PolygonGeometry позволяет создавать геометрические кривые на основе полигональной
                 модели. PolygonGeometry имеет ряд функций, с помощью которых можно создать геометрические
                 кривые, а также управлять их видимостью и цветовой гаммой.  При создании кривых вы можете
                 задать необходимый цвет, а также стиль полигона и текстуру со своей позиции. Для PolygonGeometry 
                 предусмотрено задание нормалей для отсечения при отображении обратной стороны в каждой позиции полигона. 
                 В PolygonGeometry предусмотрены вспомогательные функции при добавлении кривой с заданием индексов и 
                 с полным описанием с помощью класса PolygonDescriptor. \n.
             \en The PolygonGeometry class allows you to create geometric curves based on polygon
                 models. PolygonGeometry has a number of functions for creating geometric
                 curves, as well as control their visibility and color range. When creating curves, you can
                 set the desired color, as well as the polygon style and texture from your position. With PolygonGeometry
                 it is possible to set normals for clipping when displaying the reverse side in each position of the polygon.
                 PolygonGeometry provides helper functions when adding a curve with indexes and
                 with a full description using the PolygonDescriptor class. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS PolygonGeometry : public Geometry
{
    VSN_OBJECT(PolygonGeometry);
public:
    /// \ru Конструктор по умолчанию. \en Constructor. \~
    explicit PolygonGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~PolygonGeometry();
public:
    /// \ru Добавить две точки для отрисовки линии. \en Add two points to draw a line. \~
    ElementId AddLine(const Point3DF& p1, const Point3DF& p2, const Pen& pen = {});
    /// \ru Задать цвет линии. \en Set line color. \~
    void SetLineColor(ElementId id, const Color& color);
    /// \ru Задать ширину линии. \en Set line width. \~
    void SetLineWidth(ElementId id, float width);
    /// \ru Задать приоритет глубины линии. \en Set depth priority for line. \~
    void SetLinePriority(ElementId id, uint priority);
    /// \ru Добавить массив точек для отрисовки кривой. \en Add points array to draw a curve. \~
    ElementId AddPolygon(const std::vector<Point3DF>& positions, const Pen& pen = {});
    /// \ru Добавить массив точек для отрисовки кривой. \en Add points array to draw a curve. \~
    ElementId AddPolygon(const Point3DF* points, size_t count, const Pen& pen = {});

    /// \ru Добавить полигон с помощью описания класса PolygonDescriptor. \en Add a polygon using PolygonDescriptor. \~
    ElementId AddPolygon(const PolygonDescriptor& polygon);
    /// \ru Добавить массив полигонов с помощью описания класса PolygonDescriptor. \en Add a polygon array using PolygonDescriptor. \~
    ElementId AddPolygons(const std::vector<PolygonDescriptor>& polygons);

    /// \ru Добавить полигон с учетом индексов. \en Add a polygon with respect to indices. \~
    ElementId AddIndicesPolygon(const Point3DF* points, size_t pointsCount, const uint* indices, size_t indicesCount,
                             const Color& color, float width, uint8_t priority, const Vector3DF& = {});
    /// \ru Добавить полигон позиций и цвета с учетом индексов. \en Add a polygon of positions and colors with respect to indices. \~
    ElementId AddIndicesPolygon(const Point3DFColor* points, size_t pointsCount, const uint* indices, size_t indicesCount,
                             const Color& color, float width, uint8_t priority, const Vector3DF& = {});
    /// \ru Добавить полигон позиций и одномерной текстуры с учетом индексов. \en Add a polygon of positions and 1D texture with respect to indices. \~
    ElementId AddIndicesPolygon(const Point3DFTexture1D* points, size_t pointsCount, const uint* indices, size_t indicesCount,
                             const Pen& pen, uint8_t priority, const Vector3DF& = {});
    /// \ru Добавить полигон позиций и нормалий с учетом индексов. \en Add a polygon of positions and normals with respect to indices. \~
    ElementId AddIndicesPolygon(const Point3DNormal3D* points, size_t pointsCount, const uint* indices, size_t indicesCount,
                             const Color& color, float width, uint8_t priority);
    /// \ru Управление видимостью кривой по заданному идентификатору кривой. \en Set curve visibility. \~
    void SetVisiblePolygon(ElementId id, bool visible);
    /// \ru Вернуть видимость кривой по идентификатору кривой. \en Get curve visibility. \~
    bool IsVisiblePolygon(ElementId id) const;

    /// \ru Функция оптимизации геометрических кривых. \en Method for geometric curves optimization. \~
    void ArrangeGeometry();
public:
    /// \ru Очистить данные геометрии. \en Clear geometric data. \~
    void ClearGeometry();
public:
    /// \ru Выполнить отрисовку. \en Performs rendering.
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    virtual void Render(RenderContext& renderContext) override;
    /// \ru Получить габаритный куб. \en Returns bounding box.
    virtual const BoundingBox& GetBoundingBox() const override;
private:
    // Выполнить отрисовку.
    virtual void DoRender(const RenderState&) override;
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for internal use.
    PolygonGeometry(PolygonGeometryPrivate& dd, Node* pParent);
private:
    VSN_DECLARE_EX_PRIVATE(PolygonGeometry);
};

} // namespace VSN

#endif /* __VSN_POLYGONGEOMETRY_H */
