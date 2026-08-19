#pragma once

#include <QVector3D>

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
    float dot = QVector3D::dotProduct(lastDir, currentDir);

    // sin-компонента угла — это длина cross, но со знаком относительно нормали плоскости
    float sinAngle = axis.length();

    if (QVector3D::dotProduct(axis, referenceNormal) < 0.0f)
        sinAngle = -sinAngle;

    float angleRad = std::atan2(sinAngle, dot); // устойчиво во всём диапазоне -180..180
    return qRadiansToDegrees(angleRad);

    // float cosAngle = std::clamp(QVector3D::dotProduct(lastDir, currentDir), -1.0f, 1.0f);
    // float angleDegrees = qRadiansToDegrees(std::acos(cosAngle));

    // QVector3D axis = QVector3D::crossProduct(lastDir, currentDir);

    // if (QVector3D::dotProduct(axis, referenceNormal) < 0)
    //     angleDegrees = -angleDegrees;

    // return angleDegrees;
}
