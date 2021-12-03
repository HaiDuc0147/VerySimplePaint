#pragma once
#include <cstddef>
#include"IShape.h"
#include<memory>
#include"Point.h"
#include<vector>
#include"Rectangle.h"
#include"Line.h"
#include"Ellipse.h"
using namespace std;
class ShapeFactory{
private:
	ShapeFactory();
	inline static ShapeFactory* _instance = NULL;
	vector<shared_ptr<IShape>> _prototypes;
public:
	
	static ShapeFactory* instance() {
		if (_instance == NULL) {
			_instance = new ShapeFactory();
		}
		return _instance;
	}
	shared_ptr<IShape> create(int type, Point topLeft, Point rightBottom, int color, int style, int size);
	shared_ptr<IShape> parse(string type, string value);
};