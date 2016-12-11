#include "WidgetPhysicalSpace.h"
#include "WidgetParametersSpace.h"
#include "MainWindow.h"
#include "../model/Billiards.h"

MainWindow::MainWindow() {
	billiard = std::make_shared<CircleBilliard>(
        DEFAULT_ANGLE * M_PI / 180.,
        AbstractBilliard::incidence2direction(DEFAULT_INCIDENCE * M_PI / 180.,
                                              DEFAULT_ANGLE * M_PI / 180.));
	widgetPhys = new WidgetPhysicalSpace(billiard);
    widgetPhys->addPoint(DEFAULT_ANGLE);

	widgetParams = new WidgetParametersSpace();
    widgetParams->addPoint(billiard->getPhaseCoos());

    QHBoxLayout *areasLayout = new QHBoxLayout;
	areasLayout->addWidget(widgetPhys);
	areasLayout->addWidget(widgetParams);

    createToolbar();
    createParametersGroup();
    createShapeGroup();

    quitButton = new QPushButton(tr("Exit"));

    QHBoxLayout *groupsLayout = new QHBoxLayout;
    groupsLayout->addWidget(parametersGroup, 0, Qt::AlignLeft);
    groupsLayout->addWidget(shapeGroup, 0, Qt::AlignLeft);

    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(areasLayout);
    mainLayout->addWidget(toolbar);
    mainLayout->addLayout(groupsLayout);
    mainLayout->addWidget(quitButton, 0, Qt::AlignRight);
    setLayout(mainLayout);

    setWindowTitle(tr("Billiard"));
}

void MainWindow::reloadParameters() {
    double theta = angleSpinBox->value() * M_PI / 180.;
    double beta = incidenceSpinBox->value() * M_PI / 180.;
    billiard->setPositionAndIncidence(theta, beta);

    widgetPhys->clearHistory();

    widgetParams->changeColor();
}

void MainWindow::resetBilliard() {
    double theta = angleSpinBox->value() * M_PI / 180.;
    double beta = incidenceSpinBox->value() * M_PI / 180.;

    billiard.reset(); 

    int id = shapeCombo->currentIndex();

    if (id == 0) {
        billiard = std::make_shared<CircleBilliard>(
            theta, AbstractBilliard::incidence2direction(beta, theta));
    } else if (id == 1) {
        billiard = std::make_shared<EllipseBilliard>(
            shapeEllipseSpinBox->value(),
            theta, AbstractBilliard::incidence2direction(beta, theta));
    } else if (id == 2) {
        billiard = std::make_shared<DeformedCircleBilliard>(
            shapeDefCircleSpinBox->value(),
            theta, AbstractBilliard::incidence2direction(beta, theta));
    }

    widgetPhys->setBilliard(billiard);
    widgetPhys->addPoint(theta);

    widgetParams->clearImage();
    widgetParams->changeColor();
    widgetParams->addPoint(billiard->getPhaseCoos());
}

void MainWindow::forward() {
    billiard->updatePositionAndDirection();
    widgetPhys->addPoint(billiard->getTheta());
    widgetParams->addPoint(billiard->getPhaseCoos());
}

void MainWindow::manageShapeGroup(int selectedIndex) {
    if (selectedIndex == 0) {
        shapeEllipseLabel->hide();
        shapeEllipseSpinBox->hide();
        shapeDefCircleLabel->hide();
        shapeDefCircleSpinBox->hide();
    } else if (selectedIndex == 1) {
        shapeEllipseLabel->show();
        shapeEllipseSpinBox->show();
        shapeDefCircleLabel->hide();
        shapeDefCircleSpinBox->hide();
    } else if (selectedIndex == 2) {
        shapeEllipseLabel->hide();
        shapeEllipseSpinBox->hide();
        shapeDefCircleLabel->show();
        shapeDefCircleSpinBox->show();
    }
}

void MainWindow::createToolbar() {
    toolbar = new QToolBar;
    playAction = toolbar->addAction(
        style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"));
    pauseAction = toolbar->addAction(
        style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"));
    forwardAction = toolbar->addAction(
        style()->standardIcon(QStyle::SP_MediaSkipForward),
                              tr("Next iteration"));
    reloadAction = toolbar->addAction(
        style()->standardIcon(QStyle::SP_DialogApplyButton),
                              tr("Reload parameters"));
    resetAction = toolbar->addAction(
        style()->standardIcon(QStyle::SP_BrowserReload),
                              tr("Change shape / Reset"));

    connect(forwardAction, SIGNAL(triggered()), this, SLOT(forward()));
    connect(reloadAction, SIGNAL(triggered()), this, SLOT(reloadParameters()));
    connect(resetAction, SIGNAL(triggered()), this, SLOT(resetBilliard()));
}

void MainWindow::createParametersGroup() {
    parametersGroup = new QGroupBox(tr("Parameters"));

    angleSpinBox = new QDoubleSpinBox();
    angleSpinBox->setRange(-180., 180.);
    angleSpinBox->setSingleStep(10.);
    angleSpinBox->setValue(DEFAULT_ANGLE);
    angleSpinBox->setSuffix("°");
    angleLabel = new QLabel(tr("Initial angle:"));
    angleLabel->setBuddy(angleSpinBox);

    incidenceSpinBox = new QDoubleSpinBox();
    incidenceSpinBox->setRange(-90., 90.);
    incidenceSpinBox->setSingleStep(5.);
    incidenceSpinBox->setValue(DEFAULT_INCIDENCE);
    incidenceSpinBox->setSuffix("°");
    incidenceLabel = new QLabel(tr("Initial incidence angle:"));
    incidenceLabel->setBuddy(incidenceSpinBox);

    speedSpinBox = new QDoubleSpinBox();
    speedSpinBox->setRange(0.1, 100.);
    speedSpinBox->setSingleStep(DEFAULT_SPEED);
    speedSpinBox->setValue(2.);
    speedLabel = new QLabel(tr("Speed (1/second):"));
    speedLabel->setBuddy(speedSpinBox);

    QGridLayout *groupLayout = new QGridLayout;
    groupLayout->addWidget(angleLabel, 0, 0);
    groupLayout->addWidget(angleSpinBox, 0, 1, 1, 1, Qt::AlignLeft);
    groupLayout->addWidget(incidenceLabel, 1, 0);
    groupLayout->addWidget(incidenceSpinBox, 1, 1, 1, 1, Qt::AlignLeft);
    groupLayout->addWidget(speedLabel, 2, 0);
    groupLayout->addWidget(speedSpinBox, 2, 1, 1, 1, Qt::AlignLeft);
    groupLayout->setAlignment(Qt::AlignTop);
    parametersGroup->setLayout(groupLayout);
}

void MainWindow::createShapeGroup() {
    shapeGroup = new QGroupBox(tr("Shape"));

    shapeCombo = new QComboBox;
    shapeCombo->addItem(tr("Circle"));
    shapeCombo->addItem(tr("Ellipse"));
    shapeCombo->addItem(tr("Deformed circle"));
    shapeCombo->setCurrentIndex(0);

    shapeEllipseSpinBox = new QDoubleSpinBox();
    shapeEllipseSpinBox->setRange(0., 0.99);
    shapeEllipseSpinBox->setSingleStep(0.05);
    shapeEllipseSpinBox->setValue(0.1);
    shapeEllipseLabel = new QLabel(tr("Excentricity:"));
    angleLabel->setBuddy(angleSpinBox);

    shapeDefCircleSpinBox = new QDoubleSpinBox();
    shapeDefCircleSpinBox->setRange(0., 0.49);
    shapeDefCircleSpinBox->setSingleStep(0.05);
    shapeDefCircleSpinBox->setValue(0.1);
    shapeDefCircleLabel = new QLabel(tr("Deformation:"));
    shapeDefCircleLabel->setBuddy(shapeDefCircleSpinBox);
    shapeDefCircleLabel->hide();
    shapeDefCircleSpinBox->hide();

    QHBoxLayout *shapeEllipseLayout = new QHBoxLayout;
    shapeEllipseLayout->addWidget(shapeEllipseLabel, 0, Qt::AlignLeft);
    shapeEllipseLayout->addWidget(shapeEllipseSpinBox, 0, Qt::AlignLeft);
    QHBoxLayout *shapeDefCircleLayout = new QHBoxLayout;
    shapeDefCircleLayout->addWidget(shapeDefCircleLabel, 0, Qt::AlignLeft);
    shapeDefCircleLayout->addWidget(shapeDefCircleSpinBox, 0, Qt::AlignLeft);

    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->addWidget(shapeCombo);
    groupLayout->addLayout(shapeEllipseLayout);
    groupLayout->addLayout(shapeDefCircleLayout);
    groupLayout->setAlignment(Qt::AlignTop);
    shapeGroup->setLayout(groupLayout);

    connect(shapeCombo, SIGNAL(currentIndexChanged(int)), this,
            SLOT(manageShapeGroup(int)));
}
