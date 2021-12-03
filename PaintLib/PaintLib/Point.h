#pragma once
#include<iostream>
using namespace std;
class Point {
private:
	int _x;
	int _y;
public:
	int x();
	int y();
	Point() {};
	Point(int, int);
	friend ostream& operator << (ostream& out, const Point& point) {
		out << point._x << "," << point._y;
		return out;
	}
	static Point* parse(string buffer);
};
