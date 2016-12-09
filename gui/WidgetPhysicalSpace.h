#ifndef WIDGET_PHYSICAL_SPACE
#define WIDGET_PHYSICAL_SPACE

#define NB_ANGULAR_DIVISIONS 100
#define PHYSPACE_SIZE 400

#include <QtWidgets>
#include <memory>
#include "../model/Billiards.h"

class WidgetPhysicalSpace : public QWidget
{
    Q_OBJECT

	public:
		WidgetPhysicalSpace(std::shared_ptr<AbstractBilliard> bil,
                            QWidget *parent = 0);
		~WidgetPhysicalSpace();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;
		void setBilliard(std::shared_ptr<AbstractBilliard> bil);
		void addPoint(const double theta);

	protected:
		void paintEvent(QPaintEvent *event);

	private:
        std::shared_ptr<AbstractBilliard> billiard;
        QPolygonF *stroke;
		QList<QPointF> pointHistory;
};

#endif
