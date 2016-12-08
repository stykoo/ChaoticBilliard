#ifndef ABSTRACT_BILLIARD_H
#define ABSTRACT_BILLIARD_H

// Abstract class for shape function
class AbstractBilliard {
	public:
		virtual ~AbstractBilliard() {};
		virtual double rad(const double theta) const = 0;
		virtual double max() const = 0;
        virtual double nextPosition(const double theta, const double alpha)
           const {
        }

		virtual AbstractBilliard* clone() const = 0;
		virtual double operator()(const double theta) const {
            return rad(theta);
        }
};

#endif

