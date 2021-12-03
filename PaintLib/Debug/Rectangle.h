#pragma once
#include"Point.h"
#include"IShape.h"
#include<memory>
class CRectangle : public IShape {
private:
	Point _topLeft;
	Point _rightBottom;
	int _color;
	int _style;
	int _size;
public:
	string type() { return "Rectangle"; }
	CRectangle() {};
	CRectangle(Point, Point, int, int, int);
	Point getTopLeft() { return _topLeft; }
	Point getRightBottom() { return _rightBottom; }
	string toString();
	shared_ptr<IShape> parse(string);
	double area();
	double perimeter();
	shared_ptr<IShape> nextShape(Point leftTop, Point rightBottom, int color, int style, int size);
	int getColor() { return _color; }
	int getStyle() { return _style; }
	int getSize() { return _size; }
};