#ifndef __PlaneLayer_H__
#define __PlaneLayer_H__

#include "cocos2d.h"
#include "MyPlane.h"
#include "Bullet.h"

class PlaneLayer : public cocos2d::Layer
{
	static PlaneLayer * _PlaneLayer;

	MyPlane * cPoint;

public:

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	static PlaneLayer * getInstance();

	void HeroCollision(float dt);

	void EnemyCollision(float dt);

	void ClearBullet();

	void ClearBullet(float time);

	void ClearBullet(Bullet * bullet);

	void DeleteBullet(Ref * object);

	void UnderAttack();

	void HeroMiss();

	void EnemyInjure(MyPlane * enemy, float damage);

    // implement the "static create()" method manually
    CREATE_FUNC(PlaneLayer);
};

#endif // __PlaneLayer_SCENE_H__
