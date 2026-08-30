#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"
#include "gizmocommand.h"

class RotateCommand : public GizmoCommand
{
private:
    QVector3D m_cursorWorldPos = QVector3D();

public:
    RotateCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes, QVector3D cursorWorldPos)
        : GizmoCommand(cntx, object, axes), m_cursorWorldPos(cursorWorldPos) {};

    void OnMouseMove(QMouseEvent* e) override;
};
