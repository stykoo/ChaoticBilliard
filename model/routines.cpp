#include <cmath>
#include <stdexcept>
#include "routines.h"

int sign(const double x) {
    return (0. < x) - (x < 0.);
}

double wrapAngle(double angle) {
    angle = std::fmod(angle, 2. * M_PI); 
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

void solveSecondOrderEq(const double a, const double b, const double c,
                       double &sol1, double &sol2) {
    double d = b*b - 4*a*c;
    if(d < 0) {
        throw std::domain_error("Second order equation has no real solution.");
    }
    // Trick for numerical stability
    double tmp = -0.5 * (b + sign(b) * std::sqrt(d));
    sol1 = tmp / a;
    sol2 = c / tmp;
}

double brentSolver(std::function<double(double)> f, double a, double b,
                   size_t bits, size_t maxiter){
    bits = std::min(sizeof(double) / 2, bits);
    double tol = std::ldexp(1., 1-bits);

    double fa = f(a), fb = f(b);

    if (fa * fb >= 0) {
        throw std::runtime_error("Could not use Brent's method.");
    }

    if (std::abs(fa) < std::abs(fb)) {
        std::swap(a, b);
    }

    double c = a, fc = fa;
    bool mflag = true;

    double d = 0., s = 0., fs = 0.;
    size_t i = maxiter;

    while (i-- && fb != 0. && std::abs(b - a) > tol) {
        // Choose algorithm for intermediate point s
        if (fa != fc && fb != fc) {
            // Inverse quadratic interpolation
            s = a * fb * fc / ((fa - fb) * (fa - fc));
            s += b * fa * fc / ((fb - fa) * (fb - fc));
            s += c * fa * fb / ((fc - fa) * (fc - fb));
        } else {
            // Secant method
            s = b - fb * (b - a) / (fb - fa);
        }

        double t1 = 3. * a + b, t2 = b;
        if (t1 > t2) { std::swap(t1, t2); }
        double t3 = (mflag) ? std::abs(b - c) : std::abs(c - d);
        if (s < t1 || s > t2 || t3 <= 2. * std::abs(s - b) || t3 <= tol) {
            // Bissection method
            s = a + (a - b) / 2.;
            mflag = true;
        } else {
            mflag = false;
        }

        fs = f(s);
        d = c;
        c = b;

        // We replace one of the bounds by s
        if (fa * fs < 0) {
            b = s;
        } else {
            a = s;
        }

        if (std::abs(fa) < std::abs(fb)) {
            std::swap(a, b);
        }
        fa = f(a);
        fb = f(b);
        fc = f(c);
    }

    return b;
}
