#include "EquipScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

#define frontCount 4   //the number of front equipment + 1
#define coreCount 3    //the number of core equipment + 1
#define hindCount 1	  //the number of hind equipment + 1
#define width 1280
#define height 900


using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* EquipScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EquipScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EquipScene::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto equipScene = CSLoader::createNode("EquipScene.csb");

	addChild(equipScene);

    return true;
}

EquipScene * EquipScene::getInstance() {
	static EquipScene _EquipScene;
	return &_EquipScene;
}

Sprite * EquipScene::InitBtn(int index) {
	auto btn = Sprite::create(EquipScene::GetName(index));
	btn->setAnchorPoint(Vec2(0.125, 0.703));
	btn->setPosition(Vec2(0.9 * width, (0.7 - 0.2 * index) * height));
	return btn;
}

void EquipScene::ChangeEquip(int change, int index, cocos2d::Sprite * equip) {
	equip->setTexture(EquipScene::GetName(index, change));
}

std::string EquipScene::GetName(int index) {
	std::string name;
	switch (index) {
	case 0:
		name = StringUtils::format("Equipment/front_equip_%d.png", UserDefault::getInstance()->getIntegerForKey("frontEquip", 0));
		break;
	case 1:
		name = StringUtils::format("Equipment/core_equip_%d.png", UserDefault::getInstance()->getIntegerForKey("coreEquip", 0));
		break;
	case 2:
		name = StringUtils::format("Equipment/hind_equip_%d.png", UserDefault::getInstance()->getIntegerForKey("hindEquip", 0));
	default:
		break;
	}
	return name;
}

std::string EquipScene::GetName(int index, int change) {
	std::string name;
	int equipIndex;
	switch (index) {
	case 0:
		equipIndex = (UserDefault::getInstance()->getIntegerForKey("frontEquip") - change + frontCount) % frontCount;
		UserDefault::getInstance()->setIntegerForKey("frontEquip", equipIndex);
		name = StringUtils::format("Equipment/front_equip_%d.png", equipIndex);
		break;
	case 1:
		equipIndex = (UserDefault::getInstance()->getIntegerForKey("coreEquip") - change + coreCount) % coreCount;
		UserDefault::getInstance()->setIntegerForKey("coreEquip", equipIndex);
		name = StringUtils::format("Equipment/core_equip_%d.png", equipIndex);
		break;
	case 2:
		equipIndex = (UserDefault::getInstance()->getIntegerForKey("hindEquip") - change + hindCount) % hindCount;
		UserDefault::getInstance()->setIntegerForKey("hindEquip", equipIndex);
		name = StringUtils::format("Equipment/hind_equip_%d.png", equipIndex);
	default:
		break;
	}
	return name;
}