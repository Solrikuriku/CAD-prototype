#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QUuid>
#include "viewport3d.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Viewport3D *viewport = nullptr;

    struct ObjectCounter
    {
        int cylinder = 0;
        int cube = 0;
    };

    ObjectCounter counter;

    QStandardItemModel *objectListModel = nullptr;

    enum ObjectType { Cube, Cylinder };
    ObjectType objectType = Cube;

    float scale = 100;

    void AddObject(const float width, const float height, const float depth);
    void AddObject(const float radius, const float height);

    void AddAtTreeObject(const QUuid& id, const ObjectType& type);
    std::string GenerateName(const ObjectType &type) const;

    void ErrorMessage();
    bool TestCorrectValues(ObjectType type = Cube);
};

#endif // MAINWINDOW_H
