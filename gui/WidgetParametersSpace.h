#ifndef WIDGET_PARAMETERS_SPACE
#define WIDGET_PARAMETERS_SPACE

#define PARAMSPACE_WIDTH 600
#define PARAMSPACE_HEIGHT 600

#include <QtWidgets>
#include "../model/Billiards.h"

class WidgetParametersSpace : public QWidget
{
    Q_OBJECT

	public:
		WidgetParametersSpace(QWidget *parent = 0);
		~WidgetParametersSpace();
		QSize minimumSizeHint() const;
		QSize sizeHint() const;

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		QImage *pixels;
};

#endif
