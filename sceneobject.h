#pragma once

#include "transform.h"
#include "mesh.h"

#include <QUuid>

class SceneObject
{
public:
    //ранее генерировался тут, теперь генерируется в tree
    //а сюда передается
    SceneObject(const QUuid& objId) : id(objId) {};

    QUuid id;
    std::unique_ptr<Mesh> mesh;
    Transform transform = Transform();
    bool selected = false;

    void Draw();
    void DrawTriangulated();

// private:
//     static std::string GenerateId()
//     {
//         return QUuid::createUuid().toString().toStdString();
//     }
};

