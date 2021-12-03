#include"ShapeFactory.h"
const int RECTANGLE = 0;
const int LINE = 1;
const int ELLIPSE = 2;
const int SQAURE = 3;

ShapeFactory::ShapeFactory() {
	_prototypes.push_back(make_shared<CRectangle>());
	_prototypes.push_back(make_shared<Line>());
	_prototypes.push_back(make_shared<CEllipse>());
}
shared_ptr<IShape> ShapeFactory::create(int type, Point topLeft, Point rightBottom, int color, int style, int size) {
	return _prototypes[type]->nextShape(topLeft, rightBottom, color, style, size);
}
shared_ptr<IShape> ShapeFactory::parse(string type, string value) {
	shared_ptr<IShape> shape = NULL;
	for (int i = 0; i < _prototypes.size(); i++) {
		if (_prototypes[i]->type() == type) {
			shape = _prototypes[i]->parse(value);
			break;
		}
	}
	return shape;
	
}