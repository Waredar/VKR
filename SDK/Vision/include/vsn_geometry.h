////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс Geometry является базовым для всех геометрических объектов.
         \en Geometry class is the base class for all geometric objects. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GEOMETRY_H
#define __VSN_GEOMETRY_H

#include <vsn_node.h>
#include <vsn_pen.h>
#include <vsn_boundingbox.h>
#include <vsn_renderstate.h>
#include <vsn_math.h>
#include <vsn_global.h>

namespace VSN {

class GeometryTraits;
class GeometryPrivate;
class RenderContext;

//------------------------------------------------------------------------------
/** \brief \ru Класс Geometry является базовым для всех геометрических объектов.
           \en Geometry class is the base class for all geometric objects. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS Geometry : public Node
{
    VSN_OBJECT(Geometry)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~ 
    explicit Geometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    ~Geometry() override;
protected:
    /// \ru Вернуть список данных геометрии из этого объекта. \en Returns list of geometry data from this object. \~
    ObjectVector<GeometryTraits*> GetGeometryTraits() const;
    /// \ru Добавить группу данных о геометрическом теле. \en Adds data group of geometric solid body. \~
    void AddGeometryTraits(GeometryTraits* pTraits);
    /// \ru Удалить группу данных о геометрическом теле. \en Removes data group of geometric solid body. \~
    void RemoveGeometryTraits(GeometryTraits* pTraits);
public:
    /// \ru Разрешить двустороннее освещение. \en Set double side lighting. \~
    void SetDoubleSidedLighting( bool value );
    /// \ru Проверить использует ли геометрия двусторонее освещение. \en Does geometry use double sided lighting.
    bool IsDoubleSidedLighting() const;
    /// \ru Установить признак видимости для геометрического объекта. \en Set the visibility value to the geometry object.
    void SetVisible(bool value);
    /// \ru Проверить значение видимости у объекта. \en Check the visibility value.
    bool IsVisible() const;
public:
    /// \ru Получить перо. \en Get pen. \~
    virtual Pen GetPen() const;
    /// \ru Задать перо. \en Set pen. \~
    virtual void SetPen(const Pen& pen);

    virtual void ReplaceMainMaterial(Material* pMaterial);
    ///\ ru Задать уровень детализации в диапазоне от 0 до 100. \en Sets LOD in the range from 0 to 100.
    virtual void SetLevelDetail(int value);
    /// \ru Нужно ли учитывать геометрию в механизме PixelCulling. \en NO TRANSLATION. \~
    virtual bool IsIgnorePixelCulling() const;
    /// \ru Прозрачна ли геометрия. \en Checks if geometry is transparent. \~
    virtual bool IsTransparent() const;
    /// \ru Вернуть true, если ограничивающий габарит правильный. \en True if bounding box is valid. \~
    virtual bool IsBoundingBoxValid() const;
    /// \ru Получить габаритный куб. \en Returns bounding box.
    virtual const BoundingBox& GetBoundingBox() const;
    /// \ru Найти объекты, которые находятся в указанной область. \en NO TRANSLATION. \~
    virtual void PickObjectsInsideRect(const MbRect& rect, const Matrix3DF& viewMatrix, 
        const Matrix3DF & mx, Filter filter, bool bUnifying, HitList& hits);
    /// \ru Проверить является ли геометрия аннатационным. \en NO TRANSLATION. \~
    virtual bool IsAnnotation() const;
    /// \ru Обновить число прозрачных материалов после операций с таблицей. \en Updates transparent material count after table operations. \~
    virtual void UpdateTransparentMaterialCount();
    /// \ru Значение полупрозрачности. \en Translucent value.
    virtual TranslucentValue GetTranslucentValue() const;
    /// \ru Существует ли в таблице материал с заданным идентификатором. \en Checks if the material with set identifier exists in the table. \~
    virtual bool HasMaterialById(const NodeKey& key) const;
    /// \ru Получить число материалов из таблицы. \en Returns material count from the table. \~
    virtual size_t GetMaterialCount() const;
    /// \ru Получить таблицу материалов. \en Returns material table. \~
    virtual std::set<Material*> GetMaterialSet() const;
    /// \ru Получить объем геометрии. \en Returns geometry volume. \~
    virtual float GetVolume();
    /// \ru Инвертировать направление всех нормалей. \en Inverts direction of all vertex normals.
    virtual void InvertNormals();
    /// \ru Преобразовать вершины сетки по данной матрице. \en Transforms mesh vertices by given matrix. \~
    virtual void TransformVerticesByMatrix(const Matrix3DF& matrix);
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data. \~
    virtual void UpdateGeometry();
public:
    /// \ru Получить число граней. \en Returns face count. \~
    virtual size_t GetFaceCount(size_t indexLod = 0) const;
    /// \ru Получить число вершин. \en Returns vertex count. \~
    virtual size_t GetVertexCount() const;
public:
    /// \ru Выполнить отрисовку. \en Performs rendering.
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    virtual void DoRender(const RenderState& renderState);
    /// \ru Выполнить отрисовку. \en Performs rendering.
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    virtual void Render(RenderContext& renderContext);
    /// \ru Нарисовать каркас в одном из режимов: GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP GL_LINES. \en Renders wireframe in one of the modes: GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP GL_LINES.
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    virtual void OpenGLDraw(const RenderState& renderState);
public:
    VSN_SIGNAL(Public, OnGeometryDestroyed, void OnGeometryDestroyed(Geometry* pGeometry), pGeometry)
    /// \ru Сигнал об окончании перестроения всей геометрии. \en Signal about the end of rebuilding the whole geometry. \~
    VSN_SIGNAL(Public, OnBuildCompleted, void OnBuildCompleted(Geometry* pGeometry), pGeometry)
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for internal use.
    Geometry(GeometryPrivate& dd, Node* pParent);
private:
    NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DISABLE_COPY(Geometry);
    VSN_DECLARE_EX_PRIVATE(Geometry);
};

} // namespace VSN

#endif /* __VSN_GEOMETRY_H */
