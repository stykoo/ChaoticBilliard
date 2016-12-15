#include <cmath>
#include "EllipseBilliard.h"
#include "routines.h"

EllipseBilliard::EllipseBilliard(const double e, const double theta,
                                 const double alpha, const double a) :
        AbstractBilliard(theta, alpha), a(a), e(e) {
    b = a * std::sqrt(1 - e*e);

    currentX = std::cos(theta);
    currentY = std::sin(theta);
    normalX = -std::sin(alpha);
    normalY = std::cos(alpha);
}

double EllipseBilliard::rho(const double theta) const {
	return a * b / std::sqrt(square(b * std::cos(theta)) + square(a * std::sin(theta)));
}

double EllipseBilliard::rhoMax() const {
	return a;
}

std::string EllipseBilliard::string() const {
    return "Ellipse (e="+std::to_string(e)+")";
}

std::tuple<double, double> EllipseBilliard::xy(const double theta) const {
    return std::make_tuple(a * std::cos(theta), b * std::sin(theta));
}

void EllipseBilliard::setPositionAndIncidence(const double theta,
                                              const double beta) {
    currentTheta = wrapAngle(theta);
    currentAlpha = incidence2direction(beta, theta);
    currentX = std::cos(currentTheta);
    currentY = std::sin(currentTheta);
    normalX = -std::sin(currentAlpha);
    normalY = std::cos(currentAlpha);
}

double EllipseBilliard::nextPosition() {
    double s1 = 1. / (a*a);
    double s2 = 1. / (b*b);
    double x0 = currentX, y0 = currentY;

    // ux + vy + w = 0
    double u = normalX;
    double v = normalY;
    double w = - (u*x0 + v*y0);

    // If v is small, we swap the roles of x and y to avoid division by zero
    bool swapXY = std::abs(v) < std::abs(u);
    if (swapXY){
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
    if (swapXY){
        std::swap(xNext, yNext);
    }

    currentX = xNext;
    currentY = yNext;

    double thetaNext = std::atan2(yNext, xNext);
    return thetaNext;
}

double EllipseBilliard::nextDirection() {
    double ux = normalY;
    double uy = -normalX;

    // Normal vector to the ellipse
    double nx = -a * currentY / b;
    double ny = b * currentX / a;
    double nNorm = nx*nx + ny*ny;
    nx /= nNorm;
    ny /= nNorm;
    // Tangent vector to the ellipse
    double tx = -ny, ty = nx;

    double dx = (ux*nx + uy*ny)*nx - (ux*tx + uy*ty)*tx;
    double dy = (ux*nx + uy*ny)*ny - (ux*tx + uy*ty)*ty;
    normalX = -dy;
    normalY = dx;
    return std::atan2(dy, dx);
}
