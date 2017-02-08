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

std::string DeformedCircleBilliard::string() const {
    return "Deformed circle (eps="+std::to_string(eps)+")";
}

double DeformedCircleBilliard::nextDirection() {
    // Vector corresponding to the current direction
    double ux = -std::cos(currentAlpha);
    double uy = -std::sin(currentAlpha);

    // Normal vector to the billiard
    double nx = std::cos(currentTheta) + eps * std::cos(2. * currentTheta); 
    double ny = std::sin(currentTheta) + eps * std::sin(2. * currentTheta); 
    double nNorm = nx*nx + ny*ny;
    nx /= nNorm;
    ny /= nNorm;
    // Tangent vector to the billiard
    double tx = -ny, ty = nx;

    double dx = (ux*nx + uy*ny)*nx - (ux*tx + uy*ty)*tx;
    double dy = (ux*nx + uy*ny)*ny - (ux*tx + uy*ty)*ty;

    return std::atan2(dy, dx);
}
