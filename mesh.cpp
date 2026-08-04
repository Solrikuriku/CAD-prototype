#include "mesh.h"


Mesh::Mesh(const std::vector<float> &vertices,
           const std::vector<unsigned int> &indices,
           const std::vector<unsigned int> &edgeIndices)

{
    //CalculateBounds(vertices);

    initializeOpenGLFunctions();
    SetupBuffers(vertices, indices, edgeIndices);
}

void Mesh::DrawTriangulated()
{
    m_vao.bind();
    m_ebo.bind(); // явно говорим, какой EBO использовать для этого вызова
    glDrawElements(GL_TRIANGLES, m_triangleIndexCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::Draw()
{
    m_vao.bind();
    m_edgeEbo.bind(); // переключаемся на другой EBO
    glDrawElements(GL_LINES, m_edgeIndexCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::SetupBuffers(const std::vector<float> &v, const std::vector<unsigned int> &i, const std::vector<unsigned int> &ei)
{
    m_triangleIndexCount = static_cast<int>(i.size());
    m_edgeIndexCount = static_cast<int>(ei.size());

    m_vao.create();
    m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(v.data(), int(v.size() * sizeof(float)));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_ebo.create();
    m_ebo.bind();
    m_ebo.allocate(i.data(), int(i.size() * sizeof(unsigned int)));

    m_vao.release();

    // EBO для рёбер — заполняем отдельно, VAO этого уже не "запомнит"
    // (переключать EBO будем вручную перед каждой отрисовкой)
    m_edgeEbo.create();
    m_edgeEbo.bind();
    m_edgeEbo.allocate(ei.data(), int(ei.size() * sizeof(unsigned int)));
}
