#ifndef __SelectScene_H__
#define __SelectScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "EquipScene.h"

class SelectScene : public cocos2d::Layer
{
	Node * selectScene, * equipScene;

	int planeIndex, btnIndex;

	bool isEquipment;

	cocos2d::Vector<cocos2d::Sprite *> plane_v;

	cocos2d::Vector<cocos2d::Sprite *> btn_v;

	cocos2d::Sprite * selectArrow;

public:
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//initialize the plane list
	void InitPlaneV();

	//the action when press Z & ENTER
	void PressBtn();

	//the action when press X & ESC
	void Back();
	
	//press UP & DOWN_ARROW
	void UpDownChange(int change);

	//press LEFT & RIGHT_ARROW
	void LeftRightChange(int change);

	//the animation of plane when change plane
	void PlaneMove(int director, float scale, int alpha, cocos2d::Sprite * plane);
	//director->  -1 : left, 1 : right
    //scale -> the scale change to
	//alpha -> politics

    // implement the "static create()" method manually
    CREATE_FUNC(SelectScene);
};

#endif // __SelectScene_SCENE_H__
