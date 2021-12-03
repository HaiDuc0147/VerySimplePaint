#include"Line.h"
#include<sstream>
#include"Tokenizer.h"
#include<vector>
#include"Point.h"
Line::Line(Point start, Point end, int color, int style, int size) {
	_start = start;
	_end = end;
	_color = color;
	_style = style;
	_size = size;
}
string Line::toString() {
	stringstream builder;
	builder << "Line: " << _start << " " << _end << " " << _color << " " << _style << " " << _size;
	return builder.str();
}
shared_ptr<IShape> Line::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer);
	Point* a = Point::parse(tokens[1]);
	Point* b = Point::parse(tokens[2]);
	auto line = make_shared<Line>(*a, *b, stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
	return line;
}

double Line::area() {
	return 0;
}
double Line::perimeter() {
	int dx = _start.x() - _end.x();
	int dy = _start.y() - _end.y();
	return sqrt(dx * dx + dy * dy);
}
shared_ptr<IShape> Line::nextShape(Point start, Point end, int color, int style, int size) {
	return make_shared<Line>(start, end, color, style, size);
}