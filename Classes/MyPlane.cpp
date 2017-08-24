#include "MyPlane.h"


bool MyPlane::initWithFile(const std::string &path) {

	if (Sprite::initWithFile(path)) {

		this->type = plane_def;
		this->hp = 1;

		return true;
	}

	return false;
}

MyPlane* MyPlane::createPlane(const std::string &path) {

	MyPlane* object = NULL;

	object = new MyPlane();
	object->initWithFile(path);
	object->autorelease();

	return object;
}