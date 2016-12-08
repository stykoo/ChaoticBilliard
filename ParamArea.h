#ifndef PARAMAREA__H
#define PARAMAREA_H

#define PARAMAREA_PIX_WIDTH 600
#define PARAMAREA_PIX_HEIGHT 600

#include <QtWidgets>
#include "ShapeFunctions.h"

class ParamArea : public QWidget
{
    Q_OBJECT

	public:
		ParamArea(QWidget *parent = 0);
		~ParamArea();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		QImage *pixels;
};

#endif
