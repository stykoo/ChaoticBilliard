#include "SpaceArea.h"

SpaceArea::SpaceArea(const ShapeFunction &fun, QWidget *parent) : QWidget(parent) {
    setBackgroundRole(QPalette::Base);
	shapeFun = fun.clone();

	const double rad = UNIT_SIZE/2.0;
	QVector<QPointF> billPoints(NB_ANGULAR_DIVISIONS);
	for(int i=0 ; i < NB_ANGULAR_DIVISIONS ; i++){
		double theta = i*2*M_PI/NB_ANGULAR_DIVISIONS;
		billPoints[i].setX(rad*(*shapeFun)(theta)*std::cos(theta));
		billPoints[i].setY(rad*(*shapeFun)(theta)*std::sin(theta));
	}
	billiard = new QPolygonF(billPoints);
}

SpaceArea::~SpaceArea(){
	delete shapeFun;
	delete billiard;
}

QSize SpaceArea::minimumSizeHint() const
{
	return QSize(UNIT_SIZE*shapeFun->max(), UNIT_SIZE*shapeFun->max());
}

QSize SpaceArea::sizeHint() const
{
	return QSize(UNIT_SIZE*shapeFun->max(), UNIT_SIZE*shapeFun->max());
}

void SpaceArea::setShapeFunction(const ShapeFunction &fun){
	delete shapeFun;
	delete billiard;

	shapeFun = fun.clone();

	const double rad = UNIT_SIZE/2.0;
	QVector<QPointF> billPoints(NB_ANGULAR_DIVISIONS);
	for(int i=0 ; i < NB_ANGULAR_DIVISIONS ; i++){
		double theta = i*2*M_PI/NB_ANGULAR_DIVISIONS;
		billPoints[i].setX(rad*(*shapeFun)(theta)*std::cos(theta));
		billPoints[i].setY(rad*(*shapeFun)(theta)*std::sin(theta));
	}
	billiard = new QPolygonF(billPoints);
}

void SpaceArea::addPoint(const double theta){
	const double rad = UNIT_SIZE/2.0;
	const double x = rad*(*shapeFun)(theta)*std::cos(theta);
	const double y = rad*(*shapeFun)(theta)*std::sin(theta);
	pointHistory.prepend(QPointF(x,y));
}

void SpaceArea::paintEvent(QPaintEvent *event)
{
	(void) event; // Unused parameter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

	painter.translate(width()/ 2, height()/ 2);

	painter.setPen(QPen(QColor(0, 0, 255, 255), 3));
	painter.drawConvexPolygon(*billiard);

	painter.setPen(QPen(QColor(255, 0, 0, 127), 1));
	for(int i=0 ; i<pointHistory.size()-1 ; i++){
		painter.drawLine(pointHistory[i], pointHistory[i+1]);
	}
}

