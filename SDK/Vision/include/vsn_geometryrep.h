////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru 3D представление геометрии.
       \en 3D geometry representation. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GEOMETRYREP3D_H
#define __VSN_GEOMETRYREP3D_H

#include <set>
#include <mb_cube.h>

#include <vsn_wireframegeometry.h>
#include <vsn_geometrybuilder.h>
#include <vsn_global.h>

namespace VSN {

class Material;
class GeometryRepPrivate;
//------------------------------------------------------------------------------
/** \brief \ru 3D представление геометрических данных.
           \en 3D geometry data representation. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS GeometryRep : public Node
{
    VSN_OBJECT(GeometryRep);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GeometryRep(Node* pParent = nullptr);
    /// \ru Конструктор по геометрическим параметрам объекта. \en Constructor by geometry parameters of the object. \~
    GeometryRep(Geometry* pGeometry, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~GeometryRep();
public:
    /// \ru Является ли ссылка пустой. \en Checks if reference is empty. \~
    bool IsReferenceEmpty() const;
    /// \ru Является ли представление загруженным. \en Checks if representation is loaded. \~
    bool IsLoaded() const;

    GeometryBuilderPtr GetGeometryBuilder() const;
    void SetGeometryBuilder(const GeometryBuilderPtr& builder);

    TypeTriangulation GetPrimitiveType() const;
    void SetPrimitiveType(TypeTriangulation primitiveType);

    /// \ru Вернуть имя представления. \en Returns representation name. \~
    const String& GetNameRep() const;
    /// \ru Задать имя представления. \en Sets representation name. \~
    void SetNameRep(const String& name);

    /// \ru Вернуть геометрические данные по уникальному ключу. \en Returns geometry data by unique key. \~
    Geometry* GetGeomByKey(const NodeKey& key) const;
    /// \ru Вернуть геометрические данные по индексу. \en Returns geometry data by index. \~
    Geometry* GetGeomAt(size_t index) const;
    /// \ru Вернуть список геометрических данных. \en Returns geometry data list. \~
    const ObjectList<Geometry*>& GetGeomList() const;

    /// \ru Вернуть количество тел. \en Returns body count. \~
    size_t GetGeometryCount() const;

    /// \ru Вернуть true, если массив представлений пуст. \en True if representation array is empty. \~
    virtual bool IsEmpty() const;

    /// \ru Вернуть true, если ограничивающий габарит правильный. \en True if bounding box is valid. \~
    bool IsBoundingBoxValid() const;
    /// \ru Вернуть габарит представления. \en Returns bounding box of representation. \~
    BoundingBox GetBoundingBox() const;

    /// \ru Вернуть true, если представление содержит геометрические данные. \en True if representation contains geometry data. \~
    bool IsGeometryInRep(Geometry* pGeom);

    /// \ru Вернуть количество граней. \en Returns face count. \~
    VSN_DEPRECATED_X("Don't use this function, use Geometry::GetFaceCount.")
    size_t GetFaceCount() const;
    /// \ru Вернуть количество вершин. \en Returns vertex count. \~
    VSN_DEPRECATED_X("Don't use this function, use Geometry::GetVertexCount.")
    size_t GetVertexCount() const;
    /// \ru Вернуть количество материалов. \en Returns material count. \~
    size_t GetMaterialCount() const;
    /// \ru Вернуть набор материалов. \en Returns set of materials. \~
    std::set<Material*> GetMaterials() const;
    /// \ru Вернуть объем представления. \en Returns representation volume. \~
    float GetVolume() const;
public:
    /// \ru Добавить геометрические данные в представление. \en Adds geometry data to the representation. \~
    void AddGeometry(Geometry* pGeom);
    /// \ru Удалить пустые геометрические данные и обновить материалы. \en Deletes empty geometry data and update materials. \~
    void DeleteEmptyGeometry();
    /// \ru Удалить все геометрические данные. \en Deletes all geometry data. \~
    void Clear();
    /// \ru Сменить направление нормалей геометрии на противоположное. \en Reverses direction of all geometry normals. \~
    void ReverseNormals();
    /// \ru Заменить представление. \en Replaces the representation. \~
    virtual void ReplaceRep(GeometryRep* pRep);
    /// \ru Заменить указанный материал. \en Replaces the specified material. \~
    void ReplaceMaterialById(const NodeKey& oldKey, Material* pMaterial);
    /// \ru Преобразовать вершины сетки по данной матрице. \en Transforms mesh vertices by given matrix. \~
    void TransformGeometriesByMatrix(const Matrix3DF& matrix);
public:
    /// \ru Оператор присваивания. \en Assignment operator. \~
    virtual GeometryRep& operator = (const GeometryRep&);
public:
    VSN_SLOT(Public, OnDetachGeometry, void OnDetachGeometry(Geometry* pGeometry))
public:
    /// \ru Сигнал об окончании перестроения всей геометрии. \en Signal about the end of rebuilding the whole geometry. \~
    VSN_SIGNAL(Public, OnBuildCompleted, void OnBuildCompleted(Geometry* pGeometry), pGeometry)
protected:
    /// \ru Приватный конструктор для наследников. \en Private constructor for inheritors. \~
    GeometryRep(GeometryRepPrivate& dd, Node* parent = nullptr);
private:
    VSN_DECLARE_EX_PRIVATE(GeometryRep);
};

} // namespace VSN


#endif /* __VSN_GEOMETRYREP3D_H */
