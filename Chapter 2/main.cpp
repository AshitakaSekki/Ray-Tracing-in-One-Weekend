#include <fstream>
#include <iostream>
#include "vec3.h"

int main() {
	int nx = 200;
	int ny = 100;

	std::ofstream outfile;
	outfile.open("test.ppm");
	outfile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--) {
		for(int i = 0; i < nx; i++) {
			vec3 col;
			col.e[0] = float(i) / float(nx);
			col.e[1] = float(j) / float(ny);
			col.e[2] = 0.2;
			int ir = int(255.99*col.r());
			int ig = int(255.99*col.g());
			int ib = int(255.99*col.b());
			outfile << ir << " " << ig << " " << ib << "\n";
		}
	}
}