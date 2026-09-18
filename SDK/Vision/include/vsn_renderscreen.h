#ifndef __VSN_RENDERSCREEN_H
#define __VSN_RENDERSCREEN_H

#include <vsn_global.h>

namespace VSN {

class Canvas;
class Viewport;
class RenderContext;
class RenderScreenPrivate;

//------------------------------------------------------------------------------
/** \brief \ru . Инструмент для рисования на экране.
           \en . The tool to drawing on the screen.\~
           \details \ru Предоставляет возможность рисования Gui в экранных координатах: \n
                    \en Provides the ability to draw Gui in screen coordinates \~
*/
// ---
class VSN_CLASS RenderScreen
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    RenderScreen();
    /// \ru Деструткор. \en Destructor. \~
    virtual ~RenderScreen();
    /// \ru Конструктор копирования. \en Copy consturctor. \~
    RenderScreen(const RenderScreen &) = delete;
    /// \ru Отобразить содержимое в контексте. \en Display content in context. \~
    void     Render( RenderContext & );
    /// \ru Получить холст для рисования. \en Get Canvas for drawing. \~
    Canvas & GetCanvas( Viewport * = nullptr );
    /// \ru Очиститьт содержимое. \en Clear content. \~
    void     Clear();
public:
    void operator () ( RenderContext & );
private:
    VSN_DECLARE_PRIVATE(RenderScreen)
};

} // namespace VSN

#endif //__VSN_RENDERSCREEN_H