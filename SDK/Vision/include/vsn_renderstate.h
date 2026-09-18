////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс Renderstate представляет состояние отрисовки объекта.
         \en Renderstate class represents an object rendering state. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_RENDERSTATE_H
#define __VSN_RENDERSTATE_H

#include <set>
#include <unordered_map>

#include <vsn_material.h>
#include <vsn_namespace.h>
#include <vsn_math.h>
#include <vsn_global.h>

namespace VSN {

/* Hit */
struct Hit
{
    ObjectType typeObject;
    NodeKey key;
    int geometryIdx;
    NodeKey geometryKey;
    NodeKey geometryItemKey;
    uint primitiveId;

    Hit() : typeObject(ObjectType::None), key(NodeKey::ZERO), geometryIdx(-1), geometryKey(NodeKey::ZERO), geometryItemKey(NodeKey::ZERO), primitiveId(0) {}
    Hit(ObjectType tObject, const NodeKey& k, int geomIdx, NodeKey geomKey, NodeKey geoItemKey, uint primId) : typeObject(tObject), key(k), geometryIdx(geomIdx), geometryKey(geomKey), geometryItemKey(geoItemKey), primitiveId(primId) {}

    inline bool IsValid() const;
    inline bool operator!=(const Hit& h) const;
    inline bool operator==(const Hit& h) const;
};

inline bool Hit::IsValid() const { return key != NodeKey::ZERO; }

inline bool Hit::operator != (const Hit& h) const { return !(*this == h); }
inline bool Hit::operator == (const Hit& h) const
{
    return typeObject == h.typeObject && key == h.key &&
        geometryIdx == h.geometryIdx && geometryKey == h.geometryKey &&
        geometryItemKey == h.geometryItemKey && primitiveId == h.primitiveId;
}

typedef std::vector<Hit> HitList;

class RenderStatePrivate;
class CuttingUtil;
//------------------------------------------------------------------------------
/** \brief  \ru Состояние отрисовки объекта.
            \en Object rendering state.
    \details  \ru Класс RenderState хранит состояние отрисовки и предоставляет
                  функции для управления режимами отрисовки объектов RenderObject.
              \en RenderState class stores a rendering state and provides 
                  functions to control RenderObject object rendering modes. \~
*/
//---
class VSN_CLASS RenderState
{
public: /** \ru \name Конструкторы.
            \en \name Constructors.
            \{ */

    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    RenderState();
    /// \ru Конструктор копирования. \en Copy constructor. \~
    RenderState(const RenderState& other);
    /// \ru Деструктор. \en Destructor.
    ~RenderState();
public: /** \}
            \ru \name Функции получения/задания свойств отрисовки.
            \en \name The functions to return/set rendering properties.
            \{ */

    /// \ru Вернуть текущее состояние отрисовки. \en Returns the current rendering state. \~
    RenderingState GetRenderingState() const;

    /** \brief \ru Установить состояние отрисовки.
               \en Sets the rendering state.
        \details \ru Одно из следующих значений отрисовки: NormalRenderState, PrimitiveSelectedState, BodySelectionState и PrimitiveSelectionState.
                 \en One of the following rendering values: NormalRenderState, PrimitiveSelectedState, BodySelectionState and PrimitiveSelectionState.
    */
    void  SetRenderingState(RenderingState state);

    /** \brief \ru Вернуть собственное состояние отрисовки. 
               \en Returns the proper rendering state. \~
        \details \ru Функция возвращает собственное состояние отрисовки, присущее данному 
                    объекту вне зависимости от его временных состояний, таких как режим подсветки 
                    или выбор.
                 \en The function returns the proper rendering state that belongs to given 
                     object not depending on its temporary states such as highlight mode and selection. \~
    */
    RenderingState GetProperRenderingState() const;

    /// \ru Вернуть текущее состояние отрисовки. \en Returns the current rendering state. \~
    RenderingState GetRenderingSpecialState() const;

    /** \brief \ru Установить состояние отрисовки.
               \en Sets the rendering state.
        \details \ru Одно из следующих значений отрисовки: NormalRenderState, SpecialMaterialState, SpecialTransparencyState, SpecialMaterialTransparencyState и SpecialMaterialPrimitiveState.
                 \en One of the following rendering values: NormalRenderState, SpecialMaterialState, SpecialTransparencyState, SpecialMaterialTransparencyState и SpecialMaterialPrimitiveState.
    */
    void  SetRenderingSpecialState(RenderingState state);

    /** \brief \ru Вернуть значение режима отрисовки для граней.
               \en Returns rendering mode value for faces. \~ 
        \return \ru Одно из следующих значений отрисовки: GL_FRONT_AND_BACK, GL_FRONT или GL_BACK.
                \en One of the following rendering values: GL_FRONT_AND_BACK, GL_FRONT and GL_BACK. \~
    */
    DrawBufferMode GetPolyFaceMode() const;

    /** \brief \ru Вернуть значение режима отрисовки для полигонов.
               \en Returns rendering mode value for polygons.
        \return \ru Одно из следующих значений отрисовки: GL_POINT, GL_LINE или GL_FILL.
                \en One of the following rendering values: GL_POINT, GL_LINE and GL_FILL.
    */
    PolygonMode GetPolygonMode() const;

    /** \brief \ru Установить режим отображения для граней и полигонов.
               \en Sets rendering mode for faces and polygons. \~
        \param[in] fMode - \ru Режим отрисовки для граней с одним из следующих значений: GL_FRONT_AND_BACK, GL_FRONT, and GL_BACK.
                            \en Rendering mode for faces with one of the following values: GL_FRONT_AND_BACK, GL_FRONT, and GL_BACK. \~
        \param[in] pMode - \ru Режим отрисовки для кривых с одним из следующих значений: GL_POINT, GL_LINE, or GL_FILL.
                           \en Rendering mode for curves with one of the following values: GL_FRONT_AND_BACK, GL_FRONT, and GL_BACK. \~
    */  
    void SetPolygonMode(DrawBufferMode fMode, PolygonMode pMode);

    /// \ru Вернуть текущий режим визуализации модели. \en Returns the current model visualization mode. \~
    RenderMode  GetRenderingMode() const;

    /// \ru Установить текущий режим визуализации модели. \en Sets the current model visualization mode. \~
    void SetRenderingMode(RenderMode mode);

    /// \ru Вернуть true, если текущий режим требует отрисовки с прозрачностью. \en Returns True if the current mode requires transparency rendering. \~
    bool IsTransparencyRequired() const;

    /// \ru Вернуть текущий индекс геометрической части. \en Returns the current index of geometry part. \~
    int GetCurrentBodyIndex() const;

    /// \ru Задать текущий индекс геометрической части. \en Sets the current index of geometry part. \~
    void SetCurrentBodyIndex(int partIdx);

    // \ru Вернуть true, если состояние визуализации имеет значение по умолчанию. \en True if visualization state has the default value. \~
    bool IsRenderStateDefault() const;
public: /** \}
            \ru \name Функции работы с материалом.
            \en \name The functions for working with material.
            \{ */

    /** \brief \ru Вернуть указатель на другой материал, отличный от исходного. 
                \en Returns pointer to other material that is different from the source. \~
    */
    Material* GetSpecialMaterial() const;

    /** \brief \ru Задать другой материал, отличный от исходного.
               \en Sets other material that is different from the source. \~
    */
    void SetSpecialMaterial(Material* pMaterial);

    /** \brief \ru Установить прозрачность специального материала.
               \en Sets transparency for the special material. \~
    */
    void SetSpecialMaterialTransparency(float alpha);

    /** \brief \ru Вернуть прозрачность специального материала.
               \en Returns transparency for the special material. \~
    */
    float GetSpecialTransparency() const;

    /** \brief \ru Добавить специальный материал для примитива.
                \en Adds special material for primitive. \~
        \param[in] id - \ru Идентификатор примитива.
                        \en Primitive identifier. \~      
        \param[in] mat- \ru Указатель на идентификатор примитива.
                        \en Pointer to primitive identifier. \~      
        \param[in] partIdx - \ru Индекс геометрической части.
                            \en Geometry part index. \~ 
    */
    void AddSpecialMaterial(uint id, Material* mat, int partIdx = 0);

    /// \ru Очистить специальные материалы. \en Clears special materials.
    void ClearSpecialMaterials();

    /** \brief \ru Вернуть контейнер специальных материалов текущей геометрической части.
               \en Returns special material container of the current geometry part. \~
        \details \ru Функция возвращает таблицу указателей на специальные материалы и 
                    идентификаторы примитивов текущей геометрической части. 
                 \en The function returns pointer map to special materials and 
                     primitive identifiers of the current geometry part. \~
    */
    std::unordered_map<uint, Material*>* GetSpecialMaterials() const;

    /// \ru Вернуть true, если нет специальных материалов. \en True if no special materials. \~
    bool IsSpecialMaterialsEmpty() const;

    /// \ru Применить указанный материал. \en Applies the specified material. \~
    void ApplyMaterial(Material* pMaterial);

    /// \ru Исключить указанный материал. \en Excludes the specified material. \~
    void ExcludeMaterial(Material* pMaterial);
public: /** \}
            \ru \name Функции управления выбором.
            \en \name Selection control functions.
            \{ */

    /// \ru Вернуть массив подсвеченных объектов. \en Returns highlighted objects array. \~
    std::unordered_map<int, uint>* GetHighlightedPrimitives() const;

    /** \brief \ru Вернуть true, если примитив является выбранным.
               \en True if primitive is selected.
      \param[in] id - \ru Идентификатор примитива.
                      \en Primitive identifier. \~
    */
    bool IsHighlightedPrimitive(uint id) const;

    /// \ru Вернуть true, если нет подсвеченых объектов. \en Returns true if there are no highlighted objects. \~
    bool IsHighlightedPrimitiveEmpty() const;

    /// \ru Вернуть true, если массив подсвеченных примитивов пуст. \en True if array of highlighted primitives is empty. \~
    bool IsNoHighlightedPrimitive() const;

    /** \brief \ru Вернуть идентификатор подсвеченного примитива текущей геометрической части.
               \en Returns identifier of highlighted primitive of the current geometry part.\~
    */
    uint GetHighlightedPrimitive(int body) const;

    /** \brief \ru Добавить подсвеченый примитив по идентификатору и индексу геометрической части.
               \en Adds primitive by identifier and geometry part index to highlight. \~
    */
    void SetHighlightedPrimitiveId(uint, int body = 0);

    /** \brief \ru Удалить примитив по идентификатору и индексу геометрической части.
               \en Remove primitive by identifier and geometry part index to selection. \~
    */
    void RemoveHighlightedPrimitiveId(uint id, int body);

    /// \ru Вернуть true, если текущий режим отрисовки является подсвеченым. \en True if the current rendering mode is highlighted. \~
    bool IsHighlighted() const;

    /// \ru Установить/Сбрость подсветки. \en Sets/Resets highlighted. \~
    void SetHighlighted(bool selected);

    /// \ru Вернуть true, если текущий режим отрисовки является выбранным. \en True if the current rendering mode is selected. \~
    bool IsSelected() const;

    /// \ru Установить/Сбрость выбор. \en Sets/Resets selection. \~
    void SetSelected(bool selected);

    /// \ru Отменить выбор. \en Unselect.
    void Unselect();
    /** \brief \ru Вернуть true, если примитив является выбранным.
               \en True if primitive is selected.
        \param[in] id - \ru Идентификатор примитива.
                        \en Primitive identifier. \~
    */
    bool IsSelectedPrimitive(uint id) const;

    /** \brief \ru Вернуть true, если примитив по этому идентификатору и индексу тела является выбранным.
               \en True if primitive by identifier and body index is selected. \~
        \param[in] id - \ru Идентификатор примитива.
                        \en Primitive identifier. \~
        \param[in] partIdx - \ru Индекс геометрической части.
                             \en Geometry part index. \~
    */
    bool IsSelectedPrimitive(int partIdx, uint id) const;

    /// \ru Вернуть true, если массив выбранных примитивов пуст. \en True if array of selected primitives is empty. \~
    bool IsNoSelectedPrimitive() const;

    /// \ru Вернуть массив идентификаторов выбранных примитивов текущей геометрической части. \en Returns identifier array of selected primitives of the current geometry part.\~
    std::set<uint>* GetSelectedPrimitives() const;

    /// \ru Добавить массив выбранных примитивов по идентификатору и индексу тела. \en Adds selected primitive array by identifier and body index. \~
    void AddSelectedPrimitivesId(const std::set<uint>&, int body = 0);
    /// \ru Добавить в выбор примитив по идентификатору и индексу геометрической части. \en Adds primitive by identifier and geometry part index to selection. \~
    bool AddSelectedPrimitiveId(uint, int body = 0);
    /// \ru Удалить примитив по идентификатору и индексу геометрической части. \en Remove primitive by identifier and geometry part index to selection. \~
    void RemoveSelectedPrimitiveId(uint id, int body);
    /// \ru Очистить выбранные примитивы. \en Clears all selected primitives. \~
    void ClearSelectedPrimitives();

    /// \ru Вернуть true, если группа является выбранной. \en NO TRANSLATION. \~
    bool IsSelectedGroupGeometry(const NodeKey& key) const;
    /// \ru Добавить в выбор группу по идентификатору и примитив. \en NO TRANSLATION. \~
    void AddSelectedGroupGeometry(const NodeKey& key, uint primId);
    /// \ru Удалить группу и примитив по идентификатору. \en NO TRANSLATION. \~
    void RemoveSelectedGroupGeometry(const NodeKey& key, uint primId);
    /// \ru Очистить выбранные группы. \en NO TRANSLATION. \~
    void ClearSelectedGroupGeometry();
    /// \ru Вернуть текущую групповую геометрию. \en NO TRANSLATION. \~
    static NodeKey GetCurrentSelectedGroupGeometry();
    /// \ru Установить текущую групповую геометрию. \en NO TRANSLATION. \~
    static void SetCurrentSelectedGroupGeometry(const NodeKey& key);
    /// \ru Сбросить текущую групповую геометрию. \en NO TRANSLATION. \~
    static void ResetCurrentSelectedGroupGeometry();

    /// \ru Вернуть true, если группа по этому идентификатору является подсвеченной. \en NO TRANSLATION. \~
    bool IsHighlightedGroupGeometry(const NodeKey& key) const;
    /// \ru Добавить в группу и примитив по идентификатору и индексу геометрической части. \en NO TRANSLATION. \~
    void AddHighlightedGroupGeometry(const NodeKey& key, uint primId);
    /// \ru Удалить группу и примитив по идентификатору и индексу геометрической части. \en NO TRANSLATION. \~
    void RemoveHighlightedGroupGeometry(const NodeKey& key, uint primId);
    /// \ru Очистить выбранные группы и примитивы для подсветки. \en NO TRANSLATION. \~
    void ClearHighlightedGroupGeometry();
    /// \ru Вернуть текущую групповую геометрию для подсветки. \en NO TRANSLATION. \~
    static NodeKey GetCurrentHighlightedGroupGeometry();
    /// \ru Установить текущую групповую геометрию для подсветки. \en NO TRANSLATION. \~
    static void SetCurrentHighlightedGroupGeometry(const NodeKey& key);
    /// \ru Сбросить текущую групповую геометрию для подсветки. \en NO TRANSLATION. \~
    static void ResetCurrentHighlightedGroupGeometry();
public:
    /// \ru Получить указатель на инструмент для отсечения. \en NO TRANSLATION. \~
    CuttingUtil* GetCuttingTool() const;
    /// \ru Установить указатель на инструмент для отсечения. \en NO TRANSLATION. \~
    void SetCuttingTool(CuttingUtil* tool);
    /// \ru Получить модельньную матрицу. \en NO TRANSLATION. \~
    const Matrix3DF & GetModelViewMatrix() const;
    /// \ru Установить модельньную матрицу. \en NO TRANSLATION. \~
    void SetModelViewMatrix(const Matrix3DF& mx);
    // получить масштаб
    double GetScale() const;
    // установить масштаб
    void SetScale(double scale);
public: /** \} */
    /** \brief  \ru Очистить содержимое визуализации и обновить значения материалов.
                \en Clears visualization content and update material values. \~
    */
    void Clear();
    /// \ru Оператор присвоения. \en Assignment operator.
    RenderState & operator = ( const RenderState & );
private:
    friend class InstCustomItem;
    VSN_DECLARE_PRIVATE(RenderState)
};

} // namespace VSN

#endif /* __VSN_RENDERSTATE_H */
