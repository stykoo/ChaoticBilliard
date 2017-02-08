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
 * AbstractBilliard.h
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Define the class for an abstract billiard.
 * AbstractBilliard should be inherited from and some functions should be
 * implemented in the daughter classes to make a real billiard.
 */

#ifndef ABSTRACT_BILLIARD_H
#define ABSTRACT_BILLIARD_H

#include <string>
#include <tuple>

// Abstract class for shape function
class AbstractBilliard {
	public:
        AbstractBilliard(const double theta, const double alpha);
		virtual ~AbstractBilliard() {};

		virtual double rho(const double theta) const = 0;
		virtual double rhoMax() const = 0;
        virtual std::string string() const = 0;
		virtual AbstractBilliard* clone() const = 0;

        virtual std::tuple<double, double> xy(const double theta) const;
        double getTheta() const;
        std::tuple<double, double> getXY() const;
        std::tuple<double, double> getPhaseCoos() const;

        virtual void setPositionAndIncidence(const double theta,
                                             const double beta);
        void updatePositionAndDirection();

        static double incidence2direction(const double beta,
                                          const double theta);
        static double direction2incidence(const double alpha,
                                          const double theta);

    protected:
        AbstractBilliard();
        virtual double nextPosition();
        virtual double nextDirection() = 0;

        double currentTheta, currentAlpha;
};

#endif

