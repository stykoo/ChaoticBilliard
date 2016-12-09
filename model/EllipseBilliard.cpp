#include <cmath>
#include "EllipseBilliard.h"

EllipseBilliard::EllipseBilliard(const double e, const double theta,
                                 const double alpha, const double p) :
    AbstractBilliard(theta, alpha), e(e), p(p) {}

double EllipseBilliard::rho(const double theta) const {
	return p / (1. - e * std::cos(theta));
}

double EllipseBilliard::rhoMax() const {
	return p / (1. - e);
}

double EllipseBilliard::nextPosition(const double theta, const double alpha) {
    // lx + my + n = 0
    double l = -std::sin(alpha);
    double m = std::cos(alpha);
    double n = - l * rho(theta) * (std::cos(theta) + std::sin(theta));
    (void) n;

    if (std::abs(m) > std::abs(l)) {
    } else {
    }
    return 0;
}

