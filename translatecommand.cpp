#include "translatecommand.h"

// TranslateCommand::TranslateCommand() {}

void TranslateCommand::OnMouseMove(QMouseEvent *e)
{
    if (!e || !m_cntx || !m_object) return;
    if (m_axes == TransformAxes::None) return;

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
}
