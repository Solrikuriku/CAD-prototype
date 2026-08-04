#pragma once

#include <QPointF>
#include <QMatrix4x4>
#include "geometry.h"

class RayCasting
{
public:
    RayCasting() = default;

    static Ray ScreenToRay(const QPointF& pos, int width, int height, const QMatrix4x4 &projection, const QMatrix4x4 &view);
    static bool IsRayIntersectsAABB(const Ray &ray, const AABB &box, float &tOut);
    static bool IsRayIntersectsPlane(const Ray &ray, const Plane &plane, QVector3D &hitPoint);
};
