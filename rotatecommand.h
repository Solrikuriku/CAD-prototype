#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"

class RotateCommand
{
//есть мысль касательно повторения полей
//а еще mousemove одинаковая
private:
    IViewportContext* m_cntx = nullptr;
    SceneObject* m_object = nullptr;
    TransformAxes m_axes = TransformAxes::None;
    QVector3D m_cursorWorldPos = QVector3D();

public:
    RotateCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes, QVector3D cursorWorldPos)
        : m_cntx(cntx), m_object(object), m_axes(axes), m_cursorWorldPos(cursorWorldPos) {};

    void OnMouseMove(QMouseEvent* e);
};
