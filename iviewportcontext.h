#pragma once

#include "sceneobject.h"

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

    //данные о мировой координате
    //данные о камере
};
