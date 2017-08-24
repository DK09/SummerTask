#include "MapScene.h"
#include "IndexScene.h"
#include "SelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MusicControl.h"

USING_NS_CC;

#define ButtonSE "SoundEffect/changeButton.mp3"

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* MapScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MapScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapScene::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto mapScene = CSLoader::createNode("MapScene.csb");

	addChild(mapScene);

	//create a keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode key, Event * event){
		if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) ;
		if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW);
		if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW);
		if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
		if (key == EventKeyboard::KeyCode::KEY_Z || key == EventKeyboard::KeyCode::KEY_ENTER) PressBtn();
		if (key == EventKeyboard::KeyCode::KEY_X || key == EventKeyboard::KeyCode::KEY_ESCAPE) Back();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void MapScene::PressBtn() {
	MusicControl::getInstance()->playSE(ButtonSE);
}

void MapScene::Back() {
	MusicControl::getInstance()->playSE(ButtonSE);
	Director::getInstance()->replaceScene(IndexScene::createScene());
}