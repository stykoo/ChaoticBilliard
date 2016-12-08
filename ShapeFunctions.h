#ifndef SHAPEFUNCTIONS_H
#define SHAPEFUNCTIONS_H

#define M_PI 3.14159265358979323846

// Abstract class for shape function
class ShapeFunction {
	public:
		virtual ~ShapeFunction() = 0;
		virtual double operator()(const double theta) const = 0;
		virtual double max() const = 0;
		virtual ShapeFunction* clone() const = 0;
};

inline ShapeFunction::~ShapeFunction(){} // You HAVE TO write it!

class Circle : public ShapeFunction {
	public:
		Circle(double r = 1.0);
		~Circle(){};
		double operator()(const double theta) const;
		double max() const;
		Circle* clone() const { return new Circle(*this); }

	private:
		const double r;
};

class Ellipse : public ShapeFunction {
	public:
		Ellipse(double e, double p = 1.0);
		~Ellipse(){};
		double operator()(const double theta) const;
		double max() const;
		Ellipse* clone() const { return new Ellipse(*this); }

	private:
		const double e, p;
};

class DeformedCircle : public ShapeFunction {
	public:
		DeformedCircle(double eps, double r = 1.0);
		~DeformedCircle(){}
		double operator()(const double theta) const;
		double max() const;
		DeformedCircle* clone() const { return new DeformedCircle(*this); }

	private:
		const double eps, r;
};

#endif

