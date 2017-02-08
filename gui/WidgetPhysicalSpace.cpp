/*
Copyright (C) 2017 Alexis Poncet

This file is part of ChaoticBilliard.

ChaoticBilliard is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
 * ChaoticBilliard
 * WidgetPhysicalSpace.cpp
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Take care of the widget on which the billiard and the trajectories
 * are drawn.
 */

#include "WidgetPhysicalSpace.h"

// Construct the widget for physical space.
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

    color.setHsv(0, 255, 224);
}

// Delete the widget by deleting the shape.
WidgetPhysicalSpace::~WidgetPhysicalSpace() {
    delete stroke;
}

// Return the minimum size of the widget.
QSize WidgetPhysicalSpace::minimumSizeHint() const {
	return QSize(PHYSPACE_SIZE, PHYSPACE_SIZE);
}

// Return the advised size of the widget.
QSize WidgetPhysicalSpace::sizeHint() const {
    return minimumSizeHint();
}

// Clear the history.
void WidgetPhysicalSpace::clearHistory() {
    pointHistory.clear();
    repaint();
}

// Change the billiard.
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

// Add a point to the trajectory.
void WidgetPhysicalSpace::addPoint(const double theta) {
	const double rad = PHYSPACE_SIZE / (2. * billiard->rhoMax());
    double x, y;
    std::tie(x, y) = billiard->xy(theta);
    // Minus sign on y because of the orientation used by Qt (up->down)
	pointHistory.append(QPointF(rad * x, -rad * y));
    repaint();
}

// Set the color of the pen.
void WidgetPhysicalSpace::setColor(const QColor &c) {
    color = c;
}

// Draw the billiard and the trajectory.
void WidgetPhysicalSpace::paintEvent(QPaintEvent *event) {
	(void) event; // Unused parameter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

	painter.translate(width() / 2, height() / 2);

	painter.setPen(QPen(color, 1));
	for(int i=0 ; i<pointHistory.size()-1 ; ++i){
		painter.drawLine(pointHistory[i], pointHistory[i+1]);
	}

	painter.setPen(QPen(QColor(64, 64, 64, 255), 3));
	painter.drawConvexPolygon(*stroke);
}
