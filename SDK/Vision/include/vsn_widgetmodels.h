////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Набор стандартных моделей виджета.
         \en The set of standard models of the widget. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_WIDGETMODEL_H
#define __VSN_WIDGETMODEL_H

#include <memory>
#include <vsn_math.h>
#include <vsn_prchangewidget.h>
#include <vsn_global.h>
#include <vsn_placement.h>
#include <vsn_ray.h>

namespace VSN {

class Canvas;
class RenderContext;

enum class MarkerID : int;

class WidgetSizePrivate;
/* WidgetSize */
class VSN_CLASS WidgetSize
{
public:
    WidgetSize(const Point3DF& origin);
    virtual ~WidgetSize();
public:
    void AddPoint(const Point3DF& point);
    void AddSphere(const Point3DF& origin, float r);
    void AddRect(const Placement3DF& placement, const MbRect& rect);
    void AddBox(const Placement3DF& placement, const MbCube& box);
    void Clear();
public:
    double GetRadius() const; // distance from ziro to max point
    const MbCube& GetCube() const;
    bool IsEmpty() const;
private:
    VSN_DECLARE_PRIVATE(WidgetSize);
};

//------------------------------------------------------------------------------
/** \brief \ru Класс визуальной модели элемента управления.\n
           \en NOT TRANSLATED. \~
           \details \ru При помощи объекта этого класса можно описать визуальное представление элемента управления. \n
                    \en NOT TRANSLATED. \~
*/
// ---
class VSN_CLASS WidgetModel
{
public:
    /// \ru Деструктор. \en Destructor. \~
    virtual ~WidgetModel() {};
public:
    /// \ru Определить точку пересечения луча и элемента управления. \en NOT TRANSLATED. \~
    virtual std::pair<int, double> Intersect(const MbLine3D& ray, int state = 0) const = 0;
    /// \ru Определить точку пересечения луча и элемента управления. \en NOT TRANSLATED. \~
    virtual std::pair<int, float> Intersect(const Ray3DF& ray, int state = 0) const = 0;
    /// \ru Нарисовать элемент управления. \en NOT TRANSLATED. \~
    virtual void Render(RenderContext& ctx, int state = 0) = 0;
    /// \ru Получить размер элемента управления. \en NOT TRANSLATED. \~
    virtual const MbCube& GetSize(int state = 0) const = 0;
    virtual const WidgetSize& GetWidgetSize(int state = 0) const = 0;
};
typedef std::shared_ptr<WidgetModel> WidgetModelPtr;

//------------------------------------------------------------------------------
/** \brief \ru Класс трехмерной модели элемента управления.\n
           \en NOT TRANSLATED. \~
           \details \ru Позволяет описать предстваление манипулятора при помощи простых геометрических фигур. \n
                        - Сфера
                        - Цилиндр
                        - Конус
                        - Тор
                        - Куб
                        - Плоский прямоугольник
                        - Плоская окружность

                        Каждому элементу можно установить собственный процесс управления контролом.
                        Элементы можно групировать при поможи задания одинаковых идентификаторов.
                        Если вместо идентификатора указать -1 тогда элемент не будет кликабельным.
                    \en NOT TRANSLATED. \~
*/
// ---
class Widget3DModelPrivate;
class VSN_CLASS Widget3DModel : public WidgetModel
{
public:
    Widget3DModel();
    virtual ~Widget3DModel();
public:
    /// \ru Определить точку пересечения луча и элемента управления. \en NOT TRANSLATED. \~
    virtual std::pair<int, double> Intersect(const MbLine3D& ray, int state = 0) const override;
    /// \ru Определить точку пересечения луча и элемента управления. \en NOT TRANSLATED. \~
    virtual std::pair<int, float> Intersect(const Ray3DF& ray, int state = 0) const override;
    /// \ru Нарисовать элемент управления. \en NOT TRANSLATED. \~
    virtual void Render(RenderContext& ctx, int state = 0) override;
    /// \ru Получить размер элемента управления. \en NOT TRANSLATED. \~
    virtual const MbCube& GetSize(int state = 0) const override;
    virtual const WidgetSize& GetWidgetSize(int state = 0) const override;
public:
    /// \ru использовать элементы из другого состояния. \en NOT TRANSLATED. \~
    void InsertState(int fromState, int toStatem);
    /** \brief \ru Добавить куб в модель.
               \en NOT TRANSLATED. \~
               \param[in] id - \ru Идентификатор элемента.
                               \en NOT TRANSLATED. \~
               \param[in] p1 - \ru Первая точка на диагонали.
                               \en NOT TRANSLATED. \~
               \param[in] p2 - \ru Вторая точка на диагонали.
                               \en NOT TRANSLATED. \~
               \param[in] color - \ru Цвет элемента.
                                  \en NOT TRANSLATED. \~
    */
    void AddCube(int id, const Point3DF& p1, const Point3DF& p2,
        const Color& color, int state = 0);

    /** \brief \ru Добавить цилиндр в модель.
               \en NOT TRANSLATED. \~
               \param[in] id - \ru Идентификатор элемента.
                               \en NOT TRANSLATED. \~
               \param[in] p1 - \ru Первая точка на оси цилиндра.
                               \en NOT TRANSLATED. \~
               \param[in] p2 - \ru Вторая точка на оси цилиндра.
                               \en NOT TRANSLATED.\~
               \param[in] color - \ru Цвет элемента.
                                  \en NOT TRANSLATED. \~
    */
    void AddCylinder(int id, const Point3DF& p1, const Point3DF& p2,
        float r, const Color& color, int state = 0);

    /** \brief \ru Добавить сферу в модель.
               \en NOT TRANSLATED. \~
               \param[in] id - \ru Идентификатор элемента.
                               \en NOT TRANSLATED. \~
               \param[in] p1 - \ru Позиция.
                               \en NOT TRANSLATED. \~
               \param[in] p2 - \ru Вторая точка на оси цилиндра.
                               \en NOT TRANSLATED. \~
               \param[in] color - \ru Цвет элемента.
                                  \en NOT TRANSLATED. \~
    */
    void AddSphere(int id, const Point3DF& p1, float r, const Color& color, int state = 0);

    /** \brief \ru Добавить конус в модель.
               \en NOT TRANSLATED. \~
               \param[in] id - \ru Идентификатор элемента.
                               \en NOT TRANSLATED. \~
               \param[in] p1 - \ru Позиция центра окружности конуса.
                               \en NOT TRANSLATED. \~
               \param[in] p2 - \ru Позиция вершины конуса.
                               \en NOT TRANSLATED. \~
               \param[in] r - \ru Радиус окружности конуса.
                              \en NOT TRANSLATED.\~
               \param[in] color - \ru Цвет элемента.
                                  \en NOT TRANSLATED. \~
    */
    void AddCone(int id, const Point3DF& p1, const Point3DF& p2, float r, const Color& color, int state = 0);

    /** \brief \ru Добавить тор в модель.
               \en NOT TRANSLATED. \~
               \param[in] id - \ru Идентификатор элемента.
                               \en NOT TRANSLATED. \~
               \param[in] p1 - \ru Позиция центра тора.
                               \en NOT TRANSLATED. \~
               \param[in] p2 - \ru 
                               \en NOT TRANSLATED.\~
               \param[in] color - \ru Цвет элемента.
                                  \en NOT TRANSLATED. \~
    */
    void AddTorus(int id, const Point3DF& p1, const Point3DF& p2, float r, const Color& color, float angle1 = 0.0, float angle2 = M_PI2, int state = 0);
public:
    /** \brief \ru Добавить плоскую окружность в модель.
               \en NOT TRANSLATED. \~
               \param[in] id - \ru Идентификатор элемента.
                               \en NOT TRANSLATED. \~
               \param[in] color - \ru Цвет элемента.
                                  \en NOT TRANSLATED. \~
               \param[in] place - \ru Положение в пространстве.
                                  \en NOT TRANSLATED. \~
               \param[in] rmax - \ru  внешний радиус диска
                                 \en NOT TRANSLATED.\~
               \param[in] rmin - \ru  внутрений радиус отверсия, если равен нулю, будет цельная окружность
                                 \en NOT TRANSLATED. \~
               \param[in] angle1 - \ru  угол начала дискав радианах
                                   \en NOT TRANSLATED.\~
               \param[in] angle2 - \ru  угол окончания диска, в радианах
                                   \en NOT TRANSLATED.\~
    */
    Canvas& AddDisk(int id, const Color& color, const Placement3DF& place, float rmax, float rmin = 0.0, float angle1 = 0.0, float angle2 = 0.0, int state = 0);

    /** \brief \ru Добавить плоский прямоугольник в модель.
               \en NOT TRANSLATED. \~
               \param[in] id - \ru Идентификатор элемента.
                               \en NOT TRANSLATED. \~
               \param[in] color - \ru Цвет элемента.
                                  \en NOT TRANSLATED. \~
               \param[in] place - \ru Положение в пространстве.
                                  \en NOT TRANSLATED. \~
               \param[in] rect - \ru Параметры прямоугольника.
                                 \en NOT TRANSLATED. \~
    */
    Canvas& AddRect(int id, const Color& color, const Placement3DF& place, const RectF& rect, int state = 0);

    /** \brief \ru Добавить плоский прямоугольник в модель в плоскость экрана.
               \en NOT TRANSLATED. \~
               \param[in] id - \ru Идентификатор элемента.
                               \en NOT TRANSLATED. \~
               \param[in] color - \ru Цвет элемента.
                                  \en NOT TRANSLATED. \~
               \param[in] pntOrg - \ru Точка в пространстве.
                                  \en NOT TRANSLATED. \~
               \param[in] rect - \ru Параметры прямоугольника.
                                 \en NOT TRANSLATED. \~
     */
    Canvas& AddScreenRect(int id, const Color& color, const Point3DF& pntOrg, const RectF& rect, int state = 0);

    /** \brief \ru Добавить плоский маркер в модель.
                \en NOT TRANSLATED. \~
           \param[in] id - \ru Идентификатор элемента.
                           \en NOT TRANSLATED. \~
           \param[in] position - \ru Цвет элемента.
                                 \en NOT TRANSLATED. \~
           \param[in] markerId - \ru Идентификатор маркера.
                                 \en NOT TRANSLATED. \~
    */
    void AddMarker(int id, const Point3DF& position, MarkerID markerId, int state = 0);
public:
    /// \ru Задать цвет подсветки элемента. \en NOT TRANSLATED. \~
    void SetHighlightColor(const Color& color);
private:
    VSN_DECLARE_PRIVATE(Widget3DModel);
};
typedef  std::shared_ptr<Widget3DModel> Widget3DModelPtr;

class WidgetCanvasModelPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс плоской модели элемента управления.\n
           \en NOT TRANSLATED. \~
           \details \ru Данная модель всегда отображаеться в плоскости экрана. \n
                        Позволяет создавать виджеты в виде иконок, тулбаров, кнопок и т.п.
                    \en NOT TRANSLATED. \~
*/
// ---
class VSN_CLASS WidgetCanvasModel : public WidgetModel
{
public:
    WidgetCanvasModel();
    virtual ~WidgetCanvasModel();
public:
    /// \ru Определить точку пересечения луча и элемента управления. \en NOT TRANSLATED. \~
    virtual std::pair<int, double> Intersect(const MbLine3D& ray, int state = 0) const override;
    /// \ru Определить точку пересечения луча и элемента управления. \en NOT TRANSLATED. \~
    virtual std::pair<int, float> Intersect(const Ray3DF& ray, int state = 0) const override;
    /// \ru Нарисовать элемент управления. \en NOT TRANSLATED. \~
    virtual void Render(RenderContext& ctx, int state = 0) override;
    /// \ru Получить размер элемента управления. \en NOT TRANSLATED. \~
    virtual const MbCube& GetSize(int state = 0) const override;
    virtual const WidgetSize& GetWidgetSize(int state = 0) const override;
public:
    /// \ru Задать цвет подсветки элемента. \en NOT TRANSLATED. \~
    void SetHighlightColor(const Color& color);
public:
    /// \ru Получить холст для рисования. \en NOT TRANSLATED. \~
    Canvas& GetCanvas();
private:
    VSN_DECLARE_PRIVATE(WidgetCanvasModel);
};

} // namespace VSN

#endif //__VSN_WIDGETMODEL_H
