#-------------------------------------------------
#
# Editor project.
# Output: .exe
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG( debug, debug|release ) {
    TARGET = rmEd_x64d
} else {
    TARGET = rmEd_x64
}

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += ADS_IMPORT
#DEFINES += ADS_NAMESPACE_ENABLED

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

# execubale
DESTDIR = $$PWD/../../bin
# CONFIG( debug, debug|release ) {
#     DESTDIR = $$PWD/../../bin/editor/debug
# } else {
#     DESTDIR = $$PWD/../../bin/editor/release
# }

# objs
CONFIG( debug, debug|release ) {
    OBJECTS_DIR = $$PWD/../../obj/editor/debug
} else {
    OBJECTS_DIR = $$PWD/../../obj/editor/release
}

SOURCES += \
    $$PWD/../../src/editor/main.cpp \
    $$PWD/../../src/editor/mainwindow.cpp \
    $$PWD/../../src/editor/editorcore.cpp \
    $$PWD/../../src/editor/renderwidget.cpp \
    $$PWD/../../src/editor/icontitlewidget.cpp \
    $$PWD/../../src/editor/consolewidget.cpp \
    $$PWD/../../src/editor/consolewidget.cpp \
    $$PWD/../../src/editor/scenewidget.cpp \
    $$PWD/../../src/editor/treemodel.cpp \
    $$PWD/../../src/editor/treenode.cpp \
    $$PWD/../../src/editor/debugwidget.cpp \
    $$PWD/../../src/editor/parameterswidget.cpp \
    $$PWD/../../src/editor/selectmeshdialog.cpp \
    $$PWD/../../src/editor/manipulators/manipulatortranslator.cpp \
    $$PWD/../../src/editor/editor_common.cpp \
    $$PWD/../../src/editor/manipulators/imanipulator.cpp \
    $$PWD/../../src/editor/projectwidget.cpp \
    $$PWD/../../src/editor/propertieswidgets/camerapropertywidget.cpp \
    $$PWD/../../src/editor/propertieswidgets/modelpropertywidget.cpp \
    $$PWD/../../src/editor/propertieswidgets/lightpropertywidget.cpp \
    $$PWD/../../src/editor/settings.cpp \
    $$PWD/../../src/editor/texturelineedit.cpp \
    $$PWD/../../src/editor/importthread.cpp \
    $$PWD/../../src/editor/manipulators/manipulatorrotator.cpp \
    $$PWD/../../src/editor/manipulators/manipulatorscale.cpp \
    $$PWD/../../src/editor/mylineedit.cpp

HEADERS += \
    $$PWD/../../src/editor/mainwindow.h \
    $$PWD/../../src/editor/editorcore.h \
    $$PWD/../../src/editor/renderwidget.h \
    $$PWD/../../src/editor/icontitlewidget.h \
    $$PWD/../../src/editor/consolewidget.h \
    $$PWD/../../src/editor/consolewidget.h \
    $$PWD/../../src/editor/scenewidget.h \
    $$PWD/../../src/editor/treemodel.h \
    $$PWD/../../src/editor/treenode.h \
    $$PWD/../../src/editor/debugwidget.h \
    $$PWD/../../src/editor/parameterswidget.h \
    $$PWD/../../src/editor/myspinbox.h \
    $$PWD/../../src/editor/mylineedit.h \
    $$PWD/../../src/editor/selectmeshdialog.h \
    $$PWD/../../src/editor/manipulators/manipulatortranslator.h \
    $$PWD/../../src/editor/editor_common.h \
    $$PWD/../../src/editor/manipulators/imanipulator.h \
    $$PWD/../../src/editor/projectwidget.h \
    $$PWD/../../src/editor/propertieswidgets/camerapropertywidget.h \
    $$PWD/../../src/editor/propertieswidgets/modelpropertywidget.h \
    $$PWD/../../src/editor/colorwidget.h \
    $$PWD/../../src/editor/propertieswidgets/lightpropertywidget.h \
    $$PWD/../../src/editor/settings.h \
    $$PWD/../../src/editor/texturelineedit.h \
    $$PWD/../../src/editor/importthread.h \
    $$PWD/../../src/editor/manipulators/manipulatorrotator.h \
    $$PWD/../../src/editor/manipulators/manipulatorscale.h

INCLUDEPATH += "$$PWD/../../src/editor/thirdparty/Qt-Advanced-Docking-System/AdvancedDockingSystem/include"
DEPENDPATH += "$$PWD/../../src/editorthirdparty/Qt-Advanced-Docking-System/AdvancedDockingSystem/include"

FORMS += \
    $$PWD/../../src/editor/mainwindow.ui \
    $$PWD/../../src/editor/consolewidget.ui \
    $$PWD/../../src/editor/scenewidget.ui \
    $$PWD/../../src/editor/debugwidget.ui \
    $$PWD/../../src/editor/parameterswidget.ui \
    $$PWD/../../src/editor/selectmeshdialog.ui \
    $$PWD/../../src/editor/projectwidget.ui \
    $$PWD/../../src/editor/propertieswidgets/camerapropertywidget.ui \
    $$PWD/../../src/editor/propertieswidgets/modelpropertywidget.ui \
    $$PWD/../../src/editor/propertieswidgets/lightpropertywidget.ui \
    $$PWD/../../src/editor/settings.ui \
    $$PWD/../../src/editor/texturelineedit.ui

RC_FILE = ../../resources/editor/resources.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin1
else: unix:!android: target.path = /opt/$${TARGET}/bin1
!isEmpty(target.path): INSTALLS += target

CONFIG( debug, debug|release ) {
    # debug
    win32:LIBS += "$$PWD/../../bin/AdvancedDockingSystem_x64d.lib"
    # force relink
    PRE_TARGETDEPS += $$PWD/../../bin/AdvancedDockingSystem_x64d.lib
} else {
    # release
    win32:LIBS += "$$PWD/../../bin/AdvancedDockingSystem_x64.lib"
    # force relink
    PRE_TARGETDEPS += $$PWD/../../bin/AdvancedDockingSystem_x64.lib
}

DISTFILES +=

RESOURCES += \
    $$PWD/../../resources/editor/rm2.qrc

# Engine
INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

CONFIG( debug, debug|release ) {
    # debug
    LIBS += -L$$PWD/../../bin/ -lEngine_x64d
    # force relink
    PRE_TARGETDEPS += $$PWD/../../bin/Engine_x64d.lib

} else {
    # release
    LIBS += -L$$PWD/../../bin/ -lEngine_x64
    # force relink
    PRE_TARGETDEPS += $$PWD/../../bin/Engine_x64.lib
}

# visual leak detector
#INCLUDEPATH += $$(VLD_ROOT)/include
#DEPENDPATH += $$(VLD_ROOT)/include
#LIBS += -L$$(VLD_ROOT)/lib/Win64 -lvld

# Copy default editor settings
# copydata.commands = $(COPY_FILE) ..\..\resources\editor\save\MainWindow.dat ..\..\bin\MainWindow.dat &&
# copydata.commands += $(COPY_FILE) ..\..\resources\editor\save\Theme.dat ..\..\bin\Theme.dat &&
# copydata.commands += $(COPY_FILE) ..\..\resources\editor\save\Windows.dat ..\..\bin\Windows.dat
# first.depends = $(first) copydata
# export(first.depends)
# export(copydata.commands)
# QMAKE_EXTRA_TARGETS += first copydata

#message( "Executing qmake for editor..." )

