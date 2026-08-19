#include "rotatecommand.h"

//RotateCommand::RotateCommand() {}

void RotateCommand::OnMouseMove(QMouseEvent *e)
{
    if (!e || !m_cntx || !m_object) return;
    if (m_axes == TransformAxes::None) return;

    auto& objectPos = m_object->transform.position;
    auto& objectRotate = m_object->transform.rotation;
    auto currentPos = e->pos();

    auto newCursorWorldPos = m_cntx->GetCursorWorldPos(currentPos, objectPos, m_axes);

    QVector3D rotatePlane;

    if (m_axes == TransformAxes::X) rotatePlane = QVector3D(1, 0, 0);
    else if (m_axes == TransformAxes::Y) rotatePlane = QVector3D(0, 1, 0);
    else if (m_axes == TransformAxes::Z) rotatePlane = QVector3D(0, 0, 1);

    float angleDegrees = AngleBetweenVectors(m_cursorWorldPos, newCursorWorldPos, objectPos, rotatePlane);

    QQuaternion deltaRotation = QQuaternion::fromAxisAndAngle(rotatePlane, angleDegrees);
    objectRotate = deltaRotation * objectRotate;

    m_cursorWorldPos = newCursorWorldPos;
}
