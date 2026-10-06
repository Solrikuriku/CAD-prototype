#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDoubleValidator"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cubeWidth->setValidator(new QDoubleValidator(0.1, 1000.0, 2, this));
    ui->cubeHeight->setValidator(new QDoubleValidator(0.1, 1000.0, 2, this));
    ui->cubeDepth->setValidator(new QDoubleValidator(0.1, 1000.0, 2, this));

    ui->cylinderRadius->setValidator(new QDoubleValidator(0.1, 1000.0, 2, this));
    ui->cylinderHeight->setValidator(new QDoubleValidator(0.1, 1000.0, 2, this));

    connect(ui->AddCubeButton, &QPushButton::clicked, this, [this]()
    {
        ui->objectType->setCurrentIndex(1);
        objectType = Cube;
    });

    connect(ui->AddCylinderButton, &QPushButton::clicked, this, [this]()
    {
        ui->objectType->setCurrentIndex(0);
        objectType = Cylinder;
    });

    connect(ui->ApplyButton, &QPushButton::clicked, this, [this]()
    {
        if (!TestCorrectValues(objectType))
        {
            ErrorMessage();
            return;
        }

        if (objectType == Cube)
        {
            auto width = ui->cubeWidth->text().toFloat();
            auto height = ui->cubeHeight->text().toFloat();
            auto depth = ui->cubeDepth->text().toFloat();
            AddObject(width, height, depth);
        }
        else if (objectType == Cylinder)
        {
            auto radius = ui->cylinderRadius->text().toFloat();
            auto height = ui->cylinderHeight->text().toFloat();
            AddObject(radius, height);
        }
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddObject(const float width, const float height, const float depth)
{
    ui->openGLWidget->AddCube(width / scale, height / scale, depth / scale);
}

void MainWindow::AddObject(const float radius, const float height)
{
    ui->openGLWidget->AddCylinder(radius / scale, height / scale);
}

void MainWindow::ErrorMessage()
{
    QMessageBox::critical
    (
        this,
        tr("Критическая ошибка"),
        tr("Проверьте вводные значения объекта!"),
        QMessageBox::Ok
    );
}

bool MainWindow::TestCorrectValues(ObjectType type)
{
    if (type == Cube)
    {
        bool okW = false, okH = false, okD = false;

        ui->cubeWidth->text().toFloat(&okW);
        ui->cubeHeight->text().toFloat(&okH);
        ui->cubeDepth->text().toFloat(&okD);

        return (okW && okH && okD);
    }
    else if (type == Cylinder)
    {
        bool okR = false, okH = false;

        ui->cylinderRadius->text().toFloat(&okR);
        ui->cylinderHeight->text().toFloat(&okH);

        return (okR && okH);
    }

    return false;
}
