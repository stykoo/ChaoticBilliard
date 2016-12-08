#ifndef ABSTRACT_BILLIARD_H
#define ABSTRACT_BILLIARD_H

#include <cmath>
#include <tuple>

// Abstract class for shape function
class AbstractBilliard {
	public:
		virtual ~AbstractBilliard() {};
		virtual double rho(const double theta) const = 0;
		virtual double rhoMax() const = 0;
		virtual AbstractBilliard* clone() const = 0;

        virtual std::tuple<double, double> xy(const double theta){
            double rd = rho(theta);
            return std::make_tuple(rd * std::cos(theta), rd * std::sin(theta));
        }

        virtual double nextPosition(const double theta, const double alpha)
           const {
               (void) theta;
               (void) alpha;
           return 0;
        }
};

#endif

