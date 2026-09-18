////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс SceneContent представляет содержание сцены в виде графа.
         \en SceneContent class represents scene content as the graph. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_SCENECONTENT_H
#define __VSN_SCENECONTENT_H

#include <vsn_rendercontainer.h>
#include <vsn_scenesegment.h>
#include <vsn_scsegmentref.h>
#include <vsn_scsegmentdata.h>
#include <vsn_global.h>

namespace VSN {

class SceneContentPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс SceneContent представляет содержание сцены в виде графа.
           \en SceneContent class represents scene content as the graph. \~
  \ingroup Vision_SceneGraph
*/
// ---
class VSN_CLASS SceneContent
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    SceneContent();
    /// \ru Конструктор по корневому сегменту сцены. \en Constructor by scene root segment.
    explicit SceneContent(SceneSegment* pSegment);
    /// \ru Конструктор копирования. \en Copy-constructor.
    SceneContent(const SceneContent& other);
    /// \ru Деструктор. \en Destructor. 
    ~SceneContent();
public:
    /// \ru Вернуть габарит содержимого сцены. \en Returns bounding box of scene content. \~
    BoundingBox GetBoundingBox() const;
    /// \ru Вернуть указатель на корневой сегмент сцены. \en Returns pointer to the scene root segment. \~
    SceneSegment* GetRootSegment() const;
    /// \ru Вернуть указатель на контейнер визуальных объектов. \en Returns pointer to container of visual effects. \~
    std::shared_ptr<RenderContainer> GetContainer() const;
    /// \ru Вернуть количество объектов в сцене. \en Returns scene object count. \~
    size_t GetCount() const;
    /// \ru Вернуть true, если сцена пуста, иначе false. \en True if scene is empty. \~
    bool IsEmpty() const;
    /// \ru Вернуть количество граней. \en Returns face count. \~
    size_t GetFaceCount() const;
    /// \ru Вернуть количество вершин. \en Returns vertex count. \~
    size_t GetVertexCount() const;
    /// \ru Вернуть количество материалов. \en Returns material count. \~
    size_t GetMaterialCount() const;
    /// \ru Вернуть набор материалов. \en Returns set of materials. \~
    std::set<Material*> GetMaterials() const;
    /// \ru Вернуть список объектов в сцене. \en Returns scene object list. \~
    ObjectList<RenderObject*> GetObjects() const;
    /// \ru Вернуть список видимых объектов в сцене. \en Returns scene visible object list. \~
    ObjectList<RenderObject*> GetVisibleObjects() const;
    /** \brief \ru Вернуть указатель на сегмент сцены.
                \en Returns pointer to scene segment. \~ 
        \param[in] id - \ru Идентификатор сегмента.
                        \en Segment identifier. \~
        \return \ru Указатель на сегмент сцены.
                \en Pointer to scene segment. \~
    */
    SceneSegment* GetSegment(const NodeKey& key) const;

    /// \ru Вернуть все сегменты сцены. \en Returns all scene segments. \~
    ObjectList<SceneSegment*> GetSegments() const;

    /// \ru Вернуть количество сегментов. \en Returns segment count. \~
    size_t GetSegmentCount() const;

    /** \brief \ru Проверить, существует ли в контейнере сегменты с заданным идентификатором.
                \en Checks if segments with specified identifier exist in container. \~ 
        \param[in] id - \ru Идентификатор сегмента.
                        \en Segment identifier. \~
        \return \ru True, если в контейнере есть сегмент с таким идентификатором, иначе - false.
                \en True if segment with such identifier exists. \~
    */
    bool IsExistSegment(const NodeKey& key) const;

    /// \ru Вернуть данные сегментов. \en Returns segment data. \~
    std::list<SceneSegmentData*> GetSegmentsData() const;

    /// \ru Вернуть список указателей на ссылки. \en Returns reference pointer list. \~
    std::list<SceneSegmentRef*> GetReferenceSegments() const;

    /// \ru Вернуть количество тел. \en Returns body count. \~
    size_t GetBodyCount() const;
    /// \ru Вернуть количество представлений. \en Returns representation count. \~
    size_t GetRepCount() const;
    /// \ru Вернуть Up вектор сцены. \en Returns scene up vector. \~
    MbVector3D GetUpVector() const;
    /// \ru Отсоединить корневой сегмент от сцены. \en Detaches root segment from the scene. \~
    SceneSegment* DetachRootSegment();
    /// \ru Престроить дерево видимости \en NOT TRANSLATED \~
    void RebuildFrustumTree();
public:
    /** \brief \ru Заменить корневой сегмент сцены.
                \en Replaces scene root segment. \~ 
        \param[in] pSegment - \ru Новый корневой сегмент сцены.
                                \en New scene root segment. \~
    */
    void ReplaceRootSegment(SceneSegment* pSegment);

    /// \ru Обратить нормали сцены. \en Reverses scene normals. \~
    void ReverseNormal();

    /// \ru Очистить сцену. \en Clears scene. \~
    void Clear();

    /** \brief \ru Задать viewport сцены.
                \en Sets scene viewport. \~ 
        \param[in] pViewport - \ru Указатель на viewport.
                                \en Pointer to viewport. \~
    */
    void SetViewport(Viewport* pViewport);

//////////////////////////////////TODO////////////////////////////////////////////////////
public:
    /** \brief \ru Оператор присваивания.
                \en Assignment operator. \~ 
        \details \ru Оператор присваивания.
                    \en Assignment operator. \~
    */
    SceneContent& operator = (const SceneContent&);

    /** \brief \ru Оператор сравнения.
               \en Comparison operator. \~ 
        \details \ru Оператор сравнения.
                 \en Comparison operator. \~
        \param[in] other - \ru Сцена для сравнения.
                            \en Scene for comparison. \~
        \return \ru True, если содержание сравниваемых сцен не отличается, иначе - false.
                \en True if compared scene contents are identical. \~
    */
    bool operator == (const SceneContent& other) const;

public:
    /** \brief \ru Отрисовать все объекты сцены.
               \en Renders all scene objects. \~ 
        \param[in] groupId - \ru Идентификатор группы.
                             \en Group identifier. \~
        \param[in] renderingMode - \ru Режим отображения геометрии.
                                   \en Geometry rendering mode. \~
    */
//    void Render(uint groupId, RenderMode renderingMode = rm_Shaded);
private:
    VSN_DECLARE_PRIVATE(SceneContent)
};

typedef std::shared_ptr<SceneContent> SceneContentPtr;

} // namespace VSN

#endif /* __VSN_SCENECONTENT_H */
