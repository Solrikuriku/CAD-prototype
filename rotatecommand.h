#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"
#include "gizmocommand.h"
#include "ICommand.h"

class RotateCommand : public GizmoCommand, public ICommand
{
public:
    RotateCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes, QVector3D cursorWorldPos)
        : GizmoCommand(cntx, object, axes), m_cursorWorldPos(cursorWorldPos)
    {
        m_lastRotation = object->transform.rotation;
    };

    void OnMouseMove(QMouseEvent* e) override;
    void Execute() override;
    void Undo() override;
    void Redo() override;

private:
    QVector3D m_cursorWorldPos = QVector3D();

    QQuaternion m_lastRotation = QQuaternion();
    QQuaternion m_currentRotation = QQuaternion();

};
