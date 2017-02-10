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
 * DeformedCircleBilliard.cpp
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Contain the implementation of the functions for a deformed circular
 * billiard: rho(theta) = 1 + eps*cos(theta).
 */

#include <cmath>
#include "DeformedCircleBilliard.h"

// Construct deformed circular billiard.
// eps is the deformation.
DeformedCircleBilliard::DeformedCircleBilliard(
        const double eps, const double theta, const double alpha, double r) :
        AbstractBilliard(theta, alpha), eps(eps), r(r) {
    currentPosition.setRho(r);
}

// Return the radius given the angle.
double DeformedCircleBilliard::rho(const double theta) const {
	return r + eps*std::cos(theta);
}

// Return the maximum radius.
double DeformedCircleBilliard::rhoMax() const {
	return r + eps;
}

// Return name and deformation.
std::string DeformedCircleBilliard::string() const {
    return "Deformed circle (eps="+std::to_string(eps)+")";
}

// Update the angle of direction taking into account the current angles
// of position and direction.
// This is done by a decomposition in the right basis.
void DeformedCircleBilliard::updateDirection() {
    // Vector corresponding to the current direction
    double ux = -currentDirection.x();
    double uy = -currentDirection.y();

    // Normal vector to the billiard
    double theta = currentPosition.theta();
    double nx = std::cos(theta) + eps * std::cos(2. * theta); 
    double ny = std::sin(theta) + eps * std::sin(2. * theta); 
    double nNorm = nx*nx + ny*ny;
    nx /= nNorm;
    ny /= nNorm;
    // Tangent vector to the billiard
    double tx = -ny, ty = nx;

    double dx = (ux*nx + uy*ny)*nx - (ux*tx + uy*ty)*tx;
    double dy = (ux*nx + uy*ny)*ny - (ux*tx + uy*ty)*ty;

    currentDirection.setCartesianCoordinates(dx, dy);
    currentDirection.normalize();
}
