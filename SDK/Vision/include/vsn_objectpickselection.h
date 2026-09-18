////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru NO TRANSLATION
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_OBJECTPICKERSELECTION_H
#define __VSN_OBJECTPICKERSELECTION_H

#include <vsn_absvisioncomponent.h>
#include <vsn_processevent.h>
#include <vsn_prfindselectobject.h>
#include <name_item.h>

namespace VSN {

//------------------------------------------------------------------------------
struct PickData
{
    PickData() : m_typeObject(ObjectType::None), m_essenceKey(NodeKey::ZERO), m_geometryIdx(-1), 
        m_geometryKey(NodeKey::ZERO), m_geometryItemKey(NodeKey::ZERO), m_primitiveId(0), m_mathPrimitiveId(-1) {}

    ObjectType m_typeObject;    ///< \ru Тип объекта \en NO TRANSLATION.
    NodeKey m_essenceKey;       ///< \ru Уникальный ключ сегмента сцены \en NO TRANSLATION.
    uint m_geometryIdx;         ///< \ru Индекс геометрии \en NO TRANSLATION.
    NodeKey m_geometryKey;      ///< \ru Идентификатор геометрии \en NO TRANSLATION.
    NodeKey m_geometryItemKey;  ///< \ru Идентификатор геометрии \en NO TRANSLATION.
    uint m_primitiveId;         ///< \ru Уникальный идентификатор примитива \en NO TRANSLATION. 
    /// \ru Данные для математического объекта. \en NO TRANSLATION.
    MbPath m_mathPath;          ///< \ru Уникальный путь до объекта \en NO TRANSLATION. 
    uint32 m_mathPrimitiveId;   ///< \ru Уникальный идентифакатор примитива \en NO TRANSLATION. 
};

//------------------------------------------------------------------------------
/** \brief   \ru NO TRANSLATION.
             \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION. \n
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Pick
*/
// ---  
class VSN_CLASS PickSelectionEvent
{
public:
    /// \ru Конструктор по умолчанию \en Default constructor.
    PickSelectionEvent();
    /// \ru Конструктор с параметрами \en NO TRANSLATION. \~
    PickSelectionEvent(const NodeKey& key, int geoIdx, const NodeKey& geoKey, 
        const NodeKey& geoItemKey, uint primitiveId);
    /// \ru Конструктор копирования \en NO TRANSLATION. \~
    PickSelectionEvent(const PickSelectionEvent& other);
public:
    /// \ru Вернуть тип объекта \en NO TRANSLATION. \~
    ObjectType GetTypeObject() const;
    /// \ru Установить тип объекта \en NO TRANSLATION. \~
    void SetTypeObject(ObjectType type);

    /// \ru Вернуть уникальный ключ сегмента сцены \en NO TRANSLATION. \~
    NodeKey GetEssenceKey() const;
    /// \ru Вернуть индекс геометрии \en NO TRANSLATION. \~
    uint GetGeometryIdx() const;
    /// \ru Вернуть идентификатор геометрии \en NO TRANSLATION. \~
    NodeKey GetGeometryKey() const;
    /// \ru Вернуть идентификатор геометрии \en NO TRANSLATION. \~
    NodeKey GetGeometryItemKey() const;
    /// \ru Вернуть уникальный идентификатор примитива \en NO TRANSLATION. \~
    uint GetPrimitiveId() const;

    /// \ru Вернуть уникальный путь до математического объекта \en NO TRANSLATION. \~
    MbPath GetMathPath() const;
    /// \ru Установить уникальный путь до математического объекта \en NO TRANSLATION. \~
    void SetMathPath(const MbPath& path);
    /// \ru Вернуть уникальный идентификатор математического объекта \en NO TRANSLATION. \~
    uint32 GetMathPrimitive() const;
    /// \ru Установить уникальный идентификатор математического объекта \en NO TRANSLATION. \~
    void SetMathPrimitive(uint32 id);
    /// \ru Оператор копирования \en Copy operator.
    PickSelectionEvent & operator = (const PickSelectionEvent& other);

    /// \ru True, если клавиша Ctrl сейчас нажата \en True if Ctrl key is currently pressed.
    bool Control() const { return(m_flags & mb_Control) != 0; }
    /// \ru True, если клавиша Shift сейчас нажата \en True if Shift key is currently pressed.
    bool Shift() const { return(m_flags & mb_Shift) != 0; }
    /// \ru True, если клавиша Alt сейчас нажата \en True if Alt key is currently pressed.
    bool Alt() const { return(m_flags & mb_Alt) != 0; }
    /// \ru True, если левая клавиша Alt нажата \en True if the left Alt key is pressed.
    bool LeftAlt() const { return(m_flags & mb_Left_Alt) != 0; }
    /// \ru True, если левая клавиша Ctrl нажата \en True if the left Ctrl key is pressed.
    bool LeftControl() const { return(m_flags & mb_Left_Control) != 0; }
    /// \ru True, если левая клавиша Shift нажата \en True if the left Shift key is pressed.
    bool LeftShift() const { return(m_flags & mb_Left_Shift) != 0; }
    /// \ru True, если правая клавиша Alt нажата \en True if the right Alt key is pressed.
    bool RightAlt() const { return(m_flags & mb_Right_Alt) != 0; }
    /// \ru True, если правая клавиша Ctrl нажата \en True if the right Ctrl key is pressed.
    bool RightControl() const { return(m_flags & mb_Right_Control) != 0; }
    /// \ru True, если правая клавиша Shift нажата \en True if the right Shift key is pressed.
    bool RightShift() const { return(m_flags & mb_Right_Shift) != 0; }

    /// \ru True, если левая кнопка мыши нажата \en True if the left mouse button is pressed.
    bool LButton() const { return(m_flags & mb_LButton) != 0; }
    /// \ru True, если средняя кнопка мыши нажата \en True if the middle mouse button is pressed.
    bool MButton() const { return(m_flags & mb_MButton) != 0; }
    /// \ru True, если правая кнопка мыши нажата \en True if the right mouse button is pressed.
    bool RButton() const { return(m_flags & mb_RButton) != 0; }

    /// \ru Возвращает бит ProcessEvent флагов, таких как mb_LButton, для специальных событий клавиш Shift, Ctrl, а также левой, средней и правой кнопок мыши \en Returns ProcessEvent bit flags like mb_LButton for special events of Shift and Ctrl keys as well as left, middle and right mouse buttons. \~
    unsigned int GetFlags() const { return m_flags; }
    /** \brief \ru Этот метод устанавливает побитовые флаги, которые показывают состояние кнопок мыши, клавиш Shift и Ctrl.
               \en This method sets bitwise flags that shows the state of mouse buttons, Shift and Ctrl keys. \~
        \param[in] flags - \ru Побитовые флаги для состояния мыши и клавиш. Например, если и клавиша Shift, и левая кнопка мыши нажаты, пропустить mb_Shift|mb_LButton.
                           \en Bitwise flags for mouse and key states. For example, if both Shift key and left mouse button are pressed, pass mb_Shift|mb_LButton. \~
    */
    void SetFlags(int flags) { m_flags = flags; }

    /// \ru Вернуть координаты курсора \en NO TRANSLATION. \~
    PointI GetCursorPos() const;
    /// \ru Установить координаты курсора \en NO TRANSLATION. \~
    void SetCursorPos(const PointI& pnt);
protected:
    PickData m_pickData;
    PointI m_cursorPos;    ///< \ru Кординаты курсора \en NO TRANSLATION.
    unsigned int m_flags;  ///< \ru Флаги показывают, какая из кнопок мыши нажата, и нажаты ли клавиши Shift и Ctrl на клавиатуре \en Flags indicate which of mouse buttons is pressed and if Shift and Ctrl keyboard keys are pressed.
};

typedef std::shared_ptr<PickSelectionEvent> PickSelectionEventPtr;

//------------------------------------------------------------------------------
/** \brief   \ru NO TRANSLATION.
             \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION. \n
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Pick
*/
// ---  
class VSN_CLASS PickAreaSelectionEvent
{
public:
    /// \ru Конструктор по умолчанию \en Default constructor.
    PickAreaSelectionEvent();
public:
    inline const std::vector<PickData>& GetPickData() const;
    inline void SetPickData(const std::vector<PickData>& pick);

    /// \ru True, если клавиша Ctrl сейчас нажата \en True if Ctrl key is currently pressed.
    bool Control() const { return (m_flags & mb_Control) != 0; }
    /// \ru True, если клавиша Shift сейчас нажата \en True if Shift key is currently pressed.
    bool Shift() const { return (m_flags & mb_Shift) != 0; }

    /// \ru Возвращает бит ProcessEvent флагов, таких как mb_LButton, для специальных событий клавиш Shift, Ctrl, а также левой, средней и правой кнопок мыши \en Returns ProcessEvent bit flags like mb_LButton for special events of Shift and Ctrl keys as well as left, middle and right mouse buttons. \~
    unsigned int GetFlags() const { return m_flags; }

    /** \brief \ru Этот метод устанавливает побитовые флаги, которые показывают состояние кнопок мыши, клавиш Shift и Ctrl.
               \en This method sets bitwise flags that shows the state of mouse buttons, Shift and Ctrl keys. \~
        \param[in] flags - \ru Побитовые флаги для состояния мыши и клавиш. Например, если и клавиша Shift, и левая кнопка мыши нажаты, пропустить mb_Shift|mb_LButton.
                           \en Bitwise flags for mouse and key states. For example, if both Shift key and left mouse button are pressed, pass mb_Shift|mb_LButton. \~
    */
    void SetFlags(int flags) { m_flags = flags; }
protected:
    std::vector<PickData> m_pickData;
    unsigned int m_flags; ///< \ru Флаги показывают, какая из кнопок мыши нажата, и нажаты ли клавиши Shift и Ctrl на клавиатуре \en Flags indicate which of mouse buttons is pressed and if Shift and Ctrl keyboard keys are pressed.
};

inline const std::vector<PickData>& PickAreaSelectionEvent::GetPickData() const
{ return m_pickData; }
inline void PickAreaSelectionEvent::SetPickData(const std::vector<PickData>& data)
{ m_pickData = data; }

typedef std::shared_ptr<PickAreaSelectionEvent> PickAreaSelectionEventPtr;

class Viewport;
class OpenGLContextInterface;
class ObjectPickSelectionPrivate;
//------------------------------------------------------------------------------
/** \brief   \ru NO TRANSLATION.
             \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION. \n
             \en NO TRANSLATION. \n \~
    \ingroup 
*/
// ---
class VSN_CLASS ObjectPickSelection : public Object
{
    VSN_OBJECT(ObjectPickSelection);
    VSN_PROP_READ_WRITE_NOTIFY(hoverEnabled, IsHoverEnabled, SetHoverEnabled, HoverEnabledModified)
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    explicit ObjectPickSelection(Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~ObjectPickSelection();
public:
    /// \ru Установить текущий OpenGL контекст \en NO TRANSLATION. \~
    void SetOpenGLContext(OpenGLContextInterface* pContext);
    /// \ru Вернуть текущий OpenGL контекст \en NO TRANSLATION. \~
    OpenGLContextInterface* GetOpenGLContext() const;
    /// \ru Сбросить текущий OpenGL контекст \en NO TRANSLATION. \~
    void ResetOpenGLContext(OpenGLContextInterface* pContext);

    /// \ru Установить текущий Viewport \en NO TRANSLATION. \~
    void SetViewport(ViewportPtr ptrViewport);
    /// \ru Вернуть true, если Hover является включенным \en NO TRANSLATION. \~
    bool IsHoverEnabled() const;
    /// \ru Присылать Hover повторно при перемещении курсора над объектом
    /// \en Send Hover repeatedly when moving the cursor over an object. \~
    bool IsHoverRepeat() const;
    void SetHoverRepeat(bool value);

    /// \ru Вернуть размер ловушки для поиска \en NO TRANSLATION. \~
    uint GetSelectionSquareSize() const;
    /// \ru Установить размер ловушки для поиска \en NO TRANSLATION. \~
    void SetSelectionSquareSize(uint size);

    /// \ru Вернуть значение фильтра объектов \en NO TRANSLATION. \~
    Filter GetFilterObject() const;

    /// \ru Вернуть true, если установлен флаг поиска сегмента \en NO TRANSLATION. \~
    bool IsBodyPickEnabled() const;
    /// \ru Установить флаг для поиска сегмента \en NO TRANSLATION. \~
    void SetBodyPickEnabled(bool bPick);

    /// \ru Вернуть true, если установлен флаг поиска граней \en NO TRANSLATION. \~
    bool IsFacePickEnabled() const;
    /// \ru Установить флаг для поиска граней \en NO TRANSLATION. \~
    void SetFacePickEnabled(bool bPick);

    /// \ru Вернуть true, если установлен флаг поиска ребер \en NO TRANSLATION. \~
    bool IsEdgePickEnabled() const;
    /// \ru Установить флаг для поиска ребер \en NO TRANSLATION. \~
    void SetEdgePickEnabled(bool bPick);

    /// \ru Вернуть true, если установлен флаг поиска вершин \en NO TRANSLATION. \~
    bool IsVertexPickEnabled() const;
    /// \ru Установить флаг для поиска вершин. \en NO TRANSLATION. \~
    void SetVertexPickEnabled(bool bPick);

    /// \ru Выдать данные, которые находятся по указанным координатам. \en NO TRANSLATION. \~
    PickData HitTest(int scrX, int scrY);
    /// \ru Выдать данные, которые находятся по указанным координатам. \en NO TRANSLATION. \~
    PickData HitTest(const PointI& pnt);

    /// \ru Вернуть список указателей процессов поиска. \en NO TRANSLATION. \~
    ObjectList<PrBasicFindSelect*> GetFindProcesses() const;
    /// \ru Добавить вспомогательный процесс поиска. \en NO TRANSLATION. \~
    void AddFindProcess(PrBasicFindSelect* pProcess, SceneSegment* pParent = nullptr);
    /// \ru Удалить вспомогательный процесс поиска. \en NO TRANSLATION. \~
    void RemoveFindProcess(PrBasicFindSelect* pProcess);
public:
    VSN_SLOT(Public, SetHoverEnabled, void SetHoverEnabled(bool hoverEnabled))
public:
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, ObjectPressed, void ObjectPressed(PickSelectionEventPtr pPick, bool bMulti), pPick, bMulti)
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, ObjectHoverMove, void ObjectHoverMove(PickSelectionEventPtr pPick), pPick)
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, ObjectReleased, void ObjectReleased(PickSelectionEventPtr pPick, bool bMulti), pPick, bMulti)
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, ObjectPickArea, void ObjectPickArea(PickAreaSelectionEventPtr pPack, bool bMulti), pPack, bMulti)
public:
    VSN_SIGNAL(Public, HoverEnabledModified, void HoverEnabledModified(bool bHoverEnabled), bHoverEnabled)
private:
    VSN_DISABLE_COPY(ObjectPickSelection);
    VSN_DECLARE_EX_PRIVATE(ObjectPickSelection);
};

} // namespace VSN

#endif // __VSN_OBJECTPICKERSELECTION_H
