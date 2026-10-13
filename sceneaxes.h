#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QVector3D>

class SceneAxes : protected QOpenGLFunctions
{
public:
    SceneAxes();
    //костыльное
    //ось Z меняется с Y
    void DrawX();
    void DrawY();
    void DrawZ();
    //void Draw();

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    // void DrawX();
    // void DrawY();
    // void DrawZ();

    void SetupBuffers();
};


