QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameview.cpp \
    getscorewindow.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    qball.cpp \
    qitem.cpp \
    qmember.cpp \
    qtext.cpp \
    setnamewindow.cpp

HEADERS += \
    gameview.h \
    getscorewindow.h \
    global.h \
    mainwindow.h \
    qball.h \
    qitem.h \
    qmember.h \
    qtext.h \
    setnamewindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gfx.qrc
