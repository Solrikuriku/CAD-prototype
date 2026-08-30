#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"

class GizmoCommand
{
protected:
    IViewportContext* m_cntx = nullptr;
    SceneObject* m_object = nullptr;
    TransformAxes m_axes = TransformAxes::None;

    GizmoCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes)
        : m_cntx(cntx), m_object(object), m_axes(axes) {}

public:
    virtual ~GizmoCommand() = default;
    virtual void OnMouseMove(QMouseEvent* e) = 0;
};

