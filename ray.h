/*
 * ray.h
 *
 *  Created on: 23-Oct-2011
 *      Author: prateek
 */

#ifndef RAY_H_
#define RAY_H_
#include "Vector.h"

class ray {
public:
	Vector s;
	Vector e;

	ray();

	ray(Vector a,Vector b);
	virtual ~ray();
};

#endif /* RAY_H_ */
