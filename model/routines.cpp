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
 * routines.cpp
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Contain some general mathematical functions.
 */

#include <cmath>
#include <stdexcept>
#include "routines.h"

int sign(const double x) {
    return (0. < x) - (x < 0.);
}

double wrapAngle(double angle) {
    angle -= std::floor(angle / (2. * M_PI)) * 2 * M_PI; 
    if (angle > M_PI) {
        angle -= 2 * M_PI;
    }
    return angle;
}

void solveSecondOrderEq(const double a, const double b, const double c,
                       double &sol1, double &sol2) {
    double d = b*b - 4*a*c;
    if(d < 0) {
        throw std::runtime_error(
            "Second order equation has no real solution.");
    }
    // Trick for numerical stability
    double tmp = -0.5 * (b + sign(b) * std::sqrt(d));
    sol1 = tmp / a;
    sol2 = c / tmp;
}

double bisectionSolver(std::function<double(double)> f, double a, double b,
                       size_t bits, size_t maxiter) {
    bits = std::min(8 * sizeof(double), bits);
    double tol = std::ldexp(1., 1-bits);

    double fa = f(a), fb = f(b);

    if (fa * fb >= 0) {
        throw std::runtime_error("Could not use bisection method.");
    }

    if (a > b) {
        std::swap(a, b);
    }

    double s = b, fs = fb;
    size_t i = maxiter;

    while (i-- && fs != 0. && b - a > tol) {
        s = a + (b - a) / 2.;
        fs = f(s);
        if(fs * fb >= 0) {
            b = s;
            fb = fs;
        } else {
            a = s;
            fa = fs;
        }
    }

    return s;
}
