#include <iostream>

/*Develop a class "Triangle on the plane" 
that is defined by the coordinates of its 
vertices. Create an array of objects of this 
class. Determine the triangle with the largest area.*/

using namespace std;

class Point {
	int x;
	int y;

public:
	Point() { x = 0; y = 0; }

	Point(int valx, int valy) { x = valx, y = valy; }

	int Getx() { return this->x; }

	int Gety() { return this->y; }
};

class Triangle {
	Point p1{0, 0};
	Point p2{0, 0};
	Point p3{0, 0};

	double segment(Point& point1, Point& point2) {
		return sqrt(pow(point1.Getx() - point2.Getx(), 2) + pow(point1.Gety() - point2.Gety(), 2));
	}

public:
	Triangle() = default;

	Triangle(Point& point1, Point& point2, Point& point3) {
		p1 = point1;
		p2 = point2;
		p3 = point3;
	}

	double area(int i) {
		double a = segment(p1, p2);
		double b = segment(p1, p3);
		double c = segment(p2, p3);

		if (a + b <= c || b + c <= a || a + c <= b) {
			cout << "Triangle " << i + 1 << "doesn't exist" << endl;
			return -1.0;
		}		
		else {
			double p = (a + b + c) / 2;
			return sqrt(p * (p - a) * (p - b) * (p - c));
		}
	}
};

void input_point(int& x, int& y, int n) {
	cout << "Please enter first coordinate for your point of triangle " << n + 1 << ":" << endl;
	cout << "x = ";
	cin >> x;
	cout << "y = ";
	cin >> y;
}

void input(Triangle* t, int init, int& n) {
	int x, y, choice;
	int max_size = init;

	do {
		if (max_size == n) {
			max_size *= 2;
			Triangle* new_t = new Triangle[max_size];
			for (int i = 0; i < n; i++) {
				new_t[i] = t[i];
			}
			delete[] t;
			t = new_t;
		}

		input_point(x, y, n);
		Point p1(x, y);

		input_point(x, y, n);
		Point p2(x, y);

		input_point(x, y, n);
		Point p3(x, y);

		new (&t[n]) Triangle(p1, p2, p3);

		n++;

		cout << "Enter 0 if you want to stop provoding input: ";
		cin >> choice;
		cin.ignore();
		cout << endl;

	} while (choice != 0);
}

int find_area(Triangle* t, int n) {
	double max_area = 0;
	double temp = t[0].area(0);
	for (int i = 1; i < n; i++) {
		if (t[i].area(i) > 0) {
			cout << "Area of triangle " << i + 1 << " = " << t[i].area(i) << endl;
			if (t[i].area(i) > temp) {
				temp = t[i].area(i);
				max_area = i;
			}
		}
	}
	return max_area;
}

int main() {
	int num = 0, initial = 10;
	Triangle* t = new Triangle[initial];

	input(t, initial, num);

	int i = find_area(t, num);
	cout << "Triangle with the biggest area:" << endl;
	cout << "Triangle " << i + 1 << " = " << t[i].area(i);

	return 0;
}
