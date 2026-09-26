#pragma once

#include <QVector3D>
#include <qdebug.h>

struct Ray
{
    QVector3D origin;
    QVector3D direction;
};

struct Plane
{
    QVector3D point;
    QVector3D normal;
};

struct AABB
{
    QVector3D min;
    QVector3D max;

    static AABB GetBounds(const std::vector<float> &vertices)
    {
        AABB box;

        auto inf = std::numeric_limits<float>::max();
        QVector3D bMin(inf, inf, inf);
        QVector3D bMax(-inf, -inf, -inf);

        for (size_t i = 0; i < vertices.size(); i += 3)
        {
            float x = vertices[i];
            float y = vertices[i + 1];
            float z = vertices[i + 2];

            bMin.setX(std::min(bMin.x(), x));
            bMin.setY(std::min(bMin.y(), y));
            bMin.setZ(std::min(bMin.z(), z));

            bMax.setX(std::max(bMax.x(), x));
            bMax.setY(std::max(bMax.y(), y));
            bMax.setZ(std::max(bMax.z(), z));
        }

        box = { bMin, bMax };

        return box;
    }
};

inline float AngleBetweenVectors(const QVector3D& last, const QVector3D& current, const QVector3D& objectCenter, const QVector3D& referenceNormal)
{
    QVector3D lastDir = (last - objectCenter).normalized();
    QVector3D currentDir = (current - objectCenter).normalized();

    QVector3D axis = QVector3D::crossProduct(lastDir, currentDir);
    float cosAngle = QVector3D::dotProduct(lastDir, currentDir);

    // Возвращаем вашу длину, она гарантирует, что значение синуса не нулевое
    float sinAngle = axis.length();

    // ВНИМАНИЕ: Проверьте, что передается в referenceNormal!
    // Если знак всегда положительный, замените referenceNormal на нужную ось (например, QVector3D(0, 1, 0))
    if (QVector3D::dotProduct(axis, referenceNormal) < 0.0f) {
        sinAngle = -sinAngle;
    }

    float angleRad = std::atan2(sinAngle, cosAngle);

    //qDebug() << "текущий угол " << angleRad;

    return qRadiansToDegrees(angleRad);

    // float cosAngle = std::clamp(QVector3D::dotProduct(lastDir, currentDir), -1.0f, 1.0f);
    // float angleDegrees = qRadiansToDegrees(std::acos(cosAngle));

    // QVector3D axis = QVector3D::crossProduct(lastDir, currentDir);

    // if (QVector3D::dotProduct(axis, referenceNormal) < 0)
    //     angleDegrees = -angleDegrees;

    // return angleDegrees;
}
