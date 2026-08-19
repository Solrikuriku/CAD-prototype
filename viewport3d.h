#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QHash>
#include <cassert>
//решить вопрос с предупреждениями
#include "algorithm"
#include "raycasting.h"
#include "sceneobject.h"
#include "meshfactory.h"
#include "iviewportcontext.h"
#include "TransformAxes.h"
#include "selecthandler.h"
#include "translatecommand.h"
#include "rotatecommand.h"
#include "scalecommand.h"

class Viewport3D : public QOpenGLWidget,
                   protected QOpenGLFunctions_3_3_Core,
                   public IViewportContext
{
    Q_OBJECT

public:
    Viewport3D(QWidget* parent = nullptr);

    void AddCube(float width = 0.5f, float height = 0.5f, float depth = 0.5f);

    SceneObject* PickObject(const QPointF& currentPos) const override;
    void SetPickedObject(SceneObject* picked) override;
    QVector3D GetCursorWorldPos(const QPointF& currentPos, const QVector3D& objectPos, const TransformAxes axes) const override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    enum class TranslateMode
    {
        None,
        Choose,
        Move
    };

    enum class RotateMode
    {
        None,
        Choose,
        Rotate
    };

    enum class ScaleMode
    {
        None,
        Choose,
        Scale
    };

    // enum class TransformAxes
    // {
    //     None, X, Y, Z
    // };

    TranslateMode m_translate_mode = TranslateMode::None;
    RotateMode m_rotate_mode = RotateMode::None;
    ScaleMode m_scale_mode = ScaleMode::None;
    TransformAxes m_axes = TransformAxes::None;

    //а есть смысл в хэш с id?
    // std::vector<std::unique_ptr<SceneObject>> m_objects;
    std::unordered_map<std::string, std::unique_ptr<SceneObject>> m_objects;
    std::unique_ptr<SelectHandler> m_selectHandler;
    std::unique_ptr<TranslateCommand> m_translateCommand;
    std::unique_ptr<RotateCommand> m_rotateCommand;
    std::unique_ptr<ScaleCommand> m_scaleCommand;

    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_currentView;

    float m_cameraDistance = 3.0f;

    bool m_rotating = false;      // зажата ли кнопка прямо сейчас
    bool m_needsRedraw = false;
    QPointF m_lastMousePos = QPointF();        // где была мышь в прошлом событии
    QPointF m_lastDragPos = QPointF();
    QVector3D m_cursorWorldPos = QVector3D(); //позииция в 3д
    float m_yaw = 0.0f;           // поворот вокруг вертикальной оси (влево-вправо)
    float m_pitch = 20.0f;        // поворот вокруг горизонтальной оси (вверх-вниз), начальный наклон для вида "не в лоб"


    //СЛЕДИТЬ ЗА ВРЕМЕНЕМ ЖИЗНИ
    //а вообще это наблюдатель
    //есть смысл объединить в m_pickedObject
    SceneObject* m_pickedObject = nullptr;

    //метод для отмены всех выделений
    inline void CancelAllSelections()
    {
        for (auto &[id, obj] : m_objects)
        {
            if (!obj) continue;

            if (obj->selected)
                obj->selected = false;
        }
    }

    //пока тут

    inline void ChangeAxes(QKeyEvent* e)
    {
        if (e->key() == Qt::Key_X)
            m_axes = TransformAxes::X;
        else if (e->key() == Qt::Key_Y)
            m_axes = TransformAxes::Z;
        else if (e->key() == Qt::Key_Z)
            m_axes = TransformAxes::Y;
        else
            m_axes = TransformAxes::None;
    }

    // SceneObject* PickObject(const QPointF& currentPos) const override;
    // QVector3D GetCursorWorldPos(const QPointF& currentPos, const QVector3D& objectPos, const QMatrix4x4& currentView, const TransformAxes axes);
};
