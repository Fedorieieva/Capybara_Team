#include <iostream>
#include <iomanip>

/*- Розробити клас Point, що містить координати х та у
- Розробити Points, що містить масив об'єктів Point
- В основній програмі створити два об'єкти-масиви Points, 
	створити еще один об'єкт-масив Points, 
	у якому необхідно записати усі точки І чверті
- Знайти точки з останнього об'єкта-масива, між якими найбільша відстань */

using namespace std;

class Point {
	int x;
	int y;

public:

	Point(){}

	Point(int valuex, int valuey) {
		x = valuex;
		y = valuey;
	}

	int Getx() { return x; }
	int Gety() { return y; }

	void print() {
		cout << "x = " << setw(8) << left << x;
		cout << "y = " << setw(8) << left << y << endl << endl;
	}
};

void input_points(Point* points, int initial, int& num) {
	int x, y, choice = 1;
	int max_size = initial;

	do {
		if (num == max_size) {
			max_size *= 2;
			Point* new_points = new Point[initial];

			for (int i = 0; i < num; i++) {
				new_points[i] = points[i];
			}

			delete[] points;
			points = new_points;
		}

		cout << "Please enter coordinates for your points: " << endl;
		cout << "x = ";
		cin >> x;
		cout << "y = ";
		cin >> y;

		new (&points[num]) Point(x, y);
		num++;

		cout << "Enter 0, if you want to stop providing input: ";
		cin >> choice;
		cin.ignore();
		cout << endl;

	} while (choice != 0);
}

void first_quadrant(Point* points1, Point* points2, int num1, int& num2) {
	int i = 0;
	do {
		if (points1[i].Getx() > 0 && points1[i].Gety() > 0) {
			points2[num2] = points1[i];
			num2++;
		}
		i++;
	} while (i != num1);
}

void print_all_points(Point* points, int num) {
	for (int i = 0; i < num; i++) {
		cout << "Point " << i + 1 << ":" << endl;
		points[i].print();
	}
}

void find_segment(Point* points, int num, int& point1, int& point2) {
	double segment(Point points1, Point points2);
	for (int i = 0; i < num - 1; i++) {
		for (int j = 1; j < num; j++) {
			if (segment(points[i], points[j]) > segment(points[i + 1], points[j])) {
				point1 = i;
				point2 = j;
			}
		}
	}
}

double segment(Point points1, Point points2) {
	return sqrt(pow(points1.Getx() - points2.Getx(), 2) + pow(points1.Gety() - points2.Gety(), 2));
}

int main() {
	int num1 = 0, num2 = 0, initial = 10;	
	Point* points = new Point[initial];

	input_points(points, initial, num1);
	cout << "Here you can see the points you have entered:" << endl;
	print_all_points(points, num1);

	Point* points_first_quadrant = new Point[num1];

	first_quadrant(points, points_first_quadrant, num1, num2);
	cout << "Here you can see the points that are located in the first quadrant:" << endl;
	print_all_points(points_first_quadrant, num2);

	int point1 = 0, point2 = 0;
	find_segment(points_first_quadrant, num2, point1, point2);
	cout << "Here you can see the points that give us the largest segment:" << endl;
	cout << "Point " << point1 + 1 << ":" << endl;
	points_first_quadrant[point1].print();
	cout << "Point " << point2 + 1 << ":" << endl;
	points_first_quadrant[point2].print();
	cout << "segment = " << segment(points_first_quadrant[point1], points_first_quadrant[point2]);

	delete[] points;
	delete[] points_first_quadrant;
	return 0;
}