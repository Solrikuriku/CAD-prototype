#include "raycasting.h"

Ray RayCasting::ScreenToRay(const QPointF &pos, int width, int height, const QMatrix4x4 &projection, const QMatrix4x4 &view)
{
    Ray ray;

    float ndcX = (2 * pos.x()) / width - 1;
    float ndcY = 1 - (2 * pos.y()) / height;

    QVector4D near(ndcX, ndcY, -1.0f, 1.0f);
    QVector4D far(ndcX, ndcY, 1.0f, 1.0f);

    QMatrix4x4 invMatrix = (projection * view).inverted();

    QVector4D nearWorld = invMatrix * near;
    QVector4D farWorld = invMatrix * far;

    nearWorld /= nearWorld.w();
    farWorld /= farWorld.w();

    ray.origin = nearWorld.toVector3D();
    ray.direction = (farWorld.toVector3D() - nearWorld.toVector3D()).normalized();

    return ray;
}

bool RayCasting::IsRayIntersectsAABB(const Ray &ray, const AABB &box, float &tOut)
{
    //это для себя пока
    if (ray.direction.x() == 0)
        qDebug() << "ray.direction.x == 0";

    if (ray.direction.y() == 0)
        qDebug() << "ray.direction.y == 0";

    if (ray.direction.z() == 0)
        qDebug() << "ray.direction.z == 0";

    float xMin = (box.min.x() - ray.origin.x()) / ray.direction.x();
    float xMax = (box.max.x() - ray.origin.x()) / ray.direction.x();
    if (xMin > xMax) std::swap(xMin, xMax);

    float yMin = (box.min.y() - ray.origin.y()) / ray.direction.y();
    float yMax = (box.max.y() - ray.origin.y()) / ray.direction.y();
    if (yMin > yMax) std::swap(yMin, yMax);

    if ((xMin > yMax) || (yMin > xMax)) return false;

    float tMin = std::max(xMin, yMin);
    float tMax = std::min(xMax, yMax);

    float zMin = (box.min.z() - ray.origin.z()) / ray.direction.z();
    float zMax = (box.max.z() - ray.origin.z()) / ray.direction.z();
    if (zMin > zMax) std::swap(zMin, zMax);

    tMin = std::max(tMin, zMin);
    tMax = std::min(tMax, zMax);

    if (tMin > tMax) return false;

    tOut = tMin;

    return true;
}

bool RayCasting::IsRayIntersectsPlane(const Ray &ray, const Plane &plane, QVector3D &hitPoint)
{
    //умножаем нормаль плоскости и направление луча
    //получаем число скалярное, обозначающее сонаправленность векторов
    //раз значения нормализованны то скаляр тут является косинусом угла
    float denom = QVector3D::dotProduct(plane.normal, ray.direction);

    //близко к нулю значит луч параллелен плоскости и перпендикулярен к нормали
    if (std::abs(denom) < 1e-6f) // луч почти параллелен плоскости — пересечения нет
        return false;

    //гипотенуза расстояние от точки камеры до точки на плоскости
    //скалярная величина тут по сути ближайшее расстояние от точки камеры до плоскости
    //так как деном у нас косинус угла то через формулу находим гипотенузу t
    float t = QVector3D::dotProduct(plane.point - ray.origin, plane.normal) / denom;

    if (t < 0) // пересечение находится позади камеры — не считается
        return false;

    hitPoint = ray.origin + ray.direction * t;

    return true;
}
