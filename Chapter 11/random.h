#ifndef RANDOMH
#define RANDOMH

#include "vec3.h"

//generate random number in the range 0<=ran<1
float random() { return rand() % (100) / (float)(100); }
//random reflected ray
vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		//p vector to random direction
		p = 2.0*vec3(random(), random(), random()) - vec3(1, 1, 1);
		//make sure length of p is less than 1.0
	} while (dot(p, p) >= 1.0);
	return p;
}

#endif 
