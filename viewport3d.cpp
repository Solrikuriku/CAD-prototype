#include "viewport3d.h"

static const char *vertexShaderSrc =
R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 mvp;

    void main()
    {
        gl_Position = mvp * vec4(aPos, 1.0);
    }
)";

static const char *fragmentShaderSrc =
R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec3 objectColor;

    void main()
    {
        FragColor = vec4(objectColor, 1.0);
    }
)";

Viewport3D::Viewport3D(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    m_selectHandler = std::make_unique<SelectHandler>(this);
}

void Viewport3D::AddCube(float width, float height, float depth)
{
    makeCurrent();
    auto newObject = std::make_unique<SceneObject>();
    newObject->mesh = MeshFactory::CreateCube(width, height, depth);

    auto id = newObject->id; // ОБЯЗАТЕЛЬНО сохраняем id В ОТДЕЛЬНУЮ переменную ДО move
    m_objects.emplace(id, std::move(newObject)); // теперь move происходит для уже сохранённого id

    doneCurrent();
    update();
}

void Viewport3D::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSrc);
    m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSrc);
    m_program.link();
}

void Viewport3D::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, float(w) / float(h ? h : 1), 0.1f, 100.0f);
}

void Viewport3D::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_currentView.setToIdentity();
    m_currentView.translate(0.0f, 0.0f, -m_cameraDistance); // сначала отодвигаем камеру
    m_currentView.rotate(m_pitch, 1.0f, 0.0f, 0.0f);         // потом поворот вокруг X (вверх-вниз)
    m_currentView.rotate(m_yaw,   0.0f, 1.0f, 0.0f);
    //а это чо тут делает

    m_program.bind();

    for (auto &[id, obj] : m_objects)
    {
        m_program.setUniformValue("mvp", m_projection * m_currentView * obj->transform.GetMatrix());

        QVector3D fillColor = obj->selected
                                  ? QVector3D(0.3f, 0.6f, 0.9f)  // голубой — выделенный объект
                                  : QVector3D(0.8f, 0.4f, 0.1f); // оранжевый — обычный объект

        m_program.setUniformValue("objectColor", fillColor);
        obj->DrawTriangulated(); // заливка

        m_program.setUniformValue("objectColor", QVector3D(0.0f, 0.0f, 0.0f));
        glLineWidth(2.0f); // толщина линий рёбер (не везде работает одинаково, но попробовать стоит)
        obj->Draw(); // чёрные рёбра поверх
    }

    glDisable(GL_POLYGON_OFFSET_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // вернуть обратно для следующего кадра
}

void Viewport3D::mousePressEvent(QMouseEvent *event)
{
    m_rotating = false;

    if (m_translate_mode == TranslateMode::Move)
    {
        m_translate_mode = TranslateMode::None;
        m_axes = TransformAxes::None;
        m_pickedObject = nullptr;

        return;
    }

    if (m_rotate_mode == RotateMode::Rotate)
    {
        m_rotate_mode = RotateMode::None;
        m_axes = TransformAxes::None;
        m_pickedObject = nullptr;

        return;
    }

    if (m_scale_mode == ScaleMode::Scale)
    {
        m_scale_mode = ScaleMode::None;
        m_axes = TransformAxes::None;
        m_pickedObject = nullptr;

        return;
    }


    m_selectHandler->OnMousePress(event);
    update();

    // if (event->button() == Qt::LeftButton)
    // {
    //     auto picked = PickObject(event->pos());

    //     // сбрасываем выделение у ВСЕХ объектов перед новым выбором
    //     for (auto &[id, obj] : m_objects)
    //         obj->selected = false;

    //     if (picked) picked->selected = true;

    //     update();

    //     qDebug() << "picked:" << (picked ? "found" : "nothing");
    // }
    if (event->button() == Qt::RightButton)
    {
        m_rotating = true;
        m_lastMousePos = event->pos(); // запоминаем стартовую точку
    }
}

void Viewport3D::mouseMoveEvent(QMouseEvent *event)
{
    if (m_rotating) // кнопка не зажата — игнорируем движение мыши
    {
        QPointF delta = event->pos() - m_lastMousePos; // на сколько пикселей сдвинулась мышь
        m_lastMousePos = event->pos();

        float sensitivity = 0.3f; // скорость вращения, подбери на глаз

        m_yaw   += delta.x() * sensitivity;
        m_pitch += delta.y() * sensitivity;

        // не даём камере "перевернуться" через полюс (стандартная защита для orbit-камеры)
        //clamp -
        //"Зажимает" число в заданном диапазоне — если число выходит за границы,
        //возвращает ближайшую границу вместо него.
        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);
    }

    if (m_rotate_mode == RotateMode::Rotate)
    {
        if (!m_pickedObject) return;

        auto& objectPos = m_pickedObject->transform.position;
        auto& objectRotate = m_pickedObject->transform.rotation;
        auto currentPos = event->pos();

        auto newCursorWorldPos = GetCursorWorldPos(currentPos, objectPos, m_axes);

        QVector3D rotatePlane;

        if (m_axes == TransformAxes::X) rotatePlane = QVector3D(1, 0, 0);
        else if (m_axes == TransformAxes::Y) rotatePlane = QVector3D(0, 1, 0);
        else if (m_axes == TransformAxes::Z) rotatePlane = QVector3D(0, 0, 1);

        float angleDegrees = AngleBetweenVectors(m_cursorWorldPos, newCursorWorldPos, objectPos, rotatePlane);

        QQuaternion deltaRotation = QQuaternion::fromAxisAndAngle(rotatePlane, angleDegrees);
        objectRotate = deltaRotation * objectRotate;

        m_cursorWorldPos = newCursorWorldPos;
    }
    else if (m_scale_mode == ScaleMode::Scale)
    {
        if (!m_pickedObject) return;

        auto& objectPos = m_pickedObject->transform.position;
        auto currentPos = event->pos();
        auto new_cursorWorldPos = GetCursorWorldPos(currentPos, objectPos, m_axes);
        auto delta3D = new_cursorWorldPos - m_cursorWorldPos;
        float scaleSensitivity = 2.0f;

        auto &scale = m_pickedObject->transform.scaling;

        if (m_axes == TransformAxes::X)
        {
            scale.setX(scale.x() + (float)delta3D.x() * scaleSensitivity);
        }
        else if (m_axes == TransformAxes::Y)
        {
            scale.setY(scale.y() + (float)delta3D.y() * scaleSensitivity);
        }
        else if (m_axes == TransformAxes::Z)
        {
            scale.setZ(scale.z() + (float)delta3D.z() * scaleSensitivity);
        }

        m_cursorWorldPos = new_cursorWorldPos;
    }
    else if (m_translate_mode == TranslateMode::Move)
    {

        m_translateCommand->OnMouseMove(event);


        // if (!m_pickedObject) return;

        // auto& objectPos = m_pickedObject->transform.position;
        // auto currentPos = event->pos();

        // m_cursorWorldPos = GetCursorWorldPos(currentPos, objectPos, m_axes);

        // if (m_axes == TransformAxes::X)
        // {
        //     objectPos.setX(m_cursorWorldPos.x());
        // }
        // else if (m_axes == TransformAxes::Y)
        // {
        //     objectPos.setY(m_cursorWorldPos.y());
        // }
        // else if (m_axes == TransformAxes::Z)
        // {
        //     objectPos.setZ(m_cursorWorldPos.z());
        // }

        // //m_lastDragPos = currentPos;
    }

    update();
}

void Viewport3D::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && !m_rotating == false)
        m_rotating = false;

    // if (event->button() == Qt::LeftButton && m_mode == TransformMode::Move)
    // {
    //     m_mode = TransformMode::None;
    //     m_axes = TransformAxes::None;
    //     m_transformObject = nullptr;
    // }
}

void Viewport3D::keyPressEvent(QKeyEvent *event)
{
    //проходка по selected так себе
    //мне кажется нужно тут как то подумать насчет этого
    //скорее всего все равно создать контейнер для выделенок
    //для быстрого чтения

    //при нажатии G переходим в режим move
    if (event->key() == Qt::Key_R)
    {
        //объект который можно трансформировать
        //может быть единственным, может множественным
        //но пока он единственный
        //ищем такой объект

        for (auto &[id, obj] : m_objects)
        {
            if (obj->selected)
            {
                m_pickedObject = obj.get();
                break;
            }
        }

        //если cуществует выделенный объект, то идем дальше
        //иначе завершаем вызов метода

        if (!m_pickedObject) return;

        m_rotate_mode = RotateMode::Choose;

        return;
    }

    //я подумаю об объединении
    if (m_rotate_mode == RotateMode::Choose)
    {
        //assert(m_translateObject != nullptr);

        if (event->key() == Qt::Key_X)
            m_axes = TransformAxes::X;
        else if (event->key() == Qt::Key_Y)
            m_axes = TransformAxes::Y;
        else if (event->key() == Qt::Key_Z)
            m_axes = TransformAxes::Z;
        else return;

        m_rotate_mode = RotateMode::Rotate;

        m_cursorWorldPos = GetCursorWorldPos(mapFromGlobal(QCursor::pos()), m_pickedObject->transform.position, m_axes);

        return;
    }

    if (event->key() == Qt::Key_S)
    {
        for (auto &[id, obj] : m_objects)
        {
            if (obj->selected)
            {
                m_pickedObject = obj.get();
                break;
            }
        }

        if (!m_pickedObject) return;

        m_scale_mode = ScaleMode::Choose;

        return;
    }

    //я подумаю об объединении
    if (m_scale_mode == ScaleMode::Choose)
    {
        //assert(m_translateObject != nullptr);

        if (event->key() == Qt::Key_X)
            m_axes = TransformAxes::X;
        else if (event->key() == Qt::Key_Y)
            m_axes = TransformAxes::Y;
        else if (event->key() == Qt::Key_Z)
            m_axes = TransformAxes::Z;
        else return;

        m_scale_mode = ScaleMode::Scale;

        m_cursorWorldPos = GetCursorWorldPos(mapFromGlobal(QCursor::pos()), m_pickedObject->transform.position, m_axes);

        return;
    }

    //возможно есть архитектура получше
    if (event->key() == Qt::Key_G)
    {
        //объект который можно трансформировать
        //может быть единственным, может множественным
        //но пока он единственный
        //ищем такой объект

        for (auto &[id, obj] : m_objects)
        {
            if (obj->selected)
            {
                m_pickedObject = obj.get();
                break;
            }
        }

        //если cуществует выделенный объект, то идем дальше
        //иначе завершаем вызов метода

        if (!m_pickedObject) return;

        m_translate_mode = TranslateMode::Choose;

        return;
    }

    if (m_translate_mode == TranslateMode::Choose)
    {
        //assert(m_translateObject != nullptr);

        ChangeAxes(event);
        if (m_axes == TransformAxes::None) return;

        m_translate_mode = TranslateMode::Move;
        m_translateCommand = std::make_unique<TranslateCommand>(this, m_pickedObject, m_axes);
        m_cursorWorldPos = GetCursorWorldPos(mapFromGlobal(QCursor::pos()), m_pickedObject->transform.position, m_axes);

        return;
    }


    //ожидание выбора осей
    //если ось выбрана, то двигаем мышью строго по оси

}

void Viewport3D::wheelEvent(QWheelEvent *event)
{
    float delta = event->angleDelta().y() / 120.0f;

    m_cameraDistance -= delta * 0.5f; // 0.5f — скорость зума, подбери на глаз

    // не даём камере "провалиться" в объект или улететь слишком далеко
    //и че такое clamp
    m_cameraDistance = std::clamp(m_cameraDistance, 1.0f, 20.0f);

    update();
}

SceneObject* Viewport3D::PickObject(const QPointF &currentPos) const
{
    Ray ray = RayCasting::ScreenToRay(currentPos, width(), height(), m_projection, m_currentView);

    SceneObject* closestObject = nullptr;
    //че такое этот ваш T
    //это параметр вдоль луча, время?
    float tClosest = std::numeric_limits<float>::max();

    for (auto &[id, obj] : m_objects)
    {
        // переводим луч в локальные координаты объекта
        QMatrix4x4 invModel = obj->transform.GetMatrix().inverted();
        Ray localRay;
        localRay.origin = invModel.map(ray.origin);
        localRay.direction = invModel.mapVector(ray.direction);

        float t;

        if (RayCasting::IsRayIntersectsAABB(localRay, obj->mesh->bounds, t))
        {
            if (t < tClosest)
            {
                tClosest = t;
                closestObject = obj.get();
            }
        }
    }

    return closestObject;
}

void Viewport3D::SetPickedObject(SceneObject *picked)
{
    if (m_pickedObject && m_pickedObject != picked)
    {
        m_pickedObject->selected = false;
    }

    if (picked)
    {
        m_pickedObject = picked;
        m_pickedObject->selected = true;
    }
}

QVector3D Viewport3D::GetCursorWorldPos(const QPointF& currentPos, const QVector3D& objectPos, const TransformAxes axes) const
{
    QVector3D foundCursorPos = { 0.0f, 0.0f, 0.0f };

    Ray ray = RayCasting::ScreenToRay(currentPos, width(), height(), m_projection, m_currentView);

    Plane plane;
    plane.point = objectPos;
    plane.normal = QVector3D(0, 0, 1);

    //а куда в реальном 3D-мире сейчас направлен этот вектор взгляда (0, 0, -1), с учетом всех наших поворотов камеры
    QVector3D cameraForward = m_currentView.inverted().mapVector(QVector3D(0, 0, -1));

    if (axes == TransformAxes::X)
    {
        if (std::abs(cameraForward.z()) > std::abs(cameraForward.y()))
            plane.normal = QVector3D(0, 0, 1);
        else
            plane.normal = QVector3D(0, 1, 0);
    }
    else if (axes == TransformAxes::Y)
    {
        if (std::abs(cameraForward.z()) > std::abs(cameraForward.x()))
            plane.normal = QVector3D(0, 0, 1);
        else
            plane.normal = QVector3D(1, 0, 0);
    }
    else if (axes == TransformAxes::Z)
    {
        // выбираем нормаль плоскости в зависимости от направления взгляда камеры,
        // чтобы избежать вырожденного случая при определённых углах
        // QVector3D cameraForward = m_currentView.inverted().mapVector(QVector3D(0, 0, -1));

        // если камера смотрит больше "вдоль X", используем нормаль Y вместо X (и наоборот)
        if (std::abs(cameraForward.x()) > std::abs(cameraForward.y()))
            plane.normal = QVector3D(1, 0, 0);
        else
            plane.normal = QVector3D(0, 1, 0);
    }

    //обработчик ошибок?
    RayCasting::IsRayIntersectsPlane(ray, plane, foundCursorPos);

    return foundCursorPos;
}

