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
 * CircleBilliard.cpp
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Contain the implementation of the functions for a circular billiard.
 */

#include <cmath>
#include "CircleBilliard.h"
#include "routines.h"

// Construct circular billiard.
CircleBilliard::CircleBilliard(const double theta, const double alpha,
                               const double r) :
        AbstractBilliard(theta, alpha), r(r) {
    currentPosition.setRho(r);
}

// Return constant radius.
double CircleBilliard::rho(const double theta) const {
	(void) theta;  // Unused parameter
	return r;
}

// Return maximum radius = radius.
double CircleBilliard::rhoMax() const {
	return r;
}

// Return the name of the billiard.
std::string CircleBilliard::string() const {
    return "Circle";
}

// Return the normal vector to the curve at the current point.
Vector2d CircleBilliard::currentNormalVector() const {
    Vector2d nVec;
    nVec.setPolarCoordinates(1., currentPosition.theta());
    return nVec;
}

// Return the next angle of position taking into account the current angles
// of position and direction.
void CircleBilliard::updatePosition() {
    double nextTheta =  wrapAngle(-currentPosition.theta()
                                  + 2 * currentDirection.theta() - M_PI);
    currentPosition.setPolarCoordinates(rho(nextTheta), nextTheta);
}

// Return the next angle of direction taking into account the current angles
// of position and direction.
void CircleBilliard::updateDirection() {
    double nextAlpha = wrapAngle(2 * currentPosition.theta()
                                 - currentDirection.theta());
    currentDirection.setPolarCoordinates(1., nextAlpha);
}
