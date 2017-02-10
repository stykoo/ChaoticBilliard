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
 * Vector2d.h
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Contain the definition of the class for a 2d vector that is represented
 * both in cartesian and polar coordinates.
 */

#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d {
    public:
        Vector2d();
        double x() const;
        double y() const;
        double rho() const;
        double theta() const;

        void setCartesianCoordinates(const double x0, const double y0);
        void setPolarCoordinates(const double rho0, const double theta0);
        void setRho(const double rho0);

        void normalize();

    private:
        double _x, _y; // Cartesian coordinates
        double _rho, _theta; // Polar coordinates
};

#endif
