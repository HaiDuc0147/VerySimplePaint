#include"Rectangle.h"
#include<sstream>
#include<vector>
#include"Tokenizer.h"
#include<string>
using namespace std;
CRectangle::CRectangle(Point topLeft, Point rightBottom, int color, int style, int size) {
	_topLeft = topLeft;
	_rightBottom = rightBottom;
	_color = color;
	_style = style;
	_size = size;
}
string CRectangle::toString() {
	stringstream builder;
	builder << "Rectangle: " << _topLeft << " " << _rightBottom << " " << _color << " " << _style << " " << _size;;
	return builder.str();
}
shared_ptr<IShape> CRectangle::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer);
	Point* a = Point::parse(tokens[1]);
	Point* b = Point::parse(tokens[2]);
	auto rectangle = make_shared <CRectangle>(*a, *b, stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
	return rectangle;
}

double CRectangle::area() {
	double result = abs(_rightBottom.x() - _topLeft.x()) * abs(_rightBottom.y() - _topLeft.y());
	return result;
}
double CRectangle::perimeter() {
	double result = (abs(_rightBottom.x() - _topLeft.x()) + abs(_rightBottom.y() - _topLeft.y())) * 2;
	return result;
}
shared_ptr<IShape> CRectangle::nextShape(Point leftTop, Point rightBottom, int color, int style, int size) {
	return make_shared<CRectangle>(leftTop, rightBottom, color, style, size);
}