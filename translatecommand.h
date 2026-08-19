#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"

class TranslateCommand
{
private:
    IViewportContext* m_cntx = nullptr;
    SceneObject* m_object = nullptr;
    TransformAxes m_axes = TransformAxes::None;

public:
    TranslateCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes)
        : m_cntx(cntx), m_object(object), m_axes(axes) {};

    void OnMouseMove(QMouseEvent* e);
};

