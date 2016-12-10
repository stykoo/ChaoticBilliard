#ifndef ROUTINES_H
#define ROUTINES_H

#include <functional>

inline double square(const double x) {
    return x*x;
}

double wrapAngle(double angle);
void solveSecondOrderEq(const double a, const double b, const double c,
                        double &sol1, double &sol2);
double brentSolver(std::function<double(double)> f, double a, double b,
                   size_t bits=32, size_t maxiter=500);

#endif
