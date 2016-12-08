#include "WidgetPhysicalSpace.h"

WidgetPhysicalSpace::WidgetPhysicalSpace(const AbstractBilliard &bil,
                                         QWidget *parent) : QWidget(parent) {
    setBackgroundRole(QPalette::Base);
	billiard = bil.clone();

	const double rad = UNIT_SIZE/2.0;
	QVector<QPointF> billPoints(NB_ANGULAR_DIVISIONS);
	for(int i=0 ; i < NB_ANGULAR_DIVISIONS ; i++){
		double theta = i*2*M_PI/NB_ANGULAR_DIVISIONS;
		billPoints[i].setX(rad*(*billiard)(theta)*std::cos(theta));
		billPoints[i].setY(rad*(*billiard)(theta)*std::sin(theta));
	}
	stroke = new QPolygonF(billPoints);
}

WidgetPhysicalSpace::~WidgetPhysicalSpace(){
	delete billiard;
    delete stroke;
}

QSize WidgetPhysicalSpace::minimumSizeHint() const
{
	return QSize(UNIT_SIZE*billiard->max(), UNIT_SIZE*billiard->max());
}

QSize WidgetPhysicalSpace::sizeHint() const
{
    return minimumSizeHint();
}

void WidgetPhysicalSpace::setBilliard(const AbstractBilliard &bil){
	delete billiard;
    delete stroke;

	billiard = bil.clone();

	const double rad = UNIT_SIZE/2.0;
	QVector<QPointF> billPoints(NB_ANGULAR_DIVISIONS);
	for(int i=0 ; i < NB_ANGULAR_DIVISIONS ; i++){
		double theta = i*2*M_PI/NB_ANGULAR_DIVISIONS;
		billPoints[i].setX(rad*(*billiard)(theta)*std::cos(theta));
		billPoints[i].setY(rad*(*billiard)(theta)*std::sin(theta));
	}
	stroke = new QPolygonF(billPoints);
}

void WidgetPhysicalSpace::addPoint(const double theta){
	const double rad = UNIT_SIZE/2.0;
	const double x = rad*(*billiard)(theta)*std::cos(theta);
	const double y = rad*(*billiard)(theta)*std::sin(theta);
	pointHistory.prepend(QPointF(x,y));
}

void WidgetPhysicalSpace::paintEvent(QPaintEvent *event)
{
	(void) event; // Unused parameter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

	painter.translate(width()/ 2, height()/ 2);

	painter.setPen(QPen(QColor(0, 0, 255, 255), 3));
	painter.drawConvexPolygon(*stroke);

	painter.setPen(QPen(QColor(255, 0, 0, 127), 1));
	for(int i=0 ; i<pointHistory.size()-1 ; i++){
		painter.drawLine(pointHistory[i], pointHistory[i+1]);
	}
}

