#include "sceneobject.h"

void SceneObject::Draw()
{
    if (!mesh) return;

    mesh->Draw();
}

void SceneObject::DrawTriangulated()
{
    if (!mesh) return;

    mesh->DrawTriangulated();
}
