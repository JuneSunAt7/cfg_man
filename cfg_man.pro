QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires(qtConfig(treeview))
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpu_usage_graph.cpp \
    filesystem_view.cpp \
    get_data_of_pc.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    cpu_usage_graph.h \
    filesystem_view.h \
    get_data_of_pc.h \
    widget.h

FORMS += \
    widget.ui

LIBS += -ladvapi32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
