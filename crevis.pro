TEMPLATE = app

TARGET = crevis
MOC_DIR = $$PWD/build/moc/
OBJECTS_DIR = $$PWD/build/objects/
DESTDIR = $$PWD/build/

INCLUDEPATH += $$PWD/include/

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


HEADERS += include/gui/canvas.hpp \
           include/gui/meshesList.hpp \
           include/gui/meshesListItem.hpp \
           include/gui/window.hpp \
           include/renderer/mesh.hpp \
           include/renderer/renderer.hpp \
           include/renderer/triangle.hpp \
           include/renderer/vector/vec.hpp \
           include/renderer/vector/vec2d.hpp \
           include/renderer/vector/vec3d.hpp

SOURCES += src/main.cpp \
           src/gui/canvas.cpp \
           src/gui/meshesList.cpp \
           src/gui/meshesListItem.cpp \
           src/gui/window.cpp \
           src/renderer/mesh.cpp \
           src/renderer/renderer.cpp \
           src/renderer/triangle.cpp \
           src/renderer/vector/vec.cpp \
           src/renderer/vector/vec2d.cpp \
           src/renderer/vector/vec3d.cpp
