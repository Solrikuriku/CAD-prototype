#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"
#include "gizmocommand.h"

class TranslateCommand : public GizmoCommand
{
public:
    TranslateCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes)
        : GizmoCommand(cntx, object, axes) {}

    void OnMouseMove(QMouseEvent* e) override;
};

