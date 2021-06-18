QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databaseconnection.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    piechart.cpp \
    register.cpp

HEADERS += \
    databaseconnection.h \
    login.h \
    mainwindow.h \
    piechart.h \
    register.h
    mainwindow.h

FORMS += \
    login.ui \
    mainwindow.ui \
    piechart.ui \
    register.ui

TRANSLATIONS += \
    financialSystem_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    nowyPrzedrostek/resources.qrc \
    res.qrc
