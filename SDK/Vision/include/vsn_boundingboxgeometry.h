////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru BoundingBoxGeometry является ограничивающим параллелепипедом и служит для
             отображения информационного габарита узла в сцене по указанному сегменту.
         \en BoundingBoxGeometry is bounding box and serves for displaying
             an informational graph size in a scene by specified segment. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_BOUNDINGBOXGEOMETRY_H
#define __VSN_BOUNDINGBOXGEOMETRY_H

#include <vsn_wireframegeometry.h>
#include <vsn_global.h>

namespace VSN {

class SceneSegment;
class BoundingBoxGeometryBasePrivate;
//------------------------------------------------------------------------------
/** \brief \ru BoundingBoxGeometryBase это базовый класс для габаритного параллелепипеда.
           \en BoundingBoxGeometryBase is a base class for bounding boxes. \~
  \details \ru BoundingBoxGeometryBase имеет возможность менять цвет основных осей X, Y, Z,
               способ построения задается в производных классах. \n.
           \en BoundingBoxGeometryBase has an opportunity to change a color of main axes X, Y, Z.
               The way it's built is set in derived classes. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS BoundingBoxGeometryBase : public WireframeGeometry
{
    VSN_OBJECT(BoundingBoxGeometryBase);
public:
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~BoundingBoxGeometryBase();
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for internal use. \~
    BoundingBoxGeometryBase(BoundingBoxGeometryBasePrivate&, Node*);
public:
    /// \ru Вернуть цвет заданной оси. \en Returns color of given axis. \~
    Color GetColorAxis(AxisOrientation orientation) const;
    /// \ru Установить цвет заданной оси. \en Sets color of given axis. \~
    void SetColorAxis(AxisOrientation orientation, const Color& color);
    /// \ru Вернуть видимость BoundingBox. \en Returns visibility of the BoundingBox. \~
    bool IsVisible() const;
    /// \ru Установить видимость BoundingBox. \en Sets visibility of the BoundingBox. \~
    void SetVisible(bool visible);
public:
    /// \ru Вернуть ограничивающий параллелепипед. \en Returns bounding box. \~
    virtual const BoundingBox& GetBoundingBox() const override;
    /// \ru Блокировать PixelCulling для этой геометрии. \en Blocks PixelCulling for this geometry. \~
    virtual bool IsIgnorePixelCulling() const override;
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data. \~
    virtual void UpdateGeometry() override;
    virtual BoundingBox GetBoxToShow() const = 0;
protected:
    /// \ru Обновить BoundingBox. \en Update bounding box of geometry. \~
    void UpdateBoundingBox();
public: // signals
    /// \ru Сигнал будет генерирован при изменении габарита сегмента. \en Signal will be generated when modifying segment size. \~
    VSN_SIGNAL(Public, OnGeometryModified, void OnGeometryModified())
private:
    /// \ru Отрисовать параллелепипед с помощью OpenGL. \en Renders box with OpenGL. \~
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    /// \ru Создать каркасное представление. \en Creates wireframe representation. \~
    void BuildWireFrameBox();
private:
    VSN_DECLARE_EX_PRIVATE(BoundingBoxGeometryBase);
};

class BoundingBoxGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru BoundingBoxGeometry является ограничивающим параллелепипедом и служит для
               отображения информационного габарита узла в сцене по указанному сегменту.
           \en BoundingBoxGeometry is bounding box and serves for displaying
               an informational graph size in a scene by specified segment. \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS BoundingBoxGeometry : public BoundingBoxGeometryBase
{
    VSN_OBJECT(BoundingBoxGeometry);
public:
    BoundingBoxGeometry(Node* pParent = nullptr);
public:
    /// \ru Вернуть ограничивающий прямоугольник сегмента. \en Returns bounding box of segment. \~
    /// \ru Результат совпадает с GetBoxToShow(). \en Same result as GetBoxToShow(). \~
    BoundingBox GetSegmentBoundingBox() const;

    /// \ru Вернуть указатель на начальный сегмент. \en Returns pointer to initial segment. \~
    const SceneSegment* GetSceneSegment() const;
    /// \ru Установить начальный сегмент для отображения его габарита в сцене. \en Sets initial segment for displaying its size in scene. \~
    void SetSceneSegment(const SceneSegment* pSegment);
    /// \ru Получить габарит, который задан для отображения. \en Returns the bounding box that is set to draw. \~
    BoundingBox GetBoxToShow() const override;
protected:
private: // slots
/// \ru Удаление указателя на SceneSegment. \en Removing a pointer to a SceneSegment. \~
    VSN_SLOT(Private, OnSegmentDestroyed, void OnSegmentDestroyed())
private:
    VSN_DECLARE_EX_PRIVATE(BoundingBoxGeometry);
};

class RawBoundingBoxGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru RawBoundingBoxGeometry это ограничивающий параллелепипед,
               который строится непосредственно с заданного MbCube.
           \en BoundingBoxGeometry is bounding box that is built directly from specified
               MbCube. \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS RawBoundingBoxGeometry : public BoundingBoxGeometryBase
{
    VSN_OBJECT(RawBoundingBoxGeometry);
public:
    RawBoundingBoxGeometry(Node* pParent = nullptr);
public:
    /// \ru Получить габарит, который задан для отображения. \en Returns the bounding box that is set to draw. \~
    BoundingBox GetBoxToShow() const override;
    /// \ru Установить габарит, который требуется отобразить. \en Set bounding box to draw. \~
    void SetBoxToShow(const BoundingBox& box);
private:
    VSN_DECLARE_EX_PRIVATE(RawBoundingBoxGeometry);
protected:

};

} // namespace VSN

#endif /* __VSN_BOUNDINGBOXGEOMETRY_H */
