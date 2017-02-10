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
 * Vector2d.cpp
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Contain the implementation of the methods for a 2d vector.
 */

#include <cmath>
#include "Vector2d.h"

Vector2d::Vector2d() : _x(0), _y(0), _rho(0), _theta(0) {
}

double Vector2d::x() const {
    return _x;
}

double Vector2d::y() const {
    return _y;
}

double Vector2d::rho() const {
    return _rho;
}

double Vector2d::theta() const {
    return _theta;
}

void Vector2d::setCartesianCoordinates(const double x0, const double y0) {
    _x = x0;
    _y = y0;
    _rho = std::hypot(x0, y0);
    _theta = std::atan2(y0, x0);
}

void Vector2d::setPolarCoordinates(const double rho0, const double theta0) {
    if (rho0 >= 0) {
        _rho = rho0;
        _theta = theta0;
    } else {
        _rho = -rho0;
        _theta = theta0 + M_PI;
    }
    _x = rho0 * std::cos(theta0);
    _y = rho0 * std::sin(theta0);
}

void Vector2d::normalize() {
    if (_rho != 0) {
        _x /= _rho;
        _y /= _rho;
    }
}

void Vector2d::setRho(const double rho0) {
    if (rho0 >= 0) {
        _rho = rho0;
    } else {
        _rho = -rho0;
        _theta += M_PI;
    }
}
