#include"Point.h"
#include<string>
#include<vector>
#include"Tokenizer.h"
using namespace std;
Point::Point(int x, int y) {
	_x = x;
	_y = y;
}
int Point::x() { return _x; }
int Point::y() { return _y; }
Point* Point::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer, ",");
	int a = stoi(tokens[0]);
	int b = stoi(tokens[1]);
	Point* p = new Point(a, b);
	return p;
}