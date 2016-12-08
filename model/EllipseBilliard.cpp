#include <cmath>
#include "EllipseBilliard.h"

EllipseBilliard::EllipseBilliard(double e, double p) : AbstractBilliard(), 
	e(e), p(p) {}

double EllipseBilliard::rad(const double theta) const {
	return p / (1. - e * std::cos(theta));
}

double EllipseBilliard::max() const {
	return p / (1. - e);
}

double EllipseBilliard::nextPosition(const double theta, const double alpha) {
    // lx + my + n = 0
    double l = -std::sin(alpha);
    double m = std::cos(alpha);
    double n = - l * rad(theta) * (std::cos(theta) + std::sin(theta));

    if (std::abs(m) > std::abs(l)) {
    } else {
    }
    return 0;
}

