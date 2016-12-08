#include <cmath>
#include "CircleBilliard.h"

CircleBilliard::CircleBilliard(double r) : AbstractBilliard(), r(r) {}

double CircleBilliard::rho(const double theta) const {
	(void) theta;
	return r;
}

double CircleBilliard::rhoMax() const {
	return r;
}

double CircleBilliard::nextPosition(const double theta, const double alpha) {
    return theta - M_PI + 2 * alpha;  // Periodize it! 
}

