#-------------------------------------------------
#
# Project created by QtCreator 2011-08-15T16:44:30
#
#-------------------------------------------------

QT       += core gui \
            xml

TARGET = tools
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    productextenddlg.cpp \
    helpdlg.cpp \
    base64convertdlg.cpp \
    binaryfileeditdlg.cpp

HEADERS  += mainwindow.h \
    productextenddlg.h \
    helpdlg.h \
    base64convertdlg.h \
    binaryfileeditdlg.h

FORMS    += mainwindow.ui \
    productextenddlg.ui \
    helpdlg.ui \
    base64convertdlg.ui \
    binaryfileeditdlg.ui


win32:RC_FILE = $$PWD/$${TARGET}.rc
