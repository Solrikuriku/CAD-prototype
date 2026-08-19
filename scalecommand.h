#ifndef SCALECOMMAND_H
#define SCALECOMMAND_H

#include <QMouseEvent>
#include "iviewportcontext.h"

class ScaleCommand
{
private:
    IViewportContext* m_cntx = nullptr;
    SceneObject* m_object = nullptr;
    TransformAxes m_axes = TransformAxes::None;
    QVector3D m_cursorWorldPos = QVector3D();

public:
    ScaleCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes, QVector3D cursorWorldPos)
        : m_cntx(cntx), m_object(object), m_axes(axes), m_cursorWorldPos(cursorWorldPos) {};

    void OnMouseMove(QMouseEvent* e);
};

#endif // SCALECOMMAND_H
