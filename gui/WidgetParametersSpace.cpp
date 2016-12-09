#include "WidgetParametersSpace.h"

WidgetParametersSpace::WidgetParametersSpace(QWidget *parent) :
        QWidget(parent) {
    setBackgroundRole(QPalette::Base);

	pixels = new QImage(PARAMSPACE_WIDTH, PARAMSPACE_HEIGHT,
                        QImage::Format_RGB32);
	pixels->fill(Qt::white);
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

void WidgetParametersSpace::addPoint(const std::tuple<double, double> coos,
        const double xMin, const double xMax, const double yMin,
        const double yMax) {
    int x_screen = PARAMSPACE_WIDTH * \
        (std::get<0>(coos) - xMin) / (xMax - xMin);
    int y_screen = PARAMSPACE_HEIGHT * \
        (std::get<1>(coos) - yMin) / (yMax - yMin);
    pixels->setPixel(x_screen, y_screen, qRgb(255, 0, 0));
    repaint();
}

void WidgetParametersSpace::paintEvent(QPaintEvent *event)
{
	(void) event;  // Unused parameter
    QPainter painter(this);
	painter.drawImage(QPoint((width()-PARAMSPACE_WIDTH)/2.,
				(height()-PARAMSPACE_HEIGHT)/2.), *pixels);
}
