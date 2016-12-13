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
        void forward();
        void manageShapeGroup(int selectedIndex);

    private:
        void createToolbar();
        void createParametersGroup();
        void createShapeGroup();
		void nextTimestep();
        void updateCurrentStateLabel();

		WidgetPhysicalSpace *widgetPhys;
		WidgetParametersSpace *widgetParams;

        QLabel *currentStateLabel;

        QToolBar *toolbar;
        QAction *playAction;
        QAction *pauseAction;
        QAction *forwardAction;
        QAction *resetAction;

        QGroupBox *parametersGroup;
        QLabel *angleLabel;
        QLabel *incidenceLabel;
        QLabel *speedLabel;
        QDoubleSpinBox *angleSpinBox;
        QDoubleSpinBox *incidenceSpinBox;
        QDoubleSpinBox *speedSpinBox;
        QPushButton *parametersButton;

        QGroupBox *shapeGroup;
        QComboBox *shapeCombo;
        QLabel *shapeEllipseLabel;
        QLabel *shapeDefCircleLabel;
        QDoubleSpinBox *shapeEllipseSpinBox;
        QDoubleSpinBox *shapeDefCircleSpinBox;
        QPushButton *shapeButton;

		QPushButton *quitButton;

        std::shared_ptr<AbstractBilliard> billiard;
        unsigned int iter = 0;
};

#endif
