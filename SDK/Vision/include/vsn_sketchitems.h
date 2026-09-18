////////////////////////////////////////////////////////////////////////////////
/**
    \file
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SKETITEMS_H
#define __VSN_SKETITEMS_H

#include <vsn_global.h>
#include <vsn_node.h>
#include <vsn_pen.h>

namespace VSN {

class Canvas;
class MathSketchGeometry;
class NodePrivate;
/* LineStyles */
enum class LineStyles : uint
{
    Default,
    Axis,
    Custom,
};

enum class PointStyles : uint
{
    Default,
    Custom,
};

//------------------------------------------------------------------------------
/** \brief \ru Базовый класс элементов эскиза .
            \en NO TRANSLATION. \~
*/
// ---
class SketchItemPrivate;
/* SketchItem */
class VSN_CLASS SketchItem : public Node
{
public:
    /// \ru Конструктор. \en NO TRANSLATION \~
    SketchItem();
public:
    /// \ru Узнать являеться текущее представление неверным. \en NO TRANSLATION \~
    bool IsInvalid()  const;
    /// \ru Сделать текущее представление неверным. \en NO TRANSLATION \~
    void Invalidate();

    /// \ru Узнать являеться элемент выделеным. \en NO TRANSLATION \~
    bool IsSelected() const;
    /// \ru Выделить элемент. \en NO TRANSLATION \~
    void Select(bool);
    /// \ru Узнать являеться элемент подсвеченым. \en NO TRANSLATION \~
    bool IsHighlighted() const;
    /// \ru Подстветить элемент. \en NO TRANSLATION \~
    void Highlight(bool);
public:
    /// \ru Функция для рисования плоского представления элемента. \en NO TRANSLATION \~
    virtual void   OnDraw(Canvas & canvas) const = 0;
    /// \ru Функция поиска ближайшей точки на элементе. \en NO TRANSLATION \~
    virtual bool   OnFind( const MbCartPoint & in, MbCartPoint & out, const double & maxDistance) const = 0;
    /// \ru Получить размер элемента. \en NO TRANSLATION \~
    virtual MbRect GetSize(double scale) const = 0;
protected:
    /// \ru Конструктор. \en NO TRANSLATION \~
    SketchItem(NodePrivate &);
public:
    VSN_DECLARE_EX_PRIVATE(SketchItem);
};

//------------------------------------------------------------------------------
/** \brief \ru Элемент эскиза необходимый для отображения точки на эскизе.
            \en NO TRANSLATION. \~
*/
// ---
class MathSketchPointPrivate;
/* MathSketchPoint */
class VSN_CLASS MathSketchPoint : public SketchItem
{
public:
    /// \ru Конструктор. \en NO TRANSLATION \~
    MathSketchPoint(MbCartPoint point);
    /// \ru Конструктор с указанием стиля. \en NO TRANSLATION \~
    MathSketchPoint(MbCartPoint point, PointStyles styleId);
public:               
    /// \ru Задапть точку. \en NO TRANSLATION \~
    void                SetPoint(const MbCartPoint & pos);
    /// \ru Получить точку. \en NO TRANSLATION \~
    const MbCartPoint & GetPoint() const;
public:
    /// \ru Задапть стиль точки. \en NO TRANSLATION \~
    void                SetStyle(PointStyles styleId);
    /// \ru Получить стиль точки. \en NO TRANSLATION \~
    PointStyles         GetStyle() const;
    /// \ru Установить пользовательский цвет точки. \en NO TRANSLATION. \~
    void SetCustomColor(Color color);
    /// \ru Получить пользовательский цвет точки. \en NO TRANSLATION. \~
    const Color GetCustomColor() const;
private:
    virtual void   OnDraw(Canvas & canvas) const override;
    virtual bool   OnFind(const MbCartPoint & in, MbCartPoint & out, const double & maxDistance) const override;
    virtual MbRect GetSize(double scale) const override;
    VSN_DECLARE_EX_PRIVATE(MathSketchPoint);
};

class MathSketchCurvePrivate;
//------------------------------------------------------------------------------
/** \brief \ru Элемент эскиза необходимый для отображения математических кривых MbCurve .
            \en NO TRANSLATION. \~
        \details \ru Класс представляет возможность отображать математические кривые (MbCurve) на эскизе с разными стилями.
                 \en NO TRANSLATION;
*/
// ---
/* MathSketchCurve */
class VSN_CLASS MathSketchCurve : public SketchItem
{
public:
    /// \ru Конструктор. \en NO TRANSLATION \~
    MathSketchCurve(SPtr<const MbCurve> pCurve);
    /// \ru Конструктор с указанием стиля. \en NO TRANSLATION \~
    MathSketchCurve(SPtr<const MbCurve> pCurve, LineStyles styleId);
public:
    /// \ru Задать стиль кривой. \en NO TRANSLATION \~
    void       SetStyle(LineStyles styleId);
    /// \ru Получить стиль кривой. \en NO TRANSLATION \~
    LineStyles GetStyle() const;
    /// \ru Задать кривую. \en NO TRANSLATION \~
    void            SetCurve(SPtr<const MbCurve> curve);
    /// \ru Получить кривую. \en NO TRANSLATION \~
    const MbCurve & GetCurve() const;
    /// \ru Установить перо кривой для пользователького типа. \en NO TRANSLATION. \~
    void SetCustomPen(Pen pen);
    /// \ru Получить перо кривой для пользователького типа. \en NO TRANSLATION. \~
    const Pen GetCustomPen() const;
private:
    virtual void   OnDraw(Canvas & canvas) const override;
    virtual bool   OnFind(const MbCartPoint & in, MbCartPoint & out, const double & maxDistance) const override;
    virtual MbRect GetSize(double scale) const override;

    VSN_DECLARE_EX_PRIVATE(MathSketchCurve);
};

} // namespace VSN

#endif /* __VSN_SKETITEMS_H */
