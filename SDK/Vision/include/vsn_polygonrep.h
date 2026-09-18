////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Класс PolygonGeometry является геометрическим представлением примитивов кривых.
           \en NOT TRANSLATED. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_POLYGONREP_H
#define __VSN_POLYGONREP_H

#include <vsn_geometryrep.h>
#include <vsn_polygongeometry.h>

namespace VSN {

class PolygonRepPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PolygonRep является геометрическим объектом примитивов кривых.
           \en NOT TRANSLATED. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS PolygonRep : public GeometryRep
{
    VSN_OBJECT(PolygonRep);
public:
    /// \ru Конструктор по умолчанию. \en Constructor. \~
    explicit PolygonRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~PolygonRep();
public:
    /// \ru Добавить две точки для отрисовки линии. \en NOT TRANSLATED. \~
    ElementId AddLine(const Point3DF& p1, const Point3DF& p2, const Pen& pen = {});
    /// \ru Задать цвет линии. \en NOT TRANSLATED. \~
    void SetLineColor(ElementId id, const Color& color);
    /// \ru Задать ширину линии. \en NOT TRANSLATED. \~
    void SetLineWidth(ElementId id, float width);
    /// \ru Задать приоритет глубины линии. \en NOT TRANSLATED. \~
    void SetLinePriority(ElementId id, uint priority);
    /// \ru Добавить массив точек для отрисовки кривой. \en NOT TRANSLATED. \~
    ElementId AddPolygon(const std::vector<Point3DF>& positions, const Pen& pen = {});
    /// \ru Добавить массив точек для отрисовки кривой. \en NOT TRANSLATED. \~
    ElementId AddPolygon(const Point3DF* points, size_t count, const Pen& pen = {});

    /// \ru Добавить полигон с помощью описания класса PolygonDescriptor. \en NOT TRANSLATED. \~
    ElementId AddPolygon(const PolygonDescriptor& polygon);
    /// \ru Добавить массив полигонов с помощью описания класса PolygonDescriptor. \en NOT TRANSLATED. \~
    ElementId AddPolygons(const std::vector<PolygonDescriptor>& polygons);

    /// \ru Добавить полигон с учетом индексов. \en NOT TRANSLATED. \~
    ElementId AddIndicesPolygon(const Point3DF* points, size_t pointsCount, const uint* indices, size_t indicesCount,
        const Color& color, float width, uint8_t priority, const Vector3DF& = {});
    /// \ru Добавить полигон позиций и цвета с учетом индексов. \en NOT TRANSLATED. \~
    ElementId AddIndicesPolygon(const Point3DFColor* points, size_t pointsCount, const uint* indices, size_t indicesCount,
        const Color& color, float width, uint8_t priority, const Vector3DF& = {});
    /// \ru Добавить полигон позиций и одномерной текстуры с учетом индексов. \en NOT TRANSLATED. \~
    ElementId AddIndicesPolygon(const Point3DFTexture1D* points, size_t pointsCount, const uint* indices, size_t indicesCount,
        const Pen& pen, uint8_t priority, const Vector3DF& = {});
    /// \ru Добавить полигон позиций и нормалий с учетом индексов. \en NOT TRANSLATED. \~
    ElementId AddIndicesPolygon(const Point3DNormal3D* points, size_t pointsCount, const uint* indices, size_t indicesCount,
        const Color& color, float width, uint8_t priority);

    /// \ru Управление видимостью кривой по заданному идентификатору кривой. \en NOT TRANSLATED. \~
    void SetVisiblePolygon(ElementId id, bool visible);
    /// \ru Вернуть видимость кривой по идентификатору кривой. \en NOT TRANSLATED. \~
    bool IsVisiblePolygon(ElementId id) const;

    /// \ru Функция оптимизации геометрических кривых. \en NOT TRANSLATED. \~
    void ArrangeGeometry();
private:
    VSN_DISABLE_COPY(PolygonRep);
    VSN_DECLARE_EX_PRIVATE(PolygonRep);
};

} // namespace VSN

#endif /* __VSN_POLYGONREP_H */

