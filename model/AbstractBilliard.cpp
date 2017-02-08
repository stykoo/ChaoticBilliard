#include <cmath>
#include <stdexcept>
#include "routines.h"
#include "AbstractBilliard.h"

AbstractBilliard::AbstractBilliard(const double theta, const double alpha) :
    currentTheta(theta), currentAlpha(alpha) {
}

std::tuple<double, double> AbstractBilliard::xy(const double theta) const {
    double rd = rho(theta);
    return std::make_tuple(rd * std::cos(theta), rd * std::sin(theta));
}

double AbstractBilliard::getTheta() const {
    return currentTheta;
}

std::tuple<double, double> AbstractBilliard::getXY() const {
    return xy(currentTheta);
}

std::tuple<double, double> AbstractBilliard::getPhaseCoos() const {
    return std::make_tuple(currentTheta,
        direction2incidence(currentAlpha, currentTheta));
}

void AbstractBilliard::setPositionAndIncidence(const double theta,
                                               const double beta) {
    currentTheta = wrapAngle(theta);
    currentAlpha = incidence2direction(beta, theta);
}

void AbstractBilliard::updatePositionAndDirection() {
    currentTheta = nextPosition();     
    if (std::isnan(currentTheta)) {
        throw std::runtime_error("Encountered NaN value.");
    }
    currentAlpha = nextDirection();     
    if (std::isnan(currentAlpha)) {
        throw std::runtime_error("Encountered NaN value.");
    }
}

double AbstractBilliard::incidence2direction(const double beta,
                                             const double theta) {
    return wrapAngle(M_PI - beta + theta);
}
double AbstractBilliard::direction2incidence(const double alpha,
                                             const double theta) {
    return wrapAngle(M_PI - alpha + theta);
}

double AbstractBilliard::nextPosition() {
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