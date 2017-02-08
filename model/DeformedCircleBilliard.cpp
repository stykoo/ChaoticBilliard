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
