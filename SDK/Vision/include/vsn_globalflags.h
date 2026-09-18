////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Глобальные настройки для модуля визуализации.
           \en Global settings for visualization module. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_GLOBALFLAGS_H
#define __VSN_GLOBALFLAGS_H

#include <vsn_string.h>
#include <vsn_namespace.h>
#include <vsn_global.h>

namespace VSN {

//-----------------------------------------------------------------------------
/**
\brief \ru Глобальные настройки для модуля визуализации.
       \en Global settings for visualization module. \~
    \details \ru Класс GlobalFlags предоставляет функции для управления общими настройками модуля визуализации C3D Vision.
             \en GlobalFlags class provides functions to control C3D visualization module (C3D Vision) global settings. \~
*/
//---
class VSN_CLASS GlobalFlags
{
private:
    explicit GlobalFlags();
public:
    ~GlobalFlags();
public:
    /// \ru Инициализировать значения по умолчанию. \en Initializes default values.
    static void Initialize();
public:
    /// \ru Вернуть версию OpenGL. \en Returns OpenGL version.
    static String GetVersionOpenGl();
    /// \ru Вернуть имя поставщика. \en Returns vendor name.
    static String GetVendorOpenGl();
    /// \ru Вернуть имя отрисовщика OpenGL. \en Returns OpenGL render name.
    static String GetRendererOpenGl();

    /// \ru Вернуть флаг режима выбора. \en Returns selection mode flag.
    static bool IsSelectionMode();
    /// \ru Установить флаг режима выбора. \en Sets selection mode flag.
    static void SetSelectionMode(bool set);

    /// \ru Вернуть флаг режима выбора групповой геометрии. \en Returns selection mode flag (group geometry).
    static bool IsSelectionModeGroupGeometry();
    /// \ru Установить флаг режима выбора групповой геометрии. \en Sets selection mode flag (group geometry).
    static void SetSelectionModeGroupGeometry(bool set);

    /// \ru Вернуть флаг выбора PolygonGeometry. \en Returns selection flag of PolygonGeometry.
    static bool IsSelectionPolygonGeometry();
    /// \ru Установить флаг выбора PolygonGeometry. \en Sets selection flag of PolygonGeometry.
    static void SetSelectionPolygonGeometry(bool set);

    /// \ru Вернуть true, если используется pixel culling. \en True if pixel culling is used.
    static bool IsPixelCullingEnabled();
    /// \ru Установить флаг использования pixel culling. \en Sets pixel culling use flag.
    static void SetPixelCullingEnabled(bool set);

    /**
    \brief \ru Вернуть true, если используется pixel culling при управлении сценой.
           \en Returns true if pixel culling, while managing the scene, is enabled. \~
    \details \ru По умолчанию флаг установлен в значение false. При активации процесса PrCameraOrbit, 
                 PrCameraPan или другого процесса управления сценой этот флаг устанавливается 
                 автоматически в значение true, при деактивации процесса восстанавливает старое значение.
             \en ~The flag is set to false by default. It is set to true automatically when activating
                  PrCameraOrbit, PrCameraPan or another process for managing the scene. When deactivating
                  a process, the flag is set to an old value.\~
    \note \ru Если необходимо, чтобы функция PixelCulling работала все время нужно вручную установить 
              значение флагов scenePixelCullingEnabled и pixelCullingEnabled в true.
          \en To set PixelCulling enabled for all the time, you should manually set the value of the flags 
              scenePixelCullingEnabled and pixelCullingEnabled to true. \~
    */
    static bool IsScenePixelCullingEnabled();
    /// \ru Установить флаг использования pixel culling при управлении сценой. \en Sets pixel culling, while managing the scene, use flag.
    static void SetScenePixelCullingEnabled(bool set);

    /// \ru Вернуть true, если учитывается ориентированный габарит при pixel culling. \en Returns true if pixel culling with the oriented bounding box is used.
    static bool IsPixelCullingOrientedBoundBox();
    /// \ru Установить флаг с учетом ориентированного габарита при pixel culling. \en Sets pixel culling with the oriented bounding box use flag.
    static void SetPixelCullingOrientedBoundBox(bool set);

    /// \ru Вернуть true, если оптимизация включена для кэширования идентичных материалов. \en Returns true if optimization is enabled for caching identical content. \~
    static bool IsMaterialCache();
    /// \ru Установить флаг кэширования идентичных материалов для улучшения производительности рендеринга и экономии оперативной памяти. 
    /// \en Set the caching flag for identical materials to improve rendering performance and save RAM. \~
    static void SetMaterialCache(bool set);

    /// \ru NO TRANSLATION. \en NO TRANSLATION.
    static CullFaces GetFaceCulling();
    /// \ru NO TRANSLATION. \en NO TRANSLATION.
    static void SetFaceCulling(CullFaces set);

    /// \ru Вернуть флаг использования пространственного разбиения. \en Returns bounding volume use flag.
    static bool IsBoundingVolume();
    /// \ru Установить флаг использования пространственного разбиения. \en Sets bounding volume use flag.
    static void SetBoundingVolume(bool set);

    /// \ru Вернуть флаг использования отсечения по пирамиде. \en Returns frustum culling use flag.
    static bool IsFrustumCulling();
    /// \ru Установить флаг использования отсечения по пирамиде. \en Sets frustum culling use flag.
    static void SetFrustumCulling(bool set);

    /// \ru Вернуть флаг "скрывать ребра" при манипуляцией со сценой. \en NO TRANSLATION.
    static bool IsHiddenEdges();
    /// \ru Установить флаг "скрывать ребра" при манипуляцией со сценой. \en NO TRANSLATION.
    static void SetHideEdges(bool set);

    /// \ru Готовы ли все флаги к использованию пользователем. \en Checks if all flags are ready to be used by user.
    static bool IsReadyFlags();

    /// \ru Вернуть значение строить четырехугольную сетку. \en Returns value build quadrangle grid.
    static bool IsBuildQuadGrid();
    /// \ru Установить флаг строить четырехугольную сетку. \en Set the flag to build a quad grid.
    static void SetBuildQuadGrid(bool bBuild);

    /// \ru Вернуть значение строить четырехугольную сетку. \en Returns value build quadrangle grid.
    static bool IsUseAttributeWireFrame();
    /// \ru Установить флаг строить четырехугольную сетку. \en Set the flag to build a quad grid.
    static void SetUseAttributeWireFrame(bool bValue);

    /// \ru Вернуть тип подсветки грани. \en Returns highlight type to face.
    static HighlighterType GetFaceHighlighter();
    /// \ru Установить тип подсветки грани. \en Sets highlight type to face.
    static void SetFaceHighlighter(HighlighterType type);

    // \ru Не использовать! Опция предназначена для внутреннего использования. \en Do not use! This option is intended for internal use only.
    [[deprecated("use GraphicsScene::GetTransparencyOption instead.")]]
    static RenderingOption GetRenderingOption();
    [[deprecated("use GraphicsScene::SetTransparencyOption instead.")]]
    static void SetRenderingOption(const RenderingOption& option);

    // \ru Это экспериментальная опция.Использовать только по рекомендации. \en This is an experimental option. Use only if recommended.
    static bool GetLineAntialiasing();
    static void SetLineAntialiasing(bool set);
public: // секция отладки для разработки компонента
    // \ru Эта опция в глубокой разработке. \en This option is in deep development.
    static bool GetCoreContext();
    static bool GetPartialGLProxy();
};

} // namespace VSN


#endif // __VSN_GLOBALFLAGS_H
