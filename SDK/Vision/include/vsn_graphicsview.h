////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GRAPHICSVIEW_H
#define __VSN_GRAPHICSVIEW_H

#include <vsn_object.h>
#include <vsn_light.h>
#include <vsn_viewport.h>
#include <vsn_visionengine.h>
#include <vsn_scenecontent.h>
#include <vsn_graphicsscene.h>
#include <vsn_graphicssceneengine.h>
#include <vsn_global.h>

namespace VSN {

class BaseBrush;
/// \ru Дополнительные параметры для функции GraphicsView::ToImage(). \en NO TRANSLATION. \~
struct SnapshotSettings
{
    /// \ru Скрыть оконные виджеты на скриншоте. \en NO TRANSLATION. \~
    bool hideViewWidgets = true;
    /// \ru Скрыть виджеты сцены на скриншоте. \en NO TRANSLATION. \~
    bool hideSceneWidgets = true;
    /// \ru Установить другой фон для скриншота. \en NO TRANSLATION. \~
    BaseBrush* background = nullptr;
    /// \ru Установить размер рамки для скриншота. \en NO TRANSLATION. \~
    RectI rect;
    /// \ru Установить камеру для создания скриншота\en NO TRANSLATION. \~
    const Camera* pCamera = nullptr;
    /// \ru Учитывать соотношения сторон экрана \en NO TRANSLATION. \~
    bool bAspectRatio = true;
};

class OrientationMarker;
class GraphicsViewPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS GraphicsView : public Object
{
    VSN_OBJECT(GraphicsView)
public:
    explicit GraphicsView(GraphicsSceneEnginePtr ptrSceneEngine);
    ~GraphicsView() override;
public:
    /// \ru Инициализация GraphicsView. \en NO TRANSLATION. \~
    void Initialize();
    /// \ru Подготовка объектов Vision'а для отрисовки. \en NO TRANSLATION. \~
    void PreparingToDisplay();
    /// \ru Подготовка к уничтожению Vision. \en NO TRANSLATION. \~
    void PreparingToDestroy();
    /// \ru Вернуть указатель на VisionEngine. \en NO TRANSLATION. \~
    VisionEnginePtr GetVisionEngine() const;
    /// \ru Вернуть указатель на GraphicsSceneEngine. \en NO TRANSLATION. \~
    GraphicsSceneEnginePtr GetSceneEngine() const;
    /// \ru Вернуть указатель на источник освешения сцены. \en Returns a pointer to scene lighting source. \~
    Light* GetMainLight() const;
    /// \ru Вернуть указатель на Viewport для отображения сцены. \en Returns a pointer to Viewport to display a scene. \~
    ViewportPtr GetViewport() const;
    /// \ru Вернуть указатель на содержимое сцены. \en Returns a pointer to scene content. \~
    SceneContentPtr GetSceneContent() const;
    /// \ru Вернуть указатель на графическую сцену. \en Returns a pointer to graphic scene. \~
    GraphicsScene* GetGraphicsScene() const;

    /// \ru Установить новое положение камеры. \en NO TRANSLATION. \~
    void SetPositionCamera(const Camera& newCameraPosition);
    /// \ru Установить новую ориентацию камеры. \en NO TRANSLATION. \~
    void SetOrientationCamera(Orientation orientation, bool bZoomToFit);
    /// \ru Увеличить модель до размера viewport по габариту модели. \en Zooms the model to viewport size by bounding box of the model. \~
    void SetZoomToFit(const BoundingBox& box, float factor = 2.2f);

    /// \ru Установить вектор камеры, который будет направлен вверх. \en NO TRANSLATION. \~
    void SetOrientationUpVector(const Vector3DF& vUp);

    /// \ru Вернуть true, если камера будет плавно перемещаться из одной позиции в другую. \en NO TRANSLATION. \~
    bool GetSmoothTransition() const;
    /// \ru Этот метод определяет, должна ли камера плавно перейти от предыдущей позиции к новой. \en NO TRANSLATION. \~
    void SetSmoothTransition(bool bSmooth);

    /// \ru Вернуть продолжительность плавного перехода в секундах. \en NO TRANSLATION. \~
    float GetSmoothTransitionDuration() const;
    /// \ru Этот метод определяет продолжительность плавного перехода в секундах. \en NO TRANSLATION. \~
    void SetSmoothTransitionDuration(float duration);

    /// \ru Вернуть режим отображения модели. \en NO TRANSLATION. \~
    RenderMode GetRenderMode() const;
    /// \ru установить новый режим отображения. \en NO TRANSLATION. \~
    void SetRenderMode(RenderMode mode);

    /// \ru Вернуть указатель на маркер ориентации. \en Returns a pointer to the orientation marker. \~
    OrientationMarker* GetOrientationMarker() const;
    /// \ru Нарисовать сцену и сохранить в картинку, необходимо установить текущий контекст.  \en NO TRANSLATION. \~
    Image ToImage(int width, int height, const SnapshotSettings& = {}) const;
public:
    VSN_SIGNAL(Public, OnViewModified, void OnViewModified());
private:
    /// \ru Для обнуления OrientationMarker. \en To zero the OrientationMarker. \~
    VSN_SLOT(Private, slotDestroyed, void slotDestroyed(Object* object))
public:
    void DoRender();
    void DoResize(int width, int height);
private:
    VSN_DISABLE_COPY(GraphicsView);
    VSN_DECLARE_EX_PRIVATE(GraphicsView);
};

typedef std::shared_ptr<GraphicsView> GraphicsViewPtr;

} // namespace VSN

#endif /* __VSN_GRAPHICSVIEW_H */
