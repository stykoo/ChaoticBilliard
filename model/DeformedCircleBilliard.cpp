#include <cmath>
#include "DeformedCircleBilliard.h"

DeformedCircleBilliard::DeformedCircleBilliard(double eps, double r) :
    AbstractBilliard(), eps(eps), r(r) {}

double DeformedCircleBilliard::rho(const double theta) const {
	return r + eps*std::cos(theta);
}

double DeformedCircleBilliard::rhoMax() const {
	return r + eps;
}

