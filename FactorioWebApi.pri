CONFIG += c++17 qt
QT += core network
DEFINES += CLIWEBAPI_LIBRARY QT_DEPRECATED_WARNINGS

SOURCES += \
    FactorioWebApi/Factorio/core.cpp \
    FactorioWebApi/QWebApi/manager.cpp \
    FactorioWebApi/QWebApi/metaconnector.cpp \
    FactorioWebApi/QWebApi/metaconnectorimpl.cpp \
    FactorioWebApi/QWebApi/metatype.cpp \
    FactorioWebApi/QWebApi/metatypeimpl.cpp

HEADERS += \
    FactorioWebApi/Factorio/core.h \
    FactorioWebApi/Factorio/factorio.h \
    FactorioWebApi/Factorio/logintoken.h \
    FactorioWebApi/Factorio/mods.h \
    FactorioWebApi/QWebApi/connectorsetter.h \
    FactorioWebApi/QWebApi/core.h \
    FactorioWebApi/QWebApi/manager.h \
    FactorioWebApi/QWebApi/metaconnector.h \
    FactorioWebApi/QWebApi/metaconnectorimpl.h \
    FactorioWebApi/QWebApi/metatype.h \
    FactorioWebApi/QWebApi/metatypeimpl.h \
    FactorioWebApi/QWebApi/result.h \
    FactorioWebApi/QWebApi/WebApi_global.h
