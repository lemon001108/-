QT       += core gui
QT += sql
QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doct.cpp \
    doctor_sa.cpp \
    govern.cpp \
    login.cpp \
    main.cpp \
    mainwidget.cpp \
    medicine.cpp \
    medicine_sa.cpp \
    nurse.cpp \
    nurse_sa.cpp \
    office.cpp \
    office_sa.cpp \
    patience.cpp \
    patience_sa.cpp \
    primary.cpp

HEADERS += \
    doct.h \
    doctor_sa.h \
    govern.h \
    login.h \
    mainwidget.h \
    medicine.h \
    medicine_sa.h \
    nurse.h \
    nurse_sa.h \
    office.h \
    office_sa.h \
    patience.h \
    patience_sa.h \
    primary.h

FORMS += \
    doct.ui \
    doctor_sa.ui \
    govern.ui \
    login.ui \
    mainwidget.ui \
    medicine.ui \
    medicine_sa.ui \
    nurse.ui \
    nurse_sa.ui \
    office.ui \
    office_sa.ui \
    patience.ui \
    patience_sa.ui \
    primary.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    login_back.qrc
