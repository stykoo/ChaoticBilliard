#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class SpaceArea;
class ParamArea;

class MainWindow : public QWidget
{
    public:
		MainWindow();

    private:
		void nextTimestep();

		SpaceArea *spaceArea;
		ParamArea *paramArea;
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
