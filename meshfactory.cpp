#include "meshfactory.h"
#include <cmath>

#define TO_RADIANS(deg) ((deg) * (M_PI / 180.0f))

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

std::unique_ptr<Mesh> MeshFactory::CreateCylinder(const float radius, const float height)
{
    auto vertices = GenerateVertices(radius, height);
    auto verticesIncidies = GenerateVerticesIndecies(vertices.size());
    auto edgesIndicies = GenerateCylinderEdges(vertices.size());
    AABB bounds = AABB::GetBounds(vertices);
    auto mesh = std::make_unique<Mesh>(vertices, verticesIncidies, edgesIndicies);
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

std::vector<float> MeshFactory::GenerateVertices(const float radius, const float height, const int segments)
{
    //у нас есть шаг - угол
    //каждая координата - умножаем радиус на шаг-угол в цикле
    //формируем нижнюю окружность
    //ее координаты (0, 0, -height/2)
    //думаю, можно сформировать одновременно и верхнюю (0, 0, height/2)

    //или это или то
    //std::vector<QVector3D> vertices;
    std::vector<float> vertices;

    float radianAngle = TO_RADIANS((360.0f / segments));
    float zTop = height / 2.0f;
    float zBottom = -height / 2.0f;
    //QVector3D coordinatesCircleTop = QVector3D(0.0f, 0.0f, zTop);
    //QVector3D coordinatesCircleBottom = QVector3D(0.0f, 0.0f, zBottom);

    float step = radianAngle;

    for (int i = 0; i < segments; i++)
    {
        float angle = step * i;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        //auto vertexTop = QVector3D(x, y, zTop);
        //auto vertexBotton = QVector3D(x, y, zBottom);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(zTop);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(zBottom);

        // vertices.push_back(QVector3D(x, y, zTop));
        // vertices.push_back(QVector3D(x, y, zBottom));
    }


    return vertices;
}

std::vector<unsigned int> MeshFactory::GenerateCylinderEdges(const int verticesSize)
{
    std::vector<unsigned int> edgesIndicies;

    for (int i = 0; i < verticesSize; i++)
    {
        //жутко
        if (i == verticesSize - 2)
        {
            edgesIndicies.push_back(i);
            edgesIndicies.push_back(i+1);
            edgesIndicies.push_back(i);
            edgesIndicies.push_back(0);
            edgesIndicies.push_back(i+1);
            edgesIndicies.push_back(0);
            edgesIndicies.push_back(1);
        }

        edgesIndicies.push_back(i);
        edgesIndicies.push_back(i+1);
        edgesIndicies.push_back(i);
        edgesIndicies.push_back(i+2);
    }

    return edgesIndicies;
}

std::vector<unsigned int> MeshFactory::GenerateVerticesIndecies(const int verticesSize)
{
    std::vector<unsigned int> verticiesIndicies;

    for (int i = 0; i < verticesSize; i++)
    {
        verticiesIndicies.push_back(i);
    }

    return verticiesIndicies;
}

