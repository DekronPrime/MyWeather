QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addlocation.cpp \
    anotherday.cpp \
    changeimage.cpp \
    datadb.cpp \
    dbmanager.cpp \
    inputdatawindow.cpp \
    main.cpp \
    mainwindow.cpp \
    modifydatawindow.cpp \
    showdatawindow.cpp \
    sortorder.cpp \
    sqlitedbmanager.cpp

HEADERS += \
    addlocation.h \
    anotherday.h \
    changeimage.h \
    datadb.h \
    dbmanager.h \
    inputdatawindow.h \
    mainwindow.h \
    modifydatawindow.h \
    showdatawindow.h \
    sortorder.h \
    sqlitedbmanager.h

FORMS += \
    addlocation.ui \
    anotherday.ui \
    inputdatawindow.ui \
    mainwindow.ui \
    modifydatawindow.ui \
    showdatawindow.ui

win32:RC_FILE = projecticon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
