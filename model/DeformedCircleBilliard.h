#ifndef DEFORMED_CIRCLE_BILLIARD
#define DEFORMED_CIRCLE_BILLIARD

#include "AbstractBilliard.h"

class DeformedCircleBilliard : public AbstractBilliard {
	public:
		DeformedCircleBilliard(double eps, double r = 1.0);
		~DeformedCircleBilliard(){}

        double rho(const double theta) const;
		double rhoMax() const;

		DeformedCircleBilliard* clone() const { 
            return new DeformedCircleBilliard(*this); 
        }

	private:
		const double eps, r;
};

#endif
