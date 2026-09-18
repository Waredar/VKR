////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru RenderStatistics представляет функционал для сбора статистики при отрисовке сцены.
         \en RenderStatistics class provides the functional to compile statistics of the scene rendering. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_RENDERSTATISTICS_H
#define __VSN_RENDERSTATISTICS_H

#include <vsn_global.h>

namespace VSN {

//------------------------------------------------------------------------------
/** \brief \ru RenderStatistics представляет функционал для сбора статистики при отрисовке сцены.
           \en RenderStatistics class provides the functional to compile statistics of the scene rendering. \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS RenderStatistics
{
private:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit RenderStatistics();
    /// \ru Деструктор. \en Destructor. \~
    virtual ~RenderStatistics();
public:
    /// \ru Вернуть true, если сборщик статистики активен. \en Returns true if the collector of statistics is activated. \~
    static bool IsActivated();
    /// \ru Активизировать сборщик статистики. \en Activates the collector of statistic. \~
    static void SetActivation(bool activation);
    /// \ru Сбросить все счетчики отрисовки. \en Resets all render counters. \~
    static void ResetRenderCounters();

    /// \ru Вернуть количество тел в графе сцены. \en Returns the count of bodies in the scene graph. \~
    static int GetRenderBodiesCounter();
    /// \ru Добавляет количество тел к общему количеству. \en Adds the number of bodies to the general body number. \~
    static void AddRenderBodiesCounter(uint bodies);

    /// \ru Вернуть количество треугольников в графе сцены. \en Returns the count of triangles in the scene graph. \~
    static int GetRenderTriangleCount();
    /// \ru Добавляет количество треугольников к общему количеству. \en Adds the number of triangles to the general triangle number. \~
    static void AddRenderNumTriangles(int num);

    /// \ru Вернуть количество граней в графе сцены. \en Returns the count of faces in the scene graph. \~
    static int GetLoadedFacesCounter();
    /// \ru Добавляет количество загруженных граней к общему количеству. \en . \~
    static void AddLoadedFacesCounter(uint faces);

    /// \ru Вернуть количество загруженных тел в графе сцены. \en . \~
    static int GetLoadedBodiesCounter();
    /// \ru Добавляет количество загруженных тел к общему количеству. \en . \~
    static void AddLoadedBodiesCounter(uint bodies);
    /// \ru Сбросить счетчики загрузки тел. \en Resets loaded counters. \~
    static void ResetLoadedBodies();
protected:
    /// \ru Вернуть флаг счетчика рендеринга виджитов. \en Returns render widget counter flag. \~
    static bool IsRenderWidgetCounter();
    /// \ru Установить флаг счетчик рендеринга виджитов. \en Sets render widget counter flag. \~
    static bool SetRenderWidgetCounter(bool set);
private:
    friend class ViewWidget;
};

} // namespace VSN

#endif // __VSN_RENDERSTATISTICS_H
