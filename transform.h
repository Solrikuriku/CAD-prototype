#pragma once

#include <QVector3D>
#include <QMatrix4x4>

struct Transform
{
    QVector3D position = {0.0f, 0.0f, 0.0f};
    QVector3D scaling = { 1.0f, 1.0f, 1.0f };
    QQuaternion rotation = QQuaternion();

    QMatrix4x4 GetMatrix() const
    {
        QMatrix4x4 m;
        //единичная матрица
        m.setToIdentity();
        //умножаем текущую матрицу на матрицу сдвига
        m.translate(position);
        m.rotate(rotation);
        m.scale(scaling);

        return m;
    }
};
