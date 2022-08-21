TEMPLATE = app

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addquestiondialog.cpp \
    answerlistmodel.cpp \
    databasemanager.cpp \
    editableanswerlistmodel.cpp \
    editablequestiondialog.cpp \
    main.cpp \
    menuform.cpp \
    qt_stackwidget.cpp \
    question.cpp \
    questiontableform.cpp \
    questiontablemodel.cpp \
    readableanswerlistmodel.cpp \
    taglistmodel.cpp \
    tagsfilterdialog.cpp \
    testfilterdialog.cpp \
    testform.cpp \
    testpagemodel.cpp \
    testsessiondata.cpp \
    testwindowform.cpp \
    updatequestiondialog.cpp

HEADERS += \
    addquestiondialog.h \
    answer.h \
    answerlistmodel.h \
    databasemanager.h \
    editableanswerlistmodel.h \
    editablequestiondialog.h \
    menuform.h \
    qt_stackwidget.h \
    question.h \
    questiontableform.h \
    questiontablemodel.h \
    readableanswerlistmodel.h \
    tag.h \
    taglistmodel.h \
    tagsfilterdialog.h \
    testfilterdialog.h \
    testform.h \
    testpagemodel.h \
    testsessiondata.h \
    testwindowform.h \
    updatequestiondialog.h

FORMS += \
    editablequestiondialog.ui \
    menuform.ui \
    qt_stackwidget.ui \
    questiontableform.ui \
    tagsfilterdialog.ui \
    testfilterdialog.ui \
    testform.ui \
    testwindowform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = arm64-v8a

android {
    QMAKE_LFLAGS += -nostdlib++
}
