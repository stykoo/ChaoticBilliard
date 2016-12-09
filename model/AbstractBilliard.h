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

        std::tuple<double, double> xy(const double theta) const {
            double rd = rho(theta);
            return std::make_tuple(rd * std::cos(theta), rd * std::sin(theta));
        }


        double getTheta() const {
            return currentTheta;
        }
        std::tuple<double, double> getXY() const {
            return xy(currentTheta);
        }
        std::tuple<double, double> getPhaseCoos() {
            return std::make_tuple(currentTheta,
                wrapAngle(currentAlpha - currentTheta - M_PI));
        }

        virtual double nextPosition(const double theta, const double alpha)
           const {
               assert(false);
               (void) theta;
               (void) alpha;
           return 0;
        }
        virtual double nextDirection(const double alpha, const double theta)
           const {
               assert(false);
               (void) theta;
               (void) alpha;
           return 0;
        }
        virtual void updatePositionAndDirection() {
            currentTheta = nextPosition(currentTheta, currentAlpha);     
            currentAlpha = nextDirection(currentAlpha, currentTheta);     
        }

    private:
        AbstractBilliard();
        double currentTheta, currentAlpha;
};

#endif

