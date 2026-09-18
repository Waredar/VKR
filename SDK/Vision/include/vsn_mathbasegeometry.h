////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru NO TRANSLATION.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATHBASEGEOMETRY_H
#define __VSN_MATHBASEGEOMETRY_H

#include <vsn_meshgeometry.h>
#include <vsn_string.h>
#include <vsn_global.h>

namespace VSN {

static String C3D_PATHITEM_ID = String("C3D_PATHITEM_ID");

class MathBaseGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION. \n.
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MathBaseGeometry : public MeshGeometry
{
    VSN_OBJECT(MathBaseGeometry);
public:
    /// \ru Структура данных при запросе индентификаторов соответствия. \en Structure of data when requesting compatibility identificators. \~
    struct InfoPrimitive
    {
        InfoPrimitive() : m_type(ObjectType::None) , m_id(-1) {}
        InfoPrimitive(ObjectType type, uint id) : m_type(type) , m_id(id) {}
        ObjectType m_type; ///< \ru Тип примитива. \en Primitive type. \~
        uint32     m_id;   ///< \ru Идентификатор примитива. \en Primitive identifier. \~
    };
protected:
    /// \ru Деструктор. \en Destructor. \~
    virtual ~MathBaseGeometry();
public: 
    /// \ru Получить тип построения сетки. \en Returns mesh building type. \~
    CommandType GetBuildType() const;
    /// \ru Задать тип построения сетки. \en Sets mesh building type. \~
    void SetBuildType(CommandType type);
    /// \ru Очистить в этой геометрии все примитивы. \en Clears all primitives of this geometry. \~
    void Clear() override;
    /// \ru Очистить все математические примитивы этой геометрии. \en Clear all mathematical primitives of this geometry. \~
    virtual void ClearAllMathPrimitives();

    /// \ru Вернуть математический идентификатор примитива по уникальному идентификатору этой геометрии. \en Returns a math identifier of primitive by the unique identifier of this geometry. \~
    InfoPrimitive QueryMathByGeometry(uint geomId) const;
    /// \ru Вернуть геометрический идентификатор примитива по уникальному идентификатору математического примитива. \en Returns a geometric identifier of primitive by the unique identifier of math primitive. \~
    InfoPrimitive QueryGeomByMath(uint mathId) const;
    /// \ru Вернуть указатель на математический примитив по уникальному идентификатору математического примитива. \en NO TRANSLATION. \~
    const MbTopologyItem* QueryPrimitiveItemByMathId(uint mathId) const;
    /// \ru Вернуть указатель на математический примитив по уникальному идентификатору примитива в этой геометрии. \en NO TRANSLATION. \~
    const MbGrid* QueryGridByGeometry(uint geomPrimId) const;
    /// \ru Вернуть кэш материалов для повторного использования. \en Return the content cache for reuse. \~
    MaterialCachePtr GetMaterialCache() const;
    /// \ru Установить кэш материалов для повторного использования. \en Set a cache of materials for reuse. \~
    void SetMaterialCache(MaterialCachePtr pCache);
private:
    /// \ru Перестроить тело. \en Rebuilds a solid body. \~
    void slotDataModified(const std::vector<float>& bytes);
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION.
    MathBaseGeometry(MathBaseGeometryPrivate& dd, Node* pParent);
private:
    VSN_DISABLE_COPY(MathBaseGeometry);
    VSN_DECLARE_EX_PRIVATE(MathBaseGeometry);
    friend class MathGeometryBuilder;
};

} // namespace VSN

#endif /* __VSN_MATHBASEGEOMETRY_H */
