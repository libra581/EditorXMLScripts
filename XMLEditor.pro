#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T13:00:30
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XMLEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        myMainWindow.cpp \
    myDialog.cpp \
    CustomTreeWidgetItem.cpp \
    myXmlHighlighter.cpp \
mycheckbox.cpp \
    myplaintextedit.cpp \
    myScene.cpp \
    myBlockScen.cpp \
    myBlockTask.cpp \
    myBlockDltCpSrt.cpp \
    myBlockCondition.cpp \
    myBlockFile.cpp

HEADERS += \
        myMainWindow.h \
    myDialog.h \
    CustomTreeWidgetItem.h \
    myXmlHighlighter.h \
    myplaintextedit.h\
mycheckbox.h \
    myScene.h \
    myBlockScen.h \
    myBlockTask.h \
    myBlockDltCpSrt.h \
    myBlockCondition.h \
    myBlockFile.h

FORMS += \
        myMainWindow.ui \
    myDialog.ui

RESOURCES += \
    img.qrc

DISTFILES +=
