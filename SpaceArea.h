#ifndef SPACEAREA_H
#define SPACEAREA_H

#define NB_ANGULAR_DIVISIONS 100
#define UNIT_SIZE 300

#include <QtWidgets>
#include "ShapeFunctions.h"

class SpaceArea : public QWidget
{
    Q_OBJECT

	public:
		SpaceArea(const ShapeFunction &fun, QWidget *parent = 0);
		~SpaceArea();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;
		void setShapeFunction(const ShapeFunction &fun);
		void addPoint(const double theta);

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		ShapeFunction *shapeFun;
		QPolygonF *billiard;
		QList<QPointF> pointHistory;
};

#endif
