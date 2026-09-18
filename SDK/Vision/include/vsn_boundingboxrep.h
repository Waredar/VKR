////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс BoundingBoxRep является вспомогательным классом и представляет API 
             для управления геометрией BoundingBoxGeometry. BoundingBoxRep 
             является представлением ограничивающего параллелепипеда и служит
             для отображения информационного габарита узла в сцене по указанному 
             сегменту и вывода численых значений по всем осям в виде
             шкалы.
         \en BoundingBoxRep class is an auxiliary class and presents API to control
             BoundingBoxGeometry geometry. BoundingBoxRep class is a representation of
             a bounding box and serves for displaying informational graph size in a scene
             by the specified segment and outputting numerical values of all axes in the form
             of a scale. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BOUNDINGBOXREP_H
#define __VSN_BOUNDINGBOXREP_H

#include <vsn_geometryrep.h>
#include <vsn_namespace.h>
#include <vsn_global.h>

namespace VSN {

class SceneSegment;
class BoundingBoxRepBasePrivate;
class BoundingBoxGeometryBase;
class Font;

//------------------------------------------------------------------------------
/** \brief \ru BoxCoord служит для идентификации вершины габаритного куба по одной из осей.
           \en BoxCoord is used to identify a bounding box vertex for a specific axis. \~
  \details \ru . \n.
           \en . \n \~
  \ingroup Vision_Geometry
*/
// ---
enum class BoxCoord
{
    min,
    max
};

//------------------------------------------------------------------------------
/** \brief \ru BoxVertex представляет вершину габаритного куба.
               Например, {min, min, min} это точка с минимальными координатами по всем осям.
           \en BoxVertex represents a bounding box vertex.
           e.g. {min, min, min} is the point with the minimal coordinates along all axes \~
  \ingroup Vision_Geometry
*/
// ---
struct BoxVertex
{
    BoxCoord x = BoxCoord::min;
    BoxCoord y = BoxCoord::min;
    BoxCoord z = BoxCoord::min;
};

//------------------------------------------------------------------------------
/** \brief \ru BoundingBoxRepBase является базовым классом для представлений ограничивающего
               параллелепипеда и служит для отображения информационного габарита в сцене 
               и вывода численых значений по всем осям в виде шкалы.
           \en BoundingBoxRepBase class is a base class for representations of a bounding box
               and serves for displaying informational graph size in a scene and
               outputting numerical values of all axes in the form of a scale. \~
  \details \ru BoundingBoxRepBase имеет ряд полезных функций с помощью которых можно изменить
               толщину линий осей, изменить их цвет. BoundingBoxRep дает возможность 
               настроить вид отображения шкалы, ее направления, а также видимость. Есть
               возможность настройки начала координат, совпадение начала координат с миром
               или начала вектора направления осей. \n.
           \en BoundingBoxRepBase class has a set of useful functions with which you can change
               a thickness of axis lines, change their color. BoundingBoxRep class gives
               an opportunity to set a view of scale displaying, its direction, and also
               visibility. There is a capability of setting origin, a match of origin
               to world and vector origin of axis direction. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS BoundingBoxRepBase : public GeometryRep
{
    VSN_OBJECT(BoundingBoxRepBase)
public:
    /// \ru Деструктор. \en Destructor. 
    virtual ~BoundingBoxRepBase();
protected:
    /// \ru Для внутреннего использования. \en For internal use. \~
    explicit BoundingBoxRepBase(BoundingBoxGeometryBase* boxObject);
public:
    /// \ru Вернуть видимость BoundingBox. \en Returns visibility of the BoundingBox. \~
    bool IsVisibleBoundingBox() const;
    /// \ru Установить видимость BoundingBox. \en Sets visibility of the BoundingBox. \~
    void SetVisibleBoundingBox(bool visible);

    /// \ru Вернуть видимость указанной оси. \en Returns visibility of the specified axis. \~
    bool IsVisibleAxis(AxisOrientation orientation) const;
    /// \ru Установить видимость указанной оси. \en Sets visibility of the specified axis. \~
    void SetVisibleAxis(AxisOrientation orientation, bool visible);

    /// \ru Вернуть видимость наконечника указанной оси. \en Returns visibility of the specified axis end. \~
    bool IsVisibleTips(AxisOrientation orientation) const;
    /// \ru Установить видимость наконечника указанной оси. \en Sets visibility of the specified axis end. \~
    void SetVisibleTips(AxisOrientation orientation, bool visible);

    /// \ru Вернуть видимость текста меток указанной оси. \en Returns visibility of the specified axis label text. \~
    bool IsVisibleLabels(AxisOrientation orientation) const;
    /// \ru Установить видимость текста меток указанной оси. \en Sets visibility of the specified axis label text. \~
    void SetVisibleLabels(AxisOrientation orientation, bool visible);

    /// \ru Вернуть обратное направление указанной оси. \en Returns a reversed specified axis. \~
    bool IsReversedAxis(AxisOrientation orientation) const;
    /// \ru Установить обратное направление указанной оси. \en Sets a reversed specified axis. \~
    void SetReversedAxis(AxisOrientation orientation, bool bEnabled);

    /// \ru Вернуть признак совпадения с миром начала координат. Если true, то начало координат совпадает с миром. \en Returns a flag of matching origin to world. If true, origin matches to world. \~
    bool IsAutoAdjustOrigin(AxisOrientation orientation) const;
    /// \ru Установить совпадение начала координат с миром. Если true, то начала координат совпадают с миром. \en Sets a flag of matching origin to world. If true, origin matches to world. \~
    void SetAutoAdjustOrigin(AxisOrientation orientation, bool bAuto);

    /// \ru Вернуть количество рисок шкалы по указанной оси. \en Returns a quantity of scale lines by the specified axis. \~
    int GetSegmentCount(AxisOrientation orientation) const;
    /// \ru Установить количество рисок шкалы по указанной оси. \en Sets a quantity of scale lines by the specified axis. \~
    void SetSegmentCount(AxisOrientation orientation, int count);

    /// \ru Вернуть размер рисок шкалы по указанной оси. \en Returns a size of tip by the specified axis. \~
    float GetTipSize(AxisOrientation orientation) const;
    /// \ru Установить размер наконечника по указанной оси. \en Sets a size of tip by the specified axis. \~
    void SetTipSize(AxisOrientation orientation, float size);

    /// \ru Вернуть размер рисок шкалы по указанной оси. \en Returns a size of scale lines by the specified axis. \~
    float GetSegmentSize(AxisOrientation orientation) const;
    /// \ru Установить размер рисок шкалы по указанной оси. \en Sets a size of scale lines by the specified axis. \~
    void SetSegmentSize(AxisOrientation orientation, float size);

    /// \ru Вернуть формат отображения значений по указанной оси. \en Returns format of displaying values by the specified axis. \~
    int GetFormatPrecision(AxisOrientation orientation) const;
    /// \ru Установить формат отображения значений по указанной оси. \en Sets format of displaying values by the specified axis. \~
    void SetFormatPrecision(AxisOrientation orientation, int precision);

    /// \ru Вернуть толщину ребра ограничивающего параллелепипеда. \en Returns a thickness of bounding box edge. \~
    float GetBoundingBoxEdgeWidth() const;
    /// \ru Установить толщину ребра ограничивающего параллелепипеда. \en Sets a thickness of bounding box edge. \~
    void SetBoundingBoxEdgeWidth(float width);

    /// \ru Вернуть толщину оси. \en Returns a thickness of axis. \~
    float GetAxisThickness(AxisOrientation orientation) const;
    /// \ru Установить толщину оси. \en Sets a thickness of axis. \~
    void SetAxisThickness(AxisOrientation orientation, float width);

    /// \ru Вернуть видимость габаритного размера параллелепипеда. \en Returns visibility of a bounding box size. \~
    bool IsDimensionVisible() const;
    /// \ru Установить видимость габаритного размера параллелепипеда. \en Sets visibility of a bounding box size. \~
    void SetDimensionVisible(bool bVisible);

    /// \ru Вернуть цвет размеров. \en Returns size color. \~
    Color GetColorDimension() const;
    /// \ru Установить цвет размеров. \en Sets size color. \~
    void SetColorDimension(const Color& color);

    /// \ru Вернуть цвет указанной оси. \en Returns a color of the specified axis. \~
    Color GetColorAxis(AxisOrientation orientation) const;
    /// \ru Установить цвет указанной оси. \en Sets a color of the specified axis. \~
    void SetColorAxis(AxisOrientation orientation, const Color& color);

    /// \ru Вернуть цвет текста указанной оси. \en Returns a text color of the specified axis. \~
    Color GetColorLabels(AxisOrientation orientation) const;
    /// \ru Установить цвет текста указанной оси. \en Sets a text color of the specified axis. \~
    void SetColorLabels(AxisOrientation orientation, const Color& color);

    /// \ru Вернуть размер шрифта текста указанной оси. \en Returns a font size of the specified axis. \~
    uint GetFontSizeLabels(AxisOrientation orientation) const;
    /// \ru Установить размер шрифта текста указанной оси. \en Sets a font size of the specified axis. \~
    void SetFontSizeLabels(AxisOrientation orientation, uint size);

    /// \ru Получить шрифт текста. \en Get the font of the text.\~
    const Font& GetFontLabels(AxisOrientation orientation) const;
    /// \ru Задать шрифт текста. \en Set the font of the text.\~
    void SetFontLabels(AxisOrientation orientation, const Font& font);
    /// \ru Задать шрифт текста. \en Set the font of the text.\~
    void SetFontLabels(const Font& font);

    /// \ru Вкл./Выкл. масштабирование текста. \en Text scaling on/off.\~
    bool GetScaleLabels(AxisOrientation orientation) const;
    void SetScaleLabels(AxisOrientation orientation, bool scale);

    /// \ru Вернуть толщину указанной оси. \en Returns a Thickness of the specified axis. \~
    float GetThicknessAxis(AxisOrientation orientation) const;
    /// \ru Установить толщину указанной оси. \en Sets a thickness of the specified axis. \~
    void SetThicknessAxis(AxisOrientation orientation, float thickness);

    /// \ru Получить начальную точку координатных осей. \en Get axes origin. \~
    BoxVertex GetAxesOrigin() const;
    /// \ru Установить начальную точку координатных осей. \en Set axes origin. \~
    void SetAxesOrigin(const BoxVertex& origin);
public:
    VSN_SLOT(Protected, BoundingBoxModified, void BoundingBoxModified())
protected:
    VSN_DECLARE_EX_PRIVATE(BoundingBoxRepBase);
};

//------------------------------------------------------------------------------
/** \brief \ru BoundingBoxRep это представления для BoundingBoxGeometry.
           \en BoundingBoxRep is the representation for BoundingBoxGeometry. \~
*/
// ---
class VSN_CLASS BoundingBoxRep : public BoundingBoxRepBase
{
    VSN_OBJECT(BoundingBoxRep);
public:
    BoundingBoxRep();
public:
    /// \ru Вернуть указатель на начальный сегмент. \en Returns a pointer to initial segment. \~
    const SceneSegment* GetSceneSegment() const;
    /// \ru Установить начальный сегмент для отображения его габарита в сцене. \en Sets initial segment to display its size in a scene. \~
    void SetSceneSegment(const SceneSegment* pSegment);
};

//------------------------------------------------------------------------------
/** \brief \ru RawBoundingBoxRep это представления для RawBoundingBoxGeometry,
               то есть ограничивающий параллелепипед, который строится непосредственно
               с заданного MbCube.
           \en RawBoundingBoxRep is the representation for RawBoundingBoxGeometry, that is,
               bounding box that is built directly from the specified
               MbCube. \~
*/
// ---
class VSN_CLASS RawBoundingBoxRep : public BoundingBoxRepBase
{
    VSN_OBJECT(RawBoundingBoxRep);
public:
    RawBoundingBoxRep();
public:
    /// \ru Получить габарит, который задан для отображения. \en Returns the bounding box that is set to draw. \~
    MbCube GetBoxToShow() const;
    /// \ru Установить габарит, который требуется отобразить. \en Set bounding box to draw. \~
    void SetBoxToShow(const MbCube& box);
};

} // namespace VSN

#endif /* __VSN_BOUNDINGBOXREP_H */
