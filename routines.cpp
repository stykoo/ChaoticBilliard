#include <cmath>
#include <stdexcept>
#include "routines.h"

int sign(const double x) {
    return (0. < x) - (x < 0.);
}

double wrapAngle(const double angle) {
    return angle - 2 * M_PI * std::floor(angle / (2 * M_PI));
}

void solveSecondOrderEq(const double a, const double b, const double c,
                       double &sol1, double &sol2) {
    double d = b*b - 4*a*c;
    if(d < 0 || a == 0.) {
        throw std::runtime_error("Could not compute roots of equation.");
    }
    // Trick for numerical stability
    double tmp = -0.5 * (b + sign(b) * std::sqrt(d));
    sol1 = tmp / a;
    sol2 = c / tmp;
}

// From https://en.wikipedia.org/wiki/Brent%27s_method
double brentSolver(std::function<double(double)> f, double a, double b,
                   int bits, size_t maxiter) {
    bits = std::min(std::sizeof(double), bits);
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

        double t1 = 0.25 * (3.*a + b), t2 = b;
        if(t1 > t2) { std::swap(t1, t2); }
        double t3 = (mflag) ? std::abs(b-c) : std::abs(c-d);
        if ((s < t1) || (s > t2) || t3 <= 2 * std::abs(s-b) || t3 <= tol) {
            // Bissection method
            s = (a + b) / 2;
            mflag = true;
        } else {
            mflag = false;
        }

        fs = f(s);
        d = c;
        c = b;

        // One of the two bounds is replaced by s
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
