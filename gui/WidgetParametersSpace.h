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
 * WidgetParametersSpace.h
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Define class for visualization of parameters' space.
 */

#ifndef WIDGET_PARAMETERS_SPACE
#define WIDGET_PARAMETERS_SPACE

#define PARAMSPACE_WIDTH 599
#define PARAMSPACE_HEIGHT 599

#include <QtWidgets>
#include <tuple>
#include <cmath>
#include "../model/Billiards.h"

class WidgetParametersSpace : public QWidget {
    Q_OBJECT

	public:
		WidgetParametersSpace(const int pointsize=2,
            const double xMin = -M_PI, const double xMax = M_PI,
            const double yMin = -M_PI/2., const double yMax = +M_PI/2.,
            QWidget *parent = 0);
		~WidgetParametersSpace();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;

		void addPoint(const std::tuple<double, double> coos);
        void setColor(const QColor &c);
        void clearImage();

    signals:
        void clicked(double theta, double beta);

	protected:
        void mouseReleaseEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);

	private:
		QImage *pixels;  // Image on which we draw
        QColor color;  // Color of the current trajectory

        int pointsize;  // Size of the pen
        double xMin, xMax, yMin, yMax;  // Coordinates of the corners
        //QList<std::tuple<double, double, QRgb> history;
};

#endif
