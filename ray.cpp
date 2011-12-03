/*
 * ray.cpp
 *
 *  Created on: 23-Oct-2011
 *      Author: prateek
 */

#include "ray.h"
#include "Vector.h"

ray::ray()
{
	s.x=0.0;
	s.y=0.0;
	s.z=0.0;
	e.x=0.0;
	e.y=0.0;
	e.z=0.0;
}

ray::ray(Vector a,Vector b)
{
	s.x=a.x;
	s.y=a.y;
	s.z=a.z;
	e.x=b.x;
	e.y=b.y;
	e.z=b.z;
}

ray::~ray() {
	// TODO Auto-generated destructor stub
}
