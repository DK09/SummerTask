#include "GameScene.h"
#include "GamePauseLayer.h"
#include "HeroControl.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MusicControl.h"

USING_NS_CC;

#define width 425
#define height 425

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* GamePauseLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePauseLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
//bool GamePauseLayer::initWithColor(RGB(255, 255, 255, 255))
//{   
//    //////////////////////////////
//    // 1. super init first
//	if (!Layer::WithColor(ccc4(255, 255, 255, 255))
//    {
//        return false;
//    }
//    
//	auto gamePauseLayer = CSLoader::createNodeWithVisibleSize("GamePauseLayer.csb");
//	addChild(gamePauseLayer);
//
//	InitAllParament();
//
//    return true;
//}


void GamePauseLayer::InitAllParament() {
}