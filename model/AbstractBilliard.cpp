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
AbstractBilliard::AbstractBilliard(const double theta, const double alpha) {
    // We initiatize the radius to 1 because we don't know what it should be!
    // (Did you want to call a pure virtual function inside the constructor?)
    currentPosition.setPolarCoordinates(1., theta);

    currentDirection.setPolarCoordinates(1., alpha);
}

// Return the coordinates given an angle.
std::tuple<double, double> AbstractBilliard::xy(const double theta) const {
    double rd = rho(theta);
    return std::make_tuple(rd * std::cos(theta), rd * std::sin(theta));
}

// Return the current angle of position.
double AbstractBilliard::getTheta() const {
    return currentPosition.theta();
}

// Return the current coordinates.
std::tuple<double, double> AbstractBilliard::getXY() const {
    return std::make_tuple(currentPosition.x(), currentPosition.y());
}

// Return the current angles of position and incidence.
std::tuple<double, double> AbstractBilliard::getPhaseCoos() const {
    return std::make_tuple(currentPosition.theta(),
                           direction2incidence(currentDirection.theta(),
                                               currentPosition.theta()));
}

// Set the angles of position and incidence.
void AbstractBilliard::setPositionAndIncidence(const double theta,
                                               const double beta) {
    currentPosition.setPolarCoordinates(rho(theta), wrapAngle(theta));
    currentDirection.setPolarCoordinates(1., incidence2direction(beta, theta));
}

// Make a move on the billiard: update the angles of position and direction.
void AbstractBilliard::updatePositionAndDirection() {
    updatePosition();     
    if (std::isnan(currentPosition.theta())) {
        throw std::runtime_error("Encountered NaN value.");
    }
    updateDirection();     
    if (std::isnan(currentDirection.theta())) {
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

// Update the position.
// Solve for the intersection of the shape rho(theta) and a line.
void AbstractBilliard::updatePosition() {
    // Equation of the line: ux+vy+w=0
    const double u = -currentDirection.y();
    const double v = currentDirection.x();
    const double w = - (u*currentPosition.x() + v*currentPosition.y());

    auto fun = [&] (const double &t) {
        return rho(t) * (u * std::cos(t) + v * std::sin(t)) + w;
    };

    const double eps = 1e-6;
    double nextTheta = bisectionSolver(fun, currentPosition.theta() + eps,
                                       currentPosition.theta() + 2*M_PI - eps);
    nextTheta = wrapAngle(nextTheta);
    currentPosition.setPolarCoordinates(rho(nextTheta), nextTheta);
}

// Update the angle of direction taking into account the current angles
// of position and direction.
// This is done by a decomposition in the right basis.
void AbstractBilliard::updateDirection() {
    double ux = currentDirection.x();
    double uy = currentDirection.y();

    // Normal vector to the curve
    Vector2d nVec = currentNormalVector();
    double nx = nVec.x();
    double ny = nVec.y();
    // Tangent vector to the curve
    double tx = -ny, ty = nx;

    double dx = (ux*nx + uy*ny)*nx - (ux*tx + uy*ty)*tx;
    double dy = (ux*nx + uy*ny)*ny - (ux*tx + uy*ty)*ty;
    currentDirection.setCartesianCoordinates(dx, dy);
    currentDirection.normalize();
}
