////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс AbsCoordLocator конвертирует значения координат
             от устройств взаимодействия, например, мыши или клавиатуры.
         \en AbsCoordLocator class converts coordinate values from
             interaction devices, for example, mouse or keyboard. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COORDLOCATOR_H
#define __VSN_COORDLOCATOR_H

#include <surface.h>
#include <vsn_global.h>
#include <vsn_object.h>
#include <vsn_math.h>

namespace VSN {

class Viewport;
class AbsCoordLocatorPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс AbsCoordLocator конвертирует значения координат
               от устройств взаимодействия, например, мыши или клавиатуры.
           \en AbsCoordLocator class converts coordinate values from
               interaction devices, for example, mouse or keyboard. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS AbsCoordLocator : public Object
{
protected:
    VSN_DECLARE_EX_PRIVATE(AbsCoordLocator);
    /// \ru Конструктор. \en Constructor. \~
    explicit AbsCoordLocator(Object* pParent = nullptr);
    /// \ru Конструктор. \en Constructor. \~
    explicit AbsCoordLocator(AbsCoordLocatorPrivate & d, Object* pParent = nullptr);
public:
    /// \ru Деструктор. \en Destructor. \~
    virtual ~AbsCoordLocator();
public:
    /// \ru Вернуть указатель на отрисовочный порт. \en Returns pointer to viewport. \~
    Viewport* GetViewport() const;
    /// \ru Установить отрисовочный порт. \en Sets viewport. \~
    void SetViewport(Viewport* pViewport);
    /// \ru Вернуть матрицу преобразования из локальных координат в координаты модели. \en Returns transformation matrix from local to model coordinates. \~
    const Matrix3DF& GetTransform() const;
    /// \ru Установить матрицу преобразования из локальных координат в координаты модели. \en Sets transformation matrix from local to model coordinates. \~
    void SetTransform(const Matrix3DF& transform);
public:
    /// \ru Функция конвертации, возвращает false, если конвертирование не удалось. \en Conversion function returns false if conversion failed. \~
    virtual bool Convert(const PointI& screenPoint, Point3DF& worldPoint, const Matrix3DF * transform = nullptr) const;
    /// \ru Функция конвертации, возвращает false, если конвертирование не удалось. \en Conversion function returns false if conversion failed. \~
    virtual bool Convert(const PointI& screenPoint, Point3DF& worldPoint, const Viewport &, const Matrix3DF * transform = nullptr) const = 0;
    /// \ru Функция корректировки, transform - матрица для преобразования в ск локатора. \en Correction function. Parameter transform is matrix for transforming to locator coordinate system. \~
    virtual Point3DF Correct(const Point3DF & worldPoint, const Viewport &, const Matrix3DF * transform = nullptr) const = 0;
public:
    /// \ru Вычислить и спроецировать точку пересечения на луч. \en Calculates and projects intersection point onto ray. \~
    virtual bool ProjectOnRay(const PointI& screenPoint, Point3DF& worldPoint, const Matrix3DF * transform = nullptr) const;
    /// \ru Вычислить и спроецировать точку пересечения на луч. \en Calculates and projects intersection point onto ray. \~
    virtual bool ProjectOnRay(const PointI& screenPoint, Point3DF& worldPoint, const Viewport &, const Matrix3DF * transform = nullptr) const;
private:
    VSN_DISABLE_COPY(AbsCoordLocator)
};

class ModelCoordLocatorPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс ModelCoordLocator конвертирует значения координат
               от устройств взаимодействия, например, мыши или клавиатуры 
               в модельные координаты в плоскости эрана.
           \en ModelCoordLocator class converts coordinate values from 
               intersection devices, for example, mouse or keyboard, 
               to model coordinates in the screen plane. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS ModelCoordLocator : public AbsCoordLocator
{
    VSN_DECLARE_EX_PRIVATE(ModelCoordLocator);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit ModelCoordLocator(Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~ModelCoordLocator();
public:
    /// \ru Функция конвертации, возвращает false, если конвертирование не удалось. \en Conversion function returns false if conversion failed. \~
    virtual bool Convert(const PointI& screenPoint, Point3DF& worldPoint, const Viewport &, const Matrix3DF * transform = nullptr) const override final;
    /// \ru Функция корректировки. \en Correction function. \~
    virtual Point3DF Correct(const Point3DF & worldPoint, const Viewport &, const Matrix3DF * transform = nullptr) const override final;
private:
    VSN_DISABLE_COPY(ModelCoordLocator)
};

class SurfaceScreenCoordLocatorPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс SurfaceScreenCoordLocator конвертирует значения координат
               от устройств взаимодействия, например, мыши или клавиатуры  
               в заданную поверхность.
           \en SurfaceScreenCoordLocator class converts coordinate values
               from interaction devices, for example, mouse or keaboard, 
               to the specified surface. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS SurfaceScreenCoordLocator : public AbsCoordLocator
{
    VSN_DECLARE_EX_PRIVATE(SurfaceScreenCoordLocator);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit SurfaceScreenCoordLocator(SPtr<const MbSurface> pSurface, Object* pParent = nullptr);
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit SurfaceScreenCoordLocator(SPtr<const MbSurface> pSurface, bool bExt, Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~SurfaceScreenCoordLocator();
public:
    /// \ru Вернуть поверхность. \en Returns surface. \~
    const MbSurface* GetSurface() const;
    /// \ru Установить поверхность в качестве опорного объекта. \en Sets surface as underlying object. \~
    void SetSurface(SPtr<const MbSurface> pSurface);

    /// \ru Флаг, определяющий, искать ли проекцию на продолжении кривой(если true, то искать).
    /// \en A flag defining whether to seek projection on the extension of the curve. \~
    void SetExtension(bool ext);
public:
    /// \ru Функция конвертации, возвращает false, если конвертирование не удалось. \en Conversion function returns false if conversion failed. \~
    virtual bool Convert(const PointI& screenPoint, Point3DF& worldPoint, const Viewport&, const Matrix3DF * transform = nullptr) const override final;
    /// \ru Функция корректировки. \en Correction function. \~
    virtual Point3DF Correct(const Point3DF& worldPoint, const Viewport&, const Matrix3DF* transform = nullptr) const override final;
private:
    VSN_DISABLE_COPY(SurfaceScreenCoordLocator)
};

class GridScreenCoordLocatorPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс GridScreenCoordLocator конвертирует значения координат
               от устройств взаимодействия, например, мыши или клавиатуры
               в заданную сетку.
           \en SurfaceScreenCoordLocator class converts coordinate values
               from interaction devices, for example, mouse or keaboard,
               to the specified grid. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS GridScreenCoordLocator : public AbsCoordLocator
{
    VSN_DECLARE_EX_PRIVATE(GridScreenCoordLocator);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GridScreenCoordLocator(SPtr<const MbGrid> pSurface, Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~GridScreenCoordLocator();
public:
    /// \ru Вернуть поверхность. \en Returns surface. \~
    const MbGrid* GetGrid() const;
    /// \ru Установить поверхность в качестве опорного объекта. \en Sets surface as underlying object. \~
    void SetGrid(SPtr<const MbGrid> pGrid);
public:
    /// \ru Функция конвертации, возвращает false, если конвертирование не удалось. \en Conversion function returns false if conversion failed. \~
    virtual bool Convert(const PointI& screenPoint, Point3DF& worldPoint, const Viewport&, const Matrix3DF * transform = nullptr) const override final;
    /// \ru Функция корректировки. \en Correction function. \~
    virtual Point3DF Correct(const Point3DF& worldPoint, const Viewport&, const Matrix3DF* transform = nullptr) const override final;
private:
    VSN_DISABLE_COPY(GridScreenCoordLocator)
};

class CurveScreenCoordLocatorPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс CurveScreenCoordLocator конвертирует значения координат
               от устройств взаимодействия, например, мыши или клавиатуры
               в заданную кривую.
           \en CurveScreenCoordLocator class converts coordinate values
               from interaction devices, for example, mouse or keaboard, 
               to the specified curve. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS CurveScreenCoordLocator : public AbsCoordLocator
{
    VSN_DECLARE_EX_PRIVATE(CurveScreenCoordLocator);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit CurveScreenCoordLocator(SPtr<const MbCurve3D> pCurve,Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~CurveScreenCoordLocator();
public:
    /// \ru Вернуть кривую. \en Returns curve. \~
    const MbCurve3D* GetCurve() const;
    /// \ru Установить кривую в качестве опорного объекта. \en Sets curve as underlying object. \~
    void SetCurve(SPtr<const MbCurve3D> pCurve);
public:
    /// \ru Функция конвертации, возвращает false, если конвертирование не удалось. \en Conversion function returns false if conversion failed. \~
    virtual bool Convert(const PointI& screenPoint, Point3DF& worldPoint, const Viewport &, const Matrix3DF * transform = nullptr) const override final;
    /// \ru Функция корректировки. \en Correction function. \~
    virtual Point3DF Correct(const Point3DF & worldPoint, const Viewport &, const Matrix3DF * transform = nullptr) const override final;
private:
    VSN_DISABLE_COPY(CurveScreenCoordLocator)
};

} // namespace VSN

#endif // __VSN_COORDLOCATOR_H
