#include "widget_private.h"

#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QMessageBox>
#include <QThread>
#include <QDesktopServices>
#include <QProcessEnvironment>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOffscreenSurface>
#include <QOpenGLPaintDevice>
#include <QOpenGLFramebufferObject>
#include <QSettings>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
#include <QScreen>
#else
#include <QDesktopWidget>
#endif

#include <vsn_window.h>
#include <vsn_openglfbo.h>
#include <vsn_graphicsview.h>
#include <vsn_renderstatistics.h>
#include <vsn_graphicssceneengine.h>
#include <vsn_graphicsscene.h>
#include <vsn_texture2d.h>

#include <tool_enabler.h>

#include "context.h"

#include <last.h>


namespace VSN {

namespace QtVision {

/* QtConverterEventListener */
QtConverterEventListener::QtConverterEventListener(QObject* pParent, GraphicsScene* pListenerEvent)
    : QObject(pParent)
    , m_pListenerEvent(pListenerEvent)
    , m_idleTimerId(-1)
    , m_devicePixelRatio(1.0)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    parent()->installEventFilter(this);
#ifndef VSN_OS_WIN
    m_idleTimerId = startTimer(QGuiApplication::primaryScreen()->refreshRate());
#endif
}

//-----------------------------------------------------------------------------
//
// ---
QtConverterEventListener::~QtConverterEventListener()
{
    parent()->removeEventFilter(this);
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::keyPressEvent(QKeyEvent* event)
{
    KeyEvent processEvent(ProcessEvent::KeyDown, event->key(), event->nativeScanCode(), event->nativeVirtualKey(), event->nativeModifiers());
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::keyReleaseEvent(QKeyEvent* event)
{
    KeyEvent processEvent(ProcessEvent::KeyUp, event->key(), event->nativeScanCode(), event->nativeVirtualKey(), event->nativeModifiers());
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseHoverEvent(QHoverEvent* event)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    int flags = 0;
    PointI posMouse(event->posF().x() * m_devicePixelRatio, event->posF().y() * m_devicePixelRatio);
    HoverEvent processEvent(ProcessEvent::HoverMove, posMouse, PointI());
    processEvent.SetFlags(flags);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
static int mapModifiers(Qt::KeyboardModifiers state)
{
    int flag = 0;
    if (state & Qt::ShiftModifier)
        flag |= mb_Shift;
    if (state & Qt::ControlModifier)
        flag |= mb_Control;
    if (state & Qt::AltModifier)
        flag |= mb_Alt;
    return flag;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mousePressEvent(QMouseEvent* event)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == Qt::LeftButton)
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonDown;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonDown;
    }
    else if (event->button() == Qt::RightButton)
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonDown;
    }

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(type);
    processEvent.SetFlags(flags);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseMoveEvent(QMouseEvent* event)
{
    int flags = mapModifiers(event->modifiers());
    if (event->buttons() == Qt::LeftButton)
        flags |= mb_LButton;
    if (event->buttons() == Qt::MiddleButton)
        flags |= mb_MButton;
    if (event->buttons() == Qt::RightButton)
        flags |= mb_RButton;

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(ProcessEvent::MouseMove);
    processEvent.SetFlags(flags);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseReleaseEvent(QMouseEvent* event)
{
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == Qt::LeftButton)
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonUp;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonUp;
    }
    else if (event->button() == Qt::RightButton)
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonUp;
    }

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(type);
    processEvent.SetFlags(flags);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseDoubleClickEvent(QMouseEvent* event)
{
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == Qt::LeftButton)
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonDblClk;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonDblClk;
    }
    else if (event->button() == Qt::RightButton)
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonDblClk;
    }

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(type);
    processEvent.SetFlags(flags);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseWheelEvent(QWheelEvent* event)
{
    WheelEvent processEvent;
    int flags = mapModifiers(event->modifiers());
    processEvent.SetFlags(flags);

#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    processEvent.SetWheelDelta(event->delta());
    processEvent.SetWindowPos(PointI(event->pos().x(), event->pos().y()));
#else
    processEvent.SetWheelDelta(event->angleDelta().y() * m_devicePixelRatio);
    processEvent.SetWindowPos(PointI(event->position().x() * m_devicePixelRatio, event->position().y() * m_devicePixelRatio));
#endif
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseEnterEvent(QEnterEvent* event)
{
    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(ProcessEvent::MouseEnter);

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    processEvent.SetFlags(0);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseLeaveEvent(QEvent* event)
{
    VSN_UNUSED(event);
    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(ProcessEvent::MouseLeave);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::checkShareContexts(MouseEvent& processEvent)
{
    if (!QApplication::instance()->testAttribute(Qt::AA_ShareOpenGLContexts))  return false;
    if (QtOpenGLSceneWidget* pWidget = dynamic_cast<QtOpenGLSceneWidget*> (this->parent()))
    {
        Viewport* pViewWid = pWidget->viewport();
        if(!pViewWid)  return false;
        if (pViewWid->GetId() != processEvent.GetViewport())
            processEvent.SetViewport(pViewWid->GetId());
    }
    return true;
}

//-----------------------------------------------------------------------------
// Перегрузка для внутренних работ.
// ---
bool QtConverterEventListener::eventFilter(QObject* watched, QEvent* event)
{
    if (watched != parent())
        return QObject::eventFilter(watched, event);

    switch (event->type())
    {
        case QEvent::KeyPress:
            return keyPressEvent(static_cast<QKeyEvent*>(event));
        case QEvent::KeyRelease:
            return keyReleaseEvent(static_cast<QKeyEvent*>(event));
        case QEvent::HoverMove:
            return mouseHoverEvent(static_cast<QHoverEvent*>(event));
        case QEvent::MouseMove:
            return mouseMoveEvent(static_cast<QMouseEvent*>(event));
        case QEvent::MouseButtonDblClick:
            return mouseDoubleClickEvent(static_cast<QMouseEvent*>(event));
        case QEvent::MouseButtonPress:
            return mousePressEvent(static_cast<QMouseEvent*>(event));
        case QEvent::MouseButtonRelease:
            return mouseReleaseEvent(static_cast<QMouseEvent*>(event));
        case QEvent::Wheel:
            return mouseWheelEvent(static_cast<QWheelEvent*>(event));
        case QEvent::Enter:
            return mouseEnterEvent(static_cast<QEnterEvent*>(event));
        case QEvent::Leave:
            return mouseLeaveEvent(event);
        default:
            break;
    }
    return QObject::eventFilter(watched, event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtConverterEventListener::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_idleTimerId)
        BaseApplication::OnProcessSendPostedEvents();
    else
        QObject::timerEvent(event);
}

//-----------------------------------------------------------------------------
// 
// ---
inline QtOpenGLWidgetPrivate::~QtOpenGLWidgetPrivate()
{
    reset();
}

//-----------------------------------------------------------------------------
// 
// ---
void QtOpenGLWidgetPrivate::initialize()
{
    VSN_P(QtOpenGLWidget);
    if (m_bInitialized)
        return;
    qApp->setWindowIcon(QIcon(":/res/crystal.ico"));
    p.makeCurrent();
    m_pQContext = new QtOpenGLContextShell(&p, m_pSharedContainer);
    m_pQContext->MakeCurrent();
    m_bInitialized = true;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidgetPrivate::reset()
{
    VSN_DELETE_AND_NULL(m_pQContext);
    m_bInitialized = false;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidgetPrivate::renderNow()
{
    VSN_P(QtOpenGLWidget);
    QOpenGLContext* openGLContext = p.context();
    if (!openGLContext)
        return;
    p.makeCurrent();
    p.paintGL();
    openGLContext->swapBuffers(openGLContext->surface());
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidgetPrivate::renderLater()
{
    VSN_P(QtOpenGLWidget);
    if (!m_bUpdatePending)
    {
        m_bUpdatePending = true;
        QCoreApplication::postEvent(&p, new QEvent(QEvent::UpdateRequest));
    }
}

//-----------------------------------------------------------------------------
// Конструктор по умолчанию.
// ---
QtOpenGLWidget::QtOpenGLWidget(QWidget* parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f)
{
    VSN_INIT_PRIVATE(QtOpenGLWidget);
    setUpdateBehavior(QOpenGLWidget::PartialUpdate);
}

//-----------------------------------------------------------------------------
// Конструктор по умолчанию.
// ---
QtOpenGLWidget::QtOpenGLWidget(QtOpenGLWidgetPrivate& dd, QWidget* parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f)
{
    vsn_d_ptr = &dd;
    vsn_d_ptr->setPublic(this);
}

//-----------------------------------------------------------------------------
// Деструктор OpenGLWidget освобождает созданные ресурсы
// ---
QtOpenGLWidget::~QtOpenGLWidget()
{
    // Вылет при закрытии вкладки документа
//  C3D-10302  makeCurrent();
    VSN_FINI_PRIVATE();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidget::makeCurrent()
{
    VSN_D(QtOpenGLWidget);
    if (d.m_pQContext)
        d.m_pQContext->MakeCurrent();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidget::doneCurrent()
{
    VSN_D(QtOpenGLWidget);
    if (d.m_pQContext)
        d.m_pQContext->DoneCurrent();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на OpenGLContextInterface.
// ---
OpenGLContextInterface* QtOpenGLWidget::contextInterface()
{
    VSN_D(QtOpenGLWidget);
    return d.m_pQContext;
}

//-----------------------------------------------------------------------------
// 
// ---
void QtOpenGLWidget::showCompanyWebSite()
{
    QDesktopServices::openUrl(QUrl(QStringLiteral("https://c3dlabs.com")));
}

//-----------------------------------------------------------------------------
// Просто вызывает функцию QWidget::update(). Служит для совместимости слотов.
// ---
void QtOpenGLWidget::updateWidget()
{
    update();
}

//-----------------------------------------------------------------------------
// Просто вызывает функцию QWidget::rapaint(). Служит для совместимости слотов.
// ---
void QtOpenGLWidget::repaintWidget()
{
    repaint();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidget::initializeGL()
{
    VSN_D(QtOpenGLWidget);
    if (!d.m_bInitialized && window() && window()->windowHandle())
        d.initialize();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidget::paintEvent(QPaintEvent* event)
{
    QOpenGLWidget::paintEvent(event);
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLWidget::event(QEvent* event)
{
    VSN_D(QtOpenGLWidget);
    if (event->type() == QEvent::WindowChangeInternal && 
        d.m_bInitialized && !qGuiApp->testAttribute(Qt::AA_ShareOpenGLContexts))
        d.reset();
    
    bool ok = QOpenGLWidget::event(event);

    switch (event->type())
    {
        case QEvent::UpdateRequest:
            if (d.m_bUpdatePending)
            {
                update();
                d.m_bUpdatePending = false;
                return true;
            }
            break;
        case QEvent::WindowChangeInternal:
            if (qGuiApp->testAttribute(Qt::AA_ShareOpenGLContexts))
                break;
            if (d.m_bInitialized)
                d.reset();
            // FALLTHROUGH
        case QEvent::Show: // reparenting may not lead to a resize so reinitalize on Show too
            if (!d.m_bInitialized && !size().isEmpty() && window() && window()->windowHandle())
                d.initialize();
            break;
        default:
            break;
    }
    return ok;
}

//-----------------------------------------------------------------------------
//
// ---
QImage QtOpenGLWidget::grabFrameImage(const GraphicsView* pGraphicsView, int nWidth, int nHeight, const SnapshotSettings& settings)
{
    makeCurrent();
    Image image = pGraphicsView->ToImage(nWidth, nHeight, settings);
    if (!image.IsValid())
        return QImage();
    size_t size = nWidth * nHeight;
    QImage::Format format = QImage::Format::Format_Invalid;
    switch (image.GetFormat())
    {
        case Image::Format::UINT8:
            format = QImage::Format_Indexed8;
            break;
        case Image::Format::UINT24:
            size *=3;
            format = QImage::Format_RGB888;
            break;
        case Image::Format::UINT32:
            size *= 4;
            format = QImage::Format_ARGB32;
            break;
        default:
            size = 0;
            break;
    };
    QImage qImage = QImage(image.GetWidth(), image.GetHeight(), format);
    memcpy(qImage.bits(), image.GetBits(), image.GetWidth()* image.GetHeight()*4);
    return qImage.mirrored();
}

/* OpenGLWidgetPrivate */
class QtOpenGLSceneWidgetPrivate : public QtOpenGLWidgetPrivate
{
    VSN_DECLARE_EX_PUBLIC(QtOpenGLSceneWidget)
public:
    explicit QtOpenGLSceneWidgetPrivate(GraphicsSceneEnginePtr ptrEngine, OpenGLContextContainer* pSharedContainer)
        : QtOpenGLWidgetPrivate(pSharedContainer)
        , m_pGraphicsView(std::make_shared<GraphicsView>(ptrEngine))
        , m_pEventFilter(nullptr)
        , m_pAboutScene(nullptr)
        , m_pAutoHideWindow(nullptr)
        , m_bVsnInitialized(false)
    {
    }
    ~QtOpenGLSceneWidgetPrivate() override
    {
        VSN_P(QtOpenGLSceneWidget);
        p.makeCurrent();
        m_pGraphicsView->PreparingToDestroy();
        p.doneCurrent();
        VSN_DELETE_AND_NULL(m_pEventFilter);
    }
    void initialize() override;
public:
    void createAutoHideWindow();
    void processActivation();
    void processDeactivation();
public:
    GraphicsViewPtr m_pGraphicsView;
    QtConverterEventListener* m_pEventFilter;
    QtAboutSceneWidget* m_pAboutScene;
    QtAutoHideWindow* m_pAutoHideWindow;
    bool m_bVsnInitialized;
};

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidgetPrivate::initialize()
{
    VSN_P(QtOpenGLSceneWidget);
    if (m_bInitialized)
        return;
    QtOpenGLWidgetPrivate::initialize();
    if (m_bVsnInitialized)
        return;

    p.viewport()->SetBackgroundColour(Color(32, 32, 32));

    p.setFocusPolicy(Qt::StrongFocus);
    p.setMouseTracking(true);
    p.setAttribute(Qt::WA_Hover, true);
    m_pGraphicsView->Initialize();
    m_pEventFilter = new QtConverterEventListener(&p, m_pGraphicsView->GetGraphicsScene());
    Object::Connect(m_pGraphicsView.get(), &GraphicsView::OnViewModified, &p, &QtOpenGLWidget::repaintWidget);
    Object::Connect(m_pGraphicsView->GetViewport().get(), &Viewport::RefreshScreen, &p, &QtOpenGLWidget::repaintWidget);
    m_bVsnInitialized = true;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidgetPrivate::createAutoHideWindow()
{
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidgetPrivate::processActivation()
{
    VSN_P(QtOpenGLSceneWidget);
    if (Essence* pEssence = m_pGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        auto list = pEssence->FindChildren<Process*>();
        for (const auto& it : list)
        {
            it->SetViewport(m_pGraphicsView->GetViewport().get());
            bool bConnect = Object::Connect(it, &Process::OnModified, &p, &QtOpenGLWidget::repaintWidget);
            if (PrAbstractCamera* pAbsProcess = vobject_cast<PrAbstractCamera*>(it))
            {
                bConnect = Object::Connect(pAbsProcess, &PrAbstractCamera::OnCameraModified, &p, &QtOpenGLWidget::repaintWidget);
                Q_ASSERT(bConnect != false);
                VSN_UNUSED(bConnect);
            }

        }
    }
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidgetPrivate::processDeactivation()
{
    VSN_P(QtOpenGLSceneWidget);
    if (Essence* pEssence = m_pGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        auto list = pEssence->FindChildren<Process*>();
        for (const auto& it : list)
        {
            it->SetViewport(m_pGraphicsView->GetViewport().get());
            Object::Disconnect(it, &Process::OnModified, &p, &QtOpenGLWidget::repaintWidget);

            if (PrAbstractCamera* pAbsProcess = vobject_cast<PrAbstractCamera*>(it))
                Object::Disconnect(pAbsProcess, &PrAbstractCamera::OnCameraModified, &p, &QtOpenGLWidget::repaintWidget);
        }
    }
}

/* QtOpenGLSceneWidget */
QtOpenGLSceneWidget::QtOpenGLSceneWidget(QWidget* parent, Qt::WindowFlags f)
    : QtOpenGLWidget(*new QtOpenGLSceneWidgetPrivate(std::make_shared<GraphicsSceneEngine>(), nullptr), parent, f)
{
}

//-----------------------------------------------------------------------------
// Special constructor.
// ---
QtOpenGLSceneWidget::QtOpenGLSceneWidget(GraphicsSceneEnginePtr engine, OpenGLContextContainer* sharedContainer, QWidget* parent, Qt::WindowFlags f)
    : QtOpenGLWidget(*new QtOpenGLSceneWidgetPrivate(engine, sharedContainer), parent, f)
{
}

//-----------------------------------------------------------------------------
//
// ---
QtOpenGLSceneWidget::~QtOpenGLSceneWidget()
{
}

//-----------------------------------------------------------------------------
//
// ---
GraphicsScene* QtOpenGLSceneWidget::graphicsScene() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_pGraphicsView->GetGraphicsScene();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на компонент выбора объектов.
// ---
ObjectPickSelection* QtOpenGLSceneWidget::objectPickSelection() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_pGraphicsView->GetSceneEngine()->GetObjectPickSelection();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsSceneEngine.
// ---
GraphicsSceneEnginePtr QtOpenGLSceneWidget::graphicsEngine() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_pGraphicsView->GetSceneEngine();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsView.
// ---
GraphicsViewPtr QtOpenGLSceneWidget::ptrGraphicsView() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_pGraphicsView;
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsView
// ---
GraphicsView* QtOpenGLSceneWidget::graphicsView() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_pGraphicsView.get();
}

#define PROP_ORIENTATION "Orientation"
#define PROP_MODE        "Mode"

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::viewPortCommands()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    Orientation value = static_cast<Orientation>(pAction->property("Orientation").toInt());
    int val = int(Orientation::CustomBase);
    if ((int)value == (val + 1))
        graphicsView()->SetZoomToFit(sceneContent()->GetBoundingBox());
    else if ((int)value == (val + 2))
        viewport()->SetOrthographicProjection(!pAction->isChecked());
    else
        graphicsView()->SetOrientationCamera(value, true);
    update();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::viewPortRenderMode()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    RenderMode value = static_cast<RenderMode>(pAction->property("Mode").toInt());
    setRenderMode(value);
    update();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::setRenderMode(RenderMode mode)
{
    graphicsView()->SetRenderMode(mode);
    update();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на основной источник света
// ---
Light* QtOpenGLSceneWidget::mainLight() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_pGraphicsView->GetGraphicsScene()->GetMainLight();
}

//-----------------------------------------------------------------------------
//
// ---
Camera* QtOpenGLSceneWidget::camera() const
{
    return viewport()->GetCamera();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на Viewport для отображения сцены.
// ---
Viewport* QtOpenGLSceneWidget::viewport() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_pGraphicsView->GetViewport().get();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
SceneContentPtr QtOpenGLSceneWidget::sceneContent()
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_pGraphicsView->GetGraphicsScene()->GetSceneContent();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::resizeGL(int w, int h)
{
    VSN_D(QtOpenGLSceneWidget);
    QtOpenGLWidget::resizeGL(w, h);
    if (d.m_pQContext == nullptr)
        return;
    d.m_pQContext->MakeCurrent();
    if (OpenGLContextInterface::GetCurrentContext() && d.m_pQContext == OpenGLContextInterface::GetCurrentContext())
    {
        qreal pixelRatio = devicePixelRatio();
        d.m_pEventFilter->setDevicePixelRatio(pixelRatio);
        d.m_pGraphicsView->DoResize(w * pixelRatio, h * pixelRatio);
    }
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::paintGL()
{
    VSN_D(QtOpenGLSceneWidget);
    if (d.m_pQContext == nullptr || !updatesEnabled())
        return;
    d.m_pEventFilter->setDevicePixelRatio(devicePixelRatio());

    bool isActiveStatistics = RenderStatistics::IsActivated();
    if (isActiveStatistics)
        RenderStatistics::ResetRenderCounters();

    d.m_pQContext->MakeCurrent();
    d.m_pGraphicsView->DoRender();
    d.m_pQContext->DoneCurrent(); // C3D-10302

#ifdef Q_OS_WIN
    if (isActiveStatistics)
        update();
#endif 
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLSceneWidget::event(QEvent* event)
{
    return QtOpenGLWidget::event(event);
}

//-----------------------------------------------------------------------------
//
// ---
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
void QtOpenGLSceneWidget::enterEvent(QEvent* event)
#else
void QtOpenGLSceneWidget::enterEvent(QEnterEvent* event)
#endif
{
    VSN_D(QtOpenGLSceneWidget);
    QtOpenGLWidget::enterEvent(event);
    d.m_pGraphicsView->GetSceneEngine()->GetObjectPickSelection()->SetOpenGLContext(d.m_pQContext);
    d.m_pGraphicsView->GetSceneEngine()->GetObjectPickSelection()->SetViewport(d.m_pGraphicsView->GetViewport());
    d.processActivation();
}

//-----------------------------------------------------------------------------
//
// ---
 void QtOpenGLSceneWidget::leaveEvent(QEvent* event)
{
    VSN_D(QtOpenGLSceneWidget);
    QtOpenGLWidget::leaveEvent(event);
    d.processDeactivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::focusInEvent(QFocusEvent* event)
{
    VSN_D(QtOpenGLSceneWidget);
    QtOpenGLWidget::focusInEvent(event);
    d.processActivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::focusOutEvent(QFocusEvent* event)
{
    VSN_D(QtOpenGLSceneWidget);
    QtOpenGLWidget::focusOutEvent(event);
    d.processDeactivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::ZoomToFit()
{
    if ( viewport() && sceneContent() )
        viewport()->ZoomToFit(sceneContent()->GetBoundingBox());
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLSceneWidget::OnEvent(ProcessEvent* event)
{
    if (event->GetType() == ProcessEvent::Draw)
        repaint();
    return Object::OnEvent(event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::showEvent(QShowEvent* event)
{
    VSN_D(QtOpenGLSceneWidget);
    VSN_UNUSED(event);
    if (!d.m_bVsnInitialized)
        return;
    d.m_pGraphicsView->PreparingToDisplay();
    d.renderLater();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::closeEvent(QCloseEvent* event)
{
    QtOpenGLWidget::closeEvent(event);
}

} // namespace QtVision
} // namespace VSN
