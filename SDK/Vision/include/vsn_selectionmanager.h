////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс SelectionManager управляет списком выбранных элементов.
           \en SelectionManager class controls a list of selected items. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __SELECTIONMANAGER_H
#define __SELECTIONMANAGER_H

#include <vsn_object.h>
#include <vsn_scenecontent.h>
#include <vsn_objectpickselection.h>
#include <vsn_global.h>

namespace VSN {

class SelectionManager;
//------------------------------------------------------------------------------
/** \brief  \ru Класс SelectionItem является определением интерфейса для выбранного элемента.
            \en SelectionItem class is a definition of the interface for a selected item. \~
    \details \ru Это абстрактный базовый класс для элементов выбора, который содержится в списке класса SelectionManager. 
                 Определяет набор функций для SelectionManager и операторов для взаимодействия в момент выбора. Используйте 
                 этот класс в качестве базового класса, если вы хотите реализовать новые типы классов элементов выбора. 
                 Примечание: вы не можете создать экземпляр этого класса, т.к. он содержит чистые виртуальные функции, 
                 которые не имеют реализацию. \n
             \en It is an abstract class for the selection items that is contained in the list of SelectionManager class.
                 SelectionItem class defines a set of functions of SelectionManager, and operators for interaction at the selection moment.
                 Use this class as the base class if you need to implement new classes for selection items.
                 Note: you cannot create an instace of the class, as it contains some pure virtual functions
                 that have got no implementation. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS SelectionItem
{
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    explicit SelectionItem(const NodeKey& key, SelectionManager* pManager);
    SelectionItem(const SelectionItem& other);
    /// \ru Деструктор \en Destructor. \~
    virtual ~SelectionItem();
public:
    /// \ru Вернуть уникальный ключ \en Returns the unique key. \~
    virtual NodeKey GetNodeKey() const { return m_key; };
    /// \ru Вернуть тип объекта \en Returns the object type. \~
    virtual ObjectType GetType() const { return m_type; }
    /// \ru Подсветить элемент \en Highlights the item. \~
    virtual bool Highlight() = 0;
    /// \ru Снять подсветку элемента \en Unhighlights the item. \~
    virtual bool UnHighlight() = 0;
    /// \ru Выбрать элемент \en Selects the item. \~
    virtual bool Select() = 0;
    /// \ru Снять выбор с элемента \en Unselects the item. \~
    virtual bool UnSelect() = 0;
    /// \ru Вернуть true, когда два элемента выбора равны. \en Returns true if two selection items are equal. \~
    virtual bool IsEquals(const SelectionItem* pItem) const;
    virtual SelectionItem* Clone() const = 0;
public:
    /// \ru Вернуть указатель сегмента графа. \en Returns a pointer to the graph segment. \~
    const SceneSegment* GetSceneSegment() const;
    /// \ru Вернуть указатель на математический объект. Может быть равен нулю. \en Returns a pointer to the math object. The pointer can be null. \~
    const MbItem* GetMathItem() const;
    /// \ru Вернуть указатель на SelectionManager. \en Returns a pointer to the SelectionManager. \~
    SelectionManager* GetParent() const;
protected:
    ObjectType        m_type;
    NodeKey           m_key;
    SelectionManager* m_pManager;
    Filter            m_filter;
private:
    friend class SelectionManager;
};

//------------------------------------------------------------------------------
/** \brief  \ru InstSelectionItem - элемент выбора, который имеет реализацию функций.
            \en InstSelectionItem class is a selection item that contains functions implementation. \~
    \details \ru Эта реализация класса InstSelectionItem обрабатывает выбор сущностей (грани, ребра, вершины, ...). 
                 Реализация устанавливает цвет дополнительному материалу, чтобы распознать выбранные объекты. 
                 InstSelectionItem также имеет функции, которые выдают уникальные идентификаторы объектов сцены
                 и идентификаторы соответствия первичного представления, т.e. математического, если оно имеется. \n
             \en InstSelectionItem class implementation processes selection of such entities as faces, edges, verteces, etc.
                 The implementation sets a color to an additional material, in order to recognize selected objects.
                 InstSelectionItem class also has functions that give the unique identifiers of each scene object, 
                 and the match identifiers of the primary representation, i.e. a math representation if any. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS InstSelectionItem : public SelectionItem
{
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    explicit InstSelectionItem(const NodeKey& key, SelectionManager* pManager, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    explicit InstSelectionItem(const NodeKey& key, const NodeKey& itemKey, SelectionManager* pManager, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    InstSelectionItem(const InstSelectionItem& other);
    /// \ru Деструктор \en Destructor. \~
    virtual ~InstSelectionItem();
public:
    /// \ru Вернуть идентификатор вставки в геометрии. \en Returns the identifier of the inserts in the geometry. \~
    virtual NodeKey GetItemKey() const;
    /// \ru Вернуть индекс тела в геометрии. \en Returns the body index in the geometry. \~
    virtual int GetIndexBody() const;
    /// \ru Вернуть идентификатор примитива в геометрии. \en Returns the identifier of the primitive in the geometry. \~
    virtual uint GetPrimitiveId() const;
    /// \ru Вернуть уникальный путь до математического объекта. \en Returns the unique path to the math object. \~
    virtual MbPath GetMathPath() const;
    /// \ru Вернуть уникальный идентификатор математического объекта \en Returns the unique identifier of the math object. \~
    virtual uint32 GetMathPrimitive() const;

    /// \ru Подсветить элемент. \en Highlights the item. \~
    virtual bool Highlight() override;
    /// \ru Снять подсветку элемента. \en Unhighlights the item. \~
    virtual bool UnHighlight() override;
    /// \ru Выбрать элемент. \en Selects the item. \~
    virtual bool Select() override;
    /// \ru Снять выбор с элемента. \en Unselects the item. \~
    virtual bool UnSelect() override;
    /// \ru Вернуть true, когда два элемента выбора равны. \en Returns true if two selection items are equal. \~
    virtual bool IsEquals(const SelectionItem* pItem) const;
    virtual SelectionItem* Clone() const override;
public:
    /// \ru Вернуть указатель на геометрию. Может быть равен нулю. \en Returns pointer to geometry. The pointer can be null. \~
    Geometry* GetGeometryItem() const;
    /// \ru Вернуть указатель на математический примитив. Может быть равен нулю. \en Returns a pointer to the math primitive. The pointer can be null. \~
    const MbTopologyItem* GetPrimitiveItem() const;
    ///< \ru Вернуть позицию курсора. \en Returns cursor position. \~
    PointI& GetCursorPos() { return m_cursorPos; }
protected:
    /// \ru Уникальные идентификаторы визуальных объектов. \en The unique identifiers of the visual objects. \~
    NodeKey m_itemKey;
    PointI m_cursorPos;        ///< \ru Позиция курсора. \en The cursor position. \~
    int  m_currenyindexBody;   ///< \ru Индекс тела. \en The body index. \~
    uint m_currentPrimitiveId; ///< \ru Уникальный идентификатор примитива. \en The unique identifier of the primitive. \~
};

//------------------------------------------------------------------------------
/** \brief  \ru InstCustomItem элемент ручного выбора объектов, который имеет реализацию функций.
            \en InstCustomItem class is an item responsible for a manual object selection and that has function implementation. \~
    \details \ru Эта реализация класса InstCustomItem обрабатывает выбор сущностей (грани, ребра, вершины, ...).
                 Реализация устанавливает цвет дополнительному материалу, чтобы распознать выбранные объекты.
                 InstCustomItem также имеет функции, которые выдают уникальные идентификаторы объектов сцены
                 и идентификаторы соответствия первичного представления, т.e. математического, если оно имеется. 
                 InstCustomItem - не работает с событиями от мыши и предназначен для ручного набора объектов. \n
             \en InstCustomItem class implementation processes selection of such entities as faces, edges, verteces, etc.
                 The implementation sets a color to an additional material, in order to recognize selected objects.
                 InstCustomItem class also has functions that give the unique identifiers of each scene object, 
                 and the match identifiers of the primary representation, i.e. a math representation if any.
                 InstCustomItem class doesn't operate with mouse events and is intended for a manual object selection. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS InstCustomItem : public InstSelectionItem
{
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    explicit InstCustomItem(const NodeKey& key, SelectionManager* pManager, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    InstCustomItem(const InstCustomItem& other);
    /// \ru Деструктор \en Destructor. \~
    virtual ~InstCustomItem();
public:
    /// \ru Подсветить объект - функция не задействована. \en Highlights the item. The function isn't used. \~
    virtual bool Highlight() override;
    /// \ru Снять подсветку объекта  - функция не задействована.\en Unhighlights the item. The function isn't used. \~
    virtual bool UnHighlight() override;

    /// \ru Выбрать элемент \en Selects the item. \~
    virtual bool Select() override;
    /// \ru Снять выбор с элемента \en Unselects the item. \~
    virtual bool UnSelect() override;
    virtual SelectionItem* Clone() const override;
};


class ObjectPickSelection;
class SelectManagerPrivate;
class SelectionManagerPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс SelectionManager управляет списком выбранных элементов.
            \en SelectionManager class controls a list of selected items. \~
    \details \ru SelectionManager создает и сохраняет список геометрических примитивов или сегментов Vision. 
                 Класс имеет функции добавления и удаления отдельных и нескольких SelectionItem для списка. 
                 SelectionManager инкапсулирует определенную логику с проверками, выбран ли элемент. Все 
                 элементы, которые выбраны (т.е. находящиеся  в списке), будут выделены в сцене 
                 указанным цветом с помощью функции SetSelectionColor. Также имеется поддержка управления 
                 режимом выделения и стилем выделения. Примечание: SelectionManager может работать, 
                 как самостоятельно, так и в паре с инструментом ObjectPickSelection. С помощью функций 
                 SetMouseButtonsSelection и SetKeyboardButtonsMultiSelection пользователь может настроить
                 активность выбора объекта для режимов SingleSelection, MultiSelection. \n
             \en SelectionManager class creates and stores a list of geometric primitives or Vision segments.
                 For the list, the class has functions for adding and deleting an individual and several SelectionItem.
                 SelectionManager encapsulates certain logic with checking if an item is selected.
                 All items selected (i.e. put in the list) will be selected in the scene with a special color
                 that the SetSelectionColor function sets. Also the class provides support for controlling the selection mode
                 and the selection style. Note: SelectionManager class can operate both separately and
                 together with the ObjectPickSelection tool. With SetMouseButtonsSelection and SetKeyboardButtonsMultiSelection functions
                 the user can configure activity of object selection for SingleSelection, MultiSelection modes. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS SelectionManager : public Object
{
    VSN_OBJECT(SelectionManager);
    VSN_ENUM(SelectionManager::SelectionMode)
    VSN_PROP_READ_WRITE(dynamicHighlighting, IsDynamicHighlighting, SetDynamicHighlighting)
    VSN_PROP_READ_WRITE(selectionMode, GetSelectionMode, SetSelectionMode)
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    explicit SelectionManager();
    /// \ru Деструктор \en Destructor. \~
    virtual ~SelectionManager();
public:
    enum SelectionMode 
    {
        NoSelection,
        SingleSelection,
        MultiSelection,
        Append, ///< \ru Добавить выбранный элемент в группу выбора. \en Adds the selected item to the selection group.
    };
    enum ActivateMethod 
    { 
        Pressed = 0,
        Released = 1,
    };
public:
    /// \ru Вернуть указатель на содержание сцены. \en Returns a pointer to the scene content. \~
    SceneContentPtr GetSceneContent() const;
    /// \ru Установить указатель на содержание сцены. \en Sets a pointer to the scene content. \~
    void SetSceneContent(SceneContentPtr ptrSceneContent);
    /// \ru Вернуть указатель на инструмент поиска объектов. \en Returns a pointer to the object search tool. \~
    ObjectPickSelection* GetObjectPickSelection() const;
    /// \ru Установить указатель на инструмент поиска объектов. \en Sets a pointer to the object search tool. \~
    void SetObjectPickSelection(ObjectPickSelection* pPickSelection);

    /// \ru Вернуть способ активации выбора объектов с помощью мыши. \en Returns the activation method of the object selection with the mouse. \~
    VSN_DEPRECATED_X("Don't use this function, use GetMouseSelectionMethod.")
    ActivateMethod GetMouseActivateSelection() const;
    /// \ru Установить способ активации выбора объектов с помощью мыши. \en Sets the activation method of the object selection with the mouse. \~
    VSN_DEPRECATED_X("Don't use this function, use SetMouseSelectionMethod.")
    void SetMouseActivateSelection(ActivateMethod method);

    /// \ru Вернуть способ активации выбора объектов с помощью мыши. \en Returns the activation method of the object selection with the mouse. \~
    ActivateMethod GetMouseSelectionMethod() const;
    /// \ru Установить способ активации выбора объектов с помощью мыши. \en Sets the activation method of the object selection with the mouse. \~
    void SetMouseSelectionMethod(ActivateMethod method);

    /** \brief \ru Вернуть кнопки мыши для выбора объектов.
               \en Returns the mouse buttons for the object selection. \~
        \return \ru Вернуть массив кодов клавиш.
                \en Returns the array of the button codes. \~
    */
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    std::vector<int> GetMouseButtonsSelection() const;
    /** \brief \ru Установить кнопки мыши для выбора объектов. Можно назначить кнопки:
                   mb_LButton; mb_MButton; mb_RButton.
               \en Sets the mouse buttons for the objects selection. The following buttons can be set:
                   mb_LButton; mb_MButton; mb_RButton. \~
        \param[in] vecKey - \ru Массив кодов клавиш.
                            \en The array of the button codes. \~
    */
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    void SetMouseButtonsSelection(const std::vector<int>& vecKey);

    /** \brief \ru Вернуть кнопки клавиатуры для выбора объектов в режиме MultiSelection.
               \en Returns the keyboard keys for the object selection in MultiSelection mode. \~
        \return \ru Вернуть массив кодов клавиш.
                \en Returns the array of the key codes. \~
    */
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    std::vector<int> GetKeyboardButtonsMultiSelection() const;
    /** \brief \ru Установить кнопки клавиатуры для выбора объектов в режиме MultiSelection. Можно назначить кнопки:
                   mb_Control; mb_Shift; mb_Alt.
               \en Sets the keyboard keys for the object selection in MultiSelection mode. The following keys can be set:
                   mb_Control; mb_Shift; mb_Alt. \~
        \param[in] vecKey - \ru Массив кодов клавиш.
                            \en The array of the key codes. \~
    */
    VSN_DEPRECATED_X("Do not use this feature, it will be removed in the next version.")
    void SetKeyboardButtonsMultiSelection(const std::vector<int>& vecKey);

    /// \ru Вернуть true, если динамическое выделение включено, или false, если оно выключено. \en Returns true if the dynamic selection is turned on. Otherwise, returns false. \~
    bool IsDynamicHighlighting() const;
    /// \ru Включить или отключить динамическое выделение для геометрии в сцене. \en Turns on/off the dynamic selection for a geometry in the scene. \~
    void SetDynamicHighlighting(bool state);

    /// \ru Вернуть флаг инверсии выбора объектов. \en Returns the invert flag for object selection. \~
    bool IsFlagInverseSelectionMode() const;
    /// \ru Установить флаг инверсии выбора объектов для функций slotObjectReleased и slotObjectPickArea. 
    /// \en Set the inversion flag for object selection for functions OnSelectionObjects. \~
    void SetFlagInverseSelectionMode(bool bInverse);

    /// \ru Вернуть режим выбора объектов в сцене. \en Returns the scene object selection mode. \~
    SelectionManager::SelectionMode GetSelectionMode() const;
    /// \ru Установить режим выбора объектов в сцене. \en Sets the scene object selection mode. \~
    void SetSelectionMode(SelectionManager::SelectionMode mode);
public:
    /// \ru Вернуть указатель на подсвеченный объект. \en Returns a pointer to the highlighted object. \~
    virtual SelectionItem* GetHighlightItem() const;
    /// \ru Вернуть список указателей на SelectionItem. \en Returns the list of the SelectionItem pointers. \~
    virtual const ObjectList<SelectionItem*>& GetSelectionItems() const;
    /// \ru Вернуть true, если элемент находится в списке выбранных. \en Returns true if the item is in the list of selected items. \~
    virtual bool IsSelected(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Вернуть true, если элемент находится в списке выбранных. \en Returns true if the item is in the list of selected items. \~
    virtual bool IsSelected(const NodeKey& key, const NodeKey& itemKey, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Вернуть указателей на SelectionItem. \en Returns the SelectionItem pointers. \~
    virtual SelectionItem* GetSelection(const NodeKey& key, const NodeKey& itemKey, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Добавить элементы в список выбора. \en Adds the items to the selection list. \~
    virtual void Select(const ObjectList<SelectionItem*>& items);
    /// \ru Добавить элементы в список выбора. \en Adds the items to the selection list. \~
    virtual void Select(const ObjectVector<NodeKey>& keys);
    /// \ru Добавить элемент в список выбора. \en Adds the item to the selection list. \~
    virtual void Select(const NodeKey& key, int currenyindexBody = -1, 
        uint currentPrimitiveId = 0, const PointI& pntCursor = PointI());
    /// \ru Добавить элемент в список выбора. \en Adds the item to the selection list. \~
    virtual void Select(const NodeKey& key, const NodeKey& itemKey, int currenyindexBody = -1, 
        uint currentPrimitiveId = 0, const PointI& pntCursor = PointI());
    /// \ru Удалить элемент из списка выбора. \en Removes the item from the selection list. \~
    virtual void Unselect(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Удалить элемент из списка выбора. \en Removes the item from the selection list. \~
    virtual void Unselect(const NodeKey& key, const NodeKey& itemKey, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Удалить все элементы из списка, чтобы они больше не были выделены. \en Removes all items from the selection list to make them no more selected. \~
    virtual void UnselectAll();

    /// \ru Подсветить элемент, имеющий уникальный ключ. \en Highlights the item that has the unique key. \~
    virtual void Highlight(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Подсветить элемент, имеющий уникальный ключ. \en Highlights the item that has the unique key. \~
    virtual void Highlight(const NodeKey& key, const NodeKey& itemKey, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Снять подсветку с элемента. \en Unhighlights item. \~
    virtual void Unhighlight();

    /// \ru Вернуть список указателей на SelectionItem. \en Returns the list of the SelectionItem pointers. \~
    virtual const ObjectList<InstCustomItem*>& GetSelectionCustomItems() const;
    /// \ru Вернуть true, если элемент находится в списке выбранных. \en Returns true if the item is in the list of selected objects. \~
    virtual bool IsCustomSelected(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Добавить элементы в список выбора. \en Adds the items to the selection list. \~
    virtual void CustomSelect(const ObjectList<InstCustomItem*>& items);
    /// \ru Добавить элементы в список выбора. \en Adds the items to the selection list. \~
    virtual void CustomSelect(const ObjectVector<NodeKey>& keys);
    /// \ru Добавляет элемент в пользовательский список выбора. \en Adds the item to the custom selection list. \~
    virtual void CustomSelect(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Удалить элемент из списка пользовательских объектов. \en Removes the item from the list of custom objects. \~
    virtual void CustomUnselect(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Удалить все элементы из списка, чтобы они больше не были выделены. \en Returns all items from the selection list to make them no more selected. \~
    virtual void CustomUnselectAll();
    /// \ru Сбросить список выбора в нуль. \en Resets the selection list. \~
    virtual void ResetCustomSelect();
    /// \ru Вернуть цвет для выбора элемента. \en Returns the selection color. \~
    virtual Color GetCustomSelectionColor() const;
    /// \ru Установить цвет для выбора элемента. \en Sets the selection color. \~
    virtual void SetCustomSelectionColor(const Color& clr);

    /// \ru Вернуть длину списка выбора. \en Returns the selection list size. \~
    int GetSelectedObjectCount() const;
    /// \ru Сбросить список выбора в нуль. \en Resets the selection list. \~
    virtual void ResetSelect();
    /// \ru Сбросить подсвеченный элемент в нуль. \en Resets the highlighted item. \~
    virtual void ResetHighlight();

    /// \ru Вернуть цвет для подсветки элемента. \en Returns the highligthing color. \~
    virtual Color GetHighlightColor() const;
    /// \ru Установить цвет для подсветки элемента. \en Sets the highligthing color. \~
    virtual void SetHighlightColor(const Color& clr);

    /// \ru Вернуть цвет для выбора элемента. \en Returns the selection color. \~
    virtual Color GetSelectionColor() const;
    /// \ru Установить цвет для выбора элемента. \en Sets the selection color. \~
    virtual void SetSelectionColor(const Color& clr);

    /// \ru Селектировать с той же прозрачностью, что и селектируемый материал. \en Select with the same transparency as the material being selected. \~
    bool GetSelectionMatchesTransparency();
    void SetSelectionMatchesTransparency(bool value);

    /// \ru Вернуть значение фильтра объектов (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Returns the object filter value. (It is a convenient function. Calls the ObjectPickSelection function). \~
    Filter GetFilterObject() const;

    /// \ru Вернуть true, если установлен флаг поиска сегмента (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Returns true if the flag for searching segments is set. (It is a convenient function. Calls the ObjectPickSelection function).  \~
    virtual bool IsBodySelectionEnabled() const;
    /// \ru Установить флаг для поиска сегмента (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Sets the flag for searching segments. (It is a convenient function. Calls the ObjectPickSelection function). \~
    virtual void SetBodySelectionEnabled(bool bSelect);

    /// \ru Вернуть true, если установлен флаг поиска граней (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Returns true if the flag for searching faces is set. (It is a convenient function. Calls the ObjectPickSelection function). \~
    virtual bool IsFaceSelectionEnabled() const;
    /// \ru Установить флаг для поиска граней (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Sets the flag for searching faces. (It is a convenient function. Calls the ObjectPickSelection function). \~
    virtual void SetFaceSelectionEnabled(bool bSelect);

    /// \ru Вернуть true, если установлен флаг поиска ребер (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Returns true if the flag for searching edges is set. (It is a convenient function. Calls the ObjectPickSelection function). \~
    virtual bool IsEdgeSelectionEnabled() const;
    /// \ru Установить флаг для поиска ребер (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Sets the flag for searching edges. (It is a convenient function. Calls the ObjectPickSelection function). \~
    virtual void SetEdgeSelectionEnabled(bool bSelect);

    /// \ru Вернуть true, если установлен флаг поиска вершин (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Returns true if the flag for searching vertices is set. (It is a convenient function. Calls the ObjectPickSelection function). \~
    virtual bool IsVertexSelectionEnabled() const;
    /// \ru Установить флаг для поиска вершин (вызывает функцию у ObjectPickSelection, прописано для удобства). \en Sets the flag for searching vertices. (It is a convenient function. Calls the ObjectPickSelection function). \~
    virtual void SetVertexSelectionEnabled(bool bSelect);
public:
    VSN_SIGNAL(Public, signalUnselectAll,          void signalUnselectAll())
    VSN_SIGNAL(Public, signalItemSelectModified,   void signalItemSelectModified())
    VSN_SIGNAL(Public, signalItemsSelectModified,  void signalItemsSelectModified())
    VSN_SIGNAL(Public, signalStateModified,        void signalStateModified())
    VSN_SIGNAL(Public, signalObjectHoverModified,  void signalObjectHoverModified(const InstSelectionItem& hoverItem, bool& bHover), hoverItem, bHover)
    VSN_SIGNAL(Public, signalCurrentItemsModified, void signalCurrentItemsModified(std::list<SelectionItem*>& oldItems, std::list<SelectionItem*>& newItems), oldItems, newItems)
    VSN_SIGNAL(Public, signalMouseSelectionMethodModified, void signalMouseSelectionMethodModified(ActivateMethod method), method)
public:
    /// \ru Удалить все элементы из списка, чтобы они больше не были выделены. \en Removes all items from the selection list to make them no more selected. \~
    VSN_SLOT(Public, slotUnselectAll, void slotUnselectAll())
protected:
    /// \ru При нажатии клавиши мыши сигнал становится активным. \en When pressing a mouse button, the signal becomes active. \~
    VSN_SLOT(Protected, slotObjectPressed,   virtual void slotObjectPressed(PickSelectionEventPtr, bool))
    /// \ru При отпускании клавиши мыши сигнал становится активным. \en When releasing a mouse button, the signal becomes active. \~
    VSN_SLOT(Protected, slotObjectReleased,  virtual void slotObjectReleased(PickSelectionEventPtr, bool))
    /// \ru При движении мыши сигнал становится активным. \en When moving the mouse, the signal becomes active. \~
    VSN_SLOT(Protected, slotObjectHoverMove, virtual void slotObjectHoverMove(PickSelectionEventPtr))
    /// \ru При выборе объектов рамкой слот будет вызван. \en When selecting objects with the frame, the slot is called. \~
    VSN_SLOT(Protected, slotObjectPickArea,  virtual void slotObjectPickArea(PickAreaSelectionEventPtr, bool))
private:
    VSN_DISABLE_COPY(SelectionManager);
    VSN_DECLARE_EX_PRIVATE(SelectionManager);
};

typedef std::shared_ptr<SelectionManager> SelectionManagerPtr;

} // namespace VSN

#endif // __SELECTIONMANAGER_H
