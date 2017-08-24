#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"

typedef enum BulletType{

	///默认
	bullet_def = 0,
	///主机子弹
	bullet_main = 1,
	///敌机子弹
	bullet_enemy = 2,
	///主机激光
	bullet_main_laser = 3,
	///敌机激光
	bullet_enemy_laser = 4

}Bullet_Type;

class Bullet : public cocos2d::Sprite
{
public:	
	Bullet_Type type;
	float damage;
public:

	bool initWithFile(const std::string& path);

	static Bullet* createBullet(const std::string& path);

    // implement the "static create()" method manually
    CREATE_FUNC(Bullet);
};

#endif // __Bullet_SCENE_H__
