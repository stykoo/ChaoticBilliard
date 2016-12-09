#include <cmath>
#include "CircleBilliard.h"
#include "routines.h"

CircleBilliard::CircleBilliard(const double theta, const double alpha,
                               const double r) :
    AbstractBilliard(theta, alpha), r(r) {}

double CircleBilliard::rho(const double theta) const {
	(void) theta;
	return r;
}

double CircleBilliard::rhoMax() const {
	return r;
}

double CircleBilliard::nextPosition(const double theta, const double alpha) 
        const {
    return wrapAngle(-theta + 2 * alpha - M_PI);
}

double CircleBilliard::nextDirection(const double alpha, const double theta)
        const {
    return wrapAngle(2 * theta - alpha);
}
