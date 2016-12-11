#include "WidgetPhysicalSpace.h"

WidgetPhysicalSpace::WidgetPhysicalSpace(std::shared_ptr<AbstractBilliard> bil,
                                         QWidget *parent) : QWidget(parent) {
    setBackgroundRole(QPalette::Base);
	billiard = bil;

	const double rad = PHYSPACE_SIZE / (2. * billiard->rhoMax());
	QVector<QPointF> billPoints(NB_ANGULAR_DIVISIONS);
	for(int i=0 ; i < NB_ANGULAR_DIVISIONS ; ++i) {
		double theta = i * 2 * M_PI / NB_ANGULAR_DIVISIONS;
        double x, y;
        std::tie(x, y) = billiard->xy(theta);
		billPoints[i].setX(rad * x);
        // Minus sign on y because of the orientation used by Qt (up->down)
		billPoints[i].setY(- rad * y);
	}
	stroke = new QPolygonF(billPoints);
}

WidgetPhysicalSpace::~WidgetPhysicalSpace() {
    delete stroke;
}

QSize WidgetPhysicalSpace::minimumSizeHint() const {
	return QSize(PHYSPACE_SIZE, PHYSPACE_SIZE);
}

QSize WidgetPhysicalSpace::sizeHint() const {
    return minimumSizeHint();
}

void WidgetPhysicalSpace::clearHistory() {
    pointHistory.clear();
    repaint();
}

void WidgetPhysicalSpace::setBilliard(std::shared_ptr<AbstractBilliard> bil) {
	billiard.reset();
    delete stroke;

	billiard = bil;

	const double rad = PHYSPACE_SIZE / (2. * billiard->rhoMax());
	QVector<QPointF> billPoints(NB_ANGULAR_DIVISIONS);
	for(int i=0 ; i < NB_ANGULAR_DIVISIONS ; ++i) {
		double theta = i * 2 * M_PI / NB_ANGULAR_DIVISIONS;
        double x, y;
        std::tie(x, y) = billiard->xy(theta);
		billPoints[i].setX(rad * x);
		billPoints[i].setY(rad * y);
	}
	stroke = new QPolygonF(billPoints);
    clearHistory();
    repaint();
}

void WidgetPhysicalSpace::addPoint(const double theta) {
	const double rad = PHYSPACE_SIZE / (2. * billiard->rhoMax());
    double x, y;
    std::tie(x, y) = billiard->xy(theta);
    // Minus sign on y because of the orientation used by Qt (up->down)
	pointHistory.append(QPointF(rad * x, -rad * y));
    repaint();
}

void WidgetPhysicalSpace::paintEvent(QPaintEvent *event) {
	(void) event; // Unused parameter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

	painter.translate(width() / 2, height() / 2);

	painter.setPen(QPen(QColor(0, 0, 255, 255), 3));
	painter.drawConvexPolygon(*stroke);

	painter.setPen(QPen(QColor(255, 0, 0, 127), 1));
	for(int i=0 ; i<pointHistory.size()-1 ; ++i){
		painter.drawLine(pointHistory[i], pointHistory[i+1]);
	}
}
