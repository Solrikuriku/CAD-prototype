#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->AddCubeButton, &QPushButton::clicked, this, [this]()
    {
        ui->openGLWidget->AddCube(0.5f, 0.5f, 0.5f);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
