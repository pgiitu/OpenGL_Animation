/*
 * intersection_point.h
 *
 *  Created on: 23-Oct-2011
 *      Author: prateek
 */

#ifndef INTERSECTION_POINT_H_
#define INTERSECTION_POINT_H_
#include "vector.h"
#include "ray.h"
class intersection_point {
public:
	ray r;
	vector v; //intersection point
	int intersect;
	vector ref; //direction of reflection

	intersection_point();
	void print_intersection_point();
	virtual ~intersection_point();
};

#endif /* INTERSECTION_POINT_H_ */
