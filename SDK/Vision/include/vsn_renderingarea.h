////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс RenderingArea представляет собой абстрактную поверхность для визуализации.
         \en RenderingArea class represents abstract surface for visualization. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_RENDERINGAREA_H
#define __VSN_RENDERINGAREA_H

#include <vsn_renderingareaformat.h>
#include <vsn_global.h>

namespace VSN {

class SizeI;
class PlatformRenderingArea;
//------------------------------------------------------------------------------
/** \brief \ru Класс RenderingArea представляет собой абстрактную поверхность для визуализации.
           \en RenderingArea class represents abstract surface for visualization. \~
    \details \ru Класс RenderingArea содержит информацию о размере поверхности, а также атрибуты поверхности, которые доступны через функцию GetFormat(). 
             \en RenderingArea class contains information about surface size, and GetAttributes that are available through GetFormat() function. \~ 
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS RenderingArea
{
public:
    /** \brief \ru Перечисление классов RenderingArea.
                \en Enumeration of RenderingArea classes. \~
    */
    enum RenderingAreaClass
    {
        ac_Window,    ///< \ru Поверхность является экземпляром окна. \en Surface is a window instance.
        ac_RenderingArea  ///< \ru Нет реализации. \en Not implemented.
    };

    /** \brief \ru Перечисление типов поверхностей.
                \en Enumeration of surface types. \~
    */
    enum RenderingAreaType
    {
        at_OpenGLRenderingArea, ///< \ru Поверхность может быть использована совместно с OpenGLContext. \en Surface can be used in common with OpenGLContext.
        at_RasterRenderingArea  ///< \ru Нет реализации. \en Not implemented.
    };
protected:
    /// \ru Специальный конструктор по умолчанию для создания поверхности с заданным типом. \en The default special constructor for creating the surface with set type.
    explicit RenderingArea(RenderingAreaClass type);
public:
    /// \ru Деструктор. \en Destructor. 
    virtual ~RenderingArea();
public:
    /// \ru Вернуть класс поверхности. \en Returns surface class.
    RenderingAreaClass GetRenderingAreaClass() const;
    /// \ru Вернуть формат поверхности. \en Returns surface format.
    virtual RenderingAreaFormat GetFormat() const = 0;
    /// \ru Вернуть указатель на созданную поверхность. \en Returns pointer to the created surface.
    virtual PlatformRenderingArea* GetRenderingAreaHandle() const = 0;
    /// \ru Вернуть тип поверхности для отрисовки. \en Returns surface type for rendering.
    virtual RenderingAreaType GetRenderingAreaType() const = 0;
    /// \ru Вернуть true, если поверхность OpenGL совместима и может быть использована совместно с OpenGLContext, в противном случае вернет false. \en True if OpenGL surface is compatible and can be used in common with OpenGLContext.
    bool IsSupportsOpenGL() const;
protected:
    RenderingArea::RenderingAreaClass m_type;
};

} // namespace VSN

#endif /* __VSN_RENDERINGAREA_H */
