#ifndef ABSTRACT_BILLIARD_H
#define ABSTRACT_BILLIARD_H

#include <cmath>
#include <tuple>
#include <cassert>
#include "routines.h"

// Abstract class for shape function
class AbstractBilliard {
	public:
        AbstractBilliard(const double theta, const double alpha) :
            currentTheta(theta), currentAlpha(alpha) {}
		virtual ~AbstractBilliard() {};

		virtual double rho(const double theta) const = 0;
		virtual double rhoMax() const = 0;
		virtual AbstractBilliard* clone() const = 0;

        virtual std::tuple<double, double> xy(const double theta) const {
            double rd = rho(theta);
            return std::make_tuple(rd * std::cos(theta), rd * std::sin(theta));
        }


        double getTheta() const {
            return currentTheta;
        }
        std::tuple<double, double> getXY() const {
            return xy(currentTheta);
        }
        std::tuple<double, double> getPhaseCoos() const {
            return std::make_tuple(currentTheta,
                direction2incidence(currentAlpha, currentTheta));
        }

        void setPositionAndIncidence(const double theta, const double beta) {
            currentTheta = wrapAngle(theta);
            currentAlpha = incidence2direction(beta, theta);
        }

        void updatePositionAndDirection() {
            currentTheta = nextPosition();     
            currentAlpha = nextDirection();     
        }

        static double incidence2direction(const double beta,
                                          const double theta) {
            return wrapAngle(M_PI - beta + theta);
        }
        static double direction2incidence(const double alpha,
                                          const double theta) {
            return wrapAngle(M_PI - alpha + theta);
        }

    protected:
        AbstractBilliard();
        virtual double nextPosition()
           const {
               assert(false);
           return 0;
        }
        virtual double nextDirection()
           const {
               assert(false);
           return 0;
        }

        double currentTheta, currentAlpha;
};

#endif

