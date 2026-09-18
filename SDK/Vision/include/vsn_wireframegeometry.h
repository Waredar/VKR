////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Абстрактный базовый класс для отрисовочной геометрии.
       \en Abstract base class for rendering geometry. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_WIREFRAMEGEOMETRY_H
#define __VSN_WIREFRAMEGEOMETRY_H

#include <set>
#include <list>
#include <unordered_map>

#include <vsn_color.h>
#include <vsn_geometry.h>
#include <vsn_namespace.h>

#include <vsn_global.h>

class MbCube;
class MbCartPoint3D;

namespace VSN {

class Material;
class RenderState;
class Viewport;
class WireframeGeometryPrivate;
class Pen;
class Brush;
class RenderContext;
class Matrix3DF;

//------------------------------------------------------------------------------
/** \brief  \ru Абстрактный базовый класс для отрисовочной геометрии.
            \en Abstract base class for rendering geometry. \~
    \details  \ru Абстрактный базовый класс для отрисовочной геометрии:
                - содержит основной атрибут, который является таблицой материалов.
                - содержит ряд виртуальных функций, которые позволяют отрисовать геометрию.
                - содержит механизм отрисовки детализации заданного уровня. \n.
              \en Abstract base class for rendering geometry:
                - contains the main attribute that is material table.
                - contains virtual function row to provide rendering geometry.
                - contains rendering mechanism of set level of detail (LOD). \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS WireframeGeometry : public Geometry
{
    VSN_OBJECT(WireframeGeometry);
public:
    /// \ru Конструктор. \en Constructor. \~
    WireframeGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~WireframeGeometry() override;
public:
    /// \ru Действительна ли геометрия. \en Checks if geometry is valid. \~
    bool IsValid() const;
    /// \ru Задан ли материал. \en Checks if material is set. \~
    bool HasMaterial() const;
    /// \ru Получить первый материал из таблицы. \en Returns the first material from the table. \~
    Material* GetHeadMaterial() const;
    /// \ru Получить число материалов из таблицы. \en Returns material count from the table. \~
    size_t GetMaterialCount() const override;
    /// \ru Получить указатель, соответствующий идентификатору. \en Returns the pointer corresponding to the identifier. \~
    Material* GetMaterialById(NodeKey id) const;
    /// \ru Получить таблицу материалов. \en Returns material table. \~
    std::set<Material*> GetMaterialSet() const override;
    /// \ru Получить список идентификаторов материалов. \en Returns material identifier list. \~
    std::list<NodeKey> GetMaterialIds() const;
    /// \ru Существует ли в таблице материал с заданным идентификатором. \en Checks if the material with set identifier exists in the table. \~
    bool HasMaterialById(const NodeKey& key) const override;
    /// \ru Получить габаритный куб каркаса. \en Returns wireframe bounding box. \~
    const BoundingBox& GetWireBoundingBox() const;
    /// \ru Является ли габаритный куб допустимым. \en Checks if bounding box is valid. \~
    bool IsBoundingBoxValid() const override;
    /// \ru Прозрачна ли геометрия. \en Checks if geometry is transparent. \~
    bool IsTransparent() const override;
    /// \ru Имеется ли прозрачный материал в таблице. \en Checks if transparent material exists in the table. \~
    bool IsExistTransparentMaterials() const;
    /// \ru Задан ли цвет каждой вершины. \en Checks if color of each vertex is set. \~
    bool IsColorEachVertex() const;
    /// \ru Установить флаг назначения цвета для каждой вершины. \en Sets flag of setting color for each vertex. \~
    void SetColorEachVertex(bool bColorEachVertex);
    /// \ru Является ли геометрия каркасной. \en Checks if geometry is wireframe. \~
    bool IsWireframe() const;
    /// \ru Получить число граней. \en Returns face count. \~
    size_t GetFaceCount(size_t indexLod = 0) const override;
    /// \ru Получить число вершин. \en Returns vertex count. \~
    size_t GetVertexCount() const override;

    // \ru  Вернуть видимость примитива по идентификатору. \en Returns visibility of the primitive by its identificator. \~
    bool IsVisiblePrimitive(uint id) const;
    // \ru Установить видимость примитива по идентификатору. \en Sets visibility of the primitive by its identificator. \~
    void SetVisiblePrimitive(uint id, bool visible);

    /// \ru Получить толщину линии(перегружены для удобства). \en Returns line width(functions are overloaded for convenience). \~
    float GetLineWidth() const;
    /// \ru Задать толщину линии(перегружены для удобства). \en Sets line width(functions are overloaded for convenience). \~
    void SetLineWidth(float lineWidth);

    /// \ru Получить толщину выбранной линии(перегружены для удобства). \en Returns width of the selected line(functions are overloaded for convenience). \~
    float GetSelectedLineWidth() const;
    /// \ru Задать толщину выбранной линии(перегружены для удобства). \en Sets width of the selected line(functions are overloaded for convenience). \~
    void SetSelectedLineWidth(float lineWidth);

    /// \ru Получить цвет каркаса(перегружены для удобства). \en Returns wireframe color(functions are overloaded for convenience). \~
    Color GetWireframeColor() const;
    /// \ru Задать цвет каркаса(перегружены для удобства). \en Sets wireframe color(functions are overloaded for convenience). \~
    void SetWireframeColor(const Color& color);

    /// \ru Получить перо. \en Get pen. \~
    Pen GetPen() const override;
    /// \ru Задать перо. \en Set pen. \~
    void SetPen(const Pen& pen) override;

    /// \ru Пуст ли каркас. \en Checks if wireframe is empty. \~
    bool IsWireframeEmpty() const;
    /// \ru Получить позиции вершин. \en Returns vertex positions. \~
    std::vector<float> GetWireFrameVertexPositions() const;
    /// \ru Получить число полилиний. \en Returns polyline count. \~
    int GetPolylineCount() const;
    /// \ru Получить смещение полилинии с заданным индексом в контейнере. \en Returns polyline offset with set index in the container. \~
    uint GetPolylineOffset(int index) const;
    /// \ru Получить размер полилинии с данным индексом. \en Returns size of polyline with given index. \~
    int GetPolylineSize(int index) const;
    /// \ru Нужно ли учитывать геометрию в механизме PixelCulling. \en NO TRANSLATION. \~
    bool IsIgnorePixelCulling() const override;
    /// \ru Запретить PixelCulling для этой геометрии. \en NO TRANSLATION. \~
    virtual void IgnorePixelCulling(bool value);
    /// \ru Преобразовать вершины сетки по матрице. \en Transforms mesh vertices by the matrix. \~
    void TransformVerticesByMatrix(const Matrix3DF& matrix) override;
public:
    /// \ru Удалить всю геометрию. \en Deletes all geometry. \~
    virtual void Clear();
    /// \ru Заменить основной материал. \en Replaces the main material. \~
    void ReplaceMainMaterial(Material*) override;
    /// \ru Добавить материал в таблицу. \en Adds material to the table.
    void AddMaterial(Material* pMaterial);
    /// \ru Обновить число прозрачных материалов после операций с таблицей. \en Updates transparent material count after table operations.
    void UpdateTransparentMaterialCount() override;
    /// \ru Инвертировать направление всех нормалей. \en Inverts direction of all vertex normals.
    void InvertNormals() override;
    ///\ ru Задать уровень детализации в диапазоне от 0 до 100. \en Sets LOD in the range from 0 to 100.
    void SetLevelDetail(int value) override;
    // добавить цвета
    void AddWireframeColors(const std::vector<float>& colors);
    /// \ru Добавить группу вершин и вернуть её идентификатор. \en Adds vertex group and returns its identifier.
    uint AddPolygonGroup(const std::vector<float>& vector, uint id = 0);
    /// \ru Добавить группу вершин четырехугольной сетки и вернуть её идентификатор. \en Adds vertex quadrangle grid group and returns its identifier.
    uint AddPoligonQuadrangleGroup(const std::vector<float>& vector);
    /// \ru Задать, будет ли использоваться глобальный идентификатор. \en Sets if the global identifier will be used.
    void SetUseGlobalIdentifier(int global);
    /// \ru Скопировать буфер вершин в память. \en Copies vertex buffer into memory.
    virtual void CopyVertexBufferToClientSide();
    /// \ru Создать буфер вершин. \en Creates vertex buffer.
    virtual void ReleaseVertexBufferClientSide(bool update = false);
    /// \ru Найти объекты, которые находятся в указанной область. \en NO TRANSLATION. \~
    void PickObjectsInsideRect(const MbRect& rect, const Matrix3DF& viewMatrix, 
        const Matrix3DF& mx, Filter filter, bool bUnifying, HitList& hits) override;
    /// \ru Значение полупрозрачности. \en Translucent value.
    TranslucentValue GetTranslucentValue() const override;
public:
    /// \ru Выполнить отрисовку. \en Performs rendering.
    void DoRender(const RenderState&) override;
    /// \ru Выполнить отрисовку. \en Performs rendering.
    void Render(RenderContext&) override;
protected:
    /// \ru Выполнить отрисовку. \en  Performs rendering.
    virtual void OGLInitGeom(const RenderState&);
    /// \ru Нарисовать каркас в одном из режимов: GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP GL_LINES. \en Renders wireframe in one of the modes: GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP GL_LINES.
    void OGLDrawWireframe(const RenderState&, uint mode);
protected:
    /// \ru Очистить всю каркасную геометрию. \en Clears all wireframe.
    void ClearWireframe();
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION.
    WireframeGeometry(WireframeGeometryPrivate& dd, Node* pParent);
    void SetWireframe(bool bWireframe);
private:
    friend class RenderContainer;
    VSN_DECLARE_EX_PRIVATE(WireframeGeometry);
};

} // namespace VSN

#endif /* __VSN_WIREFRAMEGEOMETRY_H */
