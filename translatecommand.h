#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"
#include "gizmocommand.h"
#include "ICommand.h"

class TranslateCommand : public GizmoCommand, public ICommand
{
public:
    TranslateCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes)
        : GizmoCommand(cntx, object, axes)
    {
        m_lastPos = object->transform.position;
    }

    void OnMouseMove(QMouseEvent* e) override;
    void Execute() override;
    void Undo() override;

private:
    QVector3D m_lastPos = QVector3D();
    QVector3D m_currentPos = QVector3D();
};

