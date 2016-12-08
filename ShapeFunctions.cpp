#include <cmath>
#include "ShapeFunctions.h"

Circle::Circle(double r) : ShapeFunction(), r(r) {}

double Circle::operator()(double theta) const {
	(void) theta;
	return r;
}

double Circle::max() const {
	return r;
}

Ellipse::Ellipse(double e, double p) : ShapeFunction(), 
	e(e), p(p) {}

double Ellipse::operator()(double theta) const {
	return p/(1.-e*std::cos(theta));
}

double Ellipse::max() const {
	return p/(1.-e);
}

DeformedCircle::DeformedCircle(double eps, double r) : ShapeFunction(), 
	eps(eps), r(r) {}

double DeformedCircle::operator()(double theta) const {
	return r + eps*std::cos(theta);
}

double DeformedCircle::max() const {
	return r+eps;
}
