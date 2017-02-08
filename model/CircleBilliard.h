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

#ifndef CIRCLE_BILLIARD_H
#define CIRCLE_BILLIARD_H

#include "AbstractBilliard.h"

class CircleBilliard : public AbstractBilliard {
	public:
		CircleBilliard(const double theta, const double alpha,
                       const double r = 1.0);
		~CircleBilliard(){};

        double rho(const double theta) const;
		double rhoMax() const;
        std::string string() const;

		CircleBilliard* clone() const { return new CircleBilliard(*this); }

	protected:
        double nextPosition();
        double nextDirection();

		const double r;
};

#endif
