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
 * AbstractBilliard.cpp
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Contain the implementation of the functions for an abstract billiard.
 */

#include <cmath>
#include <stdexcept>
#include "routines.h"
#include "AbstractBilliard.h"

// Construct the abstract billiard.
AbstractBilliard::AbstractBilliard(const double theta, const double alpha) :
    currentTheta(theta), currentAlpha(alpha) {
}

// Return the coordinates given an angle.
std::tuple<double, double> AbstractBilliard::xy(const double theta) const {
    double rd = rho(theta);
    return std::make_tuple(rd * std::cos(theta), rd * std::sin(theta));
}

// Return the current angle of position.
double AbstractBilliard::getTheta() const {
    return currentTheta;
}

// Return the current coordinates.
std::tuple<double, double> AbstractBilliard::getXY() const {
    return xy(currentTheta);
}

// Return the current angles of position and incidence.
std::tuple<double, double> AbstractBilliard::getPhaseCoos() const {
    return std::make_tuple(currentTheta,
        direction2incidence(currentAlpha, currentTheta));
}

// Set the angles of position and incidence.
void AbstractBilliard::setPositionAndIncidence(const double theta,
                                               const double beta) {
    currentTheta = wrapAngle(theta);
    currentAlpha = incidence2direction(beta, theta);
}

// Make a move on the billiard: update the angles of position and direction.
void AbstractBilliard::updatePositionAndDirection() {
    currentTheta = nextPosition();     
    if (std::isnan(currentTheta)) {
        throw std::runtime_error("Encountered NaN value.");
    }
    currentAlpha = nextDirection();     
    if (std::isnan(currentAlpha)) {
        throw std::runtime_error("Encountered NaN value.");
    }
}

// Return angle of direction given angles of incidence and position.
double AbstractBilliard::incidence2direction(const double beta,
                                             const double theta) {
    return wrapAngle(M_PI - beta + theta);
}

// Return angle of incidence given angles of direction and position.
double AbstractBilliard::direction2incidence(const double alpha,
                                             const double theta) {
    return wrapAngle(M_PI - alpha + theta);
}

// Return the next angle of position.
// Solve for the intersection of the shape rho(theta) and a line.
double AbstractBilliard::nextPosition() {
    const double currentX = rho(currentTheta) * std::cos(currentTheta);
    const double currentY = rho(currentTheta) * std::sin(currentTheta);

    // Equation of the line: ux+xy+w=0
    const double u = -std::sin(currentAlpha);
    const double v = std::cos(currentAlpha);
    const double w = - (u*currentX + v*currentY);

    auto fun = [&] (const double &t) {
        return rho(t) * (u * std::cos(t) + v * std::sin(t)) + w;
    };

    const double eps = 1e-6;
    double nextTheta = bisectionSolver(fun, currentTheta + eps,
                                       currentTheta + 2*M_PI - eps);

    return wrapAngle(nextTheta);
}
