QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../back/affin.c \
    ../back/data_clear.c \
    ../back/matrix.c \
    ../back/parser.c \
    gifimage/3rdParty/giflib/dgif_lib.c \
    gifimage/3rdParty/giflib/egif_lib.c \
    gifimage/3rdParty/giflib/gif_err.c \
    gifimage/3rdParty/giflib/gif_font.c \
    gifimage/3rdParty/giflib/gif_hash.c \
    gifimage/3rdParty/giflib/gifalloc.c \
    gifimage/3rdParty/giflib/quantize.c \
    gifimage/gifimage/qgifimage.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../back/3DViewer.h \
    ../back/parser.h \
    gifimage/3rdParty/giflib/gif_hash.h \
    gifimage/3rdParty/giflib/gif_lib.h \
    gifimage/3rdParty/giflib/gif_lib_private.h \
    gifimage/gifimage/qgifglobal.h \
    gifimage/gifimage/qgifimage.h \
    gifimage/gifimage/qgifimage_p.h \
    glwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    gifimage/giimage/qtgifimage.pri

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
