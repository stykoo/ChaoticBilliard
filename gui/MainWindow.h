#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class WidgetPhysicalSpace;
class WidgetParametersSpace;

class MainWindow : public QWidget
{
    public:
		MainWindow();

    private:
		void nextTimestep();

		WidgetPhysicalSpace *widgetPhys;
		WidgetParametersSpace *widgetParams;
		QPushButton *reinitButton;
		QPushButton *startButton;
		QPushButton *paramButton;
		QPushButton *shapeButton;
		QPushButton *quitButton;

		int currentTime;
		double currentTheta;
		double currentAlpha;
};

#endif
