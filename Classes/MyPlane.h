#ifndef __MyPlane_H__
#define __MyPlane_H__

#include "cocos2d.h"

typedef enum PlaneType{

	///默认
	plane_def = 0,
	///主机
	plane_main = 1,
	///敌机
	plane_enemy = 2,
	///敌机Boss
	plane_boss = 3
}Plane_Type;

class MyPlane : public cocos2d::Sprite
{
public:	
	Plane_Type type;
	float hp;
public:

	bool initWithFile(const std::string& path);

	static MyPlane* createPlane(const std::string& path);

    // implement the "static create()" method manually
    CREATE_FUNC(MyPlane);
};

#endif // __Plane_SCENE_H__
