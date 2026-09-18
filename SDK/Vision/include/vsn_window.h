////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Window представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Window is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_WINDOW_H
#define __VSN_WINDOW_H

#include <vsn_object.h>
#include <vsn_rect.h>
#include <vsn_namespace.h>
#include <vsn_renderingarea.h>
#include <vsn_processevent.h>
#include <vsn_renderingareaformat.h>

#include <vsn_global.h>

namespace VSN {

class Display;
class OpenGLContextInterface;
class WindowPrivate;
class PlatformWindow;

//------------------------------------------------------------------------------
/** \brief \ru Класс Window представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Window is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS Window : public Object, public RenderingArea
{
    VSN_OBJECT(Window)
public:
    explicit Window(Display* screen = nullptr);
    ~Window() override;
public:
    // создать окно
    void Create(void* hWindow, OpenGLContextInterface* pContext);
    // вернуть формат окна
    RenderingAreaFormat GetFormat() const override;
    // установить формат отрисовочному окну
    void SetFormat(const RenderingAreaFormat& format);
    RenderingAreaFormat GetQueriedFormat() const;

    void SetRenderingAreaType(RenderingAreaType areaType);
    RenderingAreaType GetRenderingAreaType() const override;

    PlatformWindow* GetHandle() const;

    Display* GetDisplay() const;
    void SetDisplay(Display* pDisplay);

    double GetDevicePixelRatio() const;
    void Destroy();
public:
    virtual PlatformRenderingArea* GetRenderingAreaHandle() const;
protected:
    Window(WindowPrivate& dd, Window* parent);
protected:
    bool OnEvent(ProcessEvent* event) override;
private:
    friend class BaseApplicationPrivate;
    VSN_DISABLE_COPY(Window);
    VSN_DECLARE_EX_PRIVATE(Window);
};

} // namespace VSN

#endif // __VSN_WINDOW_H
