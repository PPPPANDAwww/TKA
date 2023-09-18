QT       += core gui opengl
QT       += multimedia multimediawidgets
QT       += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    playcontroler.cpp \
    player.cpp \
    threedimage.cpp \
    videodlg.cpp

HEADERS += \
    mainwindow.h \
    playcontroler.h \
    player.h \
    threedimage.h \
    videodlg.h

FORMS += \
    mainwindow.ui \
    threedimage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/icon/tka_cover.JPG

RESOURCES += \
    src.qrc

INCLUDEPATH += /opt/homebrew/Cellar/vtk/9.2.6_4/include/vtk-9.2

LIBS += -L/opt/homebrew/Cellar/vtk/9.2.6_4/lib \
        -lvtkCommonColor-9.2.1 -lvtkCommonComputationalGeometry-9.2.9.2.6 -lvtkCommonCore-9.2.9.2.6 \
        -lvtkCommonExecutionModel-9.2.9.2.6 -lvtkCommonMath-9.2.9.2.6 -lvtkCommonMisc-9.2.9.2.6 \
        -lvtkCommonDataModel-9.2.9.2.6 -lvtkCommonTransforms-9.2.9.2.6 \
        -lvtkRenderingCore-9.2.9.2.6 -lvtkRenderingOpenGL2-9.2.9.2.6 \
        -lvtkIOGeometry-9.2.9.2.6
        -lvtkIOImage-9.2.9.2.6
        -lvtkIOParallel-9.2.9.2.6
        -lvtkIOParallelXML-9.2.9.2.6
        -lvtkIOXML-9.2.9.2.6
        -lvtkIOXMLParser-9.2.9.2.6
        -lvtkFiltersCore-9.2.9.2.6
        -lvtksys-9.2.9.2.6
