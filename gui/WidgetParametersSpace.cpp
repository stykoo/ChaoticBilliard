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

#include "WidgetParametersSpace.h"

WidgetParametersSpace::WidgetParametersSpace(const int pointsize,
        const double xMin, const double xMax,
        const double yMin, const double yMax,
        QWidget *parent) : QWidget(parent), pointsize(pointsize),
        xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {
    setBackgroundRole(QPalette::Base);

	pixels = new QImage(PARAMSPACE_WIDTH, PARAMSPACE_HEIGHT,
                        QImage::Format_RGB32);
    clearImage();
    color.setHsv(0, 255, 224);

    setCursor(Qt::CrossCursor);
}

WidgetParametersSpace::~WidgetParametersSpace() {
	delete pixels;
}

QSize WidgetParametersSpace::minimumSizeHint() const
{
	return QSize(PARAMSPACE_WIDTH, PARAMSPACE_HEIGHT);
}

QSize WidgetParametersSpace::sizeHint() const
{
	return minimumSizeHint();
}

void WidgetParametersSpace::addPoint(const std::tuple<double, double> coos) {
    int x_screen = PARAMSPACE_WIDTH * \
        (std::get<0>(coos) - xMin) / (xMax - xMin);
    // Minus sign on y because of the orientation used by Qt (up->down)
    int y_screen = PARAMSPACE_HEIGHT * \
        (-std::get<1>(coos) - yMin) / (yMax - yMin);

    int dx1 = (pointsize - 1) / 2, dx2 = pointsize / 2;
    for (int i = x_screen - dx1 ; i <= x_screen + dx2 ; ++i) {
        for (int j = y_screen - dx1 ; j <= y_screen + dx2 ; ++j) {
            pixels->setPixelColor((i+PARAMSPACE_WIDTH)%PARAMSPACE_WIDTH,
                                  (j+PARAMSPACE_HEIGHT)%PARAMSPACE_HEIGHT,
                                  color);
        }
    }
    repaint();
}

void WidgetParametersSpace::setColor(const QColor &c) {
    color = c;
}

void WidgetParametersSpace::clearImage() {
	pixels->fill(Qt::white);
}

void WidgetParametersSpace::mouseReleaseEvent(QMouseEvent *event) {
    int x = event->pos().x() - (width()-PARAMSPACE_WIDTH)/2.;
    int y = event->pos().y() - (height()-PARAMSPACE_HEIGHT)/2.;

    if (x >= 0 && y >= 0 && x < PARAMSPACE_WIDTH && y < PARAMSPACE_HEIGHT) {
        double theta = xMin + x * (xMax - xMin) / PARAMSPACE_WIDTH;
        double beta = yMax - y * (yMax - yMin) / PARAMSPACE_HEIGHT;
        emit clicked(theta, beta);
    }
}

void WidgetParametersSpace::paintEvent(QPaintEvent *event) {
	(void) event;  // Unused parameter
    QPainter painter(this);
	painter.drawImage(QPoint((width()-PARAMSPACE_WIDTH)/2.,
				(height()-PARAMSPACE_HEIGHT)/2.), *pixels);
}
