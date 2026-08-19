#include "scalecommand.h"

//ScaleCommand::ScaleCommand() {}

void ScaleCommand::OnMouseMove(QMouseEvent *e)
{
    if (!e || !m_cntx || !m_object) return;
    if (m_axes == TransformAxes::None) return;

    auto& objectPos = m_object->transform.position;
    auto currentPos = e->pos();
    auto new_cursorWorldPos = m_cntx->GetCursorWorldPos(currentPos, objectPos, m_axes);
    auto delta3D = new_cursorWorldPos - m_cursorWorldPos;
    float scaleSensitivity = 2.0f;

    auto &scale = m_object->transform.scaling;

    if (m_axes == TransformAxes::X)
    {
        scale.setX(scale.x() + (float)delta3D.x() * scaleSensitivity);
    }
    else if (m_axes == TransformAxes::Y)
    {
        scale.setY(scale.y() + (float)delta3D.y() * scaleSensitivity);
    }
    else if (m_axes == TransformAxes::Z)
    {
        scale.setZ(scale.z() + (float)delta3D.z() * scaleSensitivity);
    }

    m_cursorWorldPos = new_cursorWorldPos;
}

