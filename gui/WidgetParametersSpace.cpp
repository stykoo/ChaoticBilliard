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
    changeColor();
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
    int y_screen = PARAMSPACE_HEIGHT * \
        (std::get<1>(coos) - yMin) / (yMax - yMin);

    int dx1 = (pointsize - 1) / 2, dx2 = pointsize / 2;
    for (int i = x_screen - dx1 ; i <= x_screen + dx2 ; ++i) {
        for (int j = y_screen - dx1 ; j <= y_screen + dx2 ; ++j) {
                if (i >= 0 && j >= 0 && i < PARAMSPACE_WIDTH &&
                    j < PARAMSPACE_HEIGHT) {
                    pixels->setPixelColor(i, j, color);
                }
        }
    }
    repaint();
}

void WidgetParametersSpace::changeColor() {
    color.setRgb(qrand() % 255, qrand() % 255, qrand() % 255);
}

void WidgetParametersSpace::clearImage() {
	pixels->fill(Qt::white);
}

void WidgetParametersSpace::paintEvent(QPaintEvent *event)
{
	(void) event;  // Unused parameter
    QPainter painter(this);
	painter.drawImage(QPoint((width()-PARAMSPACE_WIDTH)/2.,
				(height()-PARAMSPACE_HEIGHT)/2.), *pixels);
}
