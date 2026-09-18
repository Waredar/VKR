#pragma once

#include <QWidget>
#include <solid.h>
#include "assembly.h"
#include <vsn_cuttingtool.h>

namespace VSN {
    namespace QtVision {
        class QtOpenGLSceneWidget;
    }

    class SceneSegment;
}

enum class CuttingPlane {
    X,
    Y,
    Z
};

class CalcSceneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalcSceneWidget(QWidget* parent = nullptr);

    SPtr<MbAssembly> getAssembly() const { return m_assembly; }

    void togglePlaneCutting(bool enable, CuttingPlane plane = CuttingPlane::Y);

    void displaySolid(const c3d::SolidSPtr& solid);

    void clearScene();

    void displayModel(const SPtr<MbAssembly>& assembly);


    VSN::QtVision::QtOpenGLSceneWidget* scene() const
    {
        return m_scene;
    }

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    void initScene();

    c3d::SolidSPtr createTestSolid();

private:
    VSN::QtVision::QtOpenGLSceneWidget* m_scene = nullptr;

    VSN::SceneSegment* m_currentSegment = nullptr;

    SPtr<MbAssembly> m_assembly;

    uint32_t m_curIdPlane = 0;

    QPoint m_lastMousePos;

    bool m_firstMouse = true;

    float rotate_sensitivity = 10.0f;
    float move_sensitivity = 0.001f;
    float scale_sensitivity = 0.002f;

    QPointF start_position;
};