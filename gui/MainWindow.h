/*
Copyright (C) 2017 Alexis Poncet

This file is part of ChaoticBilliard.

ChaoticBilliard is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <memory>
#include "../model/Billiards.h"

#define DEFAULT_ANGLE 0.
#define DEFAULT_INCIDENCE 45.
#define DEFAULT_SPEED 2

class WidgetPhysicalSpace;
class WidgetParametersSpace;

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
		MainWindow();

    public slots:
        void setParameters(double theta, double beta);
        void reloadParameters();
        void resetBilliard();
        void updateSpeed();
        void play();
        void pause();
        void forward();
        void manageShapeGroup(int selectedIndex);

    private:
        void createToolbarGroup();
        void createParametersGroup();
        void createShapeGroup();
		void nextTimestep();
        void updateSpeedLabel();
        void updateCurrentStateLabel();

		WidgetPhysicalSpace *widgetPhys;
		WidgetParametersSpace *widgetParams;

        QHBoxLayout *toolbarLayout;
        QToolBar *toolbar;
        QAction *playAction;
        QAction *pauseAction;
        QAction *forwardAction;
        QAction *resetAction;
        QSlider *speedSlider;
        QLabel *speedLabel;
        QLabel *currentStateLabel;

        QGroupBox *parametersGroup;
        QLabel *angleLabel;
        QLabel *incidenceLabel;
        QDoubleSpinBox *angleSpinBox;
        QDoubleSpinBox *incidenceSpinBox;
        QPushButton *parametersButton;

        QGroupBox *shapeGroup;
        QComboBox *shapeCombo;
        QLabel *shapeEllipseLabel;
        QLabel *shapeDefCircleLabel;
        QDoubleSpinBox *shapeEllipseSpinBox;
        QDoubleSpinBox *shapeDefCircleSpinBox;
        QPushButton *shapeButton;

		QPushButton *quitButton;

        QTimer *nextTimer;
        std::shared_ptr<AbstractBilliard> billiard;
        unsigned int iter = 0;
};

#endif
