////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Application представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Application is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_APPLICATION_H
#define __VSN_APPLICATION_H

#include <vsn_baseapplication.h>
#include <vsn_global.h>

namespace VSN {

class Display;
class Window;
class ApplicationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс Application представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Application is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS Application : public BaseApplication
{
    VSN_OBJECT(Application)
public:
    explicit Application();
    virtual ~Application();
public:
    static ObjectList<Window*> GetAllWindows();
//    static ObjectList<Window*> GetTopLevelWindows();

    /// \ru Вернуть указатель на основной экран (первый в списке). \en Return the pointer to the main screen (first in the list).
    static Display* GetFirstDisplay();
    /// \ru Вернуть список всех экранов, связанных с оконной системой приложения. \en Return the list of all screens related to the window system of the application.
    static ObjectList<Display*> GetDisplays();

    /// \ru Вернуть минимальное значение при операции перетаскивания. \en Return the minimum distance for dragging commands.
    static int GetBeginDragDistance();
    /// \ru Установить минимальное значение для операции перетаскивания. \en Set the minimum distance for dragging commands.
    static void SetBeginDragDistance(int distance);

    static bool GetQuitOnLastWindowClosed();
    static void SetQuitOnLastWindowClosed(bool bQuit);
    static int OnExec();

    double GetDevicePixelRatio() const;
protected:
    bool OnProcessNotify(Object* pObject, ProcessEvent* pEvent) override final;
private:
    VSN_DISABLE_COPY(Application)
    VSN_DECLARE_EX_PRIVATE(Application)
};

} // namespace VSN

#endif // __VSN_APPLICATION_H
