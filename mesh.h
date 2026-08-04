#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <vector>
#include <QMatrix4x4>
#include <QVector3D>
#include "geometry.h"

class Mesh : protected QOpenGLFunctions
{
public:
    Mesh(const std::vector<float> &vertices,
         const std::vector<unsigned int> &indicies,
         const std::vector<unsigned int> &edgeIndicies);

    void DrawTriangulated();
    void Draw();

    AABB bounds;

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_ebo{QOpenGLBuffer::IndexBuffer};
    QOpenGLBuffer m_edgeEbo{QOpenGLBuffer::IndexBuffer};

    int m_triangleIndexCount = 0;
    int m_edgeIndexCount = 0;

    void SetupBuffers(const std::vector<float> &v, const std::vector<unsigned int> &i, const std::vector<unsigned int> &ei);
};
