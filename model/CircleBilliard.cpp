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

double CircleBilliard::nextPosition() const {
    return wrapAngle(-currentTheta + 2 * currentAlpha - M_PI);
}

double CircleBilliard::nextDirection() const {
    return wrapAngle(2 * currentTheta - currentAlpha);
}
