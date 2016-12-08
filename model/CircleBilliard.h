#ifndef CIRCLE_BILLIARD_H
#define CIRCLE_BILLIARD_H

#include "AbstractBilliard.h"

class CircleBilliard : public AbstractBilliard {
	public:
		CircleBilliard(double r = 1.0);
		~CircleBilliard(){};

        double rho(const double theta) const;
		double rhoMax() const;
        double nextPosition(const double theta, const double alpha);

		CircleBilliard* clone() const { return new CircleBilliard(*this); }

	private:
		const double r;
};

#endif
