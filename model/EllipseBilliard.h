#ifndef ELLIPSE_BILLIARD_H
#define ELLIPSE_BILLIARD_H

#include "AbstractBilliard.h"

class EllipseBilliard : public AbstractBilliard {
	public:
		EllipseBilliard(const double e, const double theta, const double alpha,
                        const double a = 1.0);
		~EllipseBilliard(){};

        double rho(const double theta) const;
		double rhoMax() const;
        std::string string() const;
        std::tuple<double, double> xy(const double theta) const;

		EllipseBilliard* clone() const { return new EllipseBilliard(*this); }

	protected:
        double nextPosition() const;
        double nextDirection() const;

		double a, b, e;
};

#endif
