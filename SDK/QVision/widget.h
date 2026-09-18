////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс QtOpenGLWidget реализует интеграцию C3D Vision c Qt. Представленные классы 
             необходимы для рендеринга графики Vision с помощью OpenGL.
         \en QtOpenGLWidget class implements integration of C3D Vision with Qt.
             The presented classes are necessary to render graphics with OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __OPENGLWIDGET_H
#define __OPENGLWIDGET_H

#include <QApplication>
#include <QWidget>
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
#include <QOpenGLWidget>
#else
#include <QtOpenGLWidgets/QOpenGLWidget>
#endif
#include <QSurfaceFormat>

#include <vsn_vision.h>
#include <vsn_application.h>
#include <vsn_meshgeometry.h>
#include <vsn_graphicsview.h>
#include <vsn_graphicssceneengine.h>
#include <vsn_objectpickselection.h>
#include <vsn_openglcontextinterface.h>

namespace VSN {

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования 
               ядра Vision с библиотекой Qt и ее классами. Этот заголовочный файл может изменяться от версии 
               к версии без предупреждения или полностью удаляться.
           \en WARNING! The file is not a part of API Vision. It is needed to illustrate how to use the Vision kernel
               with Qt library and its classes. This header file can be changed from a version to a version with
               no warning or completely deleted.\~
*/

namespace QtVision {

class QtAboutSceneWidget;
class QtOpenGLWidgetPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLWidget реализует интеграцию C3D Vision c Qt.
           \en QtOpenGLWidget class implements integration of C3D Vision with Qt. \~
    \details \ru QtOpenGLWidget необходим для работы C3D Vision с другими классами библиотеки Qt. Например,
                 как самостоятельный виджет или может быть применен в качестве viewport для QGraphicsView
                 и QGraphicsScene. Vision внутри работает с собственным представлением контекста OpenGl 
                 (OpenGLContextInterface) и класс QtOpenGLWidget содержит некоторые оболочки, обеспечивающие 
                 совместную работу QOpenGLContext и OpenGLContextInterface.
             \en QtOpenGLWidget is needed for C3D Vision to operate with other classes of the Qt library,
                 for example, as an independent widget or can be applied as the viewport for both QGraphicsView
                 and QGraphicsScene. C3D Vision inside operates with its own representation of OpenGL context
                 (OpenGLContextInterface), and QtOpenGLWidget class contains certain shells providing the ability
                 for QtOpenGLWidget and OpenGLContextInterface to operate jointly. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class QtOpenGLWidget : public QOpenGLWidget, public Object
{
    Q_OBJECT
    VSN_OBJECT(QtOpenGLWidget)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit QtOpenGLWidget(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    /// \ru Деструктор OpenGLWidget освобождает созданные ресурсы. \en OpenGLWidget destructor releases created resources. \~
    virtual ~QtOpenGLWidget();
public:
    /**
    \brief \ru Подготовка OpenGL для рендеринга в этом виджете (установить текущий OpenGL контекст).
           \en Prepares OpenGL for rendering in the widget. Sets the current OpenGL context.
        \detaild \ru Нет необходимости вызывать эту функцию в большинстве случаев, потому что она 
                     вызывается автоматически перед вызовом paintGL().
                 \en There is no need to call this function in most cases, as it is called automatically
                     before calling paintGL().
    */
    using QOpenGLWidget::makeCurrent;
    void makeCurrent();
    /**
    \brief \ru Освободить OpenGL контекст.
           \en Releases OpenGL context.
        \detailed \ru Нет необходимости вызывать эту функцию в большинстве случаев, поскольку
                      в функции paintGL() контекст будет назначен и освобожден.
                  \en There is no need to call this function in most cases, as there will be the context set and
                      released in paintGL() function.
    */
    using QOpenGLWidget::doneCurrent;
    void doneCurrent();

    /// \ru Вернуть указатель на OpenGLContextInterface. \en Returns a pointer to OpenGLContextInterface. \~
    OpenGLContextInterface* contextInterface();

    /// \ru Нарисовать сцену и сохранить в картинку. \en Draw a scene and save it as a picture. \~
    QImage grabFrameImage(const GraphicsView* pGraphicsView, int width, int height, const SnapshotSettings& settings);
public Q_SLOTS:
    /// \ru Показать сайт компании. \en Show the company website. \~
    void showCompanyWebSite();
public:
    /// \ru Просто вызывает функцию QWidget::update(). Служит для совместимости слотов.
    /// \en Just calls QWidget::update() function. Serves for compatibility of slots. \~
    VSN_SLOT(Public, updateWidget, void updateWidget())
    /// \ru Просто вызывает функцию QWidget::repaint(). Служит для совместимости слотов.
    /// \en Just calls QWidget::repaint() function. Serves for compatibility of slots. \~
    VSN_SLOT(Public, repaintWidget, void repaintWidget())
protected:
    /// \ru Инициализация OpenGL ресурсов. \en Initialises OpenGL resources. \~
    void initializeGL() override;
protected:
    bool event(QEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
protected:
    QtOpenGLWidget(QtOpenGLWidgetPrivate& dd, QWidget* parent, Qt::WindowFlags f);
    VSN_DECLARE_PRIVATE(QtOpenGLWidget);
private:
    Q_DISABLE_COPY(QtOpenGLWidget);
};

class QtAutoHideWindow;
class QtOpenGLSceneWidgetPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLSceneWidget - это виджет для рендеринга графики Vision с помощью OpenGL.
           \en QtOpenGLSceneWidget is a widget for rendering C3D Vision graphics with OpenGL. \~
    \details \ru Класс QtOpenGLSceneWidget полностью самостоятельный, создает и инициализирует 
                 в полной мере компоненты Vision. Этот класс представляет необходимые функции для работы с Vision. 
                 Класс QtOpenGLSceneWidget самостоятельно устанавливает текущий контест OpenGL, когда это необходимо. 
             \en QtOpenGLSceneWidget class is fully autonomous, so it completely creates and initialises
                 C3D Vision components. This class provides required functions to work with C3D Vision.
                 QtOpenGLSceneWidget class independently sets the current OpenGL context when necessary. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class QtOpenGLSceneWidget : public QtOpenGLWidget
{
    Q_OBJECT
    VSN_OBJECT(QtOpenGLSceneWidget)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit QtOpenGLSceneWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    /// \ru Специальный конструктор. \en Special constructor. \~
    explicit QtOpenGLSceneWidget(GraphicsSceneEnginePtr engine, OpenGLContextContainer* sharedContainer, 
                QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    /// \ru Деструктор OpenGLWidget освобождает созданные ресурсы. \en OpenGLWidget destructor releases created resources. \~
    virtual ~QtOpenGLSceneWidget();
public:
    /// \ru Вернуть указатель на источник освещения сцены. \en Returns a pointer to the lighting source in the scene. \~
    Light* mainLight() const;
    /// \ru Вернуть указатель на камеру. \en Returns a pointer to the camera. \~
    Camera* camera() const;
    /// \ru Вернуть указатель на Viewport для отображения сцены. \en Returns a pointer to Viewport for displaying the scene. \~
    Viewport* viewport() const;
    /// \ru Вернуть указатель на содержимое сцены. \en Returns a pointer to the scene content. \~
    SceneContentPtr sceneContent();
    /// \ru Вернуть указатель на графическую сцену. \en Returns a pointer to the graphic scene. \~
    GraphicsScene* graphicsScene() const;
    /// \ru Вернуть указатель на компонент выбора объектов. \en Returns a pointer to the item of the object selection. \~
    ObjectPickSelection* objectPickSelection() const;
    /// \ru Вернуть указатель на GraphicsSceneEngine. \en Returns a pointer to GraphicsSceneEngine. \~
    GraphicsSceneEnginePtr graphicsEngine() const;
    /// \ru Вернуть указатель на GraphicsView. \en Returns a pointer to GraphicsView. \~
    GraphicsViewPtr ptrGraphicsView() const;
    /// \ru Вернуть указатель на GraphicsView. \en Returns a pointer to GraphicsView. \~
    GraphicsView* graphicsView() const;
public Q_SLOTS:
    void viewPortCommands();
    void viewPortRenderMode();
    void setRenderMode(RenderMode mode);
public:
    /// \ru Масштабировать модель до размера viewport по габариту модели. \en Zooms the model to ensure the bounding box of the model fits inside the viewport. \~
    VSN_SLOT(Public, ZoomToFit, void ZoomToFit())
protected:
    void resizeGL(int w, int h) override;
    void paintGL() override;
    bool event(QEvent* event) override;
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    void enterEvent(QEvent* event) override;
#else
    void enterEvent(QEnterEvent* event) override;
#endif
    void leaveEvent(QEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
    bool OnEvent(ProcessEvent* event);
protected:
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
private:
    Q_DISABLE_COPY(QtOpenGLSceneWidget);
    VSN_DECLARE_EX_PRIVATE(QtOpenGLSceneWidget);
    friend class QtRenderSelection;
};


} // namespace QtVision

} // namespace VSN

#endif // __OPENGLWIDGET_H
