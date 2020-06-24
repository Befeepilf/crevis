TEMPLATE = app

TARGET = crevis
MOC_DIR = $$PWD/build/moc/
OBJECTS_DIR = $$PWD/build/objects/
DESTDIR = $$PWD/build/

INCLUDEPATH += $$PWD/include/

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


HEADERS += include/gui/canvas.hpp \
           include/gui/window.hpp \
           include/renderer/mesh.hpp \
           include/renderer/renderer.hpp \
           include/renderer/triangle.hpp \
           include/renderer/vector/vector.hpp \
           include/renderer/vector/vector3d.hpp

SOURCES += src/main.cpp \
           src/gui/canvas.cpp \
           src/gui/window.cpp \
           src/renderer/mesh.cpp \
           src/renderer/renderer.cpp \
           src/renderer/triangle.cpp \
           src/renderer/vector/vector.cpp \
           src/renderer/vector/vector3d.cpp
