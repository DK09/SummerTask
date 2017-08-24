#ifndef __MapScene_H__
#define __MapScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MapScene : public cocos2d::Layer
{
	
	

public:
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void PressBtn();

	void Back();

    // implement the "static create()" method manually
    CREATE_FUNC(MapScene);
};

#endif // __MapScene_SCENE_H__
