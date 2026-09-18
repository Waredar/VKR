///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс MeshGeometry для отрисовки полигонального объекта.
         \en MeshGeometry class for rendering polygon object. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_MESHGEOMETRY_H
#define __VSN_MESHGEOMETRY_H

#include <vsn_material.h>
#include <vsn_wireframegeometry.h>
#include <vsn_geometrybuilder.h>
#include <vsn_globalflags.h>
#include <vsn_namespace.h>

#include <mesh_float_point3d.h>
#include <vsn_global.h>

class MbMesh;

namespace VSN {

class MeshGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MeshGeometry для отрисовки полигонального объекта.
           \en MeshGeometry class for rendering polygon object. \~
    \details \ru Класс MeshGeometry содержит триангуляционное представление в виде triangle list, а также
                 triangle strips - способ задания геометрии лентой из треугольников. При этом
                 только первый треугольник из ленты задаётся всеми тремя вершинами,
                 а каждый последующий - лишь одной вершиной, которая добавляется к двум
                 последним вершинам из массива.
                 Наконец, последнее - это triangle fan. \n.
             \en MeshGeometry class contains triangle representation as triangle list, and also
                 triangle strips that is a method for setting geometry with triangle strip. Thus, only the first
                 triangle from the strip is set with all three vertices. Each following triangle is set with 
                 only one vertex that is added to previous two vertices from the array.
                 Finally, the last one is triangle fan. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MeshGeometry : public WireframeGeometry
{
    VSN_OBJECT(MeshGeometry);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    MeshGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    ~MeshGeometry() override;
public:
    /// \ru Получить число граней. \en Returns face count.
    size_t GetFaceCount(size_t indexLod) const override;
    /// \ru Получить число вершин. \en Returns vertex count.
    size_t GetVertexCount() const override;
    /// \ru Получить число нормалей. \en Returns normal count.
    size_t GetNormalCount() const;

    /// \ru Получить габаритный куб каркаса. \en Returns wireframe bounding box.
    const BoundingBox& GetMeshBoundingBox() const;
    /// \ru Получить габаритный куб. \en Returns bounding box.
    const BoundingBox& GetBoundingBox() const override;

    /// \ru Является ли цвет вершины активным. \en Checks if vertex color is active.
    bool IsActiveColorVertex() const;
    /// \ru Задать необходимость использования индексированных цветов в вершинах. \en Sets necessity of use of indexed color in vertices.
    void SetActiveColorVertex(bool bActive);

    /// \ru Получить число уровней детализации. \en Returns count of Levels Of Detail (LOD).
    size_t GetLevelsDetail() const;

    /// \ru Получить контейнер позиций. \en Returns position container.
    std::vector<float> GetPositions() const;
    /// \ru Получить контейнер нормалей. \en Returns normal container.
    std::vector<float> GetNormals() const;
    /// \ru Получить контейнер текселей. \en Returns texel container.
    std::vector<float> GetTexels() const;

    /// \ru Находится ли триангуляция в контейнере уровней детализации. \en Checks if triangulation exists in LOD container.
    bool IsExistTriangles(int indexLod, const NodeKey& materialId) const;

    /// \ru Получить указанные индексы триангуляции. \en Returns specified triangulation indices.
    std::vector<uint> GetTriIndices(int indexLod, const NodeKey& materialId) const;

    /// \ru Получить индексы треугольников, не зависящие от уровня детализации и материала. \en Returns indices of triangles not depending on material and LOD.
    std::vector<uint> GetSimilarTriStripsFansIndex(int lod, const NodeKey& materialId);

    /// \ru Получить число треугольников в массиве уровней детализации. \en Returns triangle count in the array of LOD.
    size_t GetTriangleCount(int lod, const NodeKey& materialId) const;

    /// \ru Содержит ли объект сетку с заданным материалом. \en Checks if object contains the mesh with given material.
    bool IsExistStrips(int lod, const NodeKey& materialId) const;

    /// \ru Получить индексы триангуляции. \en Returns triangulation indices.
    std::vector<std::vector<uint>> GetTriStripsIndex(int lod, const NodeKey& materialId) const;

    /// \ru Получить число треугольников, соответствующих уровню детализации. \en Returns count of triangles corresponding to LOD.
    int GetTriStripCount(int lod, const NodeKey& materialId) const;

    /// \ru Есть ли треугольники, соответствующие заданному уровню детализации и материалу. \en Checks if triangles with given material and LOD exist.
    bool IsExistFans(int lod, const NodeKey& materialId) const;

    /// \ru Получить индексы триангуляции. \en Returns triangulation indices.
    std::vector< std::vector<uint> > GetTriFansIndex(int lod, const NodeKey& materialId) const;

    /// \ru Получить количество треугольников, соответствующих уровню детализации и материалу. \en Returns count of triangles corresponding to material and LOD.
    int GetTriFansCount(int lod, const NodeKey& materialId) const;

    /// \ru Есть ли уровень детализации с заданным идентификатором. \en Checks if LOD with given identifier exists.
    bool IsExistLevelOfDetail(int lod) const;

    /// \ru Включен ли материал для указанного уровня детализации. \en Checks if material for the specified LOD is included.
    bool LevelOfDetailIncludesMaterial(int lod, const NodeKey& materialId) const;

    /// \ru Получить точность расчёта заданного уровня детализации. \en Returns the computational accuracy for given LOD.
    double GetAccuracyLevelOfDetail(int lod) const;

    /// \ru Задать масштаб и единицы, которые будут использованы для вычисления значений глубины. \en Set the scale and units that will be used to calculate the depth values. \~
    void SetFaceOffset(float factor, float units);

    /// \ru Получить материал примитива по указанному идентификатору и уровню детализации. \en Returns material of primitive by the specified identifier and LOD.
    Material* GetMaterialPrimitiveById(uint id, int lod = 0) const;

    /// \ru Получить идентификаторы примитивов. \en Returns primitive identifiers.
    std::set<uint> GetArrayIDsPrimitives() const;

    /// \ru Пуст ли объект. \en Checks if object is empty.
    bool IsEmpty() const;

    /// \ru Создать сетку уровня детализации. \en Creates mesh of LOD.
    MeshGeometry* CreateMeshByIndexLod(int lodIndex);
    /// \ru Создать сетку уровня детализации. \en Creates mesh of LOD.
    MeshGeometry* CreateMeshFromByIndexLod(int lodIndex);

    /// \ru Преобразовать вершины сетки по матрице. \en Transforms mesh vertices by the matrix.
    void TransformVerticesByMatrix(const Matrix3DF& matrix) override;

    /// \ru Получить объем геометрии. \en Returns geometry volume.
    float GetVolume() override;

    /// \ru Обновить полигональную модель объекта. \en Updates object mesh. 
    virtual void UpdateMesh(MbMesh* pMeshItem) { VSN_UNUSED(pMeshItem); }
public:
    /// \ru Очистить всю геометрию. \en Clears all geometry.
    void Clear() override;

    /// \ru Очистить объект и все уровни детализации. \en Clears the object and all LODs.
    void ClearMeshGeometry();

    /// \ru Вернуть true, если полигоны видны по указанному идентификатору. \en Returns true if polygons by the specified ID are visible .
    bool IsVisibleTriangles(uint primitiveId) const;
    /// \ru Установить видимость полигона по указанному идентификатору. \en Set visibility of the polygon by the specified ID.
    void SetVisibleTriangles(uint primitiveId, bool visible);
    /// \ru Сделать видимыми все треугольники. \en Make all triangles visible.
    void MakeAllTrianglesVisible();

    /// \ru Добавить координаты вершин. \en Adds vertex coordinates.
    void AddVertices(const std::vector<float>& vertices);
    /// \ru Добавить нормали. \en Adds normals.
    void AddNormals(const std::vector<float>& normals);
    /// \ru Добавить тексели. \en Adds texels.
    void AddTexels(const std::vector<float>& texels);
    /// \ru Добавить цвета. \en Adds colors.
    void AddColors(const std::vector<float>& colors);
    /// \ru Добавить триангуляцию и вернуть идентификатор. \en Adds triangulation and returns identifier.
    uint AddTriangles(TypeTriangulation type, Material* pMaterial, 
        const std::vector<uint>& indices, int lod = 0, float accuracy = 0.0f);

    /// \ru Инвертировать направление всех нормалей. \en Inverts direction of all normals.
    void ReverseNormals();

    /// \ru Завершить подготовку объекта, данные которого заданы. \en Completes preparing the object with set data.
    void CloseMesh();

    /// \ru Задать уровень детализации от 0 до 100. \en Sets LOD in the range from 0 to 100.
    void SetLevelDetail(int value) override;

    /// \ru Заменить основной материал указанным. \en Replaces the main material with the specified material.
    void ReplaceMainMaterial(Material* pMaterial) override;

    /// \ru Заменить материал с заданным идентификатором. \en Replaces the material with given identifier.
    void ReplaceMaterial(const NodeKey& key, Material* pMaterial);

    /// \ru Задать цвет каркаса. \en Sets wireframe color.
    void SetWireframeColor(const Color& color);

    /// \ru Скопировать буфер вершин в память. \en Duplicates vertex buffer into memory.
    virtual void DuplicateVertexBufferToClientSide();

    /// \ru Сформировать буфер вершин. \en Creates vertex buffer.
    virtual void ReleaseVertexBufferClientSide(bool update);

    /// \ru Найти объекты, которые находятся в указанной область. \en Find objects that are in the specified area. \~
    void PickObjectsInsideRect(const MbRect& rect, const Matrix3DF& viewMatrix, 
        const Matrix3DF& mx, Filter filter, bool bUnifying, HitList& hits) override;
protected:
    /// \ru Выполнить отрисовку. \en  Performs rendering.
    void OpenGLDraw(const RenderState&) override;
    /// \ru Отрисовка каркаса. \en  NOT TRANSLATED
    void RenderWireframe(const RenderState& state);
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for internal use.
    MeshGeometry(MeshGeometryPrivate& dd, Node* pParent);
    VSN_DECLARE_EX_PRIVATE(MeshGeometry);
};

} // namespace VSN

#endif /* __VSN_MESHGEOMETRY_H */
