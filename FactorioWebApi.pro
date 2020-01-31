TEMPLATE = lib
include(FactorioWebApi.pri)
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
