#include"Ellipse.h"
#include<sstream>
#include<vector>
#include"Tokenizer.h"
CEllipse::CEllipse(Point topLeft, Point rightBottom, int color, int style, int size) {
	_topLeft = topLeft;
	_rightBottom = rightBottom;
	_color = color;
	_style = style;
	_size = size;
}
string CEllipse::toString() {
	stringstream builder;
	builder << "Ellipse: " << _topLeft << " " << _rightBottom << " " << _color << " " << _style << " " << _size;
	return builder.str();
}
shared_ptr<IShape> CEllipse::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer);
	Point* a = Point::parse(tokens[1]);
	Point* b = Point::parse(tokens[2]);
	auto ellipse = make_shared <CEllipse>(*a, *b, stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
	return ellipse;
}

double CEllipse::area() {
	double result = abs(_rightBottom.x() - _topLeft.x()) * abs(_rightBottom.y() - _topLeft.y());
	return result;
}
double CEllipse::perimeter() {
	double result = (abs(_rightBottom.x() - _topLeft.x()) + abs(_rightBottom.y() - _topLeft.y())) * 2;
	return result;
}
shared_ptr<IShape> CEllipse::nextShape(Point leftTop, Point rightBottom, int color, int style, int size) {
	return make_shared<CEllipse>(leftTop, rightBottom, color, style, size);
}