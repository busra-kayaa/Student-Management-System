QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    derskaydi.cpp \
    dersler.cpp \
    main.cpp \
    mainwindow.cpp \
    notlar.cpp \
    ogrenci.cpp

HEADERS += \
    derskaydi.h \
    dersler.h \
    mainwindow.h \
    notlar.h \
    ogrenci.h

FORMS += \
    derskaydi.ui \
    dersler.ui \
    mainwindow.ui \
    notlar.ui \
    ogrenci.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
