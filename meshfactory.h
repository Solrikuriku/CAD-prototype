#pragma once

#include "mesh.h"
#include <cfloat>
#include <memory>

class MeshFactory
{
public:
    static std::unique_ptr<Mesh> CreateCube(const float width, const float height, const float depth);
    static std::unique_ptr<Mesh> CreateCylinder(const float radius, const float height);

private:
    static std::vector<float> GenerateVertices(const float width, const float height, const float depth);
    //GenerateVertices for cylinder
    static std::vector<float> GenerateVertices(const float radius, const float height, const int segments = 36);
    static std::vector<unsigned int> GenerateCylinderEdges(const int verticesSize);
    static std::vector<unsigned int> GenerateVerticesIndecies(const int verticesSize);
};
