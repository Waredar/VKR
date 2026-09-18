////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс Painter - набор инструментов предназначеных для рисования на холсте.
         \en -. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PAINTER_H
#define __VSN_PAINTER_H

#include <vector>
#include <vsn_point.h>
#include <vsn_pen.h>
#include <vsn_global.h>

class MbCartPoint;
class MbRect;
class MbContour;
class MbDirection;
class MbCurve;
class MbRegion;

namespace VSN {

class Texture2D;
class Canvas;
class BaseBrush;
class PainterPrivate;
class Image;

/// \ru Набор умолчательных маркеров. \en Default markers set. \~
enum class PlaneMarkers : int
{
  Arrow,
  Triangle,
  Square,
  Cross,
};

//------------------------------------------------------------------------------
/** \brief \ru . Инструмент для рисования на холсте.
           \en . Canvas painting tool\~
           \details \ru Предоставляет следующие возможности: \n
                         - рисовать на холсте стандартные примитивы(окружность, прямоугольник и т.д.), а так же плоские математические кривые(MbCurve) \n
                         - рисовать изображение  \n
                         - устанавливать заливки  \n
                         - рисовать маркеры  \n

                    \en  Provides the following features:\n 
                         - draw standard primitives (circles, rectangles, etc.) on canvas, as well as mathematical curves(MbCurve) \n
                         - draw image  \n
                         - set fills  \n
                         - draw markers \n
                    \~
*/
// ---
class VSN_CLASS Painter
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    Painter();
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit Painter(Canvas& init);
    ~Painter();
protected:
    /// \ru Активировать рисовальщик перед рисованием. \en Activate the painter before drawing. \~
    void Begin(Canvas& init);
    /// \ru Закончить рисование. \en Stop the drawing. \~
    void End();
public:
    /// \ru Нарисовать отрезок. \en Draw the line segment. \~
    void DrawLine(const PointF& p1, const PointF& p2);
    /// \ru Нарисовать прямоугольник. \en Draw the rectangle. \~
    void DrawRect(const PointF& lb, const PointF& rt);
    /// \ru Залить прямоугольник. \en Fill the rectangle. \~
    void DrawFillRect(const PointF& lb, const PointF& rt);
    /// \ru Нарисовать прямоугольник. \en Draw the rectangle. \~
    void DrawAroundRect(const PointF& lb, const PointF& rt, float r);
    /// \ru Залить прямоугольник. \en Fill the rectangle. \~
    void DrawFillAroundRect(const PointF& lb, const PointF& rt, float r);
    /// \ru Залить окружность. \en Fill the circle. \~
    void DrawFillCircle(const PointF& origin, float r);
    /// \ru Нарисовать окружность. \en Draw the circle. \~
    void DrawCircle(const PointF& origin, float r);
    /// \ru Нарисовать дугу окружности. \en Draw the arc of circle. \~
    void DrawArc(const PointF& origin, float r, float begin, float end);
    /// \ru Нарисовать эллипс. \en Draw the эллипс. \~
    void DrawEllipse(const PointF& origin, float fMinor, float fMajor);
    /// \ru Нарисовать изображение. \en Draw the image. \~
    void DrawImage(const PointF& pos, const Image& img);
    /// \ru Нарисовать отрезки по массиву точек. \en Draw lines by points array. \~
    void DrawLinesPath(const std::vector<PointF>& points);
    /// \ru Нарисовать треугольники по массиву точек. \en Draw triangles by points array. \~
    void DrawTrianglesPath(const std::vector<PointF>& points);
    /// \ru Нарисовать маркер. \en Draw the marker. \~
    void DrawMarker(PlaneMarkers, const PointF& pos, const MbDirection& xAxis);
public:
    /// \ru Нарисовать математическую кривую. \en Draw math curve. \~
    void DrawMathCurve(const MbCurve& curve);
    /// \ru Нарисовать математический регион. \en Draw math region. \~
    void DrawMathRegion(const MbRegion& region);
public:
    /// \ru Задать параметры пера. \en Set parameters of the pen. \~
    void SetPen(const Pen& pen, bool correct = false, bool endDash = false);
    /// \ru Задать параметры заливки. \en Set parameters of the brush. \~
    void SetFillBrush(const BaseBrush& params);
private:
    VSN_DECLARE_PRIVATE(Painter)
};

} // namespace VSN

#endif //__VSN_PAINTER_H
