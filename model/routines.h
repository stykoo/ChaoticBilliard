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
 * routines.h
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Contain the definitions of some general mathematical functions.
 */
#ifndef ROUTINES_H
#define ROUTINES_H

#include <functional>

inline double square(const double x) {
    return x*x;
}

double wrapAngle(double angle);
void solveSecondOrderEq(const double a, const double b, const double c,
                        double &sol1, double &sol2);
double bisectionSolver(std::function<double(double)> f, double a, double b,
                       size_t bits=64, size_t maxiter=500);

#endif
