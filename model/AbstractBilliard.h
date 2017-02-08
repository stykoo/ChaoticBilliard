#ifndef ABSTRACT_BILLIARD_H
#define ABSTRACT_BILLIARD_H

#include <cmath>
#include <string>
#include <tuple>
#include <cassert>
#include <stdexcept>
#include "routines.h"

// Abstract class for shape function
class AbstractBilliard {
	public:
        AbstractBilliard(const double theta, const double alpha) :
            currentTheta(theta), currentAlpha(alpha) {}
		virtual ~AbstractBilliard() {};

		virtual double rho(const double theta) const = 0;
		virtual double rhoMax() const = 0;
        virtual std::string string() const = 0;
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

        virtual void setPositionAndIncidence(const double theta,
                                             const double beta) {
            currentTheta = wrapAngle(theta);
            currentAlpha = incidence2direction(beta, theta);
        }

        void updatePositionAndDirection() {
            currentTheta = nextPosition();     
            if (std::isnan(currentTheta)) {
                throw std::runtime_error("Encountered NaN value.");
            }
            currentAlpha = nextDirection();     
            if (std::isnan(currentAlpha)) {
                throw std::runtime_error("Encountered NaN value.");
            }
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
        virtual double nextPosition() {
            const double currentX = rho(currentTheta) * std::cos(currentTheta);
            const double currentY = rho(currentTheta) * std::sin(currentTheta);

            // Equation of the line: ux+xy+w=0
            const double u = -std::sin(currentAlpha);
            const double v = std::cos(currentAlpha);
            const double w = - (u*currentX + v*currentY);

            auto fun = [&] (const double &t) {
                return rho(t) * (u * std::cos(t) + v * std::sin(t)) + w;
            };

            const double eps = 1e-6;
            double nextTheta = bisectionSolver(fun, currentTheta + eps,
                                               currentTheta + 2*M_PI - eps);

            return wrapAngle(nextTheta);
        }

        virtual double nextDirection() = 0;

        double currentTheta, currentAlpha;
};

#endif

