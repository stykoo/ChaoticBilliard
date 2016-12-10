#include <cmath>
#include <iostream>
#include "EllipseBilliard.h"
#include "routines.h"

EllipseBilliard::EllipseBilliard(const double e, const double theta,
                                 const double alpha, const double a) :
        AbstractBilliard(theta, alpha), a(a) {
    b = a * std::sqrt(1 - e*e);
}

double EllipseBilliard::rho(const double theta) const {
	return a * b / std::sqrt(square(b * std::cos(theta)) + square(a * std::sin(theta)));
}

double EllipseBilliard::rhoMax() const {
	return a;
}

std::tuple<double, double> EllipseBilliard::xy(const double theta) const {
    return std::make_tuple(a * std::cos(theta), b * std::sin(theta));
}

double EllipseBilliard::nextPosition() const {
    double s1 = 1. / (a*a);
    double s2 = 1. / (b*b);
    double x0, y0;
    std::tie(x0, y0) = getXY();

    // ux + vy + w = 0
    double u = -std::sin(currentAlpha);
    double v = std::cos(currentAlpha);
    double w = - (u*x0 + v*y0);

    // If v is small, we swap the roles of x and y to avoid division by zero
    if (std::abs(v) < std::abs(u)){
        std::swap(u, v);
        std::swap(x0, y0);
        std::swap(s1, s2);
    }

    // Define and solve second order equation
    double aa = s2*u*u + s1*v*v;
    double bb = 2*s2*u*w;
    double cc = s2*w*w - v*v;
    double solX1, solX2, solY1, solY2;
    solveSecondOrderEq(aa, bb, cc, solX1, solX2);
    solY1 = -(u*solX1 + w) / v;
    solY2 = -(u*solX2 + w) / v;

    // Select the solution that is not the current position
    double xNext, yNext;
    if (std::min(std::abs(solX1 - x0), std::abs(solY1 - y0)) >
            std::min(std::abs(solX2 - x0), std::abs(solY2 - y0))) {
        xNext = solX1;
        yNext = solY1;
    } else {
        xNext = solX2;
        yNext = solY2;
    }

    // We swap back if needed
    if (std::abs(v) < std::abs(u)){
        std::swap(xNext, yNext);
        // std::swap(x0, y0);
    }

    double thetaNext = std::atan2(yNext, xNext);
    return thetaNext;
}

double EllipseBilliard::nextDirection() const {
    double ux = std::cos(currentAlpha);
    double uy = std::sin(currentAlpha);

    // Normal vector to the ellipse
    double nx = -a * std::sin(currentTheta);
    double ny = b * std::cos(currentTheta);
    double nNorm = nx*nx + ny*ny;
    nx /= nNorm;
    ny /= nNorm;
    // Tangent vector to the ellipse
    double tx = -ny, ty = nx;

    double dx = (ux*nx + uy*ny)*nx - (ux*tx + uy*ty)*tx;
    double dy = (ux*nx + uy*ny)*ny - (ux*tx + uy*ty)*ty;
    return std::atan2(dy, dx);
}
