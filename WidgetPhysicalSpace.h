#ifndef WIDGET_PHYSICAL_SPACE
#define WIDGET_PHYSICAL_SPACE

#define NB_ANGULAR_DIVISIONS 100
#define UNIT_SIZE 300

#include <QtWidgets>
#include "ShapeFunctions.h"

class WidgetPhysicalSpace : public QWidget
{
    Q_OBJECT

	public:
		WidgetPhysicalSpace(const ShapeFunction &fun, QWidget *parent = 0);
		~WidgetPhysicalSpace();
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
