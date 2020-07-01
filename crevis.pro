TEMPLATE = app

TARGET = crevis
MOC_DIR = $$PWD/build/moc/
OBJECTS_DIR = $$PWD/build/objects/
DESTDIR = $$PWD/build/

INCLUDEPATH += $$PWD/include/

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


HEADERS += include/file/file.hpp \
           include/file/fileLoader.hpp \
           include/file/parsers/objParser.hpp \
           include/gui/canvas.hpp \
           include/gui/meshProperties.hpp \
           include/gui/meshesList.hpp \
           include/gui/meshesListItem.hpp \
           include/gui/window.hpp \
           include/math/trig.hpp \
           include/renderer/mesh.hpp \
           include/renderer/renderer.hpp \
           include/renderer/triangle.hpp \
           include/renderer/vector/vec.hpp \
           include/renderer/vector/vec2d.hpp \
           include/renderer/vector/vec3d.hpp

SOURCES += src/file/file.cpp \
           src/file/fileLoader.cpp \
           src/file/parsers/objParser.cpp \
           src/main.cpp \
           src/gui/canvas.cpp \
           src/gui/meshProperties.cpp \
           src/gui/meshesList.cpp \
           src/gui/meshesListItem.cpp \
           src/gui/window.cpp \
           src/math/trig.cpp \
           src/renderer/mesh.cpp \
           src/renderer/renderer.cpp \
           src/renderer/triangle.cpp \
           src/renderer/vector/vec.cpp \
           src/renderer/vector/vec2d.cpp \
           src/renderer/vector/vec3d.cpp
