/*
 * Vector.h
 *
 *  Created on: 23-Oct-2011
 *      Author: prateek
 */

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {

public:
	double x;
	double y;
	double z;

	Vector();

	Vector(double a,double b,double c);

	//Vector(const Vector &a);

public:
	double dot_product(Vector b);

	Vector cross_product(Vector b);

	Vector normalize();
	Vector add(Vector a);
	Vector subtract(Vector b);
	Vector multiply_scalar(double t);
	double magnitude();
	Vector operator +(Vector v);
	Vector operator -(Vector v);
	//operator for cross product
	Vector operator *(Vector v);
	//Vector operator (Vector v);

	virtual ~Vector();
};

#endif /* VECTOR_H_ */
