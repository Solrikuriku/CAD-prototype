#pragma once

#include <QMouseEvent>
#include "iviewportcontext.h"

class TranslateCommand
{
private:
    IViewportContext* m_cntx = nullptr;
    SceneObject* m_object = nullptr;
    TransformAxes m_axes;

public:
    TranslateCommand(IViewportContext* cntx, SceneObject* object, TransformAxes axes)
        : m_cntx(cntx), m_object(object), m_axes(axes) {};

    void OnMouseMove(QMouseEvent* e)
    {
        qDebug() << "enter is moving";

        if (!e || !m_cntx || !m_object) return;

        auto& objectPos = m_object->transform.position;
        auto currentPos = e->pos();

        auto cursorWorldPos = m_cntx->GetCursorWorldPos(currentPos, objectPos, m_axes);

        if (m_axes == TransformAxes::X)
        {
            objectPos.setX(cursorWorldPos.x());
        }
        else if (m_axes == TransformAxes::Y)
        {
            objectPos.setY(cursorWorldPos.y());
        }
        else if (m_axes == TransformAxes::Z)
        {
            objectPos.setZ(cursorWorldPos.z());
        }

        qDebug() << "mouse is moving";
    }
};

