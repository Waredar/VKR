////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс Viewport определяет viewport.
         \en Viewport class defines viewport. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_VIEWPORT_H
#define __VSN_VIEWPORT_H

#include <vsn_object.h>
#include <vsn_camera.h>
#include <vsn_rendercontainer.h>
#include <vsn_opengl.h>
#include <vsn_math.h>
#include <vsn_global.h>

namespace VSN {

class Frustum;
class RenderObject;
class Image;
class WidgetLayout;
class ViewportPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс Viewport определяет viewport.
            \en Viewport class defines viewport.
    \details  \ru Класс Viewport имеет дополнительные инструменты и функционал по управлению сценой.
              \en Viewport class has additional tools and functional for scene control. \~
    \ingroup Vision_Viewport
*/
//---
class VSN_CLASS Viewport : public Object
{
    VSN_OBJECT(Viewport)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit Viewport();
    /// \ru Деструктор. \en Destructor. \~
    ~Viewport() override;
public:
    /// \ru Вернуть указатель на камеру, ассоциированную с Viewport. \en Returns pointer to the camera associated with viewport. \~
    Camera* GetCamera() const;
    /// \ru Установить камеру ассоциированную с Viewport. \en Set the camera associated with the Viewport. \~
    void SetCamera(Camera* pCamera);

    /// \ru Вернуть размер viewport. \en Returns viewport size. \~
    SizeI GetViewportSize() const;
    /// \ru Вернуть размер viewport. \en Returns viewport size. \~
    void GetViewportSize(int& width, int& height) const;
    /// \ru Установить новые размеры viewport. \en Sets new viewport sizes. \~
    void SetSizeViewport(int width, int height, bool updateViewport = true);

    /// \ru Вернуть нормализованное положение мыши с учетом размера viewport. \en Returns normalized mouse position with given viewport size. \~
    MbCartPoint NormalizedMousePosition(int x, int y);
    /// \ru Конвертировать экранные координаты мыши в экранные координаты OpenGL. \en Transforms mouse screen coordinates to OpenGL screen coordinates. \~
    MbCartPoint ScreenPointToOpenGLScreen(int x, int y);
    /// \ru Конвертировать нормализованные экранные координаты мыши в экранные координаты OpenGL. \en Transforms normalized mouse screen coordinates to OpenGL screen coordinates. \~
    MbCartPoint ScreenNormalizedToOpenGLScreen(double x, double y);
    /// \ru Вернуть вектор взгляда по данной позиции мыши. \en Returns view vector by given mouse position. \~
    MbVector3D PositionMouseToVector(GLdouble posX, GLdouble posY) const;
    /// \ru Вернуть нормализованный вектор взгляда по данной позиции мыши. \en Returns normalized view vector by given mouse position. \~
    MbVector3D NormalizedPositionMouseToVector(double posX, double posY) const;

    /// \ru Вернуть угол обзора камеры для этого Viewport. \en Returns the camera angle for this viewport. \~
    float GetCameraAngle() const;
    /// \ru Установить угол обзора камеры для этого Viewport. \en Sets the camera angle for this viewport. \~
    void SetCameraAngle(float angle);

    /// \ru Вернуть тангенс камеры для этого Viewport. \en Returns the camera tangent for this viewport. \~
    float GetTangentCamera() const;

    /// \ru Получить расстояние до ближайшей плоскости отсечения. \en Returns a distance to the near (or front) clipping plane. \~
    float GetDistanceToNearClippingPlane() const;
    /// \ru Установить расстояние до ближайшей плоскости отсечения. \en Sets a distance to the near (or front) clipping plane. \~
    bool SetDistanceToNearClippingPlane(float dis);

    /// \ru Получить расстояние до дальней плоскости отсечения. \en Returns a distance to the far (or back) clipping plane. \~
    float GetDistanceToFarClippingPlane() const;
    /// \ru Установить расстояние до дальней плоскости отсечения. \en Sets a distance to the far (or back) clipping plane. \~
    bool SetDistanceToFarClippingPlane(float dis);
    /// \ru Установить ближнее и дальнее отсечения по габариту. \en Sets the near and far clipping by bounding box. \~
    void ComputeMinMaxPlanes(const BoundingBox& bBox);

    /// \ru Вернуть цвет фона порта. \en Returns port background colour. \~
    const Color& GetBackgroundColour() const;
    /// \ru Установить цвет фона viewport. \en Sets viewport background colour. \~
    void SetBackgroundColour(const Color& color);
    /// \ru Установить градиентный цвет фона viewport. \en Sets viewport gradient background colour. \~
    void SetGradientBackgroundColour(const Color& topColor, const Color& bottomColor);

    /// \ru Загрузить изображение фона viewport по имени файла. \en Loads viewport background image by file name. \~
    void LoadBackgroundImage(const std::string& imageFile);
    /// \ru Загрузить изображение фона viewport из Image. \en Loads viewport background image from Image. \~
    void LoadBackgroundImage(const Image& image);
    /// \ru Удалить изображение фона viewport. \en Deletes viewport background image. \~
    void DeleteBackgroundImage();

    /// \ru Вернуть размер ловушки для выбора. \en Returns selection area size. \~
    int GetSelectionAreaSize() const;
    /// \ru Установить размер ловушки для выбора. \en Sets selection area size. \~
    void SetSelectionAreaSize(int size);

    /// \ru Вернуть проекционную матрицу. \en Returns projection matrix. \~
    Matrix3DF GetProjectionMatrix() const;
    /// \ru Вернуть составную матрицу (проекционная и видовая). \en Returns composite matrix(projection matrix and view matrix). \~
    Matrix3DF GetMultipleMatrix() const;

    /// \ru Вернуть true, если используется ортогональная проекция. \en True if orthographic projection is used. \~
    bool IsOrthographicProjection() const;
    /// \ru Установить использование ортогональной проекции. \en Orthographic projection use flag. \~
    void SetOrthographicProjection(bool bOrthographic);

    /// \ru Вернуть минимальное количество пикселей при выбранном размере. \en Returns minimum pixel count for the selected size. \~
    int GetPixelCullingSize() const;
    /// \ru Установить минимальное количество пикселей при выбранном размере. \en Sets minimum pixel count for the selected size. \~
    void SetPixelCullingSize(int size);

    /// \ru Вернуть минимальное соотношение пикселей для очистки. \en Returns minimum pixel ratio for culling. \~
    float GetStaticPixelCullingRatio() const;
    /// \ru Вернуть минимальное динамическое соотношение пикселей для очистки. \en Returns minimum dynamic pixel ratio for culling. \~
    float GetDynamicPixelCullingRatio() const;
    /// \ru Вернуть значение масштаба. \en Return scale value. \~
    float GetScale() const;
    /// \ru Установить значение масштаба. \en Sets scale value. \~
    void SetScale(float scale);
public:
    /// \ru Инициализация OpenGL. \en Initializes OpenGL. \~
    void InitOpenGl();
    /// \ru Добавить матрицу камеры. \en Adds the camera matrix. \~
    void MultMatrixCamera();
    /// \ru Обновить viewport и матрицу проецирования. \en Updates viewport and projection matrix. \~
    void UpdateProjectionMatrix();
    /// \ru Вернуть соотношение сторон экрана. \en Returns screen aspect ratio. \~
    float GetAspectRatio() const;
    /// \ru Установить принудительно соотношение сторон экрана. \en Sets forcibly screen aspect ratio. \~
    void SetAspectRatio(float);
    /// \ru Обновить соотношение сторон экрана. \en Updates screen aspect ratio. \~
    void UpdateAspectRatio();

    /// \ru Вернуть усеченный конус этого вида. \en Returns view frustum. \~
    const Frustum& GetFrustum() const;
    /// \ru Вернуть усеченный конус для выбора. \en Returns view frustum for selection. \~
    Frustum SelectionFrustum(int x, int y) const;

    /// \ru Преобразовать координаты окна в плоскость, параллельную экрану и проходящую через начало координат сцены. \en Transforms window coordinates to the plane parallel to the screen and passing through the scene origin. \~
    void ConvertScreenPointToParallelScreenPlane(const PointF& logPos, const Point3DF& origin, Point3DF& point);

    /// \ru Преобразование мировой точки в оконную. \en Transforms the world point to the window point. \~
    void WorldPointToScreenPoint(const Point3DF& wp, Point3DF& lp) const;
    /// \ru Преобразование оконной точки в мировую. \en Transforms the window point to the world point. \~
    void ScreenPointToWorldPoint(const Point3DF& lp, Point3DF& wp) const;

    /// \ru Вернуть Point3DF из экранных координат. \en Returns Point3DF from screen coordinates. \~
    Point3DF UnProject(int x, int y, uint buffer = GL_FRONT) const;
    /// \ru Вернуть список Point3DF из экранных координат(размер этого списка должен быть кратным двум). \en Returns Point3DF list from screen coordinates. The size of this list must be multiple of two. \~
    std::vector<Point3DF> UnProject(const std::vector<int>& vectorX, uint buffer = GL_FRONT) const;
public:
    /// \ru Обновить усеченный конус viewport. \en Updates view frustum for viewport. \~
    bool UpdateFrustumPlanes(Matrix3DF* pMatrix = nullptr);

    /// \ru Увеличить модель до размера viewport по габариту модели. \en Zooms the model to viewport size by bounding box of the model. \~
    void ZoomToFit(const BoundingBox& box, float factor = 2.2f);
    /// \ru Получить идентификатор вьюпорта. \en Get the identifier of the viewport
    size_t GetId() const;
    /// 
    bool IsVisibleViewWidgets() const;
    /// 
    void SetVisibleViewWidgets(bool);

    /// 
    bool IsVisibleSceneWidgets() const;
    /// 
    void SetVisibleSceneWidgets(bool);

    /// 
    void UpdateSceneWidgets();
public:
    VSN_SIGNAL(Public, ViewportSizeModified, void ViewportSizeModified(const SizeI& size), size)
    VSN_SIGNAL(Public, RefreshScreen, void RefreshScreen())
    VSN_SIGNAL(Public, OnProjectionModified, void OnProjectionModified(bool bOrthographic), bOrthographic)
private:
    VSN_DECLARE_PRIVATE(Viewport)
};

typedef std::shared_ptr<Viewport> ViewportPtr;

} // namespace VSN

#endif /* __VSN_VIEWPORT_H */
