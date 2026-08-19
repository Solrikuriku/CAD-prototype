QT       += core gui
QT += widgets opengl
QT += widgets opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    iviewportcontext.cpp \
    main.cpp \
    mainwindow.cpp \
    mesh.cpp \
    meshfactory.cpp \
    raycasting.cpp \
    rotatecommand.cpp \
    scalecommand.cpp \
    sceneobject.cpp \
    selecthandler.cpp \
    translatecommand.cpp \
    viewport3d.cpp

HEADERS += \
    TransformAxes.h \
    geometry.h \
    iviewportcontext.h \
    mainwindow.h \
    mesh.h \
    meshfactory.h \
    raycasting.h \
    rotatecommand.h \
    scalecommand.h \
    sceneobject.h \
    selecthandler.h \
    transform.h \
    translatecommand.h \
    viewport3d.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Suggestions
