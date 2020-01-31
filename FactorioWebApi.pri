CONFIG += c++17 qt
QT += core network
DEFINES += CLIWEBAPI_LIBRARY QT_DEPRECATED_WARNINGS

SOURCES += \
    Factorio/core.cpp \
    QWebApi/manager.cpp \
    QWebApi/metaconnector.cpp \
    QWebApi/metaconnectorimpl.cpp \
    QWebApi/metatype.cpp \
    QWebApi/metatypeimpl.cpp

HEADERS += \
    Factorio/core.h \
    Factorio/factorio.h \
    Factorio/logintoken.h \
    Factorio/mods.h \
    QWebApi/connectorsetter.h \
    QWebApi/core.h \
    QWebApi/manager.h \
    QWebApi/metaconnector.h \
    QWebApi/metaconnectorimpl.h \
    QWebApi/metatype.h \
    QWebApi/metatypeimpl.h \
    QWebApi/result.h \
    QWebApi/WebApi_global.h
