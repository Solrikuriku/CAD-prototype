#include "meshfactory.h"

static const std::vector<uint32_t> CUBE_INDICES =
{
    0, 1, 2,  2, 3, 0,
    4, 5, 6,  6, 7, 4,
    4, 0, 3,  3, 7, 4,
    1, 5, 6,  6, 2, 1,
    4, 5, 1,  1, 0, 4,
    3, 2, 6,  6, 7, 3,
};

static const std::vector<uint32_t> CUBE_EDGE_INDICES =
{
    0,1, 1,2, 2,3, 3,0,
    4,5, 5,6, 6,7, 7,4,
    0,4, 1,5, 2,6, 3,7
};

std::unique_ptr<Mesh> MeshFactory::CreateCube(const float width, const float height, const float depth)
{
    auto vertices = GenerateVertices(width, height, depth);
    AABB bounds = AABB::GetBounds(vertices);
    auto mesh = std::make_unique<Mesh>(vertices, CUBE_INDICES, CUBE_EDGE_INDICES);
    mesh->bounds = bounds;

    return mesh;
}

std::vector<float> MeshFactory::GenerateVertices(const float width, const float height, const float depth)
{
    float w = width / 2.0f, h = height / 2.0f, d = depth / 2.0f;

    return
        {
            -w, -h, -d,
            w, -h, -d,
            w,  h, -d,
            -w,  h, -d,
            -w, -h,  d,
            w, -h,  d,
            w,  h,  d,
            -w,  h,  d,
        };
}
