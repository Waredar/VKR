////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс RectI описывает прямоугольник в плоскости и использует целочисленную точность.
         \en RectI class defines rectangle in the plane using integer precision. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_RECT_H
#define __VSN_RECT_H

#include <mb_rect.h>

#include <vsn_point.h>
#include <vsn_size.h>
#include <vsn_global.h>

namespace VSN {

class Fields;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс RectI описывает прямоугольник в плоскости и использует целочисленную точность.
           \en RectI class defines rectangle in the plane using integer precision. \~
    \details \ru Прямоугольник, как правило, выражается в виде верхнего левого угла и размера. 
                 Прямоугольник может быть построен с помощью целочисленных координат слева, сверху, ширины и высоты, или при помощи классов PointI и SizeI. 
                 Класс RectI предоставляет набор функций, которые возвращают необходимые координаты прямоугольника и позволяют их инициализировать. 
                 Класс RectI также предоставляет функции, которые дают возможность перемещать прямоугольник относительно его координат и т.д. \n
             \en Rectangle is typically expressed as top-left angle and size.
                 Rectangle can be constructed with integer coordinates of left, top, width and height, or with PointI and SizeI classes.
                 RectI class provides a set of functions that return necessary coordinates of the rectangle and allow initializing them. 
                 RectI class also provides functions for moving the rectangle about its coordinates, etc. \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS RectI
{
public:
    /// \ru Конструктор по умолчанию. Создает пустой прямоугольник. \en Default constructor for creating empty rectangle.
    RectI();
    /// \ru Специальный конструктор прямоугольника с заданием верхнего левого и нижнего правого угла. \en Special rectangle constructor with setting the top-left and bottom-right angle.
    RectI(const PointI& topleft, const PointI& bottomright);
    /// \ru Специальный конструктор прямоугольника с заданием координат верхнего левого угла и размера прямоугольника. \en Special rectangle constructor with setting top-left angle coordinates and rectangle size.
    RectI(const PointI& topleft, const SizeI& size);
    /// \ru Специальный конструктор прямоугольника с заданием координат верхнего левого угла и размера прямоугольника. \en Special rectangle constructor with setting top-left angle coordinates and rectangle size.
    RectI(int left, int top, int width, int height);
public:
    /** \brief \ru Инициализация прямоугольника с заданием координат верхнего левого угла и размера прямоугольника.
                \en Initializes the rectangle with setting top-left angle coordinates and rectangle size. \~ 
    */
    void Init(int x, int y, int w, int h);

    /** \brief \ru Инициализация прямоугольника с заданием координат верхнего левого угла и размера прямоугольника.
                \en Initializes the rectangle with setting top-left angle coordinates and rectangle size. \~
    */
    void InitCoords(int x1, int y1, int x2, int y2);

    /** \brief \ru Возвращает true, если прямоугольник пустой, в противном случае возвращает false.
                \en True if rectangle is empty. \~ 
        \details \ru Нулевой прямоугольник имеет ширину и высоту, которые равны 0 (т.е. GetRight() == GetLeft() - 1 и GetBottom() == GetTop() - 1). 
                    Нулевой прямоугольник также является пустым и, следовательно, не является действительным.
                \en Null rectangle has width and height that equal 0, i.e. GetRight() == GetLeft() - 1 и GetBottom() == GetTop() - 1.
                    Null rectangle is also empty and hence not valid.  \~ 
    \return \ru True, если прямоугольник пустой.
            \en True if rectangle is empty. \~
    */
    bool IsNull() const;
    /** \brief \ru Возвращает true, если прямоугольник пустой в противном случае возвращает false.
                \en True if rectangle is empty. \~ 
        \details \ru Пустой прямоугольник имеет GetLeft() > GetRight() или GetTop() > GetBottom(). Пустой прямоугольник не является действительным, т.е. значение функции IsEmpty() не равно значению функции IsValid().
                \en Empty rectangle has GetLeft() > GetRight() or GetTop() > GetBottom(). Empty rectangle is not valid, i.e. IsEmpty() function value is not equal to IsValid() function value. \~ 
        \note  \ru Используйте функцию Normalize(), чтобы получить правильный прямоугольник.
                \en Use Normalize() function to get regular rectangle. \~ 
    \return \ru True, если прямоугольник пустой.
            \en True if rectangle is empty. \~
    */
    bool IsEmpty() const;
    /** \brief \ru Возвращает true, если прямоугольник действительный в противном случае возвращает ложь.
                \en True if rectangle is valid. \~ 
        \details \ru Действительный прямоугольник имеет GetLeft() < GetRight() и GetTop() < GetBottom().  
                    Действительный прямоугольник не пуст, т.е. значение функции IsValid() не равно значению функции IsEmpty().
                \en Valid rectangle has GetLeft() < GetRight() and GetTop() < GetBottom().
                    Valid rectangle is not empty, i.e. IsValid() function value is not equal to IsEmpty() function value. \~ 
        \note  \ru Обратите внимание, что операции, например, пересечения не выполняются, если прямоугольник является недействительным.
                \en Please note that operations like intersection are not performed if rectangle is invalid. \~ 
    \return \ru True, если прямоугольник действителен.
            \en True if rectangle is valid. \~
    */
    bool IsValid() const;

    /** \brief \ru Возвращает X-координату левого края прямоугольника. Эквивалент GetX().
                \en Returns X-coordinate of the left rectangle edge. It is the equivalent of GetX() function. \~ 
    \return \ru X-координата левого края прямоугольника. 
            \en X-coordinate of the left rectangle edge. \~
    */
    int GetLeft() const;
    /** \brief \ru Возвращает Y-координату левого края прямоугольника. Эквивалент GetY().
                \en Returns Y-coordinate of the left rectangle edge. It is the equivalent of GetY() function. \~ 
    \return \ru Y-координата левого края прямоугольника.
            \en Y-coordinate of the left rectangle edge. \~
    */
    int GetTop() const;
    /** \brief \ru Возвращает X-координату правого края прямоугольника.
                \en Returns X-coordinate of the right rectangle edge. \~ 
    \return \ru X-координата правого края прямоугольника.
            \en X-coordinate of the right rectangle edge. \~
    */
    int GetRight() const;
    /** \brief \ru Возвращает Y-координату нижнего края прямоугольника.
                \en Returns Y-coordinate of the bottom rectangle edge. \~ 
    \return \ru Y-координата нижнего края прямоугольника.
            \en Y-coordinate of the bottom rectangle edge. \~
    */
    int GetBottom() const;

    /** \brief \ru Возвращает нормализованный прямоугольник, т.е. прямоугольник, который не имеет отрицательную ширину и высоту.
                \en Returns normalized rectangle, i.e. the rectangle has no negative width and height. \~ 
        \note \ru Если GetWidth() < 0, функция меняет местами левый и правый углы, а также, если GetHeight() < 0, то она меняет местами верхний и нижний углы. 
            \en If GetWidth() < 0, then function swaps the left and right angles. If GetHeight() < 0, then it swaps the top and bottom angles. \~ 
    \return \ru Нормализованный прямоугольник.
            \en Normalized rectangle. \~
    */
    RectI Normalized() const;

    /** \brief \ru Возвращает X-координату левого края прямоугольника. Эквивалент GetLeft().
                \en Returns X-coordinate of the left rectangle edge. It is the equivalent of GetLeft() function. \~ 
    \return \ru X-координату левого края прямоугольника.
            \en X-coordinate of the left rectangle edge. \~
    */
    int GetX() const;

    /** \brief \ru Возвращает Y-координату верхнего края прямоугольника. Эквивалент GetTop().
                \en Returns Y-coordinate of the top rectangle edge. It is the equivalent of GetTop() function. \~ 
    \return \ru Y-координату верхнего края прямоугольника.
            \en Y-coordinate of the top rectangle edge. \~
    */
    int GetY() const;

    /** \brief \ru Устанавливает левый край прямоугольника в заданную X-координату. 
                    Может изменить ширину, но не меняет координату правого края прямоугольника. Эквивалент SetX().
                \en Sets the left rectangle edge to the given X-coordinate.
                    Changes width, but it does not change coordinate of the right rectangle edge. It is the equivalent of SetX() function. \~ 
    */
    void SetLeft(int left);

    /** \brief \ru Устанавливает верхний край прямоугольника в заданную Y-координату. 
                    Может изменить высоту, но не меняет координату нижнего края прямоугольника. Эквивалент SetY().
                \en Sets the top rectangle edge to the given Y-coordinate.
                    Changes height, but it does not change coordinate of the bottom rectangle edge. It is the equivalent of SetY() function. \~ 
    */
    void SetTop(int top);

    /** \brief \ru Устанавливает правый край прямоугольника в заданную X-координату. 
                    Может изменить ширину, но не меняет координату левого края прямоугольника.
                \en Sets the right rectangle edge to the given X-coordinate.
                    Changes width, but it does not change coordinate of the left rectangle edge. \~ 
    */
    void SetRight(int right);


    /** \brief \ru Устанавливает нижний край прямоугольника в заданную Y-координату. 
                    Может изменить высоту, но не меняет координату верхнего края прямоугольника.
                \en Sets the bottom rectangle edge to the given Y-coordinate.
                    Changes height, but it does not change coordinate of the top rectangle edge. \~ 
    */
    void SetBottom(int bottom);

    /** \brief \ru Устанавливает левый край прямоугольника в заданную X-координату. 
                    Может изменить ширину, но не меняет координату правого края прямоугольника. Эквивалент SetLeft().
                \en Sets the left rectangle edge to the given X-coordinate.
                    Changes width, but it does not change coordinate of the right rectangle edge. It is the equivalent of SetLeft() function. \~ 
    */
    void SetX(int x);

    /** \brief \ru Устанавливает верхний край прямоугольника в заданную Y-координату. 
                    Может изменить высоту, но не меняет координату нижнего края прямоугольника. Эквивалент SetTop().
                \en Sets the top rectangle edge to the given Y-coordinate.
                    Changes height, but it does not change coordinate of the bottom rectangle edge. It is the equivalent of SetTop() function. \~ 
    */
    void SetY(int y);

    /** \brief \ru Устанавливает верхний левый угол прямоугольника в заданную позицию. 
                    Может изменить размер, но не меняет нижний правый угол прямоугольника.
                \en Sets the top-left rectangle angle to the given position.
                    Changes size, but it does not change the bottom-right rectangle angle. \~ 
    */
    void SetTopLeft(const PointI& p);

    /** \brief \ru Устанавливает нижний правый угол прямоугольника в заданную позицию. 
                    Может изменить размер, но не меняет верхний левый угол прямоугольника.
                \en Sets the bottom-right rectangle angle to the given position.
                    Changes size, but it does not change the top-left rectangle angle. \~ 
    */
    void SetBottomRight(const PointI& p);

    /** \brief \ru Устанавливает верхний правый угол прямоугольника в заданную позицию. 
                    Может изменить размер, но не меняет нижний левый угол прямоугольника.
                \en Sets the top-right rectangle angle to the given position.
                    Changes size, but it does not change the bottom-left rectangle angle. \~ 
    */
    void SetTopRight(const PointI& p);

    /** \brief \ru Устанавливает нижний левый угол прямоугольника в заданную позицию. 
                    Может изменить размер, но не меняет верхний правый угол прямоугольника.
                \en Sets the bottom-left rectangle angle to the given position.
                    Changes size, but it does not change the top-right rectangle angle. \~ 
    */
    void SetBottomLeft(const PointI& p);

    /** \brief \ru Возвращает позицию верхнего левого угла прямоугольника.
                \en Returns position of the top-left rectangle angle. \~ 
    \return \ru Позиция левого верхнего угла прямоугольника.
            \en Position of the top-left rectangle angle. \~
    */
    PointI GetTopLeft() const;

    /** \brief \ru Возвращает позицию правого нижнего угла прямоугольника.
                \en Returns position of the bottom-right rectangle angle. \~ 
    \return \ru Позиция правого нижнего угла прямоугольника.
            \en Position of the bottom-right rectangle angle. \~
    */
    PointI GetBottomRight() const;

    /** \brief \ru Возвращает позицию правого верхнего угла прямоугольника.
                \en Returns position of the top-right rectangle angle. \~ 
    \return \ru Позиция правого верхнего угла прямоугольника.
            \en Position of the top-right rectangle angle. \~
    */
    PointI GetTopRight() const;

    /** \brief \ru Возвращает позицию левого нижнего угла прямоугольника.
                \en Returns position of the bottom-left rectangle angle. \~ 
    \return \ru Позиция левого нижнего угла прямоугольника.
            \en Position of the bottom-left rectangle angle. \~
    */
    PointI GetBottomLeft() const;

    /** \brief \ru Возвращает центральную точку прямоугольника.
                \en Returns the rectangle center point. \~ 
    \return \ru Центральная точка прямоугольника.
            \en Rectangle center point. \~
    */
    PointI GetCenter() const;

    /** \brief \ru Перемещает прямоугольник на величину dx вдоль оси х и на величину dy вдоль оси у относительно текущей позиции. 
                \en Moves the rectangle on "dx" value along X-axis and "dy" value along Y-axis. It is all about the current position. \~ 
    */
    inline void Offset(int dx, int dy);

    /** \brief \ru Это перегруженная функция. Перемещает прямоугольник p.GetX() вдоль оси х и p.GetY() вдоль оси y относительно текущей позиции.
                \en Overloaded function. It moves the rectangle p.GetX() along X-axis and p.GetY() along Y-axis, all about the current position. \~ 
    */
    inline void Offset(const PointI &p);

    /** \brief \ru Возвращает копию прямоугольника, который перемещается на величину dx вдоль оси х и на величину dy вдоль оси у относительно текущей позиции. 
                    Положительные значения перемещают прямоугольник вправо и вниз.
                \en Returns copy of the rectangle that is moved on "dx" value along X-axis and "dy" value along Y-axis, all about the current position.
                    All positive values move the rectangle to right and down. \~ 
    \return \ru Новый прямоугольник.
            \en New rectangle. \~
    */
    inline RectI Offseted(int dx, int dy) const;

    /** \brief \ru Это перегруженная функция. Возвращает копию прямоугольника, который перемещается на величину p.GetX() вдоль оси х и 
                    на величину p.GetY() вдоль оси у относительно текущей позиции. Положительные значения перемещают прямоугольник вправо и вниз.
                \en Overloaded function. It returns copy of the rectangle that is moved p.GetX() along X-axis and 
                    p.GetY() along Y-axis, all about the current position. Positive values move the rectangle to right and down. \~ 
    \return \ru Новый прямоугольник.
            \en New rectangle. \~
    */
    inline RectI Offseted(const PointI &p) const;

    /** \brief \ru Перемещает прямоугольник, перенося верхний левый угол в заданном положении (х, у). Размер прямоугольника не изменяется.
                \en Moves the rectangle by shifting the top-left angle at the defined position (х, у). Rectangle size is not changed. \~ 
    */
    inline void MoveToXY(int x, int t);

    /** \brief \ru Перемещает прямоугольник, перенося верхний левый угол в заданную позицию.
                \en Moves the rectangle by shifting the top-left angle at the defined position. \~ 
    */
    inline void MoveToXY(const PointI &p);

    /** \brief \ru Добавляет x1, y1, x2 и y2 к имеющимся координатам прямоугольника.
                \en Adds x1, y1, x2, and y2 values to existing rectangle coordinates. \~ 
    */
    inline void Inflate(int x1, int y1, int x2, int y2);

    /** \brief \ru Возвращает новый прямоугольник с x1, y1, x2 и y2, добавленными к имеющимся координатам этого прямоугольника.
                \en Returns new rectangle with x1, y1, x2, and y2 values, added to existing rectangle coordinates. \~ 
    \return \ru Новый прямоугольник.
            \en New rectangle. \~
    */
    inline RectI Inflated(int x1, int y1, int x2, int y2) const;

    /** \brief \ru Возвращает размер прямоугольника.
                \en Returns rectangle size. \~ 
    \return \ru Размер прямоугольника.
            \en Rectangle size. \~
    */
    SizeI GetSize() const;

    /** \brief \ru Возвращает ширину прямоугольника.
                \en Returns rectangle width. \~ 
    \return \ru Ширина прямоугольника.
            \en Rectangle width. \~
    */
    int GetWidth() const;

    /** \brief \ru Возвращает высоту прямоугольника.
                \en Returns rectangle height. \~ 
    \return \ru Высота прямоугольника.
            \en Rectangle height. \~
    */
    int GetHeight() const;

    /** \brief \ru Устанавливает заданную ширину прямоугольнику. Правый край изменяется, а левый нет.
                \en Sets the defined width for the rectangle by changing its right edge. The left rectangle edge is not changed. \~ 
    */
    void SetWidth(int w);

    /** \brief \ru Устанавливает заданную высоту прямоугольнику. Нижний край изменяется, а верхний нет.
                \en Sets the defined height for the rectangle by changing its bottom edge. Top edge is not changed. \~ 
    */
    void SetHeight(int h);

    /** \brief \ru Устанавливает новый размер прямоугольнику. Верхний левый угол не перемещается.
                \en Sets the new size for the rectangle. Top-left angle is not moved. \~ 
    */
    void SetSize(const SizeI& s);

    /** \brief \ru Возвращает ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
                \en Returns bounding rectangle of the given rectangle and the defined rectangle. \~ 
    \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
            \en Bounding rectangle of the given rectangle and the defined rectangle. \~
    */
    RectI operator | (const RectI& other) const;

    /** \brief \ru Возвращает пересечение этого прямоугольника и заданного прямоугольника. Возвращает пустой прямоугольник, если нет пересечения.
                \en Returns intersection of the given rectangle and the defined rectangle. It returns empty rectangle if no intersection. \~ 
    \return \ru Пересечение этого прямоугольника и заданного прямоугольника.
            \en Intersection of the given rectangle and the defined rectangle. \~
    */
    RectI operator & (const RectI& other) const;

    /** \brief \ru Объединить этот прямоугольник с заданным прямоугольником.
                \en Union of the given rectangle with the defined rectangle. \~ 
    */
    inline RectI& operator |= (const RectI& other);


    /** \brief \ru Пересекает этот прямоугольник с заданным прямоугольником.
                \en Intersection of the given rectangle with the defined rectangle. \~ 
    */
    inline RectI& operator &= (const RectI& other);

    /** \brief \ru Это перегруженная функция.
                    Возвращает true, если данный прямоугольник находится внутри этого прямоугольника в противном случае возвращает false. 
                    Возвращает true, если прямоугольник целиком внутри этого прямоугольника, а не на краю.
                \en Overloaded function.
                    True if the defined rectangle is inside the given rectangle.
                    True if the defined rectangle is wholly inside the given rectangle, not on the edge.  \~ 
    \return \ru True, если данный прямоугольник находится внутри этого прямоугольника в противном случае возвращает false.
            \en True if the defined rectangle is inside the given rectangle. \~
    */
    bool RectInRect(const RectI& other, bool proper = false) const;

    /** \brief \ru Возвращает true, если данная точка находится внутри или на краю прямоугольника в противном случае возвращает false. 
                    Возвращает true, если данная точка находится внутри прямоугольника, т.е. не на краю. 
                \en True if the given point is inside the rectangle or on the edge.
                    True if the given point is inside the rectangle, i.e. not on the edge. \~ 
    \return \ru True, если данная точка находится внутри или на краю прямоугольника в противном случае возвращает false.
            \en True if the given point is inside the rectangle or on the edge. \~
    */
    bool PntInRect(const PointI& p, bool proper = false) const;

    /** \brief \ru Это перегруженная функция.
                    Возвращает true, если точка (х, у) находится внутри этого прямоугольника, в противном случае возвращает false. 
                \en Overloaded function.
                    True if point (х, у) is inside the rectangle. \~ 
    \return \ru True, если точка (х, у) находится внутри этого прямоугольника, в противном случае возвращает false. 
            \en True if point (х, у) is inside the rectangle. \~
    */
    bool PntInRect(int x, int y) const;

    /** \brief \ru Это перегруженная функция.
                    Возвращает true, если данная точка (x, y) находится внутри или на краю прямоугольника в противном случае возвращает false.
                    Возвращает true, если данная точка (x, y) находится внутри прямоугольника, т.е. не на краю. 
                \en Overloaded function.
                    True if the given point (x, y) is inside the rectangle or on the edge.
                    True if the given point (x, y) is inside the rectangle, i.e. not on the edge. \~ 
    \return \ru True, если данная точка (x, y) находится внутри или на краю прямоугольника в противном случае возвращает false.
            \en True if the given point (x, y) is inside the rectangle or on the edge. \~
    */
    bool PntInRect(int x, int y, bool proper) const;

    /** \brief \ru Возвращает ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника. 
                \en Returns bounding rectangle of the given rectangle and the defined rectangle. \~ 
    \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
            \en Bounding rectangle of the given rectangle and the defined rectangle. \~
    */
    RectI United(const RectI& other) const;

    /** \brief \ru Возвращает пересечение этого прямоугольника и заданного прямоугольника.
                \en Returns intersection of the given rectangle and the defined rectangle. \~ 
    \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
            \en Bounding rectangle of the given rectangle and the defined rectangle. \~
    */
    inline RectI Intersected(const RectI& other) const;

    /** \brief \ru Возвращает true, если этот прямоугольник пересекается с заданным прямоугольником (то есть, есть по меньшей мере один пиксель, 
                    который находится внутри обоих прямоугольников) в противном случае возвращает false.
                \en True if the given rectangle intersects with the defined rectangle. It means that at least one pixel, inside both rectangles, exists. \~ 
    \return \ru True, если этот прямоугольник пересекается с заданным прямоугольником в противном случае возвращает false.
            \en True if the given rectangle intersects with the defined rectangle. \~
    */
    bool Intersects(const RectI& r) const;

    /** \brief \ru Возвращает true, если этот прямоугольник равен указанному, в противном случае возвращает false. 
                \en True if the given rectangle is equal to the specified rectangle. \~ 
    \return \ru True, если этот прямоугольник равен указанному, в противном случае возвращает false.
            \en True if the given rectangle is equal to the specified rectangle. \~
    */
    bool operator == (const RectI&);

    /** \brief \ru Возвращает true, если этот прямоугольник отличается от указанного, в противном случае возвращает false. 
                \en True if the given rectangle is different from the specified rectangle. \~ 
    \return \ru True, если этот прямоугольник отличается от указанного, в противном случае возвращает false.
            \en True if the given rectangle is different from the specified rectangle. \~
    */
    bool operator != (const RectI&);

    friend VSN_FUNC_EX bool operator==(const RectI &, const RectI &);
    friend VSN_FUNC_EX bool operator!=(const RectI &, const RectI &);

    static const RectI ZERO;   ///< \ru Нулевой прямоугольник. \en Zero rect. 
private:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
};

VSN_FUNC_EX bool operator==(const RectI &, const RectI &);
VSN_FUNC_EX bool operator!=(const RectI &, const RectI &);

inline RectI::RectI() : m_x1(0) , m_y1(0) , m_x2(-1) , m_y2(-1) {}
inline RectI::RectI(int left, int top, int width, int height) : m_x1(left) , m_y1(top) , m_x2(left + width) , m_y2(top + height) {}
inline RectI::RectI(const PointI& GetTopLeft, const PointI& bottomRight) : m_x1(GetTopLeft.GetX()) , m_y1(GetTopLeft.GetY()) , m_x2(bottomRight.GetX()) , m_y2(bottomRight.GetY()) {}
inline RectI::RectI(const PointI& GetTopLeft, const SizeI& size) : m_x1(GetTopLeft.GetX()), m_y1(GetTopLeft.GetY()), m_x2(GetTopLeft.GetX() + size.GetWidth()) , m_y2(GetTopLeft.GetY() + size.GetHeight()) {}
inline void RectI::Init(int x, int y, int w, int h) { m_x1 = x; m_y1 = y; m_x2 = (x + w); m_y2 = (y + h); }
inline void RectI::InitCoords(int x1, int y1, int x2, int y2) { m_x1 = x1; m_y1 = y1; m_x2 = x2; m_y2 = y2; }
inline bool RectI::IsNull() const { return m_x2 == m_x1 && m_y2 == m_y1; }
inline bool RectI::IsEmpty() const { return m_x1 > m_x2 || m_y1 > m_y2; }
inline bool RectI::IsValid() const { return m_x1 <= m_x2 && m_y1 <= m_y2; }

inline int RectI::GetLeft() const { return m_x1; }
inline int RectI::GetTop() const { return m_y1; }
inline int RectI::GetRight() const { return m_x2; }
inline int RectI::GetBottom() const { return m_y2; }

inline int RectI::GetX() const { return m_x1; }
inline int RectI::GetY() const { return m_y1; }

inline void RectI::SetLeft(int pos) { m_x1 = pos; }
inline void RectI::SetTop(int pos) { m_y1 = pos; }

inline void RectI::SetRight(int pos) { m_x2 = pos; }
inline void RectI::SetBottom(int pos) { m_y2 = pos; }

inline void RectI::SetTopLeft(const PointI& p) { m_x1 = p.GetX(); m_y1 = p.GetY(); }
inline void RectI::SetBottomRight(const PointI& p) { m_x2 = p.GetX(); m_y2 = p.GetY(); }
inline void RectI::SetTopRight(const PointI& p) { m_x2 = p.GetX(); m_y1 = p.GetY(); }
inline void RectI::SetBottomLeft(const PointI& p) { m_x1 = p.GetX(); m_y2 = p.GetY(); }

inline void RectI::SetX(int x) { m_x1 = x; }
inline void RectI::SetY(int y) { m_y1 = y; }

inline PointI RectI::GetTopLeft() const { return PointI(m_x1, m_y1); }
inline PointI RectI::GetBottomRight() const { return PointI(m_x2, m_y2); }
inline PointI RectI::GetTopRight() const { return PointI(m_x2, m_y1); }
inline PointI RectI::GetBottomLeft() const { return PointI(m_x1, m_y2); }
inline PointI RectI::GetCenter() const { return PointI((m_x1 + m_x2) / 2, (m_y1 + m_y2) / 2); }

inline int RectI::GetWidth() const { return  m_x2 - m_x1; }
inline int RectI::GetHeight() const { return  m_y2 - m_y1; }

inline SizeI RectI::GetSize() const { return SizeI(GetWidth(), GetHeight()); }
inline void RectI::Offset(int dx, int dy) { m_x1 += dx; m_y1 += dy; m_x2 += dx; m_y2 += dy; }
inline void RectI::Offset(const PointI& pnt) { m_x1 += pnt.GetX(); m_y1 += pnt.GetY(); m_x2 += pnt.GetX(); m_y2 += pnt.GetY(); }
inline RectI RectI::Offseted(int dx, int dy) const { return RectI(PointI(m_x1 + dx, m_y1 + dy), PointI(m_x2 + dx, m_y2 + dy)); }
inline RectI RectI::Offseted(const PointI& p) const { return RectI(PointI(m_x1 + p.GetX(), m_y1 + p.GetY()), PointI(m_x2 + p.GetX(), m_y2 + p.GetY())); }

inline void RectI::MoveToXY(int x, int y) { m_x2 += x - m_x1; m_y2 += y - m_y1; m_x1 = x; m_y1 = y; }
inline void RectI::MoveToXY(const PointI& p) { m_x2 += p.GetX() - m_x1; m_y2 += p.GetY() - m_y1; m_x1 = p.GetX(); m_y1 = p.GetY(); }
inline RectI RectI::Inflated(int x1, int y1, int x2, int y2) const { return RectI(PointI(m_x1 + x1, m_y1 + y1), PointI(m_x2 + x2, m_y2 + y2)); }
inline void RectI::Inflate(int x1, int y1, int x2, int y2) { m_x1 += x1; m_y1 += y1; m_x2 += x2; m_y2 += y2; }

inline void RectI::SetWidth(int w) { m_x2 = (m_x1 + w); }
inline void RectI::SetHeight(int h) { m_y2 = (m_y1 + h); }
inline void RectI::SetSize(const SizeI& sz) { m_x2 = (sz.GetWidth() + m_x1); m_y2 = (sz.GetHeight() + m_y1); }

inline bool RectI::PntInRect(int x, int y, bool aproper) const { return PntInRect(PointI(x, y), aproper); }
inline bool RectI::PntInRect(int x, int y) const { return PntInRect(PointI(x, y), false); }

inline RectI& RectI::operator|=(const RectI& other) { *this = *this | other; return *this; }
inline RectI& RectI::operator&=(const RectI& other) { *this = *this & other; return *this; }

inline bool RectI::operator == (const RectI& other) { return m_x1 == other.m_x1 && m_x2 == other.m_x2 && m_y1 == other.m_y1 && m_y2 == other.m_y2; }

inline bool RectI::operator != (const RectI& other) { return m_x1 != other.m_x1 || m_x2 != other.m_x2 || m_y1 != other.m_y1 || m_y2 != other.m_y2; }

//----------------------------------------------------------------------------
//
/** \brief \ru Класс RectF описывает прямоугольник в плоскости и использует двойную точность.
           \en RectF class defines rectangle in the plane using float-precision. \~
    \details \ru Прямоугольник, как правило, выражается в виде верхнего левого угла и размера.
                 Прямоугольник может быть построен с помощью целочисленных координат слева, сверху, ширины и высоты, или при помощи классов RectF и DblSize.
                 Класс RectI предоставляет набор функций, которые возвращают необходимые координаты прямоугольника и позволяют их инициализировать.
                 Класс RectI также предоставляет функции, которые дают возможность перемещать прямоугольник относительно его координат и т.д. \n
             \en Rectangle is typically expressed as top-left angle and size.
                 Rectangle can be constructed with integer coordinates of left, top, width and height, or with PointF and SizeI classes.
                 RectI class provides a set of functions that return necessary coordinates of the rectangle and allow initializing them.
                 RectI class also provides functions for moving the rectangle about its coordinates, etc. \n \~
    \ingroup Vision_Mathematic
*/
// ---
class VSN_CLASS RectF
{
public:
    /// \ru Конструктор по умолчанию. Создает пустой прямоугольник. \en Default constructor for creating empty rectangle.
    RectF() : m_x(0.0), m_y(0.0), m_width(0.0), m_height(0.0) {}
    RectF(const PointF& topleft, const SizeF& size);
    RectF(const PointF& topleft, const PointF& bottomRight);
    RectF(float left, float top, float width, float height);
    RectF(const RectI& rect);
    /// \ru Конструктор копирования. \en Copy constructor. \~
    RectF(const MbRect& init);
public:
    /** \brief \ru Инициализация прямоугольника с заданием координат верхнего левого угла и размера прямоугольника.
               \en Initializes the rectangle with setting top-left angle coordinates and rectangle size. \~
    */
    void Init(float x, float y, float w, float h);
    /** \brief \ru Инициализация прямоугольника с заданием координат верхнего левого угла и размера прямоугольника.
               \en Initializes the rectangle with setting top-left angle coordinates and rectangle size. \~
    */
    void InitCoords(float x1, float y1, float x2, float y2);

    /** \brief \ru Возвращает true, если прямоугольник пустой, в противном случае возвращает false.
               \en True if rectangle is empty. \~
        \details \ru Нулевой прямоугольник имеет ширину и высоту, которые равны 0 (т.е. GetRight() == GetLeft() - 1 и GetBottom() == GetTop() - 1).
                     Нулевой прямоугольник также является пустым и, следовательно, не является действительным.
                 \en Null rectangle has width and height that equal 0, i.e. GetRight() == GetLeft() - 1 и GetBottom() == GetTop() - 1.
                     Null rectangle is also empty and hence not valid.  \~
        \return \ru True, если прямоугольник пустой.
                \en True if rectangle is empty. \~
    */
    bool IsNull() const;
    bool IsEmpty() const;
    bool IsValid() const;
    /** \brief \ru Возвращает нормализованный прямоугольник, т.е. прямоугольник, который не имеет отрицательную ширину и высоту.
               \en Returns normalized rectangle, i.e. the rectangle has no negative width and height. \~
        \note \ru Если GetWidth() < 0, функция меняет местами левый и правый углы, а также, если GetHeight() < 0, то она меняет местами верхний и нижний углы.
              \en If GetWidth() < 0, then function swaps the left and right angles. If GetHeight() < 0, then it swaps the top and bottom angles. \~
        \return \ru Нормализованный прямоугольник.
                \en Normalized rectangle. \~
    */
    RectF Normalized() const;

    float GetLeft() const{ return m_x; }
    float GetTop() const{ return m_y; }
    float GetRight() const{ return m_x + m_width; }
    float GetBottom() const{ return m_y + m_height; }

    inline float GetX() const;
    inline float GetY() const;
    inline void SetLeft(float pos);
    inline void SetTop(float pos);
    inline void SetRight(float pos);
    inline void SetBottom(float pos);

    inline void SetX(float pos) { SetLeft(pos); }
    inline void SetY(float pos) { SetTop(pos); }

    /** \brief \ru Возвращает позицию верхнего левого угла прямоугольника.
               \en Returns position of the top-left rectangle angle. \~
        \return \ru Позиция левого верхнего угла прямоугольника.
                \en Position of the top-left rectangle angle. \~
    */
    inline PointF GetTopLeft() const{ return PointF(m_x, m_y); }
    inline PointF GetBottomRight() const{ return PointF(m_x + m_width, m_y + m_height); }
    inline PointF GetTopRight() const{ return PointF(m_x + m_width, m_y); }
    inline PointF GetBottomLeft() const{ return PointF(m_x, m_y + m_height); }
    inline PointF GetCenter() const;

    /** \brief \ru Устанавливает верхний левый угол прямоугольника в заданную позицию.
                   Может изменить размер, но не меняет нижний правый угол прямоугольника.
               \en Sets the top-left rectangle angle to the given position.
                   Changes size, but it does not change the bottom-right rectangle angle. \~
    */
    inline void SetTopLeft(const PointF& p);
    /** \brief \ru Устанавливает нижний правый угол прямоугольника в заданную позицию.
                   Может изменить размер, но не меняет верхний левый угол прямоугольника.
               \en Sets the bottom-right rectangle angle to the given position.
                   Changes size, but it does not change the top-left rectangle angle. \~
    */
    inline void SetBottomRight(const PointF& p);
    inline void SetTopRight(const PointF& p);
    inline void SetBottomLeft(const PointF& p);

    /** \brief \ru Перемещает прямоугольник на величину dx вдоль оси х и на величину dy вдоль оси у относительно текущей позиции.
                \en Moves the rectangle on "dx" value along X-axis and "dy" value along Y-axis. It is all about the current position. \~
    */
    void Offset(float dx, float dy);
    /** \brief \ru Это перегруженная функция. Перемещает прямоугольник p.GetX() вдоль оси х и p.GetY() вдоль оси y относительно текущей позиции.
               \en Overloaded function. It moves the rectangle p.GetX() along X-axis and p.GetY() along Y-axis, all about the current position. \~
    */
    void Offset(const PointF &p);

    /** \brief \ru Возвращает копию прямоугольника, который перемещается на величину dx вдоль оси х и на величину dy вдоль оси у относительно текущей позиции.
                   Положительные значения перемещают прямоугольник вправо и вниз.
               \en Returns copy of the rectangle that is moved on "dx" value along X-axis and "dy" value along Y-axis, all about the current position.
                   All positive values move the rectangle to right and down. \~
        \return \ru Новый прямоугольник.
                \en New rectangle. \~
    */
    RectF Offseted(float dx, float dy) const;
    /** \brief \ru Это перегруженная функция. Возвращает копию прямоугольника, который перемещается на величину p.GetX() вдоль оси х и
                   на величину p.GetY() вдоль оси у относительно текущей позиции. Положительные значения перемещают прямоугольник вправо и вниз.
               \en Overloaded function. It returns copy of the rectangle that is moved p.GetX() along X-axis and
                   p.GetY() along Y-axis, all about the current position. Positive values move the rectangle to right and down. \~
        \return \ru Новый прямоугольник.
                \en New rectangle. \~
    */
    inline RectF Offseted(const PointF& p) const;

    /** \brief \ru Перемещает прямоугольник, перенося верхний левый угол в заданном положении (х, у). Размер прямоугольника не изменяется.
               \en Moves the rectangle by shifting the top-left angle at the defined position (х, у). Rectangle size is not changed. \~
    */
    inline void MoveToXY(float x, float y);
    /** \brief \ru Перемещает прямоугольник, перенося верхний левый угол в заданную позицию.
               \en Moves the rectangle by shifting the top-left angle at the defined position. \~
    */
    inline void MoveToXY(const PointF& p);

    /** \brief \ru Добавляет x1, y1, x2 и y2 к имеющимся координатам прямоугольника.
               \en Adds x1, y1, x2, and y2 values to existing rectangle coordinates. \~
    */
    inline void Inflate(float x1, float y1, float x2, float y2);
    /** \brief \ru Возвращает новый прямоугольник с x1, y1, x2 и y2, добавленными к имеющимся координатам этого прямоугольника.
               \en Returns new rectangle with x1, y1, x2, and y2 values, added to existing rectangle coordinates. \~
        \return \ru Новый прямоугольник.
                \en New rectangle. \~
    */
    inline RectF Inflated(float x1, float y1, float x2, float y2) const;

    inline SizeF GetSize() const;
    inline float GetWidth() const;
    inline float GetHeight() const;
    inline void SetWidth(float w);
    inline void SetHeight(float h);
    inline void SetSize(const SizeF& other);

    RectF operator|(const RectF& rc) const;
    RectF operator&(const RectF& rc) const;
    inline RectF& operator|=(const RectF& rc);
    inline RectF& operator&=(const RectF& rc);

    /** \brief \ru Это перегруженная функция.
                   Возвращает true, если данный прямоугольник находится внутри этого прямоугольника в противном случае возвращает false.
                   Возвращает true, если прямоугольник целиком внутри этого прямоугольника, а не на краю.
                \en Overloaded function.
                    True if the defined rectangle is inside the given rectangle.
                    True if the defined rectangle is wholly inside the given rectangle, not on the edge.  \~
        \return \ru True, если данный прямоугольник находится внутри этого прямоугольника в противном случае возвращает false.
                \en True if the defined rectangle is inside the given rectangle. \~
    */
    bool RectInRect(const RectF& other) const;
    /** \brief \ru Возвращает true, если данная точка находится внутри или на краю прямоугольника в противном случае возвращает false.
                   Возвращает true, если данная точка находится внутри прямоугольника, т.е. не на краю.
               \en True if the given point is inside the rectangle or on the edge.
                   True if the given point is inside the rectangle, i.e. not on the edge. \~
        \return \ru True, если данная точка находится внутри или на краю прямоугольника в противном случае возвращает false.
                \en True if the given point is inside the rectangle or on the edge. \~
    */
    bool PntInRect(const PointF& p) const;
    /** \brief \ru Это перегруженная функция.
                   Возвращает true, если точка (х, у) находится внутри этого прямоугольника, в противном случае возвращает false.
               \en Overloaded function.
                   True if point (х, у) is inside the rectangle. \~
        \return \ru True, если точка (х, у) находится внутри этого прямоугольника, в противном случае возвращает false.
                \en True if point (х, у) is inside the rectangle. \~
    */
    bool PntInRect(float x, float y) const;

    /** \brief \ru Возвращает ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
               \en Returns bounding rectangle of the given rectangle and the defined rectangle. \~
        \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
                \en Bounding rectangle of the given rectangle and the defined rectangle. \~
    */
    RectF United(const RectF& other) const;

    /** \brief \ru Возвращает пересечение этого прямоугольника и заданного прямоугольника.
               \en Returns intersection of the given rectangle and the defined rectangle. \~
        \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
                \en Bounding rectangle of the given rectangle and the defined rectangle. \~
    */
    RectF Intersected(const RectF& other) const;

    /** \brief \ru Возвращает true, если этот прямоугольник пересекается с заданным прямоугольником (то есть, есть по меньшей мере один пиксель,
                   который находится внутри обоих прямоугольников) в противном случае возвращает false.
                \en True if the given rectangle intersects with the defined rectangle. It means that at least one pixel, inside both rectangles, exists. \~
        \return \ru True, если этот прямоугольник пересекается с заданным прямоугольником в противном случае возвращает false.
                \en True if the given rectangle intersects with the defined rectangle. \~
    */
    bool Intersects(const RectF& other) const;

    friend inline bool operator==(const RectF &, const RectF &);
    friend inline bool operator!=(const RectF &, const RectF &);

    inline RectI ToRect() const;
    RectI ToSmallestRect() const;
private:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
};

inline bool operator==(const RectF& , const RectF& );
inline bool operator!=(const RectF& , const RectF& );

inline RectF::RectF(float left, float top, float width, float height) : m_x(left), m_y(top), m_width(width), m_height(height) {}
inline RectF::RectF(const PointF& topLeft, const SizeF& size) : m_x(topLeft.GetX()), m_y(topLeft.GetY()), m_width(size.GetWidth()), m_height(size.GetHeight()) {}
inline RectF::RectF(const PointF& topLeft, const PointF& bottomRight) : m_x(topLeft.GetX()), m_y(topLeft.GetY()), m_width(bottomRight.GetX() - topLeft.GetX()), m_height(bottomRight.GetY() - topLeft.GetY()){}
inline RectF::RectF(const RectI& other) : m_x(static_cast<float>(other.GetX())), m_y(static_cast<float>(other.GetY())), m_width(static_cast<float>(other.GetWidth())), m_height(static_cast<float>(other.GetHeight())) {}
inline RectF::RectF(const MbRect& init)
{
    InitCoords(static_cast<float>(init.left), static_cast<float>(init.top), 
        static_cast<float>(init.right), static_cast<float>(init.bottom));
}

inline void RectF::Init(float x, float y, float w, float h) { m_x = x; m_y = y; m_width = w; m_height = h; }
inline void RectF::InitCoords(float x1, float y1, float x2, float y2) { m_x = x1; m_y = y1; m_width = x2 - x1; m_height = y2 - y1; }

inline bool RectF::IsNull() const { return m_width == 0.f && m_height == 0.f; }
inline bool RectF::IsEmpty() const { return m_width <= 0.f || m_height <= 0.f; }
inline bool RectF::IsValid() const { return m_width > 0.f && m_height > 0.f; }
inline float RectF::GetX() const { return m_x; }
inline float RectF::GetY() const { return m_y; }

inline void RectF::SetLeft(float pos) { float diff = pos - m_x; m_x += diff; m_width -= diff; }
inline void RectF::SetRight(float pos) { m_width = pos - m_x; }
inline void RectF::SetTop(float pos) { float diff = pos - m_y; m_y += diff; m_height -= diff; }
inline void RectF::SetBottom(float pos) { m_height = pos - m_y; }

inline void RectF::SetTopLeft(const PointF& p) { SetLeft(p.GetX()); SetTop(p.GetY()); }
inline void RectF::SetTopRight(const PointF& p) { SetRight(p.GetX()); SetTop(p.GetY()); }
inline void RectF::SetBottomLeft(const PointF& p) { SetLeft(p.GetX()); SetBottom(p.GetY()); }
inline void RectF::SetBottomRight(const PointF &p) { SetRight(p.GetX()); SetBottom(p.GetY()); }
inline PointF RectF::GetCenter() const { return PointF(m_x + m_width * 0.5f, m_y + m_height * 0.5f); }

inline float RectF::GetWidth() const { return m_width; }
inline void RectF::SetWidth(float w) { m_width = w; }
inline float RectF::GetHeight() const { return m_height; }
inline void RectF::SetHeight(float h) { m_height = h; }
inline SizeF RectF::GetSize() const { return SizeF(m_width, m_height); }

inline void RectF::Offset(float dx, float dy) { m_x += dx; m_y += dy; }
inline void RectF::Offset(const PointF &p) { m_x += p.GetX(); m_y += p.GetY(); }

inline void RectF::MoveToXY(float x, float y) { m_x = x; m_y = y; }
inline void RectF::MoveToXY(const PointF& p) { m_x = p.GetX(); m_y = p.GetY(); }

inline RectF RectF::Offseted(float dx, float dy) const { return RectF(m_x + dx, m_y + dy, m_width, m_height); }
inline RectF RectF::Offseted(const PointF& p) const { return RectF(m_x + p.GetX(), m_y + p.GetY(), m_width, m_height); }

inline void RectF::Inflate(float x1, float y1, float x2, float y2) { m_x += x1; m_y += y1; m_width += x2 - x1; m_height += y2 - y1; }
inline RectF RectF::Inflated(float x1, float y1, float x2, float y2) const { return RectF(m_x + x1, m_y + y1, m_width + x2 - x1, m_height + y2 - y1); }

inline void RectF::SetSize(const SizeF& sz) { m_width = sz.GetWidth(); m_height = sz.GetHeight(); }

inline RectF& RectF::operator|=(const RectF& r) { *this = *this | r; return *this; }
inline RectF& RectF::operator&=(const RectF &r) { *this = *this & r; return *this; }

inline bool operator==(const RectF& rc1, const RectF& rc2)
{
    return IsEqual(rc1.m_x, rc2.m_x) && IsEqual(rc1.m_y, rc2.m_y)
        && IsEqual(rc1.m_width, rc2.m_width) && IsEqual(rc1.m_height, rc2.m_height);
}

inline bool operator!=(const RectF &r1, const RectF &r2)
{
    return !IsEqual(r1.m_x, r2.m_x) || !IsEqual(r1.m_y, r2.m_y)
        || !IsEqual(r1.m_width, r2.m_width) || !IsEqual(r1.m_height, r2.m_height);
}

inline RectI RectF::ToRect() const
{
    return RectI(vRound(m_x), vRound(m_y), vRound(m_width), vRound(m_height));
}


} // namespace VSN

#endif /* __VSN_RECT_H */
