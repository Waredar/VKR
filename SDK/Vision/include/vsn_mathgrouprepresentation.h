////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс MathGroupRepresentation является вспомогательным классом и представляет 
             API для управления геометрией.
         \en MathGroupRepresentation class is an auxiliary class and represents API to control geometry. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATHGROUPREPRESENTATION_H
#define __VSN_MATHGROUPREPRESENTATION_H

#include <vsn_mathgroupgeometry.h>
#include <vsn_geometryrep.h>
#include <vsn_global.h>

class MbItem;

namespace VSN {

class MathGroupRepresentationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MathGroupRepresentation является вспомогательным классом и представляет API для управления геометрией.
           \en MathGroupRepresentation class is an auxiliary class and represents API to control geometry. \~
  \details \ru MathGroupRepresentation создает MathGroupGeometry и содержит его указатель на протяжение всей своей жизни.
               MathGroupRepresentation представляет ряд полезных функций для управления своей геометрией. \n.
           \en MathGroupRepresentation class creates MathGroupGeometry and contains its pointer during its whole existing.
               MathGroupRepresentation class presents a set of useful functions to control its geometry. \n \~
  \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MathGroupRepresentation : public GeometryRep
{
    VSN_OBJECT(MathGroupRepresentation);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    MathGroupRepresentation(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    ~MathGroupRepresentation() override;
public:
    /// \ru Получить тип построения сетки. \en Get a build type. \~
    CommandType GetBuildType() const;
    /// \ru Задать тип построения сетки. \en Change a build type. \~
    void SetBuildType(CommandType type);

    /// \ru Вернуть указатель на геометрию. \en NO TRANSLATION. \~
    MathGroupGeometry* GetGeometry() const;
    /// \ru Вернуть массив указателей на все элементы. \en NO TRANSLATION. \~
    const ObjectList<MathGroupItem*>& GetItems() const;
    /// \ru Добавить указатель на математическое представление MbItem. \en NO TRANSLATION. \~
    MathGroupItem* AddItem(const MbItem* pItem, const MbMatrix3D& mx, 
        float sag = static_cast<float>(Math::visualSag), bool bRebuild = true);
    /// \ru Добавить указатель на математическое представление MbAssembly (только один уровень). \en NO TRANSLATION. \~
    ObjectList<MathGroupItem*> AddItems(const MbAssembly* pAssembly, 
        float sag = static_cast<float>(Math::visualSag));
    /// \ru Добавить массив указателей на математическое представление MbItem. \en NO TRANSLATION. \~
    ObjectList<MathGroupItem*> AddItems(const ObjectList<const MbItem*>& pItems,
        const std::vector<MbMatrix3D>& mxs, const std::vector<float>& sags);
    /// \ru Удалить массив элементов по идентификатору. \en NO TRANSLATION. \~
    void DeleteItems(const std::vector<NodeKey>& itemKeys);
    /// \ru Выдать указатель на материал по уникальному идентификатору MathGroupItem. \en NO TRANSLATION. \~
    Material* GetMaterialItem(const NodeKey& itemKey) const;
    /// \ru Выдать указатель на специальный материал по уникальному идентификатору MathGroupItem. \en NO TRANSLATION. \~
    Material* GetSpecialMaterialItem(const NodeKey& itemKey) const;
    /// \ru Вернуть true, если специальный материал есть для MathGroupItem. \en NO TRANSLATION. \~
    bool IsExistSpecialMaterialItem(const NodeKey& itemKey) const;
    /// \ru Вернуть флаг игнорирования цвета специального материала. \en NO TRANSLATION. \~
    bool IsIgnoreSpecialMaterialColorItem(const NodeKey& itemKey) const;
    /// \ru Установить флаг игнорировать цвет специального материала. \en NO TRANSLATION. \~
    void SetIgnoreSpecialMaterialColorItem(const NodeKey& itemKey, bool ignore);
    /// \ru Вернуть флаг игнорирования прозрачности специального материала. \en NO TRANSLATION. \~
    bool IsIgnoreSpecialMaterialTransparencyItem(const NodeKey& itemKey) const;
    /// \ru Установить флаг игнорировать прозрачности специального материала. \en NO TRANSLATION. \~
    void SetIgnoreSpecialMaterialTransparencyItem(const NodeKey& itemKey, bool ignore);
    /// \ru Создать материал по уникальному идентификатору MathGroupItem. \en NO TRANSLATION. \~
    Material* CreateSpecialMaterial(const NodeKey& itemKey);
    /// \ru Удалить специальный материал по уникальному идентификатору MathGroupItem. \en NO TRANSLATION. \~
    void DeleteSpecialMaterial(const NodeKey& itemKey);
    /// \ru Удалить все специальные материалы. \en NO TRANSLATION. \~
    void DeleteAllSpecialMaterial();

    // \ru Вернуть true, если будет создано Wireframe представление. \en Return true if a Wireframe view is created. \~
    bool IsBuildWireframe() const;
    // \ru Создать Wireframe представление для каждого Item, если есть данные для этого. \en Create a Wireframe view for each Item, if there is data to do so. \~
    void SetBuildWireframe(bool bBuild);

    /// \ru Получить толщину линии(перегружены для удобства). \en Returns line width(functions are overloaded for convenience). \~
    float GetLineWidth() const;
    /// \ru Задать толщину линии(перегружены для удобства). \en Sets line width(functions are overloaded for convenience). \~
    void SetLineWidth(float lineWidth);

    /// \ru Получить перо. \en Get pen. \~
    Pen GetPen() const;
    /// \ru Задать перо. \en Set pen. \~
    void SetPen(const Pen& pen);

    /// \ru Выдать указатель на groupitem по уникальному идентификатору MathGroupItem. \en NO TRANSLATION. \~
    MathGroupItem* QueryGroupGeomByItem(const NodeKey& key) const;
    /// \ru Выдать указатель на groupitem по уникальному идентификатору примитива. \en NO TRANSLATION. \~
    MathGroupItem* QueryGroupGeomByGeom(uint32 id) const;
public:
    /// \ru Перестроить геометрию по измененному MbItem. \en Rebuild geometry by modified MbItem. \~
    void RebuildGeometry();
protected:
    /// \ru Эта функция вызывается, если произошли какие-либо изменения в сцене (для внутреннего использования). \en The function is called if the scene was modified, for inner using. \~
//    virtual void SceneModificationEvent(const std::shared_ptr<SceneModification>& modification) override;
private:
    VSN_DECLARE_EX_PRIVATE(MathGroupRepresentation);
};

} // namespace VSN

#endif /* __VSN_MATHGROUPREPRESENTATION_H */
