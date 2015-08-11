#ifndef _CTRIPLE_
#define _CTRIPLE_

#include "defines.h"

class OCEAN_API CTriple {
public:
	CTriple(float a=0, float b=0, float c=0);

	float &operator[](int n);
	float *getArray();
	//float operator[](int n) const;
	
	// these ops create a new value, so I can't return by reference
	CTriple operator+(const CTriple &t) const;
	CTriple operator-(const CTriple &t) const;
	CTriple operator*(const float &d) const;
	CTriple operator/(const float &d) const;

	// ops for speed
	void add(const CTriple &a);
	void add(const CTriple &a, const CTriple &b);
	void sub(const CTriple &a);
	void sub(const CTriple &a, const CTriple &b);
	void mult(const float &a);
	void div(const float &a);
	

	// these modify "this" triple, so return by reference
	CTriple &operator+=(const CTriple &t);
	CTriple &operator-=(const CTriple &t);
	CTriple &operator*=(const float &d);
	CTriple &operator/=(const float &d);
	
	float length();	
	float dot(const CTriple &a);
	void norm();
	void cross(const CTriple &a);
	void cross(const CTriple &a, const CTriple &b);
	void clamp(const float _low, const float _high);
	
	// cartesian/polar/spherical
	void sphereToCart();

	// the data
	float v[3];
};

#endif
