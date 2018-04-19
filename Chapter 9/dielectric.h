#ifndef DIELECTRICH
#define DIELECTRICH

#include "material.h"
#include "metal.h"

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (v - dt * n) - sqrt(discriminant)*n;
		return true;
	}
	else
		return false;
}

class dielectric :public material {
public:
	dielectric(float ri) :ref_idx(ri) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nr;
		attenuation = vec3(1.0, 1.0, 0.0);
		vec3 refracted;
		if (dot(r_in.direction, rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nr = ref_idx;
		}
		else {
			outward_normal = rec.normal;
			ni_over_nr = 1.0 / ref_idx;
		}
	}

	float ref_idx;
};

#endif // !DIELECTRICH
