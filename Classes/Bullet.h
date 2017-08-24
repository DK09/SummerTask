#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"

typedef enum BulletType{

	///Ĭ��
	bullet_def = 0,
	///�����ӵ�
	bullet_main = 1,
	///�л��ӵ�
	bullet_enemy = 2,
	///��������
	bullet_main_laser = 3,
	///�л�����
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
