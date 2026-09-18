////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Файл содержит набор заливок которые могут использоваться в Painter.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BRASH_H
#define __VSN_BRASH_H

#include <vector>

#include <mb_cart_point.h>

#include <vsn_color.h>
#include <vsn_point.h>
#include <vsn_texture2d.h>
#include <vsn_global.h>

namespace VSN {

enum class BrushType
{
    Undefined,
    Solid,
    Image,
    LinearGradient,
    AngleGradient,
    RadialGradient,
    Hatching,
    LinesStyle
};

class BaseBrushPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Базовый класс.
           \en Base class. \~
*/
// ---
class VSN_CLASS BaseBrush
{
public:
    /// \ru Конструктор \en Constructor \~
    BaseBrush(BrushType);
    /// \ru Конструктор \en Constructor. \~
    BaseBrush(const BaseBrush&);
    /// \ru Деструктор \en Destructor. \~
    virtual ~BaseBrush();
public:
    /// \ru Получить тип заливки. \en Get a type of brush. \~
    BrushType GetType() const;
protected:
    BaseBrush(BaseBrushPrivate*);
    VSN_DECLARE_PRIVATE(BaseBrush);
};

class SolidBrushPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Заливка сплошным цветом.
           \en Solid color fill. \~
*/
// ---
class VSN_CLASS SolidBrush : public BaseBrush
{
public:
    /// \ru Конструктор \en Constructor. \~
    SolidBrush(const Color& color);
    /// \ru Конструктор \en Constructor. \~
    SolidBrush(const SolidBrush& other);
public:
    /// \ru Изменить цвет \en Change color. \~
    void SetColor(const Color& color);
    /// \ru Получить цвет \en Get color. \~
    const Color& GetColor() const;
private:
    VSN_DECLARE_EX_PRIVATE(SolidBrush);
};

class ImageBrushPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Заливка текстурой.
           \en Texture fill. \~
    \details \ru origin - смещение изображения относительно центра СК плоскости
             \en origin - image offset relative to the canvas plane center. \~
*/
// ---
class VSN_CLASS ImageBrush : public BaseBrush
{
public:
    /// \ru Конструктор \en Constructor. \~
    ImageBrush(const Image& img, const PointF& origin);
    /// \ru Конструктор \en Constructor. \~
    ImageBrush(const ImageBrush& other);
public:
    /// \ru Изменить точку начала изображения \en Change origin. \~
    void SetOrigin(const PointF& pnt);
    /// \ru Получить точку начала изображения \en Get origin. \~
    const PointF& GetOrigin() const;
    /// \ru Получить изображение \en Get image. \~
    const Image& GetImage() const;
private:
    VSN_DECLARE_EX_PRIVATE(ImageBrush);
};

} // namespace VSN
#endif