#ifndef ROUTINES_H
#define ROUTINES_H

#include <functional>

#define DEFAULT_PREC 1.48e-8
#define DEFAULT_MAXITER 500

double wrapAngle(const double angle);
void solveSecondOrderEq(const double a, const double b, const double c,
                        double &sol1, double &sol2);
double brentSolver(std::function<double(double)> f, double a, double b,
                   double prec=DEFAULT_PREC, int maxiter=DEFAULT_MAXITER);

#endif
