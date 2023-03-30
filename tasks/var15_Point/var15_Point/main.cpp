#include <iostream>

/*Develop a class "material point" 
which is characterized by the 
coordinates of the initial position 
and the vector of uniform velocity 
V = (V1,V2,V3,). Create an array of 
objects of this class. Determine the 
points (their numbers) that enter the 
first octant for a user-defined time.*/

using namespace std;

class Vector {
	double v1;
	double v2;
	double v3;

public:
	Vector() { v1 = 0; v2 = 0; v3 = 0; }

	Vector(double v1val, double v2val, double v3val) {
		v1 = v1val;
		v2 = v2val;
		v3 = v3val;
	}

	double Getv1() { return v1; }

	double Getv2() { return v2; }

	double Getv3() { return v3; }
};

class Point {
	int x = 0;
	int y = 0;
	int z = 0;
	Vector v{0, 0, 0};

public:
	Point() = default;

	Point(int xval, int yval, int zval, Vector vect) {
		x = xval;
		y = yval;
		z = zval;
		v = vect;
	}

	bool first_octant(double t) {
		double x_t = x + v.Getv1() * t;
		double y_t = y + v.Getv2() * t;
		double z_t = z + v.Getv3() * t;

		return x_t >= 0 && y_t >= 0 && z_t >= 0;
	}
};

void input_point(int& x, int& y, int& z) {
	cout << "Please enter coordinates for your Point:" << endl;
	cout << "x = ";
	cin >> x;
	cout << "y = ";
	cin >> y;
	cout << "z = ";
	cin >> z;
}

void input_vect(int& v1, int& v2, int& v3) {
	cout << "Please enter vectors for your Point:" << endl;
	cout << "v1 = ";
	cin >> v1;
	cout << "v2 = ";
	cin >> v2;
	cout << "v3 = ";
	cin >> v3;
}

void input(Point* p, int& num, int initial) {
	int x, y, z, v1, v2, v3, choice = 1;
	int max_size = initial;
	Vector v;

	do {
		if (num == max_size) {
			Point* new_p = new Point[max_size];

			for (int i = 0; i < num; i++) {
				new_p[i] = p[i];
			}

			delete[] p;
			p = new_p;
		}

		input_point(x, y, z);
		input_vect(v1, v2, v3);
		new(&v) Vector(v1, v2, v3);
		new (&p[num]) Point(x, y, z, v);

		num++;

		cout << "Enter 0 if you want to stop providing input:";
		cin >> choice;
		cin.ignore();
		cout << endl;

	} while (choice != 0);

}

void octant(Point* p, int num) {
	double t;

	cout << endl << "Enter time: ";
	cin >> t;

	cout << endl << "Here you can see poiints that are located in the first octant at time t = " << t << ":" << endl;
	for (int i = 0; i < num; i++) {
		if (p[i].first_octant(t)) 
			cout << "Point " << i + 1 << endl;
	}
}

int main() {
	int num = 0, initial = 10;

	Point* p = new Point[initial];
	input(p, num, initial);
	octant(p, num);
	delete[] p;

	return 0;
}