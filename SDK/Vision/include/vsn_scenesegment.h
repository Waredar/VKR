////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс SceneSegment является базовым классом для всех сегментов в графе сцены.
         \en SceneSegment class is the base class for all segments in the scene graph. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SCENESEGMENT_H
#define __VSN_SCENESEGMENT_H

#include <set>
#include <mb_cube.h>
#include <vsn_essence.h>
#include <vsn_transform.h>
#include <vsn_scsegmentdata.h>
#include <vsn_global.h>

namespace VSN {

class Material;
class RenderState;
class SceneSegmentRef;
class SceneSegmentPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс SceneSegment является базовым классом для всех сегментов в графе сцены.
           \en SceneSegment class is the base class for all segments in the scene graph.  \~
  \details \ru Класс SceneSegment может быть использован как контейнер сегментов. Входящие сегменты добавляются с помощью функций AddSegment() и InsertSegment().
               Порядок сегментов является важным, так как геометрические сегменты отрисовываются в соответствии с их положением в графе сцены.

               Сегменты графа сцены содержат механизм, который описывает, какие части сцены изменились.
               Он включает в себя комбинированные матрицы, изменения в иерархии сегментов и т.д.
           \en The SceneSegment class can be used as a segment container. Entering segments are added with the AddSegment() and InsertSegment() functions. 
               The order of segments is very important as geometry segments are rendered according to their position in the scene graph. \n

               The scene graph segments contains a mechanism to describe which parts of the scene has changed. It includes the combined matrixes, 
               changes in the segment hierarchy, and so on. \~
  \ingroup Vision_Scenegraph
*/
// ---
class VSN_CLASS SceneSegment : public Essence
{
    VSN_OBJECT(SceneSegment);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    SceneSegment(SceneSegment* pParent = nullptr);

    /** \brief \ru Специальный конструктор с данными для сегмента.
               \en Special constructor with segment data. \~ 
        \param[in] key - \ru Идентификатор сегмента.
                         \en Segment identifier. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
    */
    SceneSegment(const NodeKey& key, SceneSegment* pParent = nullptr);

    /** \brief \ru Специальный конструктор с данными для сегмента.
                \en Special constructor with segment data. \~ 
        \param[in] pSegmentData - \ru Сегмент графа данных сцены.
                                  \en Scene data graph segment. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
        \param[in] pDescriptor - \ru Описание сцены.
                                 \en Scene description. \~
        \param[in] shaderId - \ru Идентификатор шейдера.
                              \en Shader identifier. \~
    */
    SceneSegment(SceneSegmentData* pSegmentData, SceneSegment* pParent = nullptr);

    /** \brief \ru Специальный конструктор с данными для сегмента и идентификатором сегмента.
                \en Special constructor with segment data and segment identifier. \~ 
        \param[in] pSegmentData - \ru Данные сегмента графа сцены.
                                  \en Scene graph segment data. \~
        \param[in] key - \ru Идентификатор сегмента.
                         \en Segment identifier. \~
        \param[in] pDescriptor - \ru Описание сцены.
                                 \en Scene description. \~
        \param[in] shaderId - \ru Идентификатор шейдера.
                              \en Shader identifier. \~
    */
    SceneSegment(SceneSegmentData* pSegmentData, const NodeKey& key);

    /** \brief \ru Специальный конструктор с представлением.
                \en Special constructor with representation. \~ 
        \param[in] pRep - \ru Представление геометрии.
                          \en Geometry representation. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
    */
    SceneSegment(GeometryRep* pRep, SceneSegment* pParent = nullptr);

    /** \brief \ru Специальный конструктор с представлением.
                \en Special constructor with representation. \~ 
        \param[in] pRep - \ru Представление геометрии.
                          \en Geometry representation. \~
        \param[in] key - \ru Идентификатор сегмента.
                         \en Segment identifier. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
    */
    SceneSegment(GeometryRep* pRep, const NodeKey& key, SceneSegment* pParent = nullptr);

    /// \ru Деструктор. \en Destructor.
    virtual ~SceneSegment();
public:
    /** \brief \ru Функция для создания копии сегмента.
               \en function to create clone of the segment \~
        \details \ru  Если в сегменте присутствует геометрия, тогда будет создана ссылка на эту геометрию.
                 \en If the segment has a geometry, reference geometry will be created.
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
    */
    SceneSegment* Clone(SceneSegment* pParent = nullptr, bool children = true) const;

    /** \brief \ru Вернуть абсолютную матрицу сегмента.
               \en Returns absolute matrix of segment. \~ 
        \details \ru Вернуть абсолютную матрицу сегмента.
                 \en Returns absolute matrix of segment. \~
        \return \ru Абсолютная матрица сегмента.
                \en Absolute matrix of segment. \~
    */
    const Matrix3DF& GetAbsoluteMatrix() const;

    /** \brief \ru Вернуть относительную матрицу сегмента.
               \en Returns relative matrix of segment. \~
        \return \ru Относительная матрица сегмента.
                \en Relative matrix of segment. \~
    */
    Features::Transform& GetTransform() const;

    /** \brief \ru Есть ли у сегмента представление.
               \en Checks if segment has representation. \~ 
        \return \ru True, если есть представление.
                \en True if segment has representation. \~
    */
    bool HasRep() const;

    /** \brief \ru Есть ли у сегмента RenderObject.
               \en Checks if segment has RenderObject. \~ 
        \return \ru True, если в сегменте есть RenderObject.
                \en True if segment has RenderObject. \~
    */
    bool HasRenderObject() const;

    /// \ru Вернуть указатель на данные сегмента. \en Returns pointer to segment data. \~
    SceneSegmentData* GetSegmentData() const;

    /// \ru Вернуть признак наличия подсегментов. \en True if segment has subsegments. \~
    bool HasSegments() const;

    /** \brief \ru Признак возможности добавить данный сегмент в массив сегментов.
               \en Checks if segment can be added to segment array. \~ 
        \param[in] pSegment - \ru Сегмент.
                              \en Segment. \~
        \return \ru True, если данный сегмент может быть добавлен в массив сегментов.
                \en True if segment can be added to segment array. \~
    */
    bool CanInsertToSegment(SceneSegment* pSegment) const;

    /// \ru Вернуть указатель на родительский сегмент. \en Returns pointer to parent segment. \~
    SceneSegment* GetParentSegment() const;

    /// \ru Вернуть всех предков данного сегмента. \en Returns all parents for segment. \~
    std::list<SceneSegment*> GetAncestorsSegment() const;

    /// \ru Вернуть массив сегментов сцены. \en Returns array of scene segments. \~
    std::list<SceneSegment*> GetChildSegments() const;

    /// \ru Вернуть массив всех сегментов сцены данного узла. \en Returns array of all subsegments for this segment. \~
    std::list<SceneSegment*> GetSubSegments() const;

    /// \ru Вернуть количество граней представления этого сегмента. \en Returns count of representation faces for this segment. \~
    size_t GetFaceCount() const;
    /// \ru Вернуть количество вершин представления этого сегмента. \en Returns count of representation vertexes for this segment. \~
    size_t GetVertexCount() const;
    /// \ru Вернуть количество материалов представления этого сегмента. \en Returns count of representation materials for this segment. \~
    size_t GetMaterialCount() const;

    /// \ru Вернуть массив материалов представления этого сегмента. \en Returns array of representation materials for this segment. \~
    std::set<Material*> GetMaterials() const;

    ///  \ru Установить цвет материалу представления \en NOT TRANSLATED \~
    void SetColorPresentationMaterial(const Color& color);

    /// \ru Получить состояние видимости сегмента с учотом родительских элементов. \en Get the visibility state of the segment considering the parent elements. \~
    bool IsVisible() const;

    /// \ru Вернуть габаритный куб сегмента. \en Returns bounding box of segment. \~
    BoundingBox GetBoundingBox() const;

    /// \ru Вернуть номер этого сегмента. \en Returns number of segments. \~
    size_t GetSegmentNumber() const;

    /// \ru Вернуть указатель на состояние отрисовки. \en Returns pointer to rendering state. \~
    const RenderState* GetRenderState() const;

    /// \ru Вернуть количество сегментов, входящих в этот сегмент. \en Returns count of subsegments in this segment. \~
    size_t GetCountSegmentsOfLine() const;

    /// \ru Вернуть признак самостоятельного создания RenderObject. \en Returns flag for independent creation of RenderObject. \~
    bool IsIndependentCreationObject3D() const;

    /** \brief \ru Установить признак автоматического создания RenderObject.
               \en Sets flag for automatic creation of RenderObject. \~ 
        \param[in] bIndependent - \ru Значение признака.
                                  \en Value of flag. \~
    */
    void SetIndependentCreateViewObject(bool bIndependent);

    /** \brief \ru Вернуть индекс данного сегмента в массиве указанного сегмента.
                \en Returns index of segment in array of specified segment. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
        \return \ru Индекс.
                \en Index. \~
    */
    int GetIndexOf(const SceneSegment* pSegment) const;

    /** \brief \ru Вернуть признак существования указанного сегмента в данном сегменте.
               \en Returns flag for existence of specified segment in this segment. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
        \return \ru True, если в этом сегменте содержится указанный сегмент.
                \en True if segment has the specified segment. \~
    */
    bool ExistSegment(const SceneSegment* pSegment) const;
public:
    /// \ru Обновить абсолютную матрицу. \en Refreshes absolute matrix. \~
    SceneSegment* RefreshAbsoluteMatrix();

    /** \brief \ru Обновить абсолютную матрицу внутренних подсегментов.
               \en Refreshes absolute matrix of internal subsegments. \~ 
        \details \ru Обновить абсолютную матрицу внутренних подсегментов.
                 \en Refreshes absolute matrix of internal subsegments. \~
        \return \ru Сегмент сцены.
                \en Scene segment. \~
    */
    SceneSegment* RefreshSubSegmentAbsoluteMatrix();

    /** \brief \ru Добавить новый сегмент в сцену.
               \en Adds new segment to scene. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
    */
    void AddSegment(SceneSegment* pSegment);

    /** \brief \ru Вставить новый сегмент перед указанной позицией.
               \en Insert a new segment before the specified position. \~ 
        \param[in] index - \ru Индекс позиции.
                           \en Positon index. \~
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
    */
    void InsertSegment(int index, SceneSegment* pSegment);

    /** \brief \ru Создать и добавить новый сегмент с указанными данными.
               \en Creates and adds a new segment with shown data. \~ 
        \param[in] pSegmentData - \ru Сегмент данных графа сцены.
                                  \en Scene graph data segment. \~
        \return \ru Созданный сегмент сцены.
                \en Created scene segment. \~
    */
    SceneSegment* AddSegment(SceneSegmentData* pSegmentData);

    /// \ru Сделать сегмент самостоятельным. \en Makes an independent segment. \~
    void DoSegmentAlone();

    /** \brief \ru Удалить указанный сегмент из массива узлов.
                \en Removes specified segment from segment array. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
        \return \ru True, если сегмент найден и удален.
                \en True if segment is found and removed. \~
    */
    bool RemoveSegment(SceneSegment* pSegment);

    /// \ru Удалить всех детей. \en Remove all children. \~
    void RemoveChildren();

    /// \ru Сделать обращение нормалей сегмента. \en Makes reverse of the segment normals. \~
    void ReverseNormalsOfSegment();

    /** \brief \ru Создать RenderObject для этого сегмента.
               \en Creates RenderObject for this segment. \~ 
        \return \ru True, если RenderObject создан.
                \en True if RenderObject is created. \~
    */
    bool CreateRenderObject();

    /// \ru Удалить RenderObject этого сегмента. \en Removes RenderObject for this segment. \~
    bool RemoveRenderObject();

    /** \brief \ru Установить номер этому сегмента.
               \en Sets number of subsegments. \~ 
        \param[in] number - \ru Номер сегмента.
                            \en Number of segment.\~
    */
    void SetSegmentNumber(uint number);

    /** \brief \ru Обновить номер этого сегмента.
               \en Refreshes number of subsegments. \~ 
        \param[in] count - \ru Номер сегмента.
                           \en Number of subsegments. \~
        \return \ru Обновленное количество вхождений сегмента.
                \en Refreshed count of subsegments. \~
    */
    uint UpdateSegmentNumber(uint number);

    /** \brief \ru Установить видимость.
               \en Sets visibility. \~ 
        \param[in] bVisible - \ru Признак видимости.
                              \en Flag of visibility. \~
    */
    void SetVisible(bool bVisible);

    /** \brief \ru Получть значение видимости.
               \en Get visibility value. \~ 
    */
    bool GetVisible() const;

    /** \brief \ru Установить состояние отрисовки сегмента.
               \en Sets rendering state for segment. \~ 
        \param[in] renderState - \ru Состояние отрисовки.
                                 \en Rendering state. \~
    */
    void SetRenderStates(const RenderState& renderState);

    /// \ru Удалить пустые сегменты. \en Removes empty segments. \~
    void RemoveEmptySubSegment();

    /// \ru Вернуть указатель на геометрическое представление. \en Returns pointer to a geometric representation. \~
    GeometryRep* GetRepresentation() const;
    /// \ru Добавить новый указатель на GeometryRep. \en Adds new pointer to GeometryRep.
    void SetRepresentation(GeometryRep* pRepresentation);

    /// \ru Узнать слой сегмента. \n \en Get scene segment layer \~
    uint32_t GetRenderLayer() const;
    /// \ru Задать сегменту слой. \n \en Set layer to scene segment \~
    void SetRenderLayer(uint32_t, bool andSubSegments = true);

    /// \ru Исключить из мезанихма поиска объектов. \n \en Exclude from process find objects \~
    void SetIgnoreForPick(bool value);
    /// \ru Являеться ли объект исключенным из механизма поиска объектов. \n \en Check the object is excluded from process find object \~
    bool IsIgnoreForPick() const;
public:
    /// \ru Сигнал об окончании перестроения всей геометрии в сегменте. \en . \~
//    VSN_SIGNAL(Public, OnGeometryBuildCompleted, void OnGeometryBuildCompleted(SceneSegment* pSegment), pSegment)
    VSN_SIGNAL(Public, OnVisibleModified, void OnVisibleModified(SceneSegment* pSegment, bool isVisible), pSegment, isVisible)
private:
    VSN_SLOT(Private, OnRelativeMatrixModified, void OnRelativeMatrixModified())
private:
    VSN_DECLARE_EX_PRIVATE(SceneSegment);
};

} // namespace VSN

#endif /* __VSN_SCENESEGMENT_H */
