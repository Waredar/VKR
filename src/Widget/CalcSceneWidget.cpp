#include "CalcSceneWidget.h"

#include <QVBoxLayout>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

#include <vsn_namespace.h>
#include <vsn_prcameraorbit.h>
#include <vsn_prcamerarotate.h>
#include <vsn_geometryfactory.h>
#include <vsn_scenecontent.h>
#include <vsn_scenesegment.h>
#include <vsn_material.h>

#include <widget.h>
#include <solid.h>
#include <action_solid.h>
#include <vector>

using namespace std;
using namespace VSN;
using namespace c3d;


c3d::SolidSPtr CalcSceneWidget::createTestSolid()
{
    SpacePointsVector points;
    points.push_back(MbCartPoint3D(5, 0, -5));
    points.push_back(MbCartPoint3D(-5, -5, 0));
    points.push_back(MbCartPoint3D(0, 5, 5));

    MbSNameMaker names(ct_ElementarySolid, MbSNameMaker::i_SideNone, 0);
    MbElementarySolidResults results;

    MbResultType r = ::ElementarySolid(
        MbElementarySolidParams(et_Cylinder, points, names),
        results
    );

    if (r != rt_Success) return nullptr;

    c3d::SolidSPtr solid = results.GetResultSolid();

    return solid;
}

CalcSceneWidget::CalcSceneWidget(QWidget* parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    initScene();
}

void CalcSceneWidget::initScene()
{
    setMouseTracking(true);

    m_scene = new VSN::QtVision::QtOpenGLSceneWidget(this);
    m_scene->setMouseTracking(true);
    m_scene->setFocusPolicy(Qt::StrongFocus);

    m_scene->viewport()->SetVisibleSceneWidgets(true);
    m_scene->viewport()->SetVisibleViewWidgets(true);

    layout()->addWidget(m_scene);

    //displaySolid(createTestSolid());
}

void CalcSceneWidget::displaySolid(const c3d::SolidSPtr& solid)
{
    if (!m_scene || !solid) return;

    auto root = m_scene->sceneContent()->GetRootSegment();
    auto rep = VSN::GeometryFactory::Instance()->CreateMathRep(solid, VSN::CommandType::Synchronous, 0.05);

    if (!rep) return;

    m_currentSegment = new VSN::SceneSegment(rep, root);
    m_currentSegment->CreateRenderObject();
    m_currentSegment->SetColorPresentationMaterial(VSN::Color(30, 100, 220));
    m_scene->update();
}

void CalcSceneWidget::clearScene() {
    if (!m_scene) return;

    m_assembly = nullptr;

    auto content = m_scene->sceneContent();
    if (content) {
        auto root = content->GetRootSegment();
        if (root) {
            root->RemoveChildren();
        }
    }

    m_scene->blockSignals(false);
    m_scene->update();
}

void CalcSceneWidget::displayModel(const SPtr<MbAssembly>& assembly)
{
    if (!m_scene || !assembly)
        return;

    clearScene();

    m_assembly = assembly;

    auto root = m_scene->sceneContent()->GetRootSegment();

    RPArray<MbItem> items;
    assembly->GetItems(items);

    for (size_t i = 0; i < items.Count(); ++i)
    {
        MbItem* item = items[i];

        if (!item || item->IsA() != st_Instance)
            continue;

        MbInstance* instance = static_cast<MbInstance*>(item);
        const MbItem* instanceItem = instance->GetItem();

        if (!instanceItem || instanceItem->IsA() != st_Solid)
            continue;

        const MbSolid* solid = static_cast<const MbSolid*>(instanceItem);

        MbSolid* solidRaw = const_cast<MbSolid*>(solid);
        solidRaw->AddRef();
        c3d::SolidSPtr solidPtr(solidRaw);

        auto rep = VSN::GeometryFactory::Instance()->CreateMathRep(
            solidPtr,
            VSN::CommandType::Synchronous,
            0.05
        );

        if (!rep)
            continue;

        auto segment = new VSN::SceneSegment(rep, root);
        segment->CreateRenderObject();

        segment->SetColorPresentationMaterial(VSN::Color(30, 100, 220));

        MbPlacement3D placement;
        instance->GetPlacement(placement);

        MbMatrix3D mx;
        placement.GetMatrixFrom(mx);

        VSN::Matrix3DF vsnMatrix(
            (float)mx.El(0, 0), (float)mx.El(0, 1), (float)mx.El(0, 2), (float)mx.El(0, 3),
            (float)mx.El(1, 0), (float)mx.El(1, 1), (float)mx.El(1, 2), (float)mx.El(1, 3),
            (float)mx.El(2, 0), (float)mx.El(2, 1), (float)mx.El(2, 2), (float)mx.El(2, 3),
            (float)mx.El(3, 0), (float)mx.El(3, 1), (float)mx.El(3, 2), (float)mx.El(3, 3)
        );

        segment->GetTransform().SetMatrix(vsnMatrix);
        segment->RefreshAbsoluteMatrix();
    }

    m_scene->update();
}

void CalcSceneWidget::mousePressEvent(QMouseEvent* event)
{
    m_lastMousePos = event->pos();
    m_firstMouse = false;

    if (event->button() == Qt::RightButton) {
        QPointF p = event->position();
        start_position = QPointF(p.x() / width() - 0.5, p.y() / height() - 0.5);
    }
    m_scene->update();
}

void CalcSceneWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_scene || !(event->buttons() & (Qt::RightButton | Qt::MiddleButton))) {
        m_firstMouse = true;
        return;
    }

    auto cam = m_scene->camera();
    if (!cam) return;

    if (m_firstMouse) {
        m_lastMousePos = event->pos();
        m_firstMouse = false;
        return;
    }

    float dx = event->pos().x() - m_lastMousePos.x();
    float dy = m_lastMousePos.y() - event->pos().y();

    m_lastMousePos = event->pos();

    if (event->buttons() & Qt::RightButton) {
        dx = dx / width() * rotate_sensitivity;
        dy = dy / height() * rotate_sensitivity;

        cam->RotateAboutTarget(cam->GetUpVector(), -dx);
        cam->RotateAboutTarget(cam->GetSideVector(), dy);
    }

    if (event->buttons() & Qt::MiddleButton) {
        float dist = cam->DistanceCameraToTarget();
        cam->Pan(Vector3DF(-dx * move_sensitivity * dist,
            -dy * move_sensitivity * dist,
            0));
    }

    m_scene->update();
}

void CalcSceneWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_firstMouse = true;
    m_lastMousePos = event->pos();

    m_scene->update();
}

void CalcSceneWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);

    QTimer::singleShot(0, this, [this]() {
        m_scene->viewport()->SetGradientBackgroundColour(
            VSN::Color(255, 255, 255), VSN::Color(255, 255, 255));
        m_scene->viewport()->SetBackgroundColour(VSN::Color(255, 255, 255));
        m_scene->update();
        });
}

void CalcSceneWidget::wheelEvent(QWheelEvent* event)
{
    if (!m_scene) return;
    auto cam = m_scene->camera();
    if (!cam) return;

    float scale = std::pow(2.0f, event->angleDelta().y() * scale_sensitivity);
    float dist = cam->DistanceCameraToTarget();

    cam->SetZoom(scale);
    cam->Pan(Vector3DF((event->position().x() / width() - 0.5f) * (scale - 1.0f) * dist,
        -(event->position().y() / height() - 0.5f) * (scale - 1.0f) * dist,
        0));

    m_scene->update();
}

void CalcSceneWidget::togglePlaneCutting(bool enable, CuttingPlane planeType)
{
    if (!m_scene) return;
    auto tool = m_scene->graphicsScene()->GetCuttingTool();

    if (m_curIdPlane != 0) {
        tool->DeleteSectionPlane(m_curIdPlane);
        m_curIdPlane = 0;
    }

    if (!enable) {
        m_scene->update();
        return;
    }

    MbCube box = m_scene->sceneContent()->GetBoundingBox();
    MbCartPoint3D center;
    box.GetCenter(center);

    MbVector3D normal(0, 1, 0);
    if (planeType == CuttingPlane::X) normal.Init(1, 0, 0);
    if (planeType == CuttingPlane::Z) normal.Init(0, 0, 1);

    m_curIdPlane = tool->AddSectionPlane(MbPlacement3D(center, normal));

    tool->SetEnable(m_curIdPlane, true);
    tool->EnableInteractiveMode(m_curIdPlane, false);

    m_scene->update();
}