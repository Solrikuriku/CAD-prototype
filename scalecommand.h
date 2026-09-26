#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"
#include "gizmocommand.h"
#include "ICommand.h"

class ScaleCommand : public GizmoCommand, public ICommand
{
public:
    ScaleCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes, QVector3D cursorWorldPos)
        : GizmoCommand(cntx, object, axes), m_cursorWorldPos(cursorWorldPos)
    {
        m_lastScale = object->transform.scaling;
    };

    void OnMouseMove(QMouseEvent* e) override;
    void Execute() override;
    void Undo() override;
    void Redo() override;

private:
    QVector3D m_cursorWorldPos = QVector3D();
    QVector3D m_lastScale = QVector3D();
    QVector3D m_currentScale = QVector3D();
};

