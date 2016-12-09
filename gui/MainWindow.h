#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <memory>
#include "../model/Billiards.h"

class WidgetPhysicalSpace;
class WidgetParametersSpace;

class MainWindow : public QWidget
{
    public:
		MainWindow();
        ~MainWindow();

    private:
		void nextTimestep();

		WidgetPhysicalSpace *widgetPhys;
		WidgetParametersSpace *widgetParams;
		QPushButton *reinitButton;
		QPushButton *startButton;
		QPushButton *paramButton;
		QPushButton *shapeButton;
		QPushButton *quitButton;

        std::shared_ptr<AbstractBilliard> billiard;
};

#endif
