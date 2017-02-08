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

CircleBilliard::CircleBilliard(const double theta, const double alpha,
                               const double r) :
    AbstractBilliard(theta, alpha), r(r) {}

double CircleBilliard::rho(const double theta) const {
	(void) theta;
	return r;
}

double CircleBilliard::rhoMax() const {
	return r;
}

std::string CircleBilliard::string() const {
    return "Circle";
}

double CircleBilliard::nextPosition() {
    return wrapAngle(-currentTheta + 2 * currentAlpha - M_PI);
}

double CircleBilliard::nextDirection() {
    return wrapAngle(2 * currentTheta - currentAlpha);
}
