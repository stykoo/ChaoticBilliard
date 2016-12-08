#include "WidgetParametersSpace.h"

WidgetParametersSpace::WidgetParametersSpace(QWidget *parent) : QWidget(parent) {
    setBackgroundRole(QPalette::Base);

	pixels = new QImage(PARAMSPACE_WIDTH, PARAMSPACE_HEIGHT, QImage::Format_RGB32);
	pixels->fill(Qt::white);

	for(int x=0 ; x<PARAMSPACE_WIDTH ; x++){
		for(int y=0 ; y<PARAMSPACE_HEIGHT ; y++){
			if(qrand() % 10 == 0){
				pixels->setPixel(x, y, qRgb((qrand()%256), (qrand()%256), (qrand()%256)));
			}
		}
	}
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

void WidgetParametersSpace::paintEvent(QPaintEvent *event)
{
	(void) event;  // Unused parameter
    QPainter painter(this);
	painter.drawImage(QPoint((width()-PARAMSPACE_WIDTH)/2.,
				(height()-PARAMSPACE_HEIGHT)/2.), *pixels);
}
