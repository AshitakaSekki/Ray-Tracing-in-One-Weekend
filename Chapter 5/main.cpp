#include <fstream>
#include <iostream>
#include "ray.h"

//Formula:t*t*dot(B,B)+2*t*dot(B,A-C)+dot(A-C,A-C)-R*R=0
float hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center; //A-C
	float a = dot(r.direction(), r.direction()); //a = dot(B,B)
	float b = 2.0*dot(oc, r.direction()); //b = dot(A-C,B)
	float c = dot(oc, oc) - radius * radius; //c = dot(A-C,A-C)-R*R
	//Formula mathod:at^2+bt+c=0
	//determine if b^2-4ac > 0
	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0*a);
	}
}

vec3 color(const ray& r) {
	float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		//normal vector
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		//map normal vector to color vector
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction =unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
	int nx = 200;
	int ny = 100;

	std::ofstream ppmfile;
	ppmfile.open("test.ppm");
	ppmfile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	for (int j = ny - 1; j >= 0; j--) {
		for(int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(255.99*col.r());
			int ig = int(255.99*col.g());
			int ib = int(255.99*col.b());

			ppmfile << ir << " " << ig << " " << ib << "\n";
		}
	}
}