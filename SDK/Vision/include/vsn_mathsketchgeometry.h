////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Класс MathSketchGeometry представляет геометрию для последующей отрисовки,
которая была сгенерирована с помощью математического представления.
\en Class MathSketchGeometry presents geometry for next rendering that was
generated with math representation. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SKETCHGEOMETRY_H
#define __VSN_SKETCHGEOMETRY_H

#include <plane_instance.h>
#include <region.h>

#include <vsn_wireframegeometry.h>
#include <vsn_sketchitems.h>
#include <vsn_global.h>

namespace VSN {

class MathSketchGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MathSketchGeometry представляет геометрию для последующей отрисовки, которая была сгенерирована с помощью математического представления.
            \en Class MathSketchGeometry presents geometry for next rendering that was generated with math representation. \~
        \details \ru Класс MathSketchGeometry принимает указатель на математическое представление эскиза MbPlaneInstance для последующей генерации визуального представления.
                    Класс MathSketchGeometry представляет ряд полезных функций. С помощью функции GetMathNameByGeometry GetGeometryNameByMath вы можете получить идентификацию примитивов из
                    визуального представления в математическое и наоборот.
                    Этот класс находиться в разработке, его конечное представление может отличаться от текущего.\n.
                \en NO TRANSLATION;

*/
// ---
class VSN_CLASS MathSketchGeometry final : public WireframeGeometry
{
    VSN_OBJECT(MathSketchGeometry);
public:
    /// \ru Конструктор. \en Constructor. \~
    MathSketchGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~MathSketchGeometry();
public:
    /// \ru Добавить элемент эскиза. \en Add the sketch item. \~
    void AddItem(std::shared_ptr<SketchItem> item);
    /// \ru Искать элемент эскиза по ключу. \en Find the sketch item by key. \~
    std::shared_ptr<SketchItem> FindItem(NodeKey) const;
    /// \ru Удалить элемент эскиза. \en Remove the sketch item. \~
    std::shared_ptr<SketchItem> RemoveItem(NodeKey);
    /// \ru Получить элемент эскиза по индексу. \en Get the sketch item by index. \~
    std::shared_ptr<SketchItem> GetItem(size_t index) const;
    /// \ru Получить кол-во элементов в эскизе. \en Get the number of sketch items. \~
    size_t GetCountItems() const;
    /// \ru Очистить эскиз. \en Clear the sketch. \~
    void Clear();
    /// \ru Построить геометрию эскиза. \en Build sketch geometry. \~
    void Rebuild(const MbPlaneInstance & instance);

public:
    /// \ru Изменить плоскость эскиза. \en NO TRANSLATION. \~
    void SetPlacement(const MbPlacement3D & placement);
    /// \ru Получить плоскость эскиза. \en NO TRANSLATION. \~
    MbPlacement3D GetPlacement() const;
    /// \ru Получить размер эскиза. \en NO TRANSLATION. \~
    MbRect GetSize() const;
public:
    /// \ru Добавить математическую кривую. \en NO TRANSLATION. \~
    std::shared_ptr<SketchItem> AddMathCurve(MbCurve*);
    /// \ru Добавить математические кривые. \en NO TRANSLATION. \~
    std::list<std::shared_ptr<SketchItem>> AddMathCurves(const std::vector<MbCurve*> & curves);
public:
    /// \ru Получить габаритный куб объекта. \en Returns object bounding box. \~
    virtual const BoundingBox& GetBoundingBox() const override;
    /// \ru Найти элементы эскиза рядом с точкой. \en NO TRANSLATION. \~
    std::list<SketchItem*> FindItems( const MbCartPoint & point, double hatchSize ) const;
private:
    virtual void Render(RenderContext &) override;
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(MathSketchGeometry);
    VSN_DECLARE_EX_PRIVATE(MathSketchGeometry);
};

} // namespace VSN

#endif /* __VSN_SKETCHGEOMETRY_H */
