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
		WidgetParametersSpace(const int pointsize=2,
            const double xMin = -M_PI, const double xMax = M_PI,
            const double yMin = -M_PI, const double yMax = +M_PI,
            QWidget *parent = 0);
		~WidgetParametersSpace();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;

		void addPoint(const std::tuple<double, double> coos);
        void changeColor();
        void clearImage();

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		QImage *pixels;
        QColor color;

        int pointsize;
        double xMin, xMax, yMin, yMax;
        //QList<std::tuple<double, double, QRgb> history;
};

#endif
