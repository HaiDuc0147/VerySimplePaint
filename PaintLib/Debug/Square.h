#pragma once
#include"Point.h"
#include"IShape.h"
#include<memory>

class Square : public IShape {
private:
	Point _topLeft;
	Point _rightBottom;
	int _color;
public:
	Square() {};
	Square(Point, Point, int);
	string type() { return "Square"; }
	Point getTopLeft(){ return _topLeft; }
	Point getRightBottom() { return _rightBottom; }
	string toString();
	shared_ptr<IShape> parse(string);
	double area();
	double perimeter();
	shared_ptr<IShape> nextShape(Point leftTop, Point rightBottom, int color);
	int getColor() { return _color; }
};
