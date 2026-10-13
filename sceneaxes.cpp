#include "sceneaxes.h"

SceneAxes::SceneAxes()
{
    initializeOpenGLFunctions();
    SetupBuffers();
}

/*
 * void SceneAxes::DrawX() { m_vao.bind(); glDrawArrays(GL_LINES, 0, 2); m_vao.release(); }
void SceneAxes::DrawY() { m_vao.bind(); glDrawArrays(GL_LINES, 2, 2); m_vao.release(); }
void SceneAxes::DrawZ() { m_vao.bind(); glDrawArrays(GL_LINES, 4, 2); m_vao.release(); }

как мне тут еще всучить отрицательные оси?
*/

// void SceneAxes::Draw()
// {
//     DrawX();
//     DrawY();
//     DrawZ();
// }

void SceneAxes::DrawX()
{
    m_vao.bind();
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_LINES, 6, 2);
    m_vao.release();
}

void SceneAxes::DrawY()
{
    m_vao.bind();
    glDrawArrays(GL_LINES, 2, 2);
    glDrawArrays(GL_LINES, 8, 2);
    m_vao.release();
}

void SceneAxes::DrawZ()
{
    m_vao.bind();
    glDrawArrays(GL_LINES, 4, 2);
    glDrawArrays(GL_LINES, 10, 2);
    m_vao.release();
}

void SceneAxes::SetupBuffers()
{
    float axeLength = 500.0f;

    std::vector<float> vertices =
        {
            // Ось X (Красная)
            0.0f, 0.0f, 0.0f,
            axeLength, 0.0f, 0.0f,

            // Ось Y (Зеленая)
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, axeLength,

            // Ось Z (Синяя)
            0.0f, 0.0f, 0.0f,
            0.0f, axeLength, 0.0f,

            // Ось -X (Красная)
            0.0f, 0.0f, 0.0f,
            -axeLength, 0.0f, 0.0f,

            // Ось -Y (Зеленая)
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -axeLength,

            // Ось -Z (Синяя)
            0.0f, 0.0f, 0.0f,
            0.0f, -axeLength, 0.0f
        };

    m_vao.create();
    m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertices.data(), vertices.size() * sizeof(float));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    m_vao.release();
    m_vbo.release();
}
