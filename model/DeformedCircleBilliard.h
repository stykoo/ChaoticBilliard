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
 * DeformedCircleBilliard.h
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Define the class for a deformed circular billiard.
 */

#ifndef DEFORMED_CIRCLE_BILLIARD
#define DEFORMED_CIRCLE_BILLIARD

#include "AbstractBilliard.h"

class DeformedCircleBilliard : public AbstractBilliard {
	public:
		DeformedCircleBilliard(const double eps, const double theta,
                               const double alpha, const double r = 1.0);
		~DeformedCircleBilliard(){}

        double rho(const double theta) const;
		double rhoMax() const;
        std::string string() const;

		DeformedCircleBilliard* clone() const { 
            return new DeformedCircleBilliard(*this); 
        }

	protected:
        // nextPosition() is implemented in AbstractBilliard.cpp
        double nextDirection();
		const double eps, r;
};

#endif
