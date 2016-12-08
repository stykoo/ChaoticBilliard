#include "WidgetPhysicalSpace.h"
#include "WidgetParametersSpace.h"
#include "MainWindow.h"
#include "../model/Billiards.h"

MainWindow::MainWindow()
{
	CircleBilliard billiard(0.5);
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

    double theta = 0, alpha = 5. * M_PI / 6. + 1e-4;
	widgetPhys->addPoint(theta);
    for (int i = 0 ; i < 1000 ; ++i) {
        theta = billiard.nextPosition(theta, alpha);
        alpha = billiard.nextDirection(alpha, theta);
        widgetPhys->addPoint(theta);
    }
}

