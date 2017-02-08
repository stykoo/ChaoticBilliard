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

#ifndef ELLIPSE_BILLIARD_H
#define ELLIPSE_BILLIARD_H

#include "AbstractBilliard.h"

class EllipseBilliard : public AbstractBilliard {
	public:
		EllipseBilliard(const double e, const double theta, const double alpha,
                        const double a = 1.0);
		~EllipseBilliard(){};

        double rho(const double theta) const;
		double rhoMax() const;
        std::string string() const;
        std::tuple<double, double> xy(const double theta) const;
        void setPositionAndIncidence(const double theta, const double beta);

		EllipseBilliard* clone() const { return new EllipseBilliard(*this); }

	protected:
        double nextPosition();
        double nextDirection();

		double a, b, e;
        double currentX, currentY;
        double normalX, normalY;
};

#endif
