#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->AddCubeButton, &QPushButton::clicked, this, [this]()
    {
        AddObject();
        // ui->openGLWidget->AddCube(0.5f, 0.5f, 0.5f);
    });

    connect(ui->AddCylinderButton, &QPushButton::clicked, this, [this]()
    {
        ui->openGLWidget->AddCylinder();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddObject()
{
    bool ok;
    auto width = ui->objectWidth->text().toFloat(&ok);
    auto height = ok ? ui->objectHeight->text().toFloat(&ok) : 0.0f;;
    auto depth = ok ? ui->objectDepth->text().toFloat(&ok) : 0.0f;

    if (!ok) return;

    ui->openGLWidget->AddCube(width / scale, height / scale, depth / scale);

    //аддим куб ток если заполним плашечки
    //а куб ли это тогда?
    //но в блендере же это называется куб
    // ui->openGLWidget->AddCube(0.5f, 0.5f, 0.5f);
}
