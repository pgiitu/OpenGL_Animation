/*
 * Vector.cpp
 *
 *  Created on: 23-Oct-2011
 *      Author: prateek
 */

#include "Vector.h"
#include <math.h>


Vector::Vector()
{
	x=0.0;
	y=0.0;
	z=0.0;
}

Vector::Vector(double a,double b,double c)
{
	x=a;
	y=b;
	z=c;
}
/*
Vector::Vector(Vector a)
{
	x=a.x;
	y=a.y;
	z=a.z;
}
*/

double Vector::dot_product(Vector a)
{
	double dotp=a.x*x+a.y*y+a.z*z;
	return dotp;
}
/*
double Vector::operator .(Vector a)
{
	double dotp=a.x*x+a.y*y+a.z*z;
	return dotp;
}
*/

Vector Vector::cross_product(Vector b)
{

	double i=y*b.z-z*b.y;
	double j=z*b.x-x*b.z;
	double k=x*b.y-y*b.x;
	Vector v(i,j,k);
	return v;

}

Vector Vector::operator *(Vector b)
{

	double i=y*b.z-z*b.y;
	double j=z*b.x-x*b.z;
	double k=x*b.y-y*b.x;
	Vector v(i,j,k);
	return v;
}


Vector Vector::normalize()
{
	double fac=sqrt(x*x+y*y+z*z);
	Vector v(x/fac,y/fac,z/fac);
	return v;
}

Vector Vector::add(Vector a)
{
	Vector v(a.x+x,a.y+y,a.z+z);
	return v;
}

Vector Vector::operator +(Vector a)
{
	Vector v(a.x+x,a.y+y,a.z+z);
	return v;
}

Vector Vector::subtract(Vector a)
{
	Vector v(x-a.x,y-a.y,z-a.z);
	return v;
}

Vector Vector::operator -(Vector a)
{
	Vector v(x-a.x,y-a.y,z-a.z);
	return v;
}

double Vector::magnitude()
{
	double d=sqrt(x*x+y*y+z*z);
	return d;
}

Vector Vector::multiply_scalar(double t)
{
	Vector v(t*x,t*y,t*z);
	return v;
}
Vector::~Vector() {
	// TODO Auto-generated destructor stub
}
