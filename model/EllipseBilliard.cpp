/*
Copyright (C) 2017 Alexis Poncet

This file is part of ChaoticBilliard.

ChaoticBilliard is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
 * ChaoticBilliard
 * EllipseBilliard.cpp
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Contain the implementation of the functions for an elliptic billiard.
 */

#include <cmath>
#include "EllipseBilliard.h"
#include "routines.h"

// Construct elliptic billiard.
// a (resp. b) = semi major (resp. minor) axis
// e = excentricity
EllipseBilliard::EllipseBilliard(const double e, const double theta,
                                 const double alpha, const double a) :
        AbstractBilliard(theta, alpha), a(a), e(e) {
    b = a * std::sqrt(1 - e*e);

    currentX = std::cos(theta);
    currentY = std::sin(theta);
    normalX = -std::sin(alpha);
    normalY = std::cos(alpha);
}

// Return the radius according to the polar equation of the ellipse.
double EllipseBilliard::rho(const double theta) const {
	return a * b / std::sqrt(square(b * std::cos(theta)) \
           + square(a * std::sin(theta)));
}

// Return maximum radius = semi major axis.
double EllipseBilliard::rhoMax() const {
	return a;
}

// Return name and excentricity.
std::string EllipseBilliard::string() const {
    return "Ellipse (e="+std::to_string(e)+")";
}

// Re-implement the expression of the coordinates for greater numerical
// accuracy.
std::tuple<double, double> EllipseBilliard::xy(const double theta) const {
    return std::make_tuple(a * std::cos(theta), b * std::sin(theta));
}

// Re-implement this function because of the new variables.
void EllipseBilliard::setPositionAndIncidence(const double theta,
                                              const double beta) {
    currentTheta = wrapAngle(theta);
    currentAlpha = incidence2direction(beta, theta);
    currentX = std::cos(currentTheta);
    currentY = std::sin(currentTheta);
    normalX = -std::sin(currentAlpha);
    normalY = std::cos(currentAlpha);
}

// Return the next angle of position taking into account the current angles
// of position and direction. This is done by solving a second order equation.
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

// Return the next angle of direction taking into account the current angles
// of position and direction.
// This is done by a decomposition in the right basis.
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
