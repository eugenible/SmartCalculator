QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../calcModel/credit_calc.cpp \
    ../../calcModel/credit_data.cpp \
    ../../calcModel/plot_builder.cpp \
    ../../calcModel/plot_data.cpp \
    credit.cpp \
    main.cpp \
    mainwindow.cpp \
    ../../controller/controller.cpp \
    ../../calcModel/request.cpp \
    ../../calcModel/calculator.cpp \
    ../../calcModel/calc_processor.cpp \
    plotter.cpp \
    qcustomplot.cpp

HEADERS += \
    ../../calcModel/credit_calc.h \
    ../../calcModel/credit_data.h \
    ../../calcModel/plot_builder.h \
    ../../calcModel/plot_data.h \
    plotter.h \
    credit.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    mainwindow.ui \
    plotter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
