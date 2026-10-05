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

std::unique_ptr<Mesh> MeshFactory::CreateCylinder(const float radius, const float height, const int segments)
{
    auto vertices = GenerateVertices(radius, height, segments);
    auto verticesIncidies = GenerateCylinderVerticesIndecies(segments);
    auto edgesIndicies = GenerateCylinderEdgeIndices(segments);
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
    //std::vector<float> vertices;

    std::vector<float> topVerts;
    std::vector<float> bottomVerts;

    float radianAngle = TO_RADIANS((360.0f / segments));
    float yTop = height / 2.0f;
    float yBottom = -height / 2.0f;
    //QVector3D coordinatesCircleTop = QVector3D(0.0f, 0.0f, zTop);
    //QVector3D coordinatesCircleBottom = QVector3D(0.0f, 0.0f, zBottom);

    float step = radianAngle;

    for (int i = 0; i < segments; i++)
    {
        float angle = step * i;

        float x = radius * cos(angle);
        float z = radius * sin(angle);

        //auto vertexTop = QVector3D(x, y, zTop);
        //auto vertexBotton = QVector3D(x, y, zBottom);

        topVerts.push_back(x);
        topVerts.push_back(yTop);
        topVerts.push_back(z);

        bottomVerts.push_back(x);
        bottomVerts.push_back(yBottom);
        bottomVerts.push_back(z);

        // vertices.push_back(QVector3D(x, y, zTop));
        // vertices.push_back(QVector3D(x, y, zBottom));
    }

    topVerts.insert(topVerts.end(), bottomVerts.begin(), bottomVerts.end());
    topVerts.push_back(0);
    topVerts.push_back(yTop);
    topVerts.push_back(0);
    topVerts.push_back(0);
    topVerts.push_back(yBottom);
    topVerts.push_back(0);
    qDebug() << "vrtxs" << topVerts;

    return topVerts;
}


std::vector<unsigned int> MeshFactory::GenerateCylinderVerticesIndecies(const int segments)
{
    std::vector<unsigned int> indices;

    for (int i = 0; i < segments; i++)
    {
        // Находим индексы 4-х углов на боковой стенке:
        int top1 = i;                           // Верхняя левая точка
        int top2 = (i + 1) % segments;          // Верхняя правая (с замыканием в кольцо)
        int bottom1 = segments + i;             // Нижняя левая
        int bottom2 = segments + top2;          // Нижняя правая

        // Первый треугольник (верх-лево, низ-лево, низ-право)
        indices.push_back(top1);
        indices.push_back(bottom1);
        indices.push_back(bottom2);

        // Второй треугольник (верх-лево, низ-право, верх-право)
        indices.push_back(top1);
        indices.push_back(bottom2);
        indices.push_back(top2);
    }

    int topCenterIndex = 2 * segments;
    int bottomCenterIndex = 2 * segments + 1;

    for (int i = 0; i < segments; i++)
    {
        int next_i = (i + 1) % segments;

        // Верхняя крышка (Центр, текущая точка верха, следующая точка верха)
        indices.push_back(topCenterIndex);
        indices.push_back(i);
        indices.push_back(next_i);

        // Нижняя крышка (Центр, текущая точка низа, следующая точка низа)
        indices.push_back(bottomCenterIndex);
        indices.push_back(segments + next_i);
        indices.push_back(segments + i);
    }

    return indices;
}

std::vector<unsigned int> MeshFactory::GenerateCylinderEdgeIndices(int segments)
{
    std::vector<unsigned int> edges;

    for (int i = 0; i < segments; i++)
    {
        int next_i = (i + 1) % segments;

        // Линия верхнего кольца (от текущей к следующей)
        edges.push_back(i);
        edges.push_back(next_i);

        // Линия нижнего кольца
        edges.push_back(segments + i);
        edges.push_back(segments + next_i);

        // Вертикальная стойка (соединяем верх и низ)
        // edges.push_back(i);
        // edges.push_back(segments + i);
    }

    return edges;
}

