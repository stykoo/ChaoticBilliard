# Copyright (C) 2017 Alexis Poncet
#
# This file is part of ChaoticBilliard
#
# ChaoticBilliard is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Foobar is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ChaoticBilliard.  If not, see <http://www.gnu.org/licenses/>.

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
           model/Vector2d.h \
           model/routines.h
SOURCES += main.cpp \
           gui/MainWindow.cpp \
           gui/WidgetParametersSpace.cpp \
           gui/WidgetPhysicalSpace.cpp \
           model/AbstractBilliard.cpp \
           model/CircleBilliard.cpp \
           model/DeformedCircleBilliard.cpp \
           model/EllipseBilliard.cpp \
           model/Vector2d.cpp \
           model/routines.cpp
