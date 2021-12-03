#pragma once
#include<string>
#include<memory>
#include"Point.h"
using namespace std;
class IShape {
public:
	virtual std::string type() = 0;
	virtual std::string toString() = 0;
	virtual double area() = 0;
	virtual double perimeter() = 0;
	virtual Point getTopLeft() = 0;
	virtual Point getRightBottom() = 0;
	virtual int getColor() = 0;
	virtual int getStyle() = 0;
	virtual int getSize() = 0;
	virtual shared_ptr<IShape> nextShape(Point leftTop, Point rightBottom, int color, int style, int size) = 0;
	virtual shared_ptr<IShape> parse(string value) = 0;
};