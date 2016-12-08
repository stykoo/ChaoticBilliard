#include <cmath>
#include "DeformedCircleBilliard.h"

DeformedCircleBilliard::DeformedCircleBilliard(double eps, double r) :
    AbstractBilliard(), eps(eps), r(r) {}

double DeformedCircleBilliard::rad(const double theta) const {
	return r + eps*std::cos(theta);
}

double DeformedCircleBilliard::max() const {
	return r + eps;
}

