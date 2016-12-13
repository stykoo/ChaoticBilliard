#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <memory>
#include "../model/Billiards.h"

#define DEFAULT_ANGLE 0.
#define DEFAULT_INCIDENCE 45.
#define DEFAULT_SPEED 2.

class WidgetPhysicalSpace;
class WidgetParametersSpace;

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
		MainWindow();

    public slots:
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
