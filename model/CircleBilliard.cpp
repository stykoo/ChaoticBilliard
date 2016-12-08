#include <cmath>
#include "CircleBilliard.h"
#include "routines.h"

CircleBilliard::CircleBilliard(double r) : AbstractBilliard(), r(r) {}

double CircleBilliard::rho(const double theta) const {
	(void) theta;
	return r;
}

double CircleBilliard::rhoMax() const {
	return r;
}

double CircleBilliard::nextPosition(const double theta, const double alpha) {
    return wrapAngle(-theta + 2 * alpha - M_PI);
}

double CircleBilliard::nextDirection(const double alpha, const double theta) {
    return wrapAngle(2 * theta - alpha);
}
