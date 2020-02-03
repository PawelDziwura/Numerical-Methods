
#include<iostream>

using namespace std;

struct Point {
	double x;
	double y;
};

double function(Point point) {
	return 2 * point.x * point.x + 0 * point.y;
}

double forwart_euler(int n, double a, double b, double alpha) {
	double h;
	Point point;
	h = (b - a) / (double)(n);
	point.x = a;
	point.y = alpha;
	for (int i = 0; i < n; i++) {
		point.x = a + i * h;
		cout << "x: " << point.x << " y: " << point.y << endl;
		point.y = point.y + h * function(point);
	}
	cout << "x: " << b << " y: " << point.y << endl;
	return point.y;
}

double backward_euler(int n, double a, double b, double alpha) {
	double h;
	double px, py;
	Point point, point2;
	h = (b - a) / (double)(n);
	point.x = a;
	point.y = alpha;
	double tempX, tempY;
	cout << "x: " << point.x << " y: " << point.y << endl;
	do {
		tempY = point.y + h * function(point);
		tempX = point.x + h;
		point2.y = tempY;
		point2.x = tempX;
		point.y += h * (function(point2) + function(point)) / 2;

		point.x += h;
		cout << "x: " << point.x << " y: " << point.y << endl;
	} while (point.x < n);
	cout << endl;
	return point.y;
}

double improved_euler(int n, double a, double b, double alpha) {
	double h;
	double py, px;
	double forward, backward;
	Point point;
	h = (b - a) / (double)(n);
	point.x = a;
	point.y = alpha;
	for (int i = 0; i < n; i++) {
		point.x = a + i * h;
		px = point.x;
		py = point.y;
		cout << "x: " << point.x << " y: " << point.y << endl;
		point.y = point.y + h * function(point);
		forward = point.y;
		cout << "forward: " << forward << endl;
		point.x = point.x + i * h + h;
		point.y = py + h * function(point);
		backward = point.y;
		cout << "backward: " << backward << endl;
		point.y = (forward + backward) / 2;
		cout << "y: " << point.y << endl;
		point.x = px;
	}
	return point.y;
}

double direct_iteration(int n, double a, double b, double alpha) {
	double h;
	double predyktor;
	double korektor, korektor2;
	double px = 0, py = 0;
	Point point;
	h = (b - a) / (double)(n);
	point.x = a;
	point.y = alpha;
	cout << "x: " << point.x << " y: " << point.y << endl;
	for (int i = 0; i < n; i++) {
		point.x = a + i * h + 1;
		py = point.y;
		point.y = py + h * function(point);
		predyktor = point.y;
		cout << "Predyktor: " << predyktor << endl;
		//cout << "x+1: " << point.x << " py: " << py << " y+1: " << point.y << endl;


		point.y = py + h * function(point);
		korektor = point.y;
		cout << "Korektor1: " << korektor << endl;
		korektor2 = py + h * function(point);
		cout << "korektor2: " << korektor2 << endl;

		while (abs((korektor - korektor2)) > (double)0.001) {
			korektor = korektor2;
			point.y = korektor2;
			korektor2 = py + h * function(point);
			cout << "Korektor2: " << korektor2 << endl;
		}
		point.y = korektor2;
		cout << "x: " << point.x << " y: " << point.y << endl;
	}

	return point.y;
}

double runge_kutta(int n, double a, double b, double alpha) {
	double k1, k2, k3, k4;
	double h;
	Point point;
	h = (b - a) / (double)(n);
	point.x = a;
	point.y = alpha;
	double point_y = 0;
	for (int i = 0; i < n; i++) {
		point_y = point.y;


		cout << "x: " << point.x << " y: " << point.y << " h: " << h << endl;

		k1 = h * function(point);
		//cout << "k1 -> x: " << point.x << " y: " << point.y << endl;

		point.x = a + (i * h) + h / 2;
		point.y = point_y + (k1 / 2);
		k2 = h * function(point);
		//cout << "k2 -> x: " << point.x << " y: " << point.y << endl;

		point.y = point_y + (k2 / 2);
		k3 = h * function(point);
		//cout << "k3 -> x: " << point.x << " y: " << point.y << endl;

		point.x = a + i * h + h;

		point.y = point_y + k3;
		k4 = h * function(point);
		//cout << "k4 -> x: " << point.x << " y: " << point.y << endl;
		point.y = point_y;

		cout << "x: " << point.x << " k1: " << k1 << " k2: " << k2 << " k3: " << k3 << " k4: " << k4 << endl;
		point.y = ((k1 + 2 * k2 + 2 * k3 + k4) / 6) + point.y;
		cout << "y: " << point.y << endl;
	}

	return point.y;
}

int main() {
	cout << backward_euler(4, 0., 4., 0.);
	cout << forwart_euler(4, 0., 4., 0.);
	cin.get();
	cin.get();
}