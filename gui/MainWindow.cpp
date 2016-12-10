#include "WidgetPhysicalSpace.h"
#include "WidgetParametersSpace.h"
#include "MainWindow.h"
#include "../model/Billiards.h"

MainWindow::MainWindow()
{
    const double theta0 = 0., alpha0 = 5 * M_PI / 6.;
    const double excentricity = 0.86602540378443864676; 
    const int nbPoints = 100;
	billiard = std::make_shared<EllipseBilliard>(excentricity, theta0, alpha0);
	widgetPhys = new WidgetPhysicalSpace(billiard);
	widgetParams = new WidgetParametersSpace();

    QHBoxLayout *areasLayout = new QHBoxLayout;
	areasLayout->addWidget(widgetPhys);
	areasLayout->addWidget(widgetParams);

    reinitButton = new QPushButton(tr("Reinit"));
    startButton = new QPushButton(tr("Start / Stop"));
    paramButton = new QPushButton(tr("Parameters"));
    shapeButton = new QPushButton(tr("Shape"));
    quitButton = new QPushButton(tr("Quit"));
    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(reinitButton);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addWidget(paramButton);
    buttonsLayout->addWidget(shapeButton);
    buttonsLayout->addWidget(quitButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(areasLayout);
	mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Billiard"));

    widgetPhys->addPoint(theta0);
    widgetParams->addPoint(billiard->getPhaseCoos());
    for (int i = 0 ; i < nbPoints ; ++i) {
        billiard->updatePositionAndDirection();
        widgetPhys->addPoint(billiard->getTheta());
        widgetParams->addPoint(billiard->getPhaseCoos());
    }
}

MainWindow::~MainWindow() {
    delete widgetPhys; 
    delete widgetParams; 
    delete reinitButton; 
    delete startButton; 
    delete paramButton; 
    delete shapeButton; 
    delete quitButton; 
}

