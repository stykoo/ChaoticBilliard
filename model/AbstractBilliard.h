#ifndef ABSTRACT_BILLIARD_H
#define ABSTRACT_BILLIARD_H

#include <string>
#include <tuple>

// Abstract class for shape function
class AbstractBilliard {
	public:
        AbstractBilliard(const double theta, const double alpha);
		virtual ~AbstractBilliard() {};

		virtual double rho(const double theta) const = 0;
		virtual double rhoMax() const = 0;
        virtual std::string string() const = 0;
		virtual AbstractBilliard* clone() const = 0;

        virtual std::tuple<double, double> xy(const double theta) const;
        double getTheta() const;
        std::tuple<double, double> getXY() const;
        std::tuple<double, double> getPhaseCoos() const;

        virtual void setPositionAndIncidence(const double theta,
                                             const double beta);
        void updatePositionAndDirection();

        static double incidence2direction(const double beta,
                                          const double theta);
        static double direction2incidence(const double alpha,
                                          const double theta);

    protected:
        AbstractBilliard();
        virtual double nextPosition();
        virtual double nextDirection() = 0;

        double currentTheta, currentAlpha;
};

#endif

