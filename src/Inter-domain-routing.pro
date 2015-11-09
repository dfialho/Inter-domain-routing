#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T08:33:40
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Inter-domain-routing
TEMPLATE = app


SOURCES += \
    backend/LinkPriorityQueue.cpp \
    backend/Network.cpp \
    backend/NetworkIdGenerator.cpp \
    backend/StatsTable.cpp \
    main.cpp \
	frontend/qcustomplot.cpp \
    frontend/statsdialog.cpp

HEADERS  += \
	backend/Link.h \
    backend/LinkPriorityQueue.h \
    backend/Network.h \
    backend/NetworkIdGenerator.h \
    backend/Node.h \
    backend/StatsTable.h \
	frontend/qcustomplot.h \
    frontend/statsdialog.h

FORMS    += \
    frontend/statsdialog.ui
