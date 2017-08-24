#ifndef __EquipScene_H__
#define __EquipScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class EquipScene : public cocos2d::Layer
{
	

public:
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	static EquipScene * getInstance();

	cocos2d::Sprite * InitBtn(int index);

	void ChangeEquip(int change, int index, cocos2d::Sprite * equip);

	std::string GetName(int index);

	std::string GetName(int index, int change);

    // implement the "static create()" method manually
    CREATE_FUNC(EquipScene);
};

#endif // __EquipScene_SCENE_H__
