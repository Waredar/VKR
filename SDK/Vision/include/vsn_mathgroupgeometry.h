////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс MathGroupGeometry для отрисовки сгруппированных полигональных объектов.
         \en The MathGroupGeometry class is for drawing grouped polygon object. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATHGROUPGEOMETRY_H
#define __VSN_MATHGROUPGEOMETRY_H

#include <model_item.h>
#include <assembly.h>
#include <topology_item.h>
#include <vsn_mathbasegeometry.h>
#include <vsn_global.h>

namespace VSN {

class MathGroupGeometry;
class MathGroupItemPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MathGroupItem предоставляет элемент для использования с классом MathGroupGeometry.
           \en The MathGroupItem class provides an item for use with the MathGroupGeometry class. \~
  \details \ru MathGroupItem представляет отдельный элемент для MathGroupGeometry. Каждый элемент может 
               содержать определенную информацию для его отображения соответствующим образом. \n.
           \en MathGroupItem represents a single element for MathGroupGeometry. Each element can
               contain certain information to appropriately display it. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MathGroupItem
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit MathGroupItem(MathGroupGeometry* pGeometry, const MbItem* pItem, 
        const MbMatrix3D& mx, float sag = static_cast<float>(Math::visualSag));
    /// \ru Деструктор. \en Destructor. \~
    ~MathGroupItem();
public:
    /// \ru Вернуть указатель на MathGroupGeometry, который содержит список этих элементов. \en Return a pointer to a MathGroupGeometry that contains a list of these elements. \~
    MathGroupGeometry* GetGroupGeometry() const;
    /// \ru Вернуть ключ, идентифицирующий этот элемент. \en Return a key identifying this element. \~
    NodeKey GetUniqueKey() const;
    
    /// \ru Вернуть true, если этот элемент скрыт, в противном случае вернуть false. \en Return true if this element is hidden, otherwise return false. \~
    bool IsHidden() const;
    /// \ru Скрыть элемент, если hide имеет значение true, в противном случае элемент показать. \en Hide the element if hide is true, otherwise show the element. \~
    void SetHidden(bool hide);

    /// \ru Вернуть текст элемента. \en Return the text of the element. \~
    String GetText() const;
    /// \ru Установить текст для этого элемента. \en Set text for this element. \~
    void SetText(const String& text);

    /// \ru Вернуть путь в модели MbItem, если такой имеется. \en Return the path of the element. \~
    const MbPath& GetPath() const;
    /// \ru Установить путь в модели MbItem. \en Set path for this element. \~
    void SetPath(const MbPath& path);

    /// \ru Вернуть указатель на математическое представление. \en Return a pointer to the mathematical representation. \~
    const MbItem* GetItem() const;

    /// \ru Выдать матрицу этого элемента. \en Return the matrix of this element. \~
    Matrix3DFPtr GetMatrix() const;
    /// \ru Установить матрицу этому элементу. \en Return a matrix to this element. \~
    void SetMatrix(const Matrix3DF& mx);
    /// \ru Сбросить матрицу в ноль для этого элемента. \en Reset the matrix to zero for this element. \~
    void ResetMatrix();

    /// \ru Выдать значение точности расчета полигонов для этого элемента. \en Return polygon calculation accuracy value for this element. \~
    float GetVisualSag() const;
    /// \ru Установить значение точности расчета полигонов для этого элемента. \en Set polygon calculation accuracy value for this element. \~
    void SetVisualSag(float sag = static_cast<float>(Math::visualSag));

    /// \ru Вернуть указатель на материал MathGroupItem. \en Return pointer to MathGroupItem material. \~
    Material* GetMaterial() const;
    /// \ru Вернуть указатель на специальный материал MathGroupItem. \en Return pointer to MathGroupItem special material. \~
    Material* GetSpecialMaterial() const;
    /// \ru Вернуть true, если специальный материал есть для MathGroupItem. \en Return true if there is a special material for MathGroupItem. \~
    bool IsExistSpecialMaterial() const;

    /// \ru Вернуть флаг игнорирования цвета специального материала. \en Return the flag to ignore the color of the special material. \~
    bool IsIgnoreSpecialMaterialColor() const;
    /// \ru Установить флаг игнорировать цвет специального материала. \en Set the flag to ignore the color of the special material. \~
    void SetIgnoreSpecialMaterialColor(bool ignore);

    /// \ru Вернуть флаг игнорирования прозрачности специального материала. \en Return the flag to ignore the transparency of the special material. \~
    bool IsIgnoreSpecialMaterialTransparency() const;
    /// \ru Установить флаг игнорировать прозрачность специального материала. \en Set the flag to ignore the transparency of the special material. \~
    void SetIgnoreSpecialMaterialTransparency(bool ignore);

    /// \ru Создать материал для MathGroupItem. \en Create special material for MathGroupItem. \~
    Material* CreateSpecialMaterial();
    /// \ru Удалить специальный материал в MathGroupItem. \en Delete special material for MathGroupItem. \~
    void DeleteSpecialMaterial();
private:
    MathGroupItemPrivate* m_dataPrivate;
private:
    friend class MathGroupItemPrivate;
    VSN_DISABLE_COPY(MathGroupItem);
};

class RenderState;
class MathGroupGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MathGroupGeometry для отрисовки сгруппированных полигональных объектов.
           \en The MathGroupGeometry class for drawing grouped polygon objects. \~
    \details \ru Класс MathGroupGeometry позволяет создать группу объектов из математического 
                 представления для последующей их отрисовки. MathGroupGeometry имеет ряд вспомогательного 
                 функционала, который позволяет управлять видимостью, местоположением, а также удалением 
                 или добавлением элементов. MathGroupGeometry реализованы вспомогательные функции,
                 которые позволяют получить по идентификатору примитива или элемента вставленный элемент
                 для последующей его модификации.\n.
             \en The MathGroupGeometry class allows you to create a group of objects from a mathematical
                 representations for their subsequent rendering. MathGroupGeometry has a number of helpers
                 functionality that allows you to control visibility, location, and removal
                 or adding elements. MathGroupGeometry also implements helper functions,
                 which allow you to get the inserted element by the identifier of the primitive or element
                 for later modification. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MathGroupGeometry : public MathBaseGeometry
{
    VSN_OBJECT(MathGroupGeometry);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit MathGroupGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~MathGroupGeometry() override;
public:
    /// \ru Вернуть массив указателей на все элементы. \en Return an array of pointers to all elements. \~
    const ObjectList<MathGroupItem*>& GetItems() const;
    /// \ru Добавить указатель на математическое представление MbItem. \en Add pointer to mathematical representation of MbItem. \~
    MathGroupItem* AddItem(const MbItem* pItem, const MbMatrix3D& mx, float sag = static_cast<float>(Math::visualSag));
    /// \ru Добавить указатель на математическое представление MbAssembly (только один уровень). \en Add pointer to mathematical representation of MbAssembly. \~
    ObjectList<MathGroupItem*> AddItems(const MbAssembly* pAssembly, float sag = static_cast<float>(Math::visualSag));
    /// \ru Добавить массив указателей на математическое представление MbItem. \en Add an array of pointers to mathematical representation of MbItem. \~
    ObjectList<MathGroupItem*> AddItems(const ObjectList<const MbItem*>& pItems,
        const std::vector<MbMatrix3D>& mxs, const std::vector<float>& sags);
    /// \ru Удалить массив элементов по идентификатору. \en Delete an array of elements by id. \~
    void DeleteItems(const std::vector<NodeKey>& itemKeys);

    /// \ru Вернуть указатель на материал по уникальному идентификатору MathGroupItem. \en Return a pointer to the material by unique identifier of MathGroupItem. \~
    Material* GetMaterialItem(const NodeKey& itemKey) const;
    /// \ru Вернуть указатель на специальный материал по уникальному идентификатору MathGroupItem. \en Return a pointer to the special material by unique identifier of MathGroupItem. \~
    Material* GetSpecialMaterialItem(const NodeKey& itemKey) const;
    /// \ru Вернуть true, если специальный материал есть для MathGroupItem. \en Return true if there is a special material for MathGroupItem. \~
    bool IsExistSpecialMaterialItem(const NodeKey& itemKey) const;

    /// \ru Вернуть флаг игнорирования цвета специального материала. \en Return the flag to ignore the color of the special material. \~
    bool IsIgnoreSpecialMaterialColorItem(const NodeKey& itemKey) const;
    /// \ru Установить флаг игнорировать цвет специального материала. \en Set the flag to ignore the color of the special material. \~
    void SetIgnoreSpecialMaterialColorItem(const NodeKey& itemKey, bool ignore);

    /// \ru Вернуть флаг игнорирования прозрачности специального материала. \en Return the flag to ignore the transparency of the special material. \~
    bool IsIgnoreSpecialMaterialTransparencyItem(const NodeKey& itemKey) const;
    /// \ru Установить флаг игнорировать прозрачность специального материала. \en Set the flag to ignore the transparency of the special material. \~
    void SetIgnoreSpecialMaterialTransparencyItem(const NodeKey& itemKey, bool ignore);

    /// \ru Создать материал по уникальному идентификатору MathGroupItem. \en Create material by unique id of MathGroupItem. \~
    Material* CreateSpecialMaterial(const NodeKey& itemKey);
    /// \ru Удалить специальный материал по уникальному идентификатору MathGroupItem. \en Delete material by unique id of MathGroupItem. \~
    void DeleteSpecialMaterial(const NodeKey& itemKey);
    /// \ru Удалить все специальные материалы. \en Delete all special materials. \~
    void DeleteAllSpecialMaterial();

    // \ru Вернуть true, если будет создано Wireframe представление. \en Return true if a Wireframe view is created. \~
    bool IsBuildWireframe() const;
    // \ru Создать Wireframe представление для каждого Item, если есть данные для этого. \en Create a Wireframe view for each Item, if there is data to do so. \~
    void SetBuildWireframe(bool bBuild);

    /// \ru Вернуть указатель на groupitem по уникальному идентификатору MathGroupItem. \en Return pointer to groupitem by unique id of MathGroupItem. \~
    MathGroupItem* QueryGroupGeomByItem(const NodeKey& key) const;
    /// \ru Вернуть указатель на groupitem по уникальному идентификатору примитива. \en NO Return pointer to groupitem by unique id of primitive. \~
    MathGroupItem* QueryGroupGeomByGeom(uint32 id) const;
public:
    /// \ru Перестроить геометрию по измененному MbItem. \en Rebuild geometry by modified MbItem. \~
    void RebuildGeometry();
public:
    /// \ru Очистить в этой геометрии все примитивы. \en Clears all primitives of this geometry. \~
    void Clear() override;
    /// \ru Получить габаритный куб объекта. \en Returns object bounding box. \~
    const BoundingBox& GetBoundingBox() const override;
    /// \ru Обновить геометрию по новым данным для внутреннего использования. \en Updates geometry with new data for inner using. \~
    void UpdateGeometry() override;
    /// \ru Обновить число прозрачных материалов после операций с таблицей. \en Updates transparent material count after table operations.
    void UpdateTransparentMaterialCount() override;
    /// \ru Найти объекты, которые находятся в указанной области. \en Find objects that are in the specified area. \~
    void PickObjectsInsideRect(const MbRect& rect, const Matrix3DF& viewMatrix, 
        const Matrix3DF& mx, Filter filter, bool bUnifying, HitList& hits) override;
public:
    /// \ru Установить максимально допустимый прогиб кривой или поверхности в соседних точках на расстоянии шага.
    /// \en Sets the maximum permissible sag of a curve or surface at adjacent points a step away. \~
    VSN_SLOT(Public, SetVisualSag, void SetVisualSag(float sag))
public:
    /// \ru Сигнал модификации шага расчета триангуляции. \en Signal about modifying step of triangulation computing. \~
    VSN_SIGNAL(Public, OnVisualSagModified, void OnVisualSagModified(float sag), sag)
private:
    /// \ru Перестроить тело. \en Rebuilds a solid body. \~
    void slotDataModified(const std::vector<float>& bytes);
    /// \ru Отрисовка тела. \en Renders a solid body. \~
    void OpenGLDraw(const RenderState& state) override;
    /// \ru Выполнить отрисовку. \en Performs rendering.
    void Render(RenderContext&) override;
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for internal use.
    MathGroupGeometry(MathGroupGeometryPrivate& dd, Node* pParent);
private:
    VSN_DISABLE_COPY(MathGroupGeometry);
    VSN_DECLARE_EX_PRIVATE(MathGroupGeometry);
    friend class MathGeometryBuilder;
};

} // namespace VSN

#endif /* __VSN_MATHGROUPGEOMETRY_H */
