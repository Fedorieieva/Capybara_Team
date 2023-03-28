#include <iostream>

/*Develop a class "convex quadrilateral
on the plane", which is defined by the
coordinates of its vertices. Create
an array of objects of this class.
Determine the quadrilateral with the
largest perimeter.*/

using namespace std;

class Point {
	int x;
	int y;

public:
	Point() { x = 0; y = 0; }

	Point(int valx, int valy) { x = valx, y = valy; }

	int Getx() { return x; }

	int Gety() { return y; }
};

class Quadrilateral {
	Point p1{0, 0};
	Point p2{0, 0};
	Point p3{0, 0};
	Point p4{0, 0};

	double segment(Point& point1, Point& point2) {
		return sqrt(pow(point1.Getx() - point2.Getx(), 2) + pow(point1.Gety() - point2.Gety(), 2));
	}

public:
	Quadrilateral() = default;

	Quadrilateral(Point& point1, Point& point2, Point& point3, Point& point4) {
		p1 = point1;
		p2 = point2;
		p3 = point3;
		p4 = point4;
	}

	double perimeter(int i) {
		double a = segment(p1, p2);
		double b = segment(p3, p2);
		double c = segment(p3, p4);
		double d = segment(p1, p4);

		if (a == 0 || b == 0 || c == 0 || d == 0) {
			cout << "Convex quadrilateral "<< i + 1 << " doesn't exist" << endl;
			return -1.0;
		}
		else {
			return a + b + c + d;
		}
	}
};

void input_point(int& x, int& y, int n) {
	cout << "Please enter coordinates for your convex quadrilateral " << n + 1 << ":" << endl;
	cout << "x = ";
	cin >> x;
	cout << "y = ";
	cin >> y;
}

void input(Quadrilateral* q, int initial, int& n) {
	int max_size = initial;
	int x, y, choice = 1;

	do {
		if (n == max_size) {
			max_size *= 2;
			Quadrilateral* new_q = new Quadrilateral[max_size];

			for (int i = 0; i < n; i++) {
				new_q[i] = q[i];
			}

			delete[] q;
			q = new_q;
		}

		input_point(x, y, n);
		Point p1(x, y);

		input_point(x, y, n);
		Point p2(x, y);

		input_point(x, y, n);
		Point p3(x, y);

		input_point(x, y, n);
		Point p4(x, y);

		new (&q[n]) Quadrilateral(p1, p2, p3, p4);

		n++;

		cout << "Enter 0 if you want to stop providing input: ";
		cin >> choice;
		cin.ignore();
		cout << endl;

	} while (choice != 0);
}

int find_perimeter(Quadrilateral* q, int n) {
	double max_per = 0;
	double temp = q[0].perimeter(0);

	for (int i = 0; i < n; i++) {
		if (q[i].perimeter(i) > 0) {
			cout << "Perimeter of convex quadrilateral " << i + 1 << " = " << q[i].perimeter(i) << endl;
			if (q[i].perimeter(i) > temp) {
				temp = q[i].perimeter(i);
				max_per = i;
			}
		}		
	}
	return max_per;
}

int main() {
	int initial = 10, num = 0;

	Quadrilateral* q = new Quadrilateral[initial];

	input(q, initial, num);

	int i = find_perimeter(q, num);
	cout << "Convex quadrilateral with the greatest perimeter:" << endl;
	cout << "Convex quadrilateral " << i + 1 << " = " << q[i].perimeter(i) << endl;

	return 0;
}