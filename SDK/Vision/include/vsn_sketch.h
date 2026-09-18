////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Класс MathSketch . \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SKETCH_H
#define __VSN_SKETCH_H

#include <plane_instance.h>
#include <vsn_sketchitems.h>
#include <vsn_geometryrep.h>
#include <vsn_global.h>

namespace VSN {

class MathSketchPrivate;
//------------------------------------------------------------------------------
/** \brief \ru  Класс Эскиза предназначеный для работы с плоскими математическими кривыми.
            \en NO TRANSLATION. \~
        \details \ru Реализация эскиза позволяет:
                        - Подсвечивать объекты эскиза.\n.
                        - Селектировать объекты эскиза. \n
                        - осуществлять поиск объектов эскиза под курсором. \n
                        - задавать стили линий математическим кривым
                \en NO TRANSLATION;
*/
// ---
class VSN_CLASS MathSketch final : public GeometryRep
{
    VSN_OBJECT(MathSketch);
public:
    /// \ru Конструктор. \en Constructor. \~
    MathSketch(Node* pParent = nullptr);
    /// \ru Конструктор. \en Constructor. \~
    MathSketch(const MbPlacement3D & placement, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~MathSketch();
public:
    /// \ru Добавить элемент эскиза. \en Add the sketch item. \~
    void AddItem(std::shared_ptr<SketchItem> item);
    /// \ru Искать элемент эскиза по ключу. \en Find the sketch item by key. \~
    std::shared_ptr<SketchItem> FindItem(const NodeKey& key) const;
    /// \ru Удалить элемент эскиза. \en Remove the sketch item. \~
    std::shared_ptr<SketchItem> RemoveItem(const NodeKey& key);
    /// \ru Получить элемент эскиза по индексу. \en Get the sketch item by index. \~
    std::shared_ptr<SketchItem> GetItem(size_t index) const;
    /// \ru Получить кол-во элементов в эскизе. \en Get the number of sketch items. \~
    size_t GetCountItems() const;
    /// \ru Очистить эскиз. \en Clear the sketch. \~
    void Clear();
    /// \ru Построить геометрию эскиза. \en Build sketch geometry. \~
    void Rebuild(const MbPlaneInstance& instance);

    /// \ru Изменить плоскость эскиза. \en NO TRANSLATION. \~
    void SetPlacement(const MbPlacement3D& placement);
    /// \ru Получить плоскость эскиза. \en NO TRANSLATION. \~
    MbPlacement3D GetPlacement() const;
public:
    /// \ru Добавить математическую кривую. \en NO TRANSLATION. \~
    std::shared_ptr<SketchItem> AddMathCurve(MbCurve* pCurve);
    /// \ru Добавить математические кривые. \en NO TRANSLATION. \~
    std::list<std::shared_ptr<SketchItem>> AddMathCurves(const std::vector<MbCurve*> & curves);
public:
    /// \ru Получить размер эскиза. \en NO TRANSLATION. \~
    MbRect GetSize() const;
    /// \ru Найти элементы эскиза рядом с точкой. \en NO TRANSLATION. \~
    std::list<SketchItem*> FindItems(const MbCartPoint& point, double hatchSize) const;
private:
    VSN_DISABLE_COPY(MathSketch);
    VSN_DECLARE_EX_PRIVATE(MathSketch);
};

} // namespace VSN

#endif /* __VSN_SKETCHGEOMETRY_H */
