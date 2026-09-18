////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс MathGeometry представляет геометрию для последующей отрисовки, 
             которая была сгенерирована с помощью математического представления.
         \en Class MathGeometry presents geometry for next rendering that was
             generated with math representation. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATHGEOMETRY_H
#define __VSN_MATHGEOMETRY_H

#include <model_item.h>
#include <topology_item.h>
#include <vsn_mathbasegeometry.h>
#include <vsn_global.h>

namespace VSN {

class MathGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MathGeometry представляет геометрию для последующей отрисовки, которая была сгенерирована с помощью математического представления.
           \en Class MathGeometry presents geometry for next rendering that was generated with math representation. \~
    \details \ru Класс MathGeometry принимает указатель на математическое представление MbItem для последующей генерации визуального представления.
                 MbItem может представлять собой такие объекты, как MbSolid, MbMesh, MbContour, ... которые способны генерировать самостоятельно
                 полигональную модель. Класс MathGeometry представляет ряд полезных функций. Для вычисления шага триангуляции поверхностей и граней,
                 вы можете воспользоваться функцией SetVisualSag и вызвать перегенерацию триангуляции в реальном времени, что влияет на качество 
                 отображения геометрии. С помощью функций QueryMathByGeometry и QueryGeomByMath вы можете получить идентификацию примитивов из
                 визуального представления в математическое и наоборот. Необходимо знать, что идентификаторы математического представления являются
                 хеш'ом реальных идентификаторов и пути к этим примитивам. \n.
             \en MathGeometry class takes a pointer to MbItem math representation for the next generating visual representation.
                 MbItem can presents such objects as MbSolid, MbMesh, MbContour, etc that are able to generate a polygonal model independently.
                 MathGeometry class presents a set of useful functions. You can use SetVisualSag function to compute a triangulation step of planes and faces
                 and you can call regeneration of triangulation in real time, what influences quality of geometry display. You can get primitive identification
                 from visual representation to math one and vice versa using QueryMathByGeometry and QueryGeomByMath functions. It's necessary to know that identifiers
                 of math representation are hash of real identifiers and paths to these primitives. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MathGeometry : public MathBaseGeometry
{
    VSN_OBJECT(MathGeometry);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit MathGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~MathGeometry() override;
public: 
    /// \ru Вернуть значение флага отображать вершин. \en Returns flag value of the vertices displaying. \~
    bool IsVerticesDisplaying() const;
    /// \ru Установить значение флага отображать вершин. \en Set flag value to vertices displaying. \~
    void SetVerticesDisplaying(bool bDisplay);

    /// \ru Вернуть размер отображения вершин. \en Returns vertex display size. \~
    float GetSizeVertices() const;
    /// \ru Установить размер отображения вершин. \en Set vertex display size. \~
    void SetSizeVertices(float size);

    /// \ru Вернуть максимально допустимый прогиб кривой или поверхности в соседних точках на расстоянии шага. \en Returns the maximum permissible sag of a curve or surface at adjacent points a step away. \~
    double GetVisualSag() const;
    /// \ru Установить точность для вычисления шага при триангуляции поверхностей и граней. \en Returns accuracy to calculate step when triangulating surfaces and faces. \~
    void SetVisualSag(double sag, bool bRebuildMesh);

    /// \ru Вернуть указатель на математическое точное представление MbItem. \en Returns a pointer to math precise representation of MbItem. \~
    const MbItem* GetMathItem() const;
    /// \ru Установить указатель на математическое точное представление MbItem. \en Sets a pointer to math precise representation of MbItem. \~
    void SetMathItem(const MbItem* pItem, double sag = Math::visualSag);
    /// \ru Перестроить геометрию по измененному MbItem. \en Rebuild geometry by modified MbItem. \~
    void RebuildGeometry();
    /// \ru Очистить в этой геометрии все примитивы. \en Clears all primitives of this geometry. \~
    void Clear() override;
public:
    /// \ru Получить габаритный куб объекта. \en Returns object bounding box. \~
    const BoundingBox& GetBoundingBox() const override;
    /// \ru Обновить геометрию по новым данным для внутреннего использования. \en Updates geometry with new data for inner using. \~
    void UpdateGeometry() override;
    /// \ru Найти объекты, которые находятся в указанной область. \en NO TRANSLATION. \~
    void PickObjectsInsideRect(const MbRect& rect, const Matrix3DF& viewMatrix, 
        const Matrix3DF& mx, Filter filter, bool bUnifying, HitList& hits) override;
private:
    /// \ru Отрисовка тела. \en Renders a solid body. \~
    void OpenGLDraw(const RenderState& state) override;
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION.
    MathGeometry(MathGeometryPrivate& dd, Node* pParent);
private:
    VSN_DISABLE_COPY(MathGeometry);
    VSN_DECLARE_EX_PRIVATE(MathGeometry);
    friend class MathGeometryBuilder;
};

} // namespace VSN

#endif /* __VSN_MATHGEOMETRY_H */
