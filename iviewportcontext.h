#pragma once

#include "sceneobject.h"
#include "TransformAxes.h"

/*
 * интерфейс для данных
 * которые нужно вытащить из вьюпорта
 * и куда-нибудь передать по необходимости
*/

class IViewportContext
{
public:
    virtual ~IViewportContext() = default;

    //данные о выбранном объекте
    virtual SceneObject* PickObject(const QPointF& currentPos) const = 0;
    virtual void SetPickedObject(SceneObject* picked) = 0;
    virtual QVector3D GetCursorWorldPos(const QPointF& currentPos, const QVector3D& objectPos, const TransformAxes axes) const = 0;

    //данные о мировой координате
    //данные о камере
};
