/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "viewport3d.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    Viewport3D *openGLWidget;
    QPushButton *AddCubeButton;
    QPushButton *AddCylinderButton;
    QStackedWidget *objectType;
    QWidget *cylinder;
    QLineEdit *cylinderRadius;
    QLineEdit *cylinderHeight;
    QLabel *labelCylinderRadius;
    QLabel *labelCylinderHeight;
    QLabel *labelCylinderType;
    QWidget *cube;
    QLineEdit *cubeWidth;
    QLineEdit *cubeHeight;
    QLineEdit *cubeDepth;
    QLabel *labelCubeWidth;
    QLabel *labelCubeHeight;
    QLabel *labelCubeDepth;
    QLabel *labelCubeType;
    QPushButton *ApplyButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1266, 758);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        openGLWidget = new Viewport3D(centralwidget);
        openGLWidget->setObjectName("openGLWidget");
        openGLWidget->setGeometry(QRect(10, 20, 1081, 701));
        AddCubeButton = new QPushButton(centralwidget);
        AddCubeButton->setObjectName("AddCubeButton");
        AddCubeButton->setGeometry(QRect(1110, 20, 141, 29));
        AddCylinderButton = new QPushButton(centralwidget);
        AddCylinderButton->setObjectName("AddCylinderButton");
        AddCylinderButton->setGeometry(QRect(1110, 70, 141, 29));
        objectType = new QStackedWidget(centralwidget);
        objectType->setObjectName("objectType");
        objectType->setGeometry(QRect(1110, 120, 131, 231));
        cylinder = new QWidget();
        cylinder->setObjectName("cylinder");
        cylinderRadius = new QLineEdit(cylinder);
        cylinderRadius->setObjectName("cylinderRadius");
        cylinderRadius->setGeometry(QRect(10, 60, 113, 28));
        cylinderHeight = new QLineEdit(cylinder);
        cylinderHeight->setObjectName("cylinderHeight");
        cylinderHeight->setGeometry(QRect(10, 110, 113, 28));
        labelCylinderRadius = new QLabel(cylinder);
        labelCylinderRadius->setObjectName("labelCylinderRadius");
        labelCylinderRadius->setGeometry(QRect(10, 40, 63, 20));
        labelCylinderHeight = new QLabel(cylinder);
        labelCylinderHeight->setObjectName("labelCylinderHeight");
        labelCylinderHeight->setGeometry(QRect(10, 90, 63, 20));
        labelCylinderType = new QLabel(cylinder);
        labelCylinderType->setObjectName("labelCylinderType");
        labelCylinderType->setGeometry(QRect(10, 10, 63, 20));
        objectType->addWidget(cylinder);
        cube = new QWidget();
        cube->setObjectName("cube");
        cubeWidth = new QLineEdit(cube);
        cubeWidth->setObjectName("cubeWidth");
        cubeWidth->setGeometry(QRect(10, 70, 113, 28));
        cubeHeight = new QLineEdit(cube);
        cubeHeight->setObjectName("cubeHeight");
        cubeHeight->setGeometry(QRect(10, 120, 113, 28));
        cubeDepth = new QLineEdit(cube);
        cubeDepth->setObjectName("cubeDepth");
        cubeDepth->setGeometry(QRect(10, 170, 113, 28));
        labelCubeWidth = new QLabel(cube);
        labelCubeWidth->setObjectName("labelCubeWidth");
        labelCubeWidth->setGeometry(QRect(10, 50, 63, 20));
        labelCubeHeight = new QLabel(cube);
        labelCubeHeight->setObjectName("labelCubeHeight");
        labelCubeHeight->setGeometry(QRect(10, 100, 63, 20));
        labelCubeDepth = new QLabel(cube);
        labelCubeDepth->setObjectName("labelCubeDepth");
        labelCubeDepth->setGeometry(QRect(10, 150, 63, 20));
        labelCubeType = new QLabel(cube);
        labelCubeType->setObjectName("labelCubeType");
        labelCubeType->setGeometry(QRect(10, 10, 63, 20));
        objectType->addWidget(cube);
        ApplyButton = new QPushButton(centralwidget);
        ApplyButton->setObjectName("ApplyButton");
        ApplyButton->setGeometry(QRect(1119, 370, 121, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1266, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        objectType->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        AddCubeButton->setText(QCoreApplication::translate("MainWindow", "\320\232\321\203\320\261", nullptr));
        AddCylinderButton->setText(QCoreApplication::translate("MainWindow", "\320\246\320\270\320\273\320\270\320\275\320\264\321\200", nullptr));
        labelCylinderRadius->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\264\320\270\321\203\321\201", nullptr));
        labelCylinderHeight->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260", nullptr));
        labelCylinderType->setText(QCoreApplication::translate("MainWindow", "\320\246\320\270\320\273\320\270\320\275\320\264\321\200", nullptr));
        labelCubeWidth->setText(QCoreApplication::translate("MainWindow", "\320\250\320\270\321\200\320\270\320\275\320\260", nullptr));
        labelCubeHeight->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260", nullptr));
        labelCubeDepth->setText(QCoreApplication::translate("MainWindow", "\320\223\320\273\321\203\320\261\320\270\320\275\320\260", nullptr));
        labelCubeType->setText(QCoreApplication::translate("MainWindow", "\320\232\321\203\320\261", nullptr));
        ApplyButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
