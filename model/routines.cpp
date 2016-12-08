#include <cmath>
#include <stdexcept>
#include "routines.h"

double wrapAngle(const double angle) {
    return angle - 2 * M_PI * std::floor(angle / (2 * M_PI));
}

void solveSecondOrderEq(const double a, const double b, const double c,
                       double &sol1, double &sol2) {
    double d = b*b - 4*a*c;
    if(d < 0) {
        throw std::domain_error("Second order equation has no real solution.");
    }
    d = std::sqrt(d);
    sol1 = -(b + d) / (2*a);
    sol2 = (-b + d) / (2*a);
}

double brentSolver(std::function<double(double)> f, double a, double b,
                   double tol, int maxiter) {
    double fa = f(a), fb = f(b);

    if (fa * fb >= 0) {
        throw std::runtime_error("Could not use Brent's method.");
    }

    if (std::abs(fa) < std::abs(fb)) {
        std::swap(a, b);
    }

    double c = a;
    double d = 0., s = 0.;
    double fc = f(c), fs = 0.;
    bool mflag = true;
    int i = 0;

    while (i < maxiter && fb != 0. && fs != 0. && std::abs(b - a) > tol) {
        if (fa != fc and fb !=fc) {
            // Inverse quadratic interpolation
            s = a * fb * fc / ((fa - fb) * (fa - fc));
            s += b * fa * fc / ((fb - fa) * (fb - fc));
            s += c * fa * fb / ((fc - fa) * (fc - fb));
        } else {
            // Secant method
            s = b - fb * (b - a) / (fb - fa);
        }

        if ((s < (3.*a + b)/4. && s < b) || (s > (3.*a + b)/4. && s > b) ||
                (mflag && std::abs(s-b) >= std::abs(b-c) / 2.) ||
                (!mflag && std::abs(s-b) >= std::abs(c-d) / 2.) ||
                (mflag && std::abs(b-c) < tol) ||
                (!mflag && std::abs(c-d) < tol)
           ) {
            // Bissection method
            s = (a + b) / 2;
            mflag = true;
        } else {
            mflag = false;
        }

        fs = f(s);
        d = c;
        c = b;
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

        ++i;
    }

    if (std::abs(fs) < std::abs(fb)) {
        return s;
    } else {
        return b;
    }
}
