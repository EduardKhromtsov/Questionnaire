QT       += core gui sql printsupport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartform.cpp \
    databaseform.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    questionnaireform.cpp

HEADERS += \
    chartform.h \
    databaseform.h \
    loginform.h \
    mainwindow.h \
    questionnaireform.h

FORMS += \
    chartform.ui \
    databaseform.ui \
    loginform.ui \
    mainwindow.ui \
    questionnaireform.ui

win32:RC_FILE = icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
