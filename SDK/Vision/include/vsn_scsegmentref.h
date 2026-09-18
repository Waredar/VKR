////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс SceneSegmentRef представляет ссылку на представление геометрии.
           \en SceneSegmentRef class sets reference to geometry representation. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_SCSEGMENTREF_H
#define __VSN_SCSEGMENTREF_H

#include <set>
#include <list>
#include <vsn_geometryrep.h>
#include <vsn_string.h>
#include <vsn_global.h>

namespace VSN {

class Material;
class GeometryRep;
class SceneSegment;
class SceneSegmentData;
//------------------------------------------------------------------------------
/** \brief \ru Класс SceneSegmentRef представляет ссылку на представление геометрии.
           \en SceneSegmentRef class sets reference to geometry representation. \~
    \details \ru Класс SceneSegmentRef необходим и выполняет функцию экономии памяти для одинакового представления геометрии.
             \en SceneSegmentRef class is required. It performs the function of memory saving for equal geometry representation.
    \ingroup Vision_SceneGraph
*/
// ---
class VSN_CLASS SceneSegmentRef
{
public:
    /** \brief \ru Специальный конструктор с указателем на представление.
               \en Special constructor with pointer to representation. \~
        \param[in] pRep - \ru Представление.
                          \en Representation. \~
    */
    explicit SceneSegmentRef(GeometryRep* pRep = nullptr);
    /// \ru Деструктор. \en Destructor. 
    ~SceneSegmentRef();
public:
    /** \brief \ru Вернуть true, если в этой ссылке есть экземпляр данных.
               \en True if data instance exists in the reference. \~
        \return \ru True, если в этой ссылке есть экземпляр данных.
                \en True if data instance exists in the reference. \~
    */
    bool HasDataSegment() const;

    /** \brief \ru Вернуть указатель на первый сегмент данных.
               \en Returns pointer to the first data segment. \~
        \return \ru Указатель на первый сегмент данных.
                \en Pointer to the first data segment. \~
    */
    SceneSegmentData* GetHeadDataSegment() const;

    /// \ru Вернуть список указателей на сегменты сцены. \en Returns the list of pointers to scene segments. \~
    std::list<SceneSegmentData*> GetSegmentData() const;

    /// \ru Вернуть массив указателей на сегменты сцены этой ссылки. \en Returns the array of pointers to scene segments of given reference. \~
    std::set<SceneSegment*> GetSceneSegmentsSet() const;

    /// \ru Вернуть список указателей на сегменты сцены этой ссылки. \en Returns the list of pointers to scene segments of given reference. \~
    std::list<SceneSegment*> GetSceneSegmentsList() const;

    /** \brief \ru Вернуть true, если данная ссылка имеет представление.
               \en True if given reference has representation. \~
        \return \ru True, если данная ссылка имеет представление.
                \en True if given reference has representation. \~
    */
    bool IsHasRep() const;

    /// \ru Вернуть указатель на представление этой ссылки. \en Returns pointer to representation of given reference. \~
    GeometryRep* GetRepresentation() const;

    /** \brief \ru Установить представление этой ссылки.
               \en Sets representation for the reference. \~
        \param[in] pRep - \ru Источник представления.
                          \en Representation source. \~
    */
    void SetRepresentation(GeometryRep* pRep);

    /// \ru Вернуть имя ссылки. \en Returns reference name. \~
    inline const String& GetName() const;

    /** \brief \ru Установить имя этой ссылки.
               \en Sets reference name. \~
        \param[in] name - \ru Имя.
                          \en Name. \~
    */
    inline void SetName(const String& name);

    /// \ru Вернуть количество граней. \en Returns face count. \~
    size_t GetFaceCount() const;

    /// \ru Вернуть количество вершин. \en Returns vertex count. \~
    size_t GetVertexCount() const;

    /// \ru Вернуть количество материалов. \en Returns material count. \~
    size_t GetMaterialCount() const;

    /// \ru Вернуть количество тел. \en Returns body count. \~
    size_t GetGeometryCount() const;

    /// \ru Вернуть массив материалов. \en Returns material array. \~
    std::set<Material*> GetMaterials() const;

    /// \ru Вернуть имя представления. \en Returns representation name. \~
    String GetNameRep() const;

    /** \brief \ru Установить имя представления.
               \en Sets representation name. \~
        \param[in] repName - \ru Имя представления.
                             \en Representation name. \~
    */
    inline void SetRepName(const String& repName);

    /** \brief \ru Вернуть true, если представление загружено.
               \en True if representation is loaded. \~
        \return \ru True, если представление загружено.
                \en True if representation is loaded. \~
    */
    inline bool IsLoadedRep() const;

    /** \brief \ru Вернуть true, если представление является пустым либо представления нет.
               \en True if no representation is found or representation is empty. \~
        \return \ru True, если представление является пустым либо представления нет.
                \en True if no representation is found or representation is empty. \~
    */
    inline bool IsEmptyRep() const;
public:
    /** \brief \ru Добавить сегмент данных.
               \en Adds data segment. \~
        \param[in] pSegmentData - \ru Новый сегмент данных.
                                  \en New data segment. \~
    */
    void AddSegmentData(SceneSegmentData* pSegmentData);

    /** \brief \ru Удалить из массива сегмент данных.
               \en Removes data segment from array. \~
        \param[in] pSegmentData - \ru Удаляемый сегмент данных.
                                  \en Removable data segment. \~
    */
    void RemoveSegmentData(SceneSegmentData* pSegmentData);
private:
    std::set<SceneSegmentData*> m_segmentOfData;  /// массив ссылок экземпляров данных
    GeometryRep* m_pRepresentation;               /// представление ссылки
    String m_name;                                /// имя ссылки
private:
    VSN_DISABLE_COPY(SceneSegmentRef);
};

// ---
inline const String& SceneSegmentRef::GetName() const
{ return m_name; }
// ---
inline void SceneSegmentRef::SetName(const String& name)
{ m_name = name; }

// ---
inline void SceneSegmentRef::SetRepName(const String& repName)
{
    if (m_pRepresentation != nullptr)
        m_pRepresentation->SetNameRep(repName);
}

// ---
bool SceneSegmentRef::IsLoadedRep() const
{
    if (m_pRepresentation != nullptr)
        return m_pRepresentation->IsLoaded();
    return false;
}

// ---
inline bool SceneSegmentRef::IsEmptyRep() const
{
    if (m_pRepresentation != nullptr)
        return m_pRepresentation->IsEmpty();
    return true;
}

} // namespace VSN

#endif /* __VSN_SCSEGMENTREF_H */
