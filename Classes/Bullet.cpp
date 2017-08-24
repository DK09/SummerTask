#include "Bullet.h"

bool Bullet::initWithFile(const std::string &path) {

	if (Sprite::initWithFile(path)) {

		this->type = bullet_def;
		this->damage = 0;

		return true;
	}

	return false;
}

Bullet* Bullet::createBullet(const std::string &path) {

	Bullet* object = NULL;

	object = new Bullet();
	object->initWithFile(path);
	object->autorelease();

	return object;
}