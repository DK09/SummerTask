#ifndef __CollisionManager_H__
#define __CollisionManager_H__

#include "cocos2d.h"
#include "MyPlane.h"
#include "Bullet.h"


class CollisionManager 
{

public:

	void ItemCollosion(cocos2d::Node * parent, cocos2d::Node * hero);
	
	void HeroCollosion(cocos2d::Node * parent, cocos2d::Node * cPoint);

	void EnemyCollosion(cocos2d::Node * parent, cocos2d::Node * cPoint);

//	static CollisionManager * getInstance();
//    // there's no 'id' in cpp, so we recommend returning the class instance pointer
//    static cocos2d::Scene * createScene();
//

//
//    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
//    virtual bool init();
//
//	void InitAllParament();
//
//    // implement the "static create()" method manually
//    CREATE_FUNC(CollisionManager);
};

#endif // __CollisionManager_SCENE_H__
