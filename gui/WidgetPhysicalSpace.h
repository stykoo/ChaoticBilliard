#ifndef WIDGET_PHYSICAL_SPACE
#define WIDGET_PHYSICAL_SPACE

#define NB_ANGULAR_DIVISIONS 100
#define UNIT_SIZE 300

#include <QtWidgets>
#include "../model/Billiards.h"

class WidgetPhysicalSpace : public QWidget
{
    Q_OBJECT

	public:
		WidgetPhysicalSpace(const AbstractBilliard &bil, QWidget *parent = 0);
		~WidgetPhysicalSpace();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;
		void setBilliard(const AbstractBilliard &bil);
		void addPoint(const double theta);

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		AbstractBilliard *billiard;
		QPolygonF *stroke;
		QList<QPointF> pointHistory;
};

#endif
