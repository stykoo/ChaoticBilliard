#include "SpaceArea.h"
#include "ParamArea.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
	DeformedCircle shapeFun(0.5);
	spaceArea = new SpaceArea(shapeFun);
	paramArea = new ParamArea();

    QHBoxLayout *areasLayout = new QHBoxLayout;
	areasLayout->addWidget(spaceArea);
	areasLayout->addWidget(paramArea);

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

	spaceArea->addPoint(0.);
	spaceArea->addPoint(M_PI/3.);
	spaceArea->addPoint(6.*M_PI/5.);
}



