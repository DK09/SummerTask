#include "SelectScene.h"
#include "IndexScene.h"
#include "EquipScene.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MusicControl.h"

USING_NS_CC;

#define planeCount 4
#define ButtonSE "SoundEffect/changeButton.mp3"
#define width 1280
#define height 900

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* SelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectScene::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    selectScene = CSLoader::createNode("IndexScene.csb");

	addChild(selectScene);
	
	//create a keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode key, Event * event){
		if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW) LeftRightChange(1);
		if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) LeftRightChange(-1);
		if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) UpDownChange(2);
		if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) UpDownChange(1);
		if (key == EventKeyboard::KeyCode::KEY_Z || key == EventKeyboard::KeyCode::KEY_ENTER) PressBtn();
		if (key == EventKeyboard::KeyCode::KEY_X || key == EventKeyboard::KeyCode::KEY_ESCAPE) Back();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	InitPlaneV();

    return true;
}


void SelectScene::InitPlaneV() {
	for (int i = 0; i <= planeCount - 1; i++) {
		std::string name = StringUtils::format("PlaneImage/heroplane_%d.png", i);
		auto plane = Sprite::create(name);
		plane->setPosition(Vec2(0.5 * width, 0.7 * height));
		plane->setScale(0.7);
		plane->setAnchorPoint(Vec2(0.5, 0.5));
		if (i != 0) plane->setOpacity(0);
		if (i == 1)	{ 
			plane->setPosition(Vec2(0.75 * width, 0.7 * height));
			plane->setScale(0.5);
			plane->setOpacity(127);
		}
		if (planeCount - i == 1) {
			plane->setPosition(Vec2(0.25 * width, 0.7 * height));
			plane->setScale(0.5);
			plane->setOpacity(127);
		}
		addChild(plane);
		plane_v.pushBack(plane);
	}
	planeIndex = 0;
	isEquipment = false;
}

void SelectScene::LeftRightChange(int change) {
	MusicControl::getInstance()->playSE(ButtonSE);
	if (isEquipment) {
		EquipScene::getInstance()->ChangeEquip(change, btnIndex, btn_v.at(btnIndex));
	}
	else {
		PlaneMove(change, 0.5, 127, plane_v.at(planeIndex));
		PlaneMove(-change, 0.7, 0, plane_v.at((planeIndex + planeCount + change) % planeCount));
		PlaneMove(change, 0.7, 255, plane_v.at((planeIndex + planeCount - change) % planeCount));
		PlaneMove(-change, 0.5, 127, plane_v.at((planeIndex + planeCount - 2 * change) % planeCount));
		planeIndex = (planeIndex + planeCount - change) % planeCount;
	}
}

void SelectScene::PlaneMove(int director,float scale, int alpha, Sprite * plane) {
	auto moveTo = MoveTo::create(0.2, plane->getPosition()+  Vec2(director * 0.25 * width, 0));
	auto alphaTo = FadeTo::create(0.2, alpha);
	auto scaleTo = ScaleTo::create(0.2, scale);
	plane->runAction(moveTo);
	plane->runAction(alphaTo);
	plane->runAction(scaleTo);
}

void SelectScene::UpDownChange(int change) {
	if (isEquipment) {
		MusicControl::getInstance()->playSE(ButtonSE);
		btnIndex = (btnIndex + change) % 3;
		selectArrow->setPosition(btn_v.at(btnIndex)->getPosition());
	}
}

void SelectScene::PressBtn() {
	MusicControl::getInstance()->playSE(ButtonSE);
	UserDefault::getInstance()->setIntegerForKey("planeIndex", planeIndex);
	if (!isEquipment) {
		equipScene = EquipScene::create();
		addChild(equipScene);
		isEquipment = true;
		btnIndex = 0;
		//create the equipment choice and set the animation
		for (int i = 0; i <= 2; i++) {
			auto btn = EquipScene::getInstance()->InitBtn(i);
			addChild(btn);
			auto moveTo = MoveTo::create(0.3, Vec2(0.54 * width, (0.7 - 0.2 * i) * height));
			auto fadeIn = FadeIn::create(0.3);
			btn->runAction(moveTo);
			btn->runAction(fadeIn);
			btn_v.pushBack(btn);
		}

		//th animation of the select arrow when select the plane
		selectArrow = Sprite::create("Equipment/select_arrow.png");
		selectArrow->setPosition(btn_v.at(0)->getPosition());
		auto moveTo = MoveTo::create(0.3, Vec2(0.54 * width, 0.7 * height));
		auto fadeIn = FadeIn::create(0.3);
		selectArrow->runAction(moveTo);
		selectArrow->runAction(fadeIn);
		addChild(selectArrow);

		//the animation of the plane when select the plane
		auto moveTo1 = MoveTo::create(0.3, Vec2(0.23 * width, 0.66 * height));
		auto fadeOut = FadeTo::create(0.3, 0);
		auto fadeOut2 = FadeTo::create(0.3, 0);
		plane_v.at(planeIndex)->runAction(moveTo1);
		plane_v.at((planeIndex + 1) % planeCount)->runAction(fadeOut);
		plane_v.at((planeIndex + planeCount - 1) % planeCount)->runAction(fadeOut2);
	}
	else {
		UserDefault::getInstance()->setIntegerForKey("planeIndex", planeIndex);
		Director::getInstance()->replaceScene(GameScene::createScene());
	}
	
}

void SelectScene::Back() {
	if (isEquipment) {
		isEquipment = false;
		for (int i = 0; i <= 2; i++) btn_v.at(i)->removeFromParentAndCleanup(btn_v.at(i));
		btn_v.clear();
		equipScene->removeFromParentAndCleanup(equipScene);
		selectArrow->removeFromParentAndCleanup(selectArrow);
		//the animation when back to plane select
		auto moveTo = MoveTo::create(0.3, Vec2(0.5 * width, 0.7 * height));
		auto fadeIn = FadeTo::create(0.3, 127);
		auto fadeIn2 = FadeTo::create(0.3, 127);
		plane_v.at(planeIndex)->runAction(moveTo);
		plane_v.at((planeIndex + 1) % planeCount)->runAction(fadeIn2);
		plane_v.at((planeIndex + planeCount - 1) % planeCount)->runAction(fadeIn);
	}
	else {
		Director::getInstance()->replaceScene(IndexScene::createScene());
	}
	MusicControl::getInstance()->playSE(ButtonSE);
}
