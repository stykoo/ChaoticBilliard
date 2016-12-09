#include <cmath>
#include "DeformedCircleBilliard.h"

DeformedCircleBilliard::DeformedCircleBilliard(
        const double eps, const double theta, const double alpha, double r) :
    AbstractBilliard(theta, alpha), eps(eps), r(r) {}

double DeformedCircleBilliard::rho(const double theta) const {
	return r + eps*std::cos(theta);
}

double DeformedCircleBilliard::rhoMax() const {
	return r + eps;
}

