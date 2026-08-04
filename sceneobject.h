#pragma once

#include "transform.h"
#include "mesh.h"

#include <QUuid>

class SceneObject
{
public:
    SceneObject() { id = GenerateId(); };

    std::string id; // генерируется всегда при создании поля
    std::unique_ptr<Mesh> mesh;     // unique_ptr и так nullptr по умолчанию
    Transform transform = Transform();            // Transform() и так вызывается по умолчанию
    bool selected = false;

    void Draw();
    void DrawTriangulated();

private:
    static std::string GenerateId()
    {
        return QUuid::createUuid().toString().toStdString();
    }
};

