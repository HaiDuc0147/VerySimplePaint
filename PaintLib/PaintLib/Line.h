#pragma once
#include"Point.h"
#include"IShape.h"
#include<memory>
class Line : public IShape {
private:
	Point _start;
	Point _end;
	int _color;
	int _style;
	int _size;
public:

	Line() {};
	string type() { return "Line"; }
	Line(Point, Point, int, int, int);
	Point getTopLeft() { return _start; }
	Point getRightBottom() { return _end; }
	string toString();
	shared_ptr<IShape> parse(string);
	double area();
	double perimeter();
	shared_ptr<IShape> nextShape(Point start, Point end, int color, int style, int size);
	int getColor() { return _color; }
	int getStyle() { return _style; }
	int getSize() { return _size; }
};