#include "WidgetPhysicalSpace.h"
#include "WidgetParametersSpace.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
	//DeformedCircle shapeFun(0.5);
	Ellipse shapeFun(0.5);
	widgetPhys = new WidgetPhysicalSpace(shapeFun);
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

	widgetPhys->addPoint(0.);
	widgetPhys->addPoint(M_PI/3.);
	widgetPhys->addPoint(6.*M_PI/5.);
}

