#include "ParamArea.h"

ParamArea::ParamArea(QWidget *parent) : QWidget(parent) {
    setBackgroundRole(QPalette::Base);

	pixels = new QImage(PARAMAREA_PIX_WIDTH, PARAMAREA_PIX_HEIGHT, QImage::Format_RGB32);
	pixels->fill(Qt::white);

	for(int x=0 ; x<PARAMAREA_PIX_WIDTH ; x++){
		for(int y=0 ; y<PARAMAREA_PIX_HEIGHT ; y++){
			if(qrand() % 10 == 0){
				pixels->setPixel(x, y, qRgb((qrand()%256), (qrand()%256), (qrand()%256)));
			}
		}
	}
}

ParamArea::~ParamArea() {
	delete pixels;
}

QSize ParamArea::minimumSizeHint() const
{
	return QSize(PARAMAREA_PIX_WIDTH, PARAMAREA_PIX_HEIGHT);
}

QSize ParamArea::sizeHint() const
{
	return QSize(PARAMAREA_PIX_WIDTH, PARAMAREA_PIX_HEIGHT);
}

void ParamArea::paintEvent(QPaintEvent *event)
{
	(void) event; // Unused parameter
    QPainter painter(this);
	painter.drawImage(QPoint((width()-PARAMAREA_PIX_WIDTH)/2.,
				(height()-PARAMAREA_PIX_HEIGHT)/2.), *pixels);
}
