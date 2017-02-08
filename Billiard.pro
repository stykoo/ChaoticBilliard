TEMPLATE = app
QT += gui declarative
TARGET = Billiard
INCLUDEPATH += .

# Input
HEADERS += gui/MainWindow.h \
           gui/WidgetParametersSpace.h \
           gui/WidgetPhysicalSpace.h \
           model/AbstractBilliard.h \
           model/CircleBilliard.h \
           model/DeformedCircleBilliard.h \
           model/EllipseBilliard.h \
           model/routines.h
SOURCES += main.cpp \
           gui/MainWindow.cpp \
           gui/WidgetParametersSpace.cpp \
           gui/WidgetPhysicalSpace.cpp \
           model/AbstractBilliard.cpp \
           model/CircleBilliard.cpp \
           model/DeformedCircleBilliard.cpp \
           model/EllipseBilliard.cpp \
           model/routines.cpp
