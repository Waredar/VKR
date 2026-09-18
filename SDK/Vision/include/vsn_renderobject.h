////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс RenderObject содержит GeometryRep + bounding box.
         \en RenderObject class contains GeometryRep + bounding box. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_RENDEROBJECT_H
#define __VSN_RENDEROBJECT_H

#include <mb_cube.h>
#include <mb_matrix3d.h>

#include <vsn_mutex.h>
#include <vsn_node.h>
#include <vsn_renderstate.h>
#include <vsn_namespace.h>
#include <vsn_globalflags.h>
#include <vsn_geometryrep.h>

#include <vsn_global.h>

namespace VSN {

class Viewport;
class CuttingUtil;
typedef uint64 SectionPlaneId;
//------------------------------------------------------------------------------
/** \brief   \ru Класс RenderObject содержит GeometryRep + bounding box.
             \en RenderObject class contains GeometryRep + bounding box. \~
    \details \ru Класс RenderObject содержит GeometryRep + bounding box. \n
             \en RenderObject class contains GeometryRep + bounding box. \n \~
    \ingroup NO GROUP
*/
// ---
class VSN_CLASS RenderObject
{
public:
    // состояние видимости 
    enum VisibleState
    {
        Absolute_Visible = 300,  /// абсолютно видимый
        Relative_Visible = 301,  /// относительно видимый
        Absolute_Hide    = 302,  /// абсолютно невидимый
        Absolute_Visible_Pixel_Culling = 304, /// абсолютно видимый
        Absolute_Hide_Pixel_Culling    = 308, /// абсолютно невидимый
    };
public:
    /// \ru Специальный конструктор с инициализацией геометрического представления и идентификатором. \en Special constructor with initialization of geometry representation and the unique identifier. \~
    explicit RenderObject(GeometryRep* pRep, const NodeKey& key = NodeKey::GenerationKey());
    /// \ru Деструктор. \en Destructor. \~ 
    ~RenderObject();
public:
    /// \ru Вернуть ключ, идентифицирующий экземпляр Node. \en Returns key identifing Node instance. \~
    const NodeKey& GetUniqueKey() const { return m_key; }
    /// \ru Прозрачен ли весь объект. \en Checks if the whole object is transparent. \~
    bool IsTransparent() const;
    /// \ru Есть ли хотя бы одна прозрачная часть объекта. \en Checks if transparent parts of object exist (at least one part). \~
    bool IsExistTransparentMaterials() const;

    /// \ru Является ли объект пустым. \en Checks if object is empty. \~
    bool IsEmpty() const;
    /// \ru Выбран ли объект. \en Checks if object is selected. \~
    bool IsSelected() const;

    /// \ru Вернуть количество геометрии. \en Returns geometry count. \~
    int GetGeometryCount() const;
    /// \ru Вернуть геометрическую часть по индексу. \en Returns geometry part by index. \~
    Geometry* GetGeometryByIndex(size_t index) const;
    /// \ru Получить геометрическое представление объекта. \en Returns geometry representation of the object. \~
    const GeometryRep& GetRepresentation() const;
    /// \ru Вернуть массив геометрии. \en Returns an array of geometry. \~
    const ObjectList<Geometry*>& GetGeometry() const;

    /// \ru Получить копию габаритного куба объекта. \en Returns copy of object bounding box. \~
    const BoundingBox& GetBoundingBox();

    /// \ru Является ли габаритный куб действительным. \en Checks if bounding box is valid. \~
    bool IsBoundingBoxValid() const;

    /// \ru Вернуть абсолютную матрицу трансформации. \en Returns absolute transformation matrix. \~
    const Matrix3DF& GetMatrix() const;

    /** \brief \ru Вернуть режим отрисовки объекта.
               \en Returns object rendering mode. \~    
        \details \ru Вернуть режим отрисовки объекта. Режим может быть: GL_POINT, GL_LINE или GL_FILL. \n
                 \en Returns object rendering mode. It can be GL_POINT, GL_LINE or GL_FILL. \n \~
    */
    PolygonMode GetPolygonMode() const;

    /** \brief \ru Установить режим отображения полигонов в выбранном стиле.
               \en Sets polygon mapping mode in selected style. \~
       \details \ru Установить режим отображения полигонов в выбранном стиле. 
                    Режим сетки может быть: GL_FRONT_AND_BACK, GL_FRONT или GL_BACK.
                    Стиль может быть: GL_POINT, GL_LINE или GL_FILL. \n
                \en Sets polygon mapping mode in selected style.
                    Mesh mode can be GL_FRONT_AND_BACK, GL_FRONT or GL_BACK. 
                    The style can be GL_POINT, GL_LINE or GL_FILL. \n \~
    */
    void SetPolygonMode(DrawBufferMode face, PolygonMode mode);

    /// \ru Вернуть указатель на состояние отрисовки. \en Returns pointer to rendering state. \~
    RenderState* GetRenderState();
    /// \ru Вернуть ссылку на состояние отрисовки. \en Returns reference to rendering state. \~
    RenderState& GetRenderStateRef();
    /// \ru Установить состояние отрисовки для этого объекта. \en Sets rendering state for this object. \~
    void SetStateRender(const RenderState& renderState);

    /// \ru Является ли объект видимым. \en Checks if object is visible. \~
    bool IsVisible() const;
    /// \ru Установить видимость объекту. \en Sets visibility for object. \~
    void SetVisible(bool bVisible);

    /// \ru Вернуть состояние видимости объекта. \en Returns object visibility state. \~
    VisibleState GetVisibleState() const;
    /// \ru Установить состояние видимости объекта. \en Sets object visibility state.
    bool SetStateVisible(VisibleState state);

    /// \ru Является ли видимым объект, полученный по индексу. \en Checks if object received by index is visible.
    bool IsGeomVisibleByIndex(size_t index) const;
    /// \ru Установить видимость геометрии внутри этого объекта по индексу. \en Sets geometry visibility inside the object by index.
    void SetVisibleGeomByIndex(size_t index, bool bVisible);

    /// \ru Получить количество граней. \en Returns face count.
    size_t GetFaceCount() const;
    /// \ru Получить количество вершин. \en Returns vertex count.
    size_t GetVertexCount() const;

    /// \ru Вернуть количество материалов. \en Returns material count.
    size_t GetMaterialCount() const;
    /// \ru Вернуть массив материалов. \en Returns material array.
    std::set<Material*> GetMaterials() const;

    /// \ru Вернуть значение LOD по умолчанию. \en Returns the default value of LOD.
    int GetDefaultLevelOfDetail() const;
    /// \ru Установить значение LOD по умолчанию этому объекту. \en Sets the default value of LOD for this object.
    void SetDefaultLevelOfDetail(int value);

    /// \ru Вернуть представление объекта. \en Returns object representation.
    const GeometryRep* GetRepObject() const;
    /// \ru Вернуть глобальное значение уровня детализации. \en Returns the global value of LOD.
    static int GetGlobalDefaultLevelOfDetail();
    /// \ru Установить глобальное значение уровня детализации. \en Sets the global value of LOD.
    static void SetGlobalDefaultLevelOfDetail(int value);

    void SetRenderLayer(uint32_t);
    uint32_t GetRenderLayer() const;

    void SetNoScalable(bool);
    bool GetNoScalable() const;

    void SetScreenOnly(bool value);
    bool GetScreenOnly();

    void SetDisableForPick(bool value);
    bool IsDisabledForPick();

    void SetDoubleSidedLighting(bool value);
    bool IsDoubleSidedLighting() const;

    CullFaces GetFaceCulling() const;
    void SetFaceCulling(CullFaces);

    void SetRenderMode(RenderMode mode);
    RenderMode GetRenderMode() const;

    void SetCustomClipPlanes(const ObjectSet<SectionPlaneId> & ids);
    const ObjectSet<SectionPlaneId>&  GetCustomClipPlanes() const;
public:
    /// \ru Добавить новую геометрию. \en Adds new geometry.
    bool AddGeometry(Geometry* pGeometry);
    /// \ru Удалить пустую геометрию. \en Deletes empty geometry.
    void DeleteEmptyGeometry();
    /// \ru Инвертировать нормали геометрии. \en Reverses geometry normals.
    void ReverseNormalsOfGeometry();

    /// \ru Преобразовать объект по параметрам. \en Transforms object by parameters.
    RenderObject& Translate(float px, float py, float pz);

    /// \ru Установить абсолютную матрицу по матрице. \en Sets absolute matrix by specified matrix.
    RenderObject& SetMatrix(const Matrix3DF& mx);

    /// \ru Сбросить абсолютную матрицу до единичной. \en Resets absolute matrix to identity matrix.
    RenderObject& ResetMatrixToIdentityMatrix();

    /// \ru Установить признак выбранного объекта в геометрии. \en Sets flag of selected object in geometry.
    void SetSelect(bool primitive);
    /// \ru Снять выбор объекта в геометрии. \en Unselects object within geometry.
    void Unselect();

    /// \ru Установить идентификатор объекту. \en Sets identifier for object.
    void SetUniqueKey(const NodeKey& key);

    /// \ru Найти объекты, которые находятся в указанной область. \en NO TRANSLATION. \~
    void PickObjectsInsideRect(const MbRect& rect, const Matrix3DF& viewMatrix, Filter filter, bool bUnifying, HitList& hits);
public:
    /// \ru Отрисовать представления этого объекта в заданном режиме. \en Renders representation of the object in set mode.
    void OGLDrawGivenMode(RenderMode renderingMode = rm_Shaded, bool useLod = false, 
        const Viewport* pView = nullptr, CuttingUtil* cuttingTool = nullptr);
    /// \ru Отрисовка тела в режиме выбора. \en Renders body in selection mode.
    void OGLDrawBodySelectionMode();
    /// \ru Отрисовать примитивы объекта в режиме выбора по идентификатору тела и вернуть индекс тела. \en Renders object primitives in selection mode by body identifier and return body index.
    size_t OGLDrawPrimitiveSelectionMode(uint idBody);
private:
    // установить свойства визуализации объекта
    void SetVisualisationMode();
    // подсчитать габаритник всей геометрии и преобразовать его в матрицу объекта
    void CalcBoundingBox();
    // очистить этот объект
    void Clear();
    // подсчитать и выбрать уровень детализации для этого объекта
    int CalcChoseLevelOfDetail(const MbCube&, const Viewport*, bool);
    // подсчитать и выбрать уровень детализации для этого объекта c учетом ориентированного его габарита
    int CalcChoseLevelOfDetailOrientedBoundBox(const MbCube&, const Viewport*, bool);
    RenderingState PrepareSelectionState(RenderingState state);
    void ResetSelectionState(RenderState& renderState, RenderingState previousRenderMode);
private:
    GeometryRep* m_pRepresentation;       /// 3D представление объекта
    BoundingBox m_boundingBox;            /// габаритник представления
    Matrix3DF m_absoluteMatrix;           /// абсолютная матрица объекта
    RenderState m_renderState;            /// состояние визуализации объекта
    bool m_bIsVisible;                    /// признак видимости объекта
    int m_defaultLODetail;                /// значение уровня детализации по умолчанию
    VisibleState m_visibleState;          /// флаг видимости объекта
    std::vector<bool> m_visibleGeomFlags; /// массив признаков видимости объекта
    NodeKey m_key;
    uint32_t m_layer;
    bool m_noScalable;
    bool m_screenOnly;
    bool m_disableForPick;
    bool m_doubleSideLighting;
    CullFaces m_faceCullingMode;
    RenderMode m_renderMode;
    ObjectSet<SectionPlaneId> m_clipPlanes;

    static Mutex m_mutex;             /// Mutex
    static int g_defaultLevelDetail;  /// глобальное значение уровня детализации по умолчанию
private:
    friend class RenderContainerPrivate;
    friend class RenderContainer;
};

} // namespace VSN

#endif /* __VSN_RENDEROBJECT_H */
