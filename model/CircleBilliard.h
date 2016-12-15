#ifndef CIRCLE_BILLIARD_H
#define CIRCLE_BILLIARD_H

#include "AbstractBilliard.h"

class CircleBilliard : public AbstractBilliard {
	public:
		CircleBilliard(const double theta, const double alpha,
                       const double r = 1.0);
		~CircleBilliard(){};

        double rho(const double theta) const;
		double rhoMax() const;
        std::string string() const;

		CircleBilliard* clone() const { return new CircleBilliard(*this); }

	protected:
        double nextPosition();
        double nextDirection();

		const double r;
};

#endif
