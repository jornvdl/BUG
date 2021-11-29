TEMPLATE = app
TARGET = bug-configurator

QT += qml quick bluetooth widgets
CONFIG += c++11 config qml_debug static

HEADERS += \
    connectionhandler.h \
    deviceinfo.h \
    devicefinder.h \
    devicehandler.h \
    bluetoothbaseclass.h

SOURCES += main.cpp \
    connectionhandler.cpp \
    deviceinfo.cpp \
    devicefinder.cpp \
    devicehandler.cpp \
    bluetoothbaseclass.cpp

RESOURCES += qml.qrc \
    images.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

target.path = /user/Documents/GitHub/BUG/Configurator (PC)/builds
INSTALLS += target
