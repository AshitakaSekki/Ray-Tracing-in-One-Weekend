#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "material.h"

class sphere :public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r, material *m) :center(cen), radius(r), ma(m) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
	material *ma;
};

//Formula:t*t*dot(B,B)+2*t*dot(B,A-C)+dot(A-C,A-C)-R*R=0
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center; //A-C
	float a = dot(r.direction(), r.direction()); //a = dot(B,B)
	float b = 2.0*dot(oc, r.direction()); //b = dot(A-C,B)
	float c = dot(oc, oc) - radius * radius; //c = dot(A-C,A-C)-R*R
	//Formula mathod:at^2+bt+c=0
	//determine if b^2-4ac > 0
	float discriminant = b * b - 4 * a*c;
	if (discriminant > 0) {
		//save the minimal root
		float temp = (-b - sqrt(discriminant)) / (2 * a);
		if (temp<t_max&&temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = ma;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / (2 * a);
		if (temp<t_max&&temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = ma;
			return true;
		}
	}
	return false;
}

#endif