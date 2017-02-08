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

#ifndef WIDGET_PHYSICAL_SPACE
#define WIDGET_PHYSICAL_SPACE

#define NB_ANGULAR_DIVISIONS 100
#define PHYSPACE_SIZE 400

#include <QtWidgets>
#include <memory>
#include "../model/Billiards.h"

class WidgetPhysicalSpace : public QWidget {
    Q_OBJECT

	public:
		WidgetPhysicalSpace(std::shared_ptr<AbstractBilliard> bil,
                            QWidget *parent = 0);
		~WidgetPhysicalSpace();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;
        void clearHistory();
		void setBilliard(std::shared_ptr<AbstractBilliard> bil);
		void addPoint(const double theta);
        void setColor(const QColor &c);

	protected:
		void paintEvent(QPaintEvent *event);

	private:
        std::shared_ptr<AbstractBilliard> billiard;
        QPolygonF *stroke;
        QColor color; 
		QList<QPointF> pointHistory;
};

#endif
