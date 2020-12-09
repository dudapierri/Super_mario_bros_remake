TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        funcoesJogoMario.cpp \
    main.cpp



win32: LIBS += -L$$PWD/../../Desktop/SDL2-2.0.12/lib/x64/ -lSDL2

INCLUDEPATH += $$PWD/../../Desktop/SDL2-2.0.12/include
DEPENDPATH += $$PWD/../../Desktop/SDL2-2.0.12/include

win32: LIBS += -L$$PWD/../../Desktop/SDL2_mixer-2.0.4/lib/x64/ -lSDL2_mixer

INCLUDEPATH += $$PWD/../../Desktop/SDL2_mixer-2.0.4/include
DEPENDPATH += $$PWD/../../Desktop/SDL2_mixer-2.0.4/include


INCLUDEPATH += $$PWD/../../Desktop/SDL2_ttf-2.0.15/include
DEPENDPATH += $$PWD/../../Desktop/SDL2_ttf-2.0.15/include

HEADERS += \
    funcoesJogoMario.h \
    structsJogoMario.h
