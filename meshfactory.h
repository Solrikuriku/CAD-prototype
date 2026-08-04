#pragma once

#include "mesh.h"
#include <cfloat>
#include <memory>

class MeshFactory
{
public:
    static std::unique_ptr<Mesh> CreateCube(const float width, const float height, const float depth);

private:
    static std::vector<float> GenerateVertices(const float width, const float height, const float depth);
};
