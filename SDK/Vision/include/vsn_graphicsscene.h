////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс GraphicsScene представляет реализацию отрисовки сцены.
           \en GraphicsScene class represents the scene rendering implementation. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GRAPHICSSCENE_H
#define __VSN_GRAPHICSSCENE_H

#include <vsn_object.h>
#include <vsn_viewport.h>
#include <vsn_absvisioncomponent.h>
#include <vsn_scenecontent.h>
#include <vsn_cuttingtool.h>
#include <vsn_renderlayers.h>
#include <vsn_global.h>

namespace VSN {

class Light;
class GraphicsScenePrivate;
class RenderPostProcess;
//------------------------------------------------------------------------------
/** \brief \ru Класс GraphicsScene представляет собой реализацию отрисовки сцены.
           \en GraphicsScene class represents the scene rendering implementation. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS GraphicsScene : public AbsVisionComponent
{
    VSN_OBJECT(GraphicsScene)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GraphicsScene(Object* pParent = nullptr);
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GraphicsScene(SceneContentPtr ptrContent, Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~GraphicsScene();
public:
    /// \ru Инициализация OpenGL. \en Initializes OpenGL. \~
    void InitializeGL();
    /// \ru Установить режим множественной выборки сглаживания (MSAA). \en Sets (turn on/off) the mode of multisample anti-aliasing (MSAA). \~
    void SetMultiSampleMode(bool mode);

    /// \ru Вернуть указатель на содержимое сцены. \en Returns a pointer to the scene content.\~
    SceneContentPtr GetSceneContent() const;

    /// \ru Вернуть указатель на Viewport. \en Returns pointer to Viewport. \~
    ViewportPtr GetViewport() const;
    /// \ru Установить указатель на Viewport. \en Sets pointer to Viewport. \~
    void SetViewport(ViewportPtr ptrViewport);

    /// \ru Вернуть указатель на основной источник света. \en Returns pointer to the main light source. \~
    Light* GetMainLight() const;
    /// \ru Установить двустороннее освещение. \en Sets double-sided lighting. \~
    void SetDoubleSidedLighting(bool flag);

    /// \ru Вернуть список указателей на дополнительные источники освещения. \en Returns the pointer list to additional lighting sources. \~
    std::list<Light*> GetExtraLights() const;
    /// \ru Создать дополнительный источник освещения. \en Creates an additional lighting source. \~
    Light* CreateExtraLight();
    /// \ru Разрушить дополнительный источник освещения. \en Destroys the additional lighting source. \~
    void DestroyExtraLight(Light* pLight);

    /// \ru Вернуть и обновить глобальный ограниченный куб.  \en Returns and updates the global bounding box. \~
    BoundingBox GetGlobalBoundingBox() const;
    /// \ru Вернуть ссылку на инструмент динамического сечения. \en Returns a reference to the dynamic section tool. \~
    CuttingTool* GetCuttingTool();

    /// \ru Задать параметры слоя.  \en Sets layer settings. \~
    void SetRenderLayerSettings(uint32_t layer, const RenderLayerSettings&);
    /// \ru Получить параметры слоя.  \en Returns layer settings. \~
    const RenderLayerSettings& GetRenderLayerSettings(uint32_t layer) const;

    /// \ru Задать пользовательский шейдер постобработки. \en Set custom post processing shader. \~
    void SetPostProcess(RenderPostProcess* postProcess = nullptr);
    /// \ru Удалить пользовательский шейдер постобработки. \en Remove custom post processing shader. \~
    void RemovePostProcess();

    void SetTransparencyOption(TransparencyOption option);
    TransparencyOption GetTransparencyOption() const;
    int GetTransparencyLayers() const;
    void SetTransparencyLayers(int nLayers);
    bool IsTransparentModeAntialiasing() const;
    void SetTransparentModeAntialiasing(bool transparentModeAntialiasing);
public:
    void RenderScene();
protected:
    void OnEngineStarting() override;
    void OnInstalled() override;
    void OnUninstalled() override;
    ObjectVector<VisionWorkPtr> WorksToExecute(int64 time) override;
private:
    VSN_DISABLE_COPY(GraphicsScene);
    VSN_DECLARE_EX_PRIVATE(GraphicsScene);
    friend class PickLimitingVolumeWork;
};

} // namespace VSN

#endif // __VSN_GRAPHICSSCENE_H
