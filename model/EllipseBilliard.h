#ifndef ELLIPSE_BILLIARD_H
#define ELLIPSE_BILLIARD_H

#include "AbstractBilliard.h"

class EllipseBilliard : public AbstractBilliard {
	public:
		EllipseBilliard(double e, double p = 1.0);
		~EllipseBilliard(){};

        double rad(const double theta) const;
		double max() const;
        double nextPosition(const double theta, const double alpha);

		EllipseBilliard* clone() const { return new EllipseBilliard(*this); }

	private:
		const double e, p;
};

#endif
