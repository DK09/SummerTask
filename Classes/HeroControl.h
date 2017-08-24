#ifndef __HeroControl_H__
#define __HeroControl_H__

#include "cocos2d.h"
#include "MyPlane.h"
#include "Item.h"

class HeroControl : public cocos2d::Layer
{	
	static HeroControl * _HeroControl;
	
	bool isShoot, canMove;
	float speed;
	float maxSpeed, lowSpeed;
	float planeWidth, planeHeight;

	cocos2d::Vec2 director;
public:
    MyPlane * hero, * cPoint;
	

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	static HeroControl * getInstance();

	void InitAllParament();

	void MoveDirector(cocos2d::EventKeyboard::KeyCode key, int pr);
	void HeroMove(cocos2d::Vec2 director);
	void Shoot();

	void MoveUpdate(float detal);

	void BulletUpdate(float detal);

	void BulletShoot(cocos2d::Vec2 pos, float x);

	void DeleteBullet(cocos2d::Ref * pSender);

	//make the hero invincible
	void Invincible(float time);

	void UnInvincible(float dt);

	void HeroMiss();

    // implement the "static create()" method manually
    CREATE_FUNC(HeroControl);
};

#endif // __HeroControl_SCENE_H__
