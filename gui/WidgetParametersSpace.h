#ifndef WIDGET_PARAMETERS_SPACE
#define WIDGET_PARAMETERS_SPACE

#define PARAMSPACE_WIDTH 600
#define PARAMSPACE_HEIGHT 600

#include <QtWidgets>
#include <tuple>
#include <cmath>
#include "../model/Billiards.h"

class WidgetParametersSpace : public QWidget {
    Q_OBJECT

	public:
		WidgetParametersSpace(QWidget *parent = 0);
		~WidgetParametersSpace();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;

		void addPoint(const std::tuple<double, double> coos,
                      const double xMin = -M_PI, const double xMax = M_PI,
                      const double yMin = -M_PI, const double yMax = +M_PI);

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		QImage *pixels;
};

#endif
